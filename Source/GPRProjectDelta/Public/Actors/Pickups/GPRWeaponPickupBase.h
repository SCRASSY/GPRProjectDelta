// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPRPickupBase.h"
#include "GPRWeaponPickupBase.generated.h"

class AGPRWeaponBase;

UCLASS()
class GPRPROJECTDELTA_API AGPRWeaponPickupBase : public AGPRPickupBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGPRWeaponPickupBase();

	// The weapon class to spawn when the player picks this up.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftClassPtr<AGPRWeaponBase> WeaponClassToSpawn;
	
	virtual void Interact(AActor* InstigatedActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
