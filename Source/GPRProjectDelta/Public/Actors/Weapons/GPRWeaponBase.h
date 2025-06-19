// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPRWeaponBase.generated.h"

class AGPRPlayerCharacter;
class UGPRWeaponStatsDataAssetBase;
class AGPRWeaponPickupBase;

UCLASS(Abstract)
class GPRPROJECTDELTA_API AGPRWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGPRWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> WeaponBodyStaticMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> WeaponMagStaticMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> WeaponMuzzleComponent;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AGPRWeaponPickupBase> WeaponPickupClassToDrop;
	
	UPROPERTY(EditDefaultsOnly)
	int32 CurrentMagAmmo;

	UPROPERTY(EditDefaultsOnly)
	int32 CurrentReserveAmmo;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UGPRWeaponStatsDataAssetBase> WeaponData;

	UPROPERTY()
	TObjectPtr<AGPRPlayerCharacter> OwningPlayerCharRef;
	
	// A weapon must always have some sort of fire logic implemented
	virtual void FireWeapon();

	void FireWeaponSemi();
	void FireWeaponBurst();
	void FireWeaponAuto();

	void StopFireWeapon();

	UFUNCTION()
	void SetupPlayerReference();

	// Not all weapons will have a reload option. Example, energy weapons which overheat or melee weapons
	UFUNCTION()
	virtual void ReloadWeapon();

	// Used to check if the weapon can be reloaded using the reserve ammo
	UFUNCTION()
	virtual bool CanReloadWeapon();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
