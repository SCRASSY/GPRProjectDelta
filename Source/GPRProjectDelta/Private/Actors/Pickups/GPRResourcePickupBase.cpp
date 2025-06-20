// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/GPRResourcePickupBase.h"
#include "Actors/Characters/GPRPlayerCharacter.h"
#include "Structs/GPRResourceDataBase.h"


// Sets default values
AGPRResourcePickupBase::AGPRResourcePickupBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGPRResourcePickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGPRResourcePickupBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Gets a reference to the resource data table info
	const FGPRResourceDataBase* LocalResourceData = ResourceDataTableRowHandle.GetRow<FGPRResourceDataBase>("");

	// Only sets the resource static mesh if the resource data static mesh is not null
	if (!LocalResourceData->ResourceStaticMesh.IsNull())
	{
		// Sets the resource static mesh to the resource data static mesh
		PickupStaticMesh->SetStaticMesh(LocalResourceData->ResourceStaticMesh.LoadSynchronous());
	}
}

// Called every frame
void AGPRResourcePickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGPRResourcePickupBase::Interact(AActor* InstigatedActor)
{
	Super::Interact(InstigatedActor);

	// Checks if the actor that interacted with this class is a player character
	if (TObjectPtr<AGPRPlayerCharacter> LocalPlayerCharRef = Cast<AGPRPlayerCharacter>(InstigatedActor))
	{
		
	}
}

