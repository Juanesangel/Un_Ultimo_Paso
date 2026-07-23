#include "Pieza_coleccionable.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/NameTypes.h"
#include "Un_Ultimo_Paso/Protagonista/Protagonista.h"
#include "Logica_coleccion_component.h"

APieza_coleccionable::APieza_coleccionable()
{
	PrimaryActorTick.bCanEverTick = false;

	// Sphere Collision
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Collision->SetSphereRadius(70.f);

	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);

	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Collision->SetGenerateOverlapEvents(true);

	// Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APieza_coleccionable::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(
		this,
		&APieza_coleccionable::OnSphereOverlap);
}

void APieza_coleccionable::OnSphereOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (bCollected)
	{
		return;
	}

	AProtagonista* Protagonista = Cast<AProtagonista>(OtherActor);

	if (!Protagonista)
	{
		return;
	}

	bCollected = true;

	if (ULogica_coleccion_component* CollectionComponent =
		Protagonista->GetCollectionComponent())
	{
		CollectionComponent->CollectPiece(
			CollectionID,
			PieceIndex,
			TotalPieces);
	}

	Destroy();
}