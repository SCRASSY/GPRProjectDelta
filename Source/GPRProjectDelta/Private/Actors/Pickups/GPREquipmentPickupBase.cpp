// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/GPREquipmentPickupBase.h"

#include "Actors/ActorComponents/GPRInventoryComponentBase.h"
#include "Actors/Characters/GPRPlayerCharacter.h"
#include "Actors/Equipment/GPREquipmentBase.h"

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

void AGPREquipmentPickupBase::Interact(AActor* InstigatedActor)
{
	Super::Interact(InstigatedActor);

	// Checks if the actor that interacted with this class is a player character
	if (AGPRPlayerCharacter* LocalPlayerCharRef = Cast<AGPRPlayerCharacter>(InstigatedActor))
	{
		// If the weapon class is null, then this function will be terminated
		if (EquipmentClassToSpawn.IsNull()) return;
		
		// Loads the reference to the weapon class to spawn
		TSubclassOf<AGPREquipmentBase> LocalWeaponToSpawn = EquipmentClassToSpawn.LoadSynchronous();

		// Declares & sets spawn params
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Spawns a weapon into the world, which will be instantly attached to the player character who picked-ip this weapon
		TObjectPtr<AGPREquipmentBase> LocalSpawnedEquipment = GetWorld()->SpawnActor<AGPREquipmentBase>(LocalWeaponToSpawn, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

		// Sets the spawned weapons owning player to be the player which picked up this weapon
		LocalSpawnedEquipment->OwningPlayerCharRef = LocalPlayerCharRef;
		
		// Adds this spawned weapon to the player's inventory
		LocalPlayerCharRef->GetPlayerInventoryComponent()->AddEquipmentToInventory(LocalSpawnedEquipment);

		// When this weapon is picked up, destroy it.
		this->Destroy();
	}
}

