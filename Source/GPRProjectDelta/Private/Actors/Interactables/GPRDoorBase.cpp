// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/GPRDoorBase.h"
#include "Actors/ActorComponents/GPRInventoryComponentBase.h"
#include "Actors/Characters/GPRPlayerCharacter.h"
#include "Core/Controllers/GPRPrimaryPlayerControllerBase.h"


// Sets default values
AGPRDoorBase::AGPRDoorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	DoorFrameStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameStaticMesh"));
	DoorFrameStaticMesh->SetupAttachment(SceneRoot);
	
	DoorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorStaticMesh"));
	DoorStaticMesh->SetupAttachment(DoorFrameStaticMesh);
}

// Called when the game starts or when spawned
void AGPRDoorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGPRDoorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGPRDoorBase::Interact(AActor* InstigatedActor)
{
	// Checks if the actor that interacted with this class is the player character
	if (TObjectPtr<AGPRPlayerCharacter> LocalPlayerCharRef = Cast<AGPRPlayerCharacter>(InstigatedActor))
	{
		// Gets a reference to the player's resource inventory
		TArray<FGPRResourceDataBase>& LocalResourceInventory = LocalPlayerCharRef->GetPlayerInventoryComponent()->ResourceInventoryArray;

		// Loops through each element in the player character's resource inventory array
		for (FGPRResourceDataBase& LocalResourceData : LocalResourceInventory)
		{
			// Checks if the current element is gold.
			if (LocalResourceData.ResourceName == "Gold")
			{
				// Checks if the player has enough gold to open the door.
				if (LocalResourceData.ResourceQuantity >= 5 )
				{
					// If the player does have enough gold, then the door will open.
					LocalResourceData.ResourceQuantity -= 5;

					// If there is no items left of this type in the slot then this item is now gone
					if (LocalResourceData.ResourceQuantity <= 0)
					{
						// Creates a default struct with default values & assigns it to the "destroyed" struct
						FGPRResourceDataBase LocalDefaultStruct{};
						LocalResourceData = LocalDefaultStruct;
					}

					// Gets a reference to the player's player controller
					if (TObjectPtr<AGPRPrimaryPlayerControllerBase> LocalPlayerControllerRef = Cast<AGPRPrimaryPlayerControllerBase>(GetWorld()->GetFirstPlayerController()))
					{
						// Updates the player's resource UI
						LocalPlayerControllerRef->UpdateResourcePickupUI();
					}

					// Destroys the door component.
					DoorStaticMesh->DestroyComponent();
					return;
				}
			}
		}
	}
}