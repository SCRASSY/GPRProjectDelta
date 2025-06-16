// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/GPRWeaponBase.h"


// Sets default values
AGPRWeaponBase::AGPRWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponBodyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponBody"));
	WeaponBodyStaticMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	RootComponent = WeaponBodyStaticMesh;

	WeaponMagStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMag"));
	WeaponMagStaticMesh->SetupAttachment(WeaponBodyStaticMesh);
	WeaponMagStaticMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

// Called when the game starts or when spawned,
void AGPRWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGPRWeaponBase::ReloadWeapon()
{
	
}

bool AGPRWeaponBase::CanReloadWeapon()
{
	return true;
}

// Called every frame
void AGPRWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}