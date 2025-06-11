// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ActorComponents/GPRInventoryComponentBase.h"
#include "Actors/Weapons/GPRWeaponBase.h"
#include "Actors/Equipment/GPREquipmentBase.h"


// Sets default values for this component's properties
UGPRInventoryComponentBase::UGPRInventoryComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGPRInventoryComponentBase::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGPRInventoryComponentBase::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UGPRInventoryComponentBase::CanAddWeaponToInventory()
{
	// Loop through each element of the weapons inventory array and check if it is valid.
	for (AGPRWeaponBase* Weapon : WeaponInventoryArray)
	{
		if (!IsValid(Weapon))
		{
			// Returns true if there is an available slot in the inventory.
			return true;
		}
	}

	return false;
}

bool UGPRInventoryComponentBase::CanAddEquipmentToInventory()
{
	
}

bool UGPRInventoryComponentBase::CanAddResourceToInventory()
{
	
}

