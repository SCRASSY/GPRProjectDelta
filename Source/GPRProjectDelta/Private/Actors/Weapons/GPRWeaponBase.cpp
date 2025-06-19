// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/GPRWeaponBase.h"
#include "Actors/Characters/GPRPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "DataAssets/GPRWeaponStatsDataAssetBase.h"


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

	WeaponMuzzleComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponMuzzleComponent"));
	WeaponMuzzleComponent->SetupAttachment(WeaponBodyStaticMesh);
}

// Called when the game starts or when spawned,
void AGPRWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// Sets up a reference to the owning player character
	SetupPlayerReference();
}

void AGPRWeaponBase::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// If a data asset has been added, then all weapon data will be updated based on the data assets info
	if (IsValid(WeaponData))
	{
		CurrentMagAmmo = WeaponData->WeaponMagSize;
		CurrentReserveAmmo = WeaponData->WeaponReserveAmmoSize;
		WeaponBodyStaticMesh->SetStaticMesh(WeaponData->WeaponBodyMesh.LoadSynchronous());
	}
}

void AGPRWeaponBase::FireWeapon()
{
	switch (WeaponData->WeaponFireType)
	{
	case EWeaponFireType::EWF_Semi:
		// Fires a single line trace
		FireWeaponSemi();
		break;
	case EWeaponFireType::EWF_Burst:
		// Fires a single line trace 3 times
		FireWeaponBurst();
		break;
	case EWeaponFireType::EWF_Auto:
		// Fires a single line trace at a set timer rate until the player stops shooting or this weapon is out of ammo
		FireWeaponAuto();
		break;
	default:
		break;
	}
}

void AGPRWeaponBase::FireWeaponSemi()
{
	// Declares a ptr variable for code readability
	const TObjectPtr<UCameraComponent> LocalCamera = OwningPlayerCharRef->GetPlayerCameraComponent();
	
	// Line trace start & end values
	const FVector LocalCamTraceStart = LocalCamera->GetComponentLocation();
	const FVector LocalCamTraceEnd = LocalCamTraceStart + LocalCamera->GetForwardVector() * WeaponData->WeaponFireRange;

	// Line trace params
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActors(TArray<AActor*>{this, OwningPlayerCharRef});
	CollisionQueryParams.bTraceComplex = true;

	// Fires the first line trace from the player's cam to the cam's forward vector multiplied by the weapons range
	FHitResult LocalCamHitResult;
	if (GetWorld()->LineTraceSingleByChannel(LocalCamHitResult, LocalCamTraceStart, LocalCamTraceEnd, ECC_Visibility, CollisionQueryParams))
	{
		// Line trace start & end values
		const FVector LocalWeaponTraceStart = WeaponMuzzleComponent->GetComponentLocation();
		const FVector LocalWeaponTraceEnd = LocalCamHitResult.ImpactPoint;
		
		FHitResult LocalWeaponHitResult;
		if (GetWorld()->LineTraceSingleByChannel(LocalWeaponHitResult, LocalWeaponTraceStart, LocalWeaponTraceEnd, ECC_Visibility, CollisionQueryParams))
		{
			
		}

		DrawDebugLine(GetWorld(), LocalWeaponTraceStart, LocalWeaponTraceEnd, FColor::Red, false, 2.0f);
	}
	// If the first line trace doesn't hit anything then another line trace will fire a line trace from the player's weapon to the same end location as the first cam line trace
	else
	{
		// Line trace start & end values
		const FVector LocalWeaponTraceStart = WeaponMuzzleComponent->GetComponentLocation();
		
		FHitResult LocalWeaponHitResult;
		if (GetWorld()->LineTraceSingleByChannel(LocalWeaponHitResult, LocalWeaponTraceStart, LocalCamTraceEnd, ECC_Visibility, CollisionQueryParams))
		{
			
		}

		DrawDebugLine(GetWorld(), LocalWeaponTraceStart, LocalCamTraceEnd, FColor::Red, false, 2.0f);
	}
}

void AGPRWeaponBase::FireWeaponBurst()
{
	
}

void AGPRWeaponBase::FireWeaponAuto()
{
	
}

void AGPRWeaponBase::StopFireWeapon()
{
	
}

void AGPRWeaponBase::SetupPlayerReference()
{
	// Sets up a reference to the owning player character if there isn't already a reference
	if (!IsValid(OwningPlayerCharRef)) OwningPlayerCharRef = Cast<AGPRPlayerCharacter>(GetOwner());
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