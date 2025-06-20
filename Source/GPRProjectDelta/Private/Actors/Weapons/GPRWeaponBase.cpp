// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/GPRWeaponBase.h"
#include "Actors/Characters/GPRPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Core/Controllers/GPRPrimaryPlayerControllerBase.h"
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

	// Gets a reference to the owning player character controller
	OwningPlayerControllerRef = Cast<AGPRPrimaryPlayerControllerBase>(GetWorld()->GetFirstPlayerController());
}

void AGPRWeaponBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// If a data asset has been added, then all weapon data will be updated based on the data assets info
	if (IsValid(WeaponData))
	{
		CurrentMagAmmo = WeaponData->WeaponMagSize;
		CurrentReserveAmmo = WeaponData->WeaponReserveAmmoSize;
		WeaponBodyStaticMesh->SetStaticMesh(WeaponData->WeaponBodyMesh.LoadSynchronous());
	}
}

// Called every frame
void AGPRWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGPRWeaponBase::FireWeapon()
{
	// If this weapon has no bullets left, then this function will terminate early
	if (CurrentMagAmmo <= 0) return;

	// Fires the weapon differently based on which fire type the weapon has selected
	switch (WeaponData->WeaponFireType)
	{
	case EWeaponFireType::EWF_Semi:
		// Fires a single line trace
		FireWeaponSemi();
		break;
	case EWeaponFireType::EWF_Burst:
		// Only shoots this weapon if it is not currently shooting from it's last burst fire
		if (!bIsFiring) FireWeaponBurst();
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
	// Terminates this function early if the player ref is not valid
	if (!IsValid(OwningPlayerCharRef)) return;
	
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

		// Hit result
		FHitResult LocalWeaponHitResult;

		// Draws a debug line trace for the player dev to see
		DrawDebugLine(GetWorld(), LocalWeaponTraceStart, LocalWeaponTraceEnd, FColor::Red, false, 2.0f);
		if (GetWorld()->LineTraceSingleByChannel(LocalWeaponHitResult, LocalWeaponTraceStart, LocalWeaponTraceEnd, ECC_Visibility, CollisionQueryParams))
		{
			
		}
	}
	// If the first line trace doesn't hit anything then another line trace will fire a line trace from the player's weapon to the same end location as the first cam line trace
	else
	{
		// Line trace start & end values
		const FVector LocalWeaponTraceStart = WeaponMuzzleComponent->GetComponentLocation();

		// Hit result
		FHitResult LocalWeaponHitResult;

		// Draws a debug line trace for the player dev to see
		DrawDebugLine(GetWorld(), LocalWeaponTraceStart, LocalCamTraceEnd, FColor::Red, false, 2.0f);
		if (GetWorld()->LineTraceSingleByChannel(LocalWeaponHitResult, LocalWeaponTraceStart, LocalCamTraceEnd, ECC_Visibility, CollisionQueryParams))
		{
			
		}
	}

	// Takes 1 bullet away from the fired weapon
	CurrentMagAmmo--;

	// Updates the UI responsible for showing the weapon ammo & any other stats
	OwningPlayerControllerRef->OnPlayerAttack();
}

void AGPRWeaponBase::FireWeaponBurst()
{
	// This weapon is being fired
	bIsFiring = true;
	
	// Declares a shared pointer to an int32 variable which is used by the weapons shooting timer
	TSharedPtr<int32> LocalShotCounter = MakeShared<int32>(0);
	
	// Declares a local fire rate variable which calculates how fast the timer should fire per sec
	const float LocalFireRate = 1 / WeaponData->WeaponFireRate;

	// Sets a timer which will fire this weapon on a timed loop until the player stops shooting or if they run out of ammo
	GetWorld()->GetTimerManager().SetTimer(WeaponFireTimerHandle, [this, LocalShotCounter]()
	{
		// Fires a single line trace
		FireWeaponSemi();

		// Adds +1 to the counter
		(*LocalShotCounter)++;

		// If the weapon has shot 3 times or has run out of ammo, then the weapon will stop shooting
		if (*LocalShotCounter >= 3 || CurrentMagAmmo <= 0)
		{
			// Clears the weapons shooting timer
			GetWorld()->GetTimerManager().ClearTimer(WeaponFireTimerHandle);

			// The weapon has stopped firing
			bIsFiring = false;
		}
	},
	LocalFireRate,
	true,
	0.0f);
}

void AGPRWeaponBase::FireWeaponAuto()
{
	// This weapon is being fired
	bIsFiring = true;
	
	// Declares a local fire rate variable which calculates how fast the timer should fire per sec
	const float LocalFireRate = 1 / WeaponData->WeaponFireRate;

	// Sets a timer which will fire this weapon on a timed loop until the player stops shooting or if they run out of ammo
	GetWorld()->GetTimerManager().SetTimer(WeaponFireTimerHandle, [this]()
	{
		// Fires a single line trace
		FireWeaponSemi();

		// If the weapon has run out of ammo, then the weapon will stop shooting
		if (CurrentMagAmmo <= 0)
		{
			// Clears the weapons shooting timer
			GetWorld()->GetTimerManager().ClearTimer(WeaponFireTimerHandle);

			// The weapon has stopped firing
			bIsFiring = false;
		}
	},
	LocalFireRate,
	true,
	0.0f);
}

void AGPRWeaponBase::StopFireWeapon()
{
	/* Only stops the weapon from firing if it's fire type is set to auto
	 * Since single shot weapons stop on their own & burst weapons stop shooting once the burst is complete*/
	if (WeaponData->WeaponFireType == EWeaponFireType::EWF_Auto)
	{
		// Clears the timer & stops this weapon from firing if this weapon is automatic
		GetWorld()->GetTimerManager().ClearTimer(WeaponFireTimerHandle);
	}

	// Only stops firing this weapon if it is not a burst weapon, because burst weapons stop firing on their own
	if (WeaponData->WeaponFireType != EWeaponFireType::EWF_Burst)
	{
		// This weapon is not being fired
		bIsFiring = false;
	}
}

void AGPRWeaponBase::ReloadWeapon()
{
	// Checks if this weapon can be reloaded otherwise this function will terminate early
	if (!CanReloadWeapon()) return;

	// How much ammo is needed to fill this weapon's magazine
	const int32 LocalAmmoNeeded = WeaponData->WeaponMagSize - CurrentMagAmmo;

	/* Checks if there is enough reserve ammo to fill the magazine.
	 * If not, then the magazine will be filled with the rest of the reserve ammo */
	if (CurrentReserveAmmo >= LocalAmmoNeeded)
	{
		CurrentMagAmmo += LocalAmmoNeeded;
		CurrentReserveAmmo -= LocalAmmoNeeded;
	}
	else
	{
		CurrentMagAmmo += CurrentReserveAmmo;
		CurrentReserveAmmo = 0;
	}

	/* Even though this function is designed for the player attack,
	 * it will still allow the UI to update when the player reloads this weapon */
	OwningPlayerControllerRef->OnPlayerAttack();
}

bool AGPRWeaponBase::CanReloadWeapon()
{
	// This weapon can reload if the mag is not full & the reserve ammo is greater than 0
	return CurrentMagAmmo != WeaponData->WeaponMagSize || CurrentReserveAmmo > 0;
}