// Fill out your copyright notice in the Description page of Project Settings.


#include "Logica_coleccion_component.h"


// Sets default values
ULogica_coleccion_component::ULogica_coleccion_component()
{
 	// Set this component to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;


}

// Called when the game starts or when spawned
void ULogica_coleccion_component::BeginPlay()
{
	Super::BeginPlay();
	
}

void ULogica_coleccion_component::CollectPiece(
	FName CollectionID,
	int32 PieceIndex,
	int32 TotalPieces)
{
	// Si la colección no existe, la creamos
	if (!Collections.Contains(CollectionID))
	{
		FCollectionData NewCollection;

		NewCollection.TotalPieces = TotalPieces;

		NewCollection.CollectedPieces.Init(false, TotalPieces);

		Collections.Add(CollectionID, NewCollection);
	}

	FCollectionData& Collection = Collections[CollectionID];

	// Verificar que el índice sea válido
	if (!Collection.CollectedPieces.IsValidIndex(PieceIndex))
	{
		return;
	}

	// Si ya estaba recogida, no hacer nada
	if (Collection.CollectedPieces[PieceIndex])
	{
		return;
	}

	// Marcar como recogida
	Collection.CollectedPieces[PieceIndex] = true;


    int32 CollectedCount = 0;

    for (bool bCollected : Collection.CollectedPieces)
    {
        if (bCollected)
        {
            CollectedCount++;
        }
    }
	// Avisar a la UI
    OnPieceCollected.Broadcast(
        CollectionID,
        PieceIndex,
        CollectedCount,
        Collection.TotalPieces
    );

	// ¿Está completa?
	bool bComplete = true;

	for (bool bPiece : Collection.CollectedPieces)
	{
		if (!bPiece)
		{
			bComplete = false;
			break;
		}
	}

	if (bComplete)
	{
		Collection.bCompleted = true;

		OnCollectionCompleted.Broadcast(CollectionID);
	}
}

bool ULogica_coleccion_component::IsCollectionCompleted(FName CollectionID) const
{
	const FCollectionData* Collection = Collections.Find(CollectionID);

	if (!Collection)
	{
		return false;
	}

	return Collection->bCompleted;
}

int32 ULogica_coleccion_component::GetCollectedPieces(FName CollectionID) const
{
	const FCollectionData* Collection = Collections.Find(CollectionID);

	if (!Collection)
	{
		return 0;
	}

	int32 Count = 0;

	for (bool bCollected : Collection->CollectedPieces)
	{
		if (bCollected)
		{
			Count++;
		}
	}

	return Count;
}

int32 ULogica_coleccion_component::GetTotalPieces(FName CollectionID) const
{
	const FCollectionData* Collection = Collections.Find(CollectionID);

	if (!Collection)
	{
		return 0;
	}

	return Collection->TotalPieces;
}

TArray<bool> ULogica_coleccion_component::GetCollectedPiecesArray(FName CollectionID) const
{
    const FCollectionData* Collection = Collections.Find(CollectionID);
    if (!Collection)
    {
        return TArray<bool>();
    }
    return Collection->CollectedPieces;
}