// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GPREquipmentDataAssetBase.generated.h"

UCLASS()
class GPRPROJECTDELTA_API UGPREquipmentDataAssetBase : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FName EquipmentName;

	UPROPERTY(EditDefaultsOnly)
	FText EquipmentDescription;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UTexture2D> EquipmentIcon;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UStaticMesh> EquipmentStaticMesh;
};