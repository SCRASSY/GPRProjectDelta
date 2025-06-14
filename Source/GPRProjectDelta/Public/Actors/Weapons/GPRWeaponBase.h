// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPRWeaponBase.generated.h"

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

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> WeaponBodyStaticMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> WeaponMagStaticMesh;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AGPRWeaponPickupBase> WeaponPickupClassToDrop;

protected:
	// A weapon must always have some sort of fire logic implemented
	UFUNCTION()
	virtual void FireWeapon() PURE_VIRTUAL(&AGPRWeaponBase::FireWeapon);

	// Not all weapons will have a reload option. Example, energy weapons which overheat or melee weapons
	UFUNCTION()
	virtual void ReloadWeapon();

	// Used to check if the weapon can be reloaded using the reserve ammo
	UFUNCTION()
	virtual bool CanReloadWeapon();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
