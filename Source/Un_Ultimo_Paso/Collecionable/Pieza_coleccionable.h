#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pieza_coleccionable.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class UN_ULTIMO_PASO_API APieza_coleccionable : public AActor
{
	GENERATED_BODY()

public:

	APieza_coleccionable();

protected:

	virtual void BeginPlay() override;

	// Malla del objeto
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collectible")
	TObjectPtr<UStaticMeshComponent> Mesh;

	// Colisión para recoger el objeto
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collectible")
	TObjectPtr<USphereComponent> Collision;

	// Nombre de la colección
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectible")
	FName CollectionID;

	// Índice de esta pieza
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectible")
	int32 PieceIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectible")
	int32 TotalPieces = 0;

	// Evita recoger dos veces
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collectible")
	bool bCollected = false;

	UFUNCTION()
	void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:

	FORCEINLINE FName GetCollectionID() const
	{
		return CollectionID;
	}

	FORCEINLINE int32 GetPieceIndex() const
	{
		return PieceIndex;
	}

	FORCEINLINE int32 GetTotalPieces() const
	{
		return TotalPieces;
	}
};