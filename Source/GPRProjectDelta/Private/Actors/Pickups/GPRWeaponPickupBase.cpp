// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/GPRWeaponPickupBase.h"

#include "Actors/ActorComponents/GPRInventoryComponentBase.h"
#include "Actors/Characters/GPRPlayerCharacter.h"
#include "Actors/Weapons/GPRWeaponBase.h"


// Sets default values
AGPRWeaponPickupBase::AGPRWeaponPickupBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void AGPRWeaponPickupBase::Interact(AActor* InstigatedActor)
{
	// Checks if the actor that interacted with this class is a player character
	if (TObjectPtr<AGPRPlayerCharacter> LocalPlayerCharRef = Cast<AGPRPlayerCharacter>(InstigatedActor))
	{
		// If the weapon class is null then this function will be terminated
		if (WeaponClassToSpawn.IsNull()) return;
		
		// Loads the reference to the weapon class to spawn
		TSubclassOf<AGPRWeaponBase> LocalWeaponToSpawn = WeaponClassToSpawn.LoadSynchronous();

		// Declares & sets spawn params
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Spawns a weapon into the world, which will be instantly attached to the player character who picked-ip this weapon
		TObjectPtr<AGPRWeaponBase> LocalSpawnedWeapon = GetWorld()->SpawnActor<AGPRWeaponBase>(LocalWeaponToSpawn, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

		// Sets the spawned weapons owning player to be the player which picked up this weapon
		LocalSpawnedWeapon->OwningPlayerCharRef = LocalPlayerCharRef;
		
		// Adds this spawned weapon to the player's inventory
		LocalPlayerCharRef->GetPlayerInventoryComponent()->AddWeaponToInventory(LocalSpawnedWeapon);

		// When this weapon is picked up, destroy it.
		this->Destroy();
	}
}

// Called when the game starts or when spawned
void AGPRWeaponPickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGPRWeaponPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

