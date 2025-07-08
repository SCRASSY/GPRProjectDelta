// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPREquipmentDataAssetBase.h"
#include "GPRHealingPotionDataAssetBase.generated.h"

UCLASS()
class GPRPROJECTDELTA_API UGPRHealingPotionDataAssetBase : public UGPREquipmentDataAssetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 HealingAmount;
};