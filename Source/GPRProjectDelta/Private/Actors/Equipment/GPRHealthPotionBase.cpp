// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Equipment/GPRHealthPotionBase.h"
#include "Actors/Characters/GPRPlayerCharacter.h"
#include "DataAssets/GPRHealingPotionDataAssetBase.h"

// Sets default values
AGPRHealthPotionBase::AGPRHealthPotionBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGPRHealthPotionBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGPRHealthPotionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGPRHealthPotionBase::UseEquipment(AGPRPlayerCharacter* UsingPlayerCharacter)
{
	// If the equipment data is not valid, this function will be terminated early
	if (!EquipmentData) return;

	if (UGPRHealingPotionDataAssetBase* PotionData = Cast<UGPRHealingPotionDataAssetBase>(EquipmentData))
	{
		// Applies health to the player character
		// NEED TO APPLY HEALTH TO CHARACTER

		// 3. Destroy the potion actor
		this->Destroy();
	}
}

