// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ActorComponents/GPRInventoryComponentBase.h"
#include "Actors/Characters/GPRPlayerCharacter.h"
#include "Actors/Weapons/GPRWeaponBase.h"
#include "Actors/Pickups/GPRWeaponPickupBase.h"


// Sets default values for this component's properties
UGPRInventoryComponentBase::UGPRInventoryComponentBase()
{
	// Set this component to be initialized when the game starts and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Sets the size of the inventory for weapons, equipment & resources
	SetInventoryArraySize();
}


// Called when the game starts
void UGPRInventoryComponentBase::BeginPlay()
{
	Super::BeginPlay();

	// Sets up a reference to the character that owns this inventory component.
	SetupCharacterReference();
}


// Called every frame
void UGPRInventoryComponentBase::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGPRInventoryComponentBase::AddWeaponToInventory(AGPRWeaponBase* NewWeapon)
{
	/* Declares 2 variables to determine if there is an available slot in the inventory &
	 * if there is an available slot, the index of the available slot.*/
	bool bLocalCanAddItem = false;
	int32 LocalAvailableSlotIndex = 0;

	// Checks the weapon inventory array to see if there is an available slot.
	CanAddWeaponToInventory(bLocalCanAddItem, LocalAvailableSlotIndex);

	// If there is an available weapon slot, the interacted weapon is added to the weapon inventory.
	if (bLocalCanAddItem)
	{
		// Adds the weapon to the player's weapon inventory
		WeaponInventoryArray[LocalAvailableSlotIndex] = NewWeapon;

		// Sets the active weapon index to the slot the picked-up weapon was added to 
		ActiveWeaponSlotIndex = LocalAvailableSlotIndex;

		// Calls the player character to attach this newly added weapon to itself.
		PlayerCharRef->AttachAddedWeaponToCharacter(NewWeapon);
	}
	else // If there is no available slot, then the player's currently held weapon will be swapped
	{
		// Declares an object ptr to the weapon slot that will be removed
		TObjectPtr<AGPRWeaponBase> LocalWeaponToRemove = WeaponInventoryArray[ActiveWeaponSlotIndex];

		// Drops the player's currently active weapon
		DropWeapon(LocalWeaponToRemove);

		// The player's currently active weapon slot will now be the new picked-up weapon
		WeaponInventoryArray[ActiveWeaponSlotIndex] = NewWeapon;
		
		// Calls the player character to attach this newly added weapon to itself.
		PlayerCharRef->AttachAddedWeaponToCharacter(NewWeapon);
	}
}

void UGPRInventoryComponentBase::AddEquipmentToInventory(AGPREquipmentBase* NewEquipment)
{
	
}

void UGPRInventoryComponentBase::AddResourceToInventory(const FGPRResourceDataBase& NewResource)
{
	
}

void UGPRInventoryComponentBase::CanAddWeaponToInventory(bool& bCanAddItem, int32& AvailableSlotIndex)
{
	// Loop through each element of the weapons inventory array
	for (int i = 0; i < WeaponInventoryArray.Max(); ++i)
	{
		// Checks if the current element is empty.
		if (!IsValid(WeaponInventoryArray[i]))
		{
			// Returns true if there is an available slot in the inventory & gives the index of the available slot.
			bCanAddItem = true;
			AvailableSlotIndex = i;
			return;
		}
	}

	// If there is no available slot, returns false.
	bCanAddItem = false;
}

void UGPRInventoryComponentBase::CanAddEquipmentToInventory(bool& bCanAddItem, int32& AvailableSlotIndex)
{
	
}

void UGPRInventoryComponentBase::CanAddResourceToInventory(bool& bCanAddItem, int32& AvailableSlotIndex)
{
	
}

void UGPRInventoryComponentBase::DropWeapon(AGPRWeaponBase* WeaponToRemove)
{
	// Loads the weapons pickup class to drop soft class ptr & stores the value in a subclass ptr
	TSubclassOf<AGPRWeaponPickupBase> LocalWeaponPickupClassToDrop = WeaponToRemove->WeaponPickupClassToDrop.LoadSynchronous();

	// Declares & sets spawn params
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	/* Gets & stores a modified version of the player location which adds 50f to the player's forward vector
	 * This makes the weapon drop in front of the player */
	const FVector LocalSpawnLocation = PlayerCharRef->GetActorLocation() + PlayerCharRef->GetActorForwardVector() * 50.0f;
	
	// Spawns the pickup version of the removed weapon (player has swapped their weapon)
	GetWorld()->SpawnActor<AGPRWeaponPickupBase>(LocalWeaponPickupClassToDrop, LocalSpawnLocation, FRotator::ZeroRotator, SpawnParams);

	WeaponToRemove->Destroy(); // After dropping the weapon in the world, the weapon the player was holding will be destroyed
	WeaponInventoryArray[ActiveWeaponSlotIndex] = nullptr; // Free's up space in the slot the weapon was using
}

void UGPRInventoryComponentBase::SetupCharacterReference()
{
	// In case this inventory component already has a reference to the owning player character.
	if (IsValid(PlayerCharRef)) return;

	// Gets the inventory actor components owning actor & casts it to the player character.
	if (TObjectPtr<AGPRPlayerCharacter> LocalPlayerCharRef = Cast<AGPRPlayerCharacter>(GetOwner()))
	{
		PlayerCharRef = LocalPlayerCharRef;
	}
}

void UGPRInventoryComponentBase::SetInventoryArraySize()
{
	WeaponInventoryArray.SetNum(MaxWeaponInventorySize);
	EquipmentInventoryArray.SetNum(MaxEquipmentInventorySize);
	ResourceInventoryArray.SetNum(MaxResourceInventorySize);
}