#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CollectionDataAsset.generated.h"

class UTexture2D;

UCLASS(BlueprintType, Blueprintable)
class UN_ULTIMO_PASO_API UCollectionDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:

    UCollectionDataAsset();

    // Identificador único de la colección
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collection")
    FName CollectionID;

    // Nombre de la colección
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collection")
    FText CollectionName;

    // Descripción
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collection", meta = (MultiLine = "true"))
    FText Description;

    // Imagen completa
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collection")
    TObjectPtr<UTexture2D> CompleteImage;

    // Piezas de la imagen
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collection")
    TArray<TObjectPtr<UTexture2D>> PieceImages;
};