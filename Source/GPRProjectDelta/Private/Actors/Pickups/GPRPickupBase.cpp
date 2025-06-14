// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/GPRPickupBase.h"


// Sets default values
AGPRPickupBase::AGPRPickupBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;
	
	PickupStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupStaticMesh"));
	PickupStaticMesh->SetupAttachment(RootSceneComponent);
}

// Called when the game starts or when spawned
void AGPRPickupBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGPRPickupBase::Interact(AActor* InstigatedActor)
{
	// Must be overriden inside child classes
}

// Called every frame
void AGPRPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

