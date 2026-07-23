#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollectionStruct.h"
#include "Logica_coleccion_component.generated.h"

// Evento cuando se recoge una pieza
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(
    FOnPieceCollected,
    FName, CollectionID,
    int32, PieceIndex,
    int32, CollectedPieces,
    int32, TotalPieces
);

// Evento cuando una colección se completa
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnCollectionCompleted,
	FName,
	CollectionID);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UN_ULTIMO_PASO_API ULogica_coleccion_component : public UActorComponent
{
	GENERATED_BODY()

public:

	ULogica_coleccion_component();

protected:

	virtual void BeginPlay() override;

	// Todas las colecciones del juego
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Colecciones")
	TMap<FName, FCollectionData> Collections;

public:

	// Recoger una pieza
	UFUNCTION(BlueprintCallable)
	void CollectPiece(FName CollectionID, int32 PieceIndex, int32 TotalPieces);

	// Saber si una colección está completa
	UFUNCTION(BlueprintCallable)
	bool IsCollectionCompleted(FName CollectionID) const;

	// Saber cuántas piezas tiene recogidas
	UFUNCTION(BlueprintCallable)
	int32 GetCollectedPieces(FName CollectionID) const;

	// Obtener el total de piezas
	UFUNCTION(BlueprintCallable)
	int32 GetTotalPieces(FName CollectionID) const;

    // Obtener el array completo de piezas recogidas (para inicializar la UI)
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Colecciones")
    TArray<bool> GetCollectedPiecesArray(FName CollectionID) const;

public:

	UPROPERTY(BlueprintAssignable)
	FOnPieceCollected OnPieceCollected;

	UPROPERTY(BlueprintAssignable)
	FOnCollectionCompleted OnCollectionCompleted;
};