// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/GPREquipmentPickupBase.h"


// Sets default values
AGPREquipmentPickupBase::AGPREquipmentPickupBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGPREquipmentPickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGPREquipmentPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

