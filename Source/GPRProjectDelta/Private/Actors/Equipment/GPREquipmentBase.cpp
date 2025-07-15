// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Equipment/GPREquipmentBase.h"
#include "DataAssets/GPREquipmentDataAssetBase.h"

// Sets default values
AGPREquipmentBase::AGPREquipmentBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EquipmentStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentStaticMesh"));
	EquipmentStaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGPREquipmentBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGPREquipmentBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Checks if the equipment data asset is valid
	if (IsValid(EquipmentData))
	{
		// Checks if there is a valid static mesh in the data asset
		if (!EquipmentData->EquipmentStaticMesh.IsNull())
		{
			// Sets this equipment static mesh to be it's data asset static mesh
			EquipmentStaticMesh->SetStaticMesh(EquipmentData->EquipmentStaticMesh.LoadSynchronous());
		}
	}
}

void AGPREquipmentBase::UseEquipment(AGPRPlayerCharacter* UsingPlayerCharacter)
{
	// Base implementation. Meant to be overridden by child classes like the potion class.
}

// Called every frame
void AGPREquipmentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

