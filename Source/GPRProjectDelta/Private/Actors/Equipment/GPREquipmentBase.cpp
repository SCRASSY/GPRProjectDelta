// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Equipment/GPREquipmentBase.h"


// Sets default values
AGPREquipmentBase::AGPREquipmentBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGPREquipmentBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGPREquipmentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

