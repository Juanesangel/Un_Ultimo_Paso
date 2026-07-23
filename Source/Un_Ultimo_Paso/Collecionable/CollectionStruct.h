#pragma once
#include "CoreMinimal.h"
#include "CollectionStruct.generated.h"

USTRUCT(BlueprintType)
struct FCollectionData
{
    GENERATED_BODY()

    // Número total de piezas de esta colección
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalPieces = 0;

    // Piezas recogidas
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<bool> CollectedPieces;

    // ¿Está completada?
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCompleted = false;
};