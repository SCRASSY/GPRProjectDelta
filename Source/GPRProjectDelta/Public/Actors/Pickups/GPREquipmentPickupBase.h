// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPRPickupBase.h"
#include "GPREquipmentPickupBase.generated.h"

class AGPREquipmentBase;
class AGPRPlayerCharacter;

UCLASS()
class GPRPROJECTDELTA_API AGPREquipmentPickupBase : public AGPRPickupBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGPREquipmentPickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* InstigatedActor) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AGPREquipmentBase> EquipmentClassToSpawn;
};
