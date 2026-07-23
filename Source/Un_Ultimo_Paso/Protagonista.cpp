#include "Protagonista.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Logica_coleccion_component.h"

// Sets default values
AProtagonista::AProtagonista()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// --- Cámara ---
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	// --- Push detector ---
	PushDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("PushDetector"));
	PushDetector->SetupAttachment(RootComponent);
	PushDetector->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	PushDetector->SetRelativeLocation(FVector(60.f, 0.f, 0.f));
	PushDetector->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PushDetector->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	// --- Sistema de colisiones---
	CollectionComponent = CreateDefaultSubobject<ULogica_coleccion_component>(TEXT("CollectionComponent"));
}

// Called when the game starts or when spawned
void AProtagonista::BeginPlay()
{
	Super::BeginPlay();

	PushDetector->OnComponentBeginOverlap.AddDynamic(this, &AProtagonista::OnPushDetectorBeginOverlap);
	PushDetector->OnComponentEndOverlap.AddDynamic(this, &AProtagonista::OnPushDetectorEndOverlap);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

// Called every frame
void AProtagonista::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsPushing && CurrentPushable)
	{
		const FVector PushDirection = GetActorForwardVector();
		CurrentPushable->AddForce(PushDirection * PushForce, NAME_None, true);
	}
}

// Called to bind functionality to input
void AProtagonista::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Move)
		{
			EnhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AProtagonista::OnMove);
		}

		if (IA_Jump)
		{
			EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
			EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}

		if (IA_Empujar)
		{
			EnhancedInput->BindAction(IA_Empujar, ETriggerEvent::Started, this, &AProtagonista::OnEmpujarStarted);
			EnhancedInput->BindAction(IA_Empujar, ETriggerEvent::Completed, this, &AProtagonista::OnEmpujarCompleted);
			EnhancedInput->BindAction(IA_Empujar, ETriggerEvent::Canceled, this, &AProtagonista::OnEmpujarCompleted);
		}
	}
}

void AProtagonista::OnMove(const FInputActionValue& Value)
{
	const FVector2D MoveInput = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator ControlRotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDir, MoveInput.Y);
		AddMovementInput(RightDir, MoveInput.X);
	}
}

void AProtagonista::OnEmpujarStarted(const FInputActionValue& Value)
{
	bIsPushing = true;
}

void AProtagonista::OnEmpujarCompleted(const FInputActionValue& Value)
{
	bIsPushing = false;
}

void AProtagonista::OnPushDetectorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		CurrentPushable = OtherComp;
	}
}

void AProtagonista::OnPushDetectorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp == CurrentPushable)
	{
		CurrentPushable = nullptr;
	}
}