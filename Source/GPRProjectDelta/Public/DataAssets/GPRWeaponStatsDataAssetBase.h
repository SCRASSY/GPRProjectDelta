// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GPRWeaponStatsDataAssetBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponFireType : uint8
{
	EWF_Semi UMETA(DisplayName = "Semi"),
	EWF_Burst UMETA(DisplayName = "Burst"),
	EWF_Auto UMETA(DisplayName = "Auto"),
	EWF_MAX UMETA(Hidden)
};

UCLASS(BlueprintType)
class GPRPROJECTDELTA_API UGPRWeaponStatsDataAssetBase : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FName WeaponName;
	
	UPROPERTY(EditDefaultsOnly)
	FText WeaponDescription;
	
	UPROPERTY(EditDefaultsOnly)
	int32 WeaponMagSize;
	
	UPROPERTY(EditDefaultsOnly)
	int32 WeaponReserveAmmoSize;
	
	UPROPERTY(EditDefaultsOnly)
	float WeaponDamage;
	
	UPROPERTY(EditDefaultsOnly)
	float WeaponFireRate;

	UPROPERTY(EditDefaultsOnly)
	float WeaponFireRange;

	UPROPERTY(EditDefaultsOnly)
	EWeaponFireType WeaponFireType;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UStaticMesh> WeaponBodyMesh;
};
