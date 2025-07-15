// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GPREquipmentBase.h"
#include "GPRHealthPotionBase.generated.h"

UCLASS()
class GPRPROJECTDELTA_API AGPRHealthPotionBase : public AGPREquipmentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGPRHealthPotionBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// -- Properties --
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay Tags")
	FGameplayTag HealthPotionTag;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UseEquipment(AGPRPlayerCharacter* UsingPlayerCharacter) override;
};
