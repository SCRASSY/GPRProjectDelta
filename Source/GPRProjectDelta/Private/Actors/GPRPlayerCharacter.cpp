// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GPRPlayerCharacter.h"


// Sets default values
AGPRPlayerCharacter::AGPRPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGPRPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGPRPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGPRPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

