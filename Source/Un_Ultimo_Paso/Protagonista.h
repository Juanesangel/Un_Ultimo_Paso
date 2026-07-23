// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Protagonista.generated.h"

class UBoxComponent;
class UInputAction;
class UInputMappingContext;
class UPrimitiveComponent;
class USpringArmComponent;
class UCameraComponent;
class ULogica_coleccion_component;


UCLASS()
class UN_ULTIMO_PASO_API AProtagonista : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProtagonista();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE ULogica_coleccion_component* GetCollectionComponent() const { return CollectionComponent; }


protected:
	// --- Cámara ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;

	// --- Enhanced Input ---
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Push")
	TObjectPtr<UInputAction> IA_Empujar;

	// --- Mecánica de empuje ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Push")
	TObjectPtr<UBoxComponent> PushDetector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Push")
	float PushForce = 800.f;

	UPROPERTY(BlueprintReadOnly, Category = "Push")
	TObjectPtr<UPrimitiveComponent> CurrentPushable;

	UPROPERTY(BlueprintReadOnly, Category = "Push")
	bool bIsPushing = false;

	// --- Mecanica recolectar objetos ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collection")
	TObjectPtr<ULogica_coleccion_component> CollectionComponent;

	// --- Handlers de movimiento ---
	void OnMove(const FInputActionValue& Value);

	// --- Handlers de empuje ---
	void OnEmpujarStarted(const FInputActionValue& Value);
	void OnEmpujarCompleted(const FInputActionValue& Value);

	UFUNCTION()
	void OnPushDetectorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPushDetectorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};