// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPRWeaponBase.generated.h"

class AGPRPrimaryPlayerControllerBase;
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
	
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> WeaponBodyStaticMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> WeaponMagStaticMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> WeaponMuzzleComponent;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AGPRWeaponPickupBase> WeaponPickupClassToDrop;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 CurrentMagAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 CurrentReserveAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UGPRWeaponStatsDataAssetBase> WeaponData;

	// References to the owning players character and controller
	UPROPERTY() TObjectPtr<AGPRPlayerCharacter> OwningPlayerCharRef;
	UPROPERTY() TObjectPtr<AGPRPrimaryPlayerControllerBase> OwningPlayerControllerRef;
	
	FTimerHandle WeaponFireTimerHandle;

	// Keeps track of if the player's currently active weapon is being fired
	bool bIsFiring = false;
	
	// A weapon must always have some sort of fire logic implemented
	virtual void FireWeapon();

	// Used for firing the weapon
	void FireWeaponSemi();
	void FireWeaponBurst();
	void FireWeaponAuto();

	// Stops the weapon from firing only when using burst or auto
	void StopFireWeapon();

	// Not all weapons will have a reload option. Example, energy weapons which overheat or melee weapons
	UFUNCTION()
	virtual void ReloadWeapon();

	// Used to check if the weapon can be reloaded using the reserve ammo
	UFUNCTION()
	virtual bool CanReloadWeapon();
};
