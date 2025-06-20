// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/GPRPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Actors/ActorComponents/GPRInventoryComponentBase.h"
#include "Actors/Equipment/GPREquipmentBase.h"
#include "Actors/Weapons/GPRWeaponBase.h"
#include "Components/SphereComponent.h"
#include "Core/Controllers/GPRPrimaryPlayerControllerBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/GPRInteractable.h"

// Sets default values
AGPRPlayerCharacter::AGPRPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PlayerCameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CharacterCameraSpringArm"));
	PlayerCameraSpringArmComponent->SetupAttachment(GetCapsuleComponent());
	
	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	PlayerCameraComponent->SetupAttachment(PlayerCameraSpringArmComponent);

	PlayerInteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerInteractionSphere"));
	PlayerInteractionSphere->SetupAttachment(GetCapsuleComponent());

	PlayerInventoryComponent = CreateDefaultSubobject<UGPRInventoryComponentBase>(TEXT("PlayerInventoryComponent"));
}

// Called when the game starts or when spawned
void AGPRPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Sets up function bindings
	SetupFunctionBindings();

	// Gets a reference to the owning player character controller
	PlayerControllerRef = Cast<AGPRPrimaryPlayerControllerBase>(GetController());
}

void AGPRPlayerCharacter::PlayerMove(const FInputActionValue& InputValue)
{
	const FVector2D MoveAxis = InputValue.Get<FVector2D>();

	// Only adds input if the x-axis is non-zero.
	if (MoveAxis.X != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), MoveAxis.X);
	}

	// Only adds input if the y-axis is non-zero.
	if (MoveAxis.Y != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), MoveAxis.Y);
	}
}

void AGPRPlayerCharacter::PlayerLook(const FInputActionValue& InputValue)
{
	const FVector2D LookAxis = InputValue.Get<FVector2D>();

	// Only adds input if the x-axis is non-zero.
	if (LookAxis.X != 0.0f)
	{
		AddControllerYawInput(LookAxis.X);
	}

	// Only adds input if the y-axis is non-zero.
	if (LookAxis.Y != 0.0f)
	{
		AddControllerPitchInput(LookAxis.Y);
	}
}

void AGPRPlayerCharacter::PlayerStartJump(const FInputActionValue& InputValue)
{
	this->Jump();
}

void AGPRPlayerCharacter::PlayerStopJump(const FInputActionValue& InputValue)
{
	this->StopJumping();
}

void AGPRPlayerCharacter::PlayerSprint(const FInputActionValue& InputValue)
{
	// If the player character is not sprinting, then they will start sprinting & vice versa
	if (!bIsPlayerSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultSprintSpeed;
		bIsPlayerSprinting = true;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
		bIsPlayerSprinting = false;
	}
}

void AGPRPlayerCharacter::PlayerCrouch(const FInputActionValue& InputValue)
{
	// If the crouch button is pressed, the player character will crouch.
	if (!bIsPlayerCrouching)
	{
		this->Crouch();
		bIsPlayerCrouching = true;
	}
	else
	{
		this->UnCrouch();
		bIsPlayerCrouching = false;
	}
}

void AGPRPlayerCharacter::PlayerInteract(const FInputActionValue& InputValue)
{
	// Line trace start & end values
	const FVector LocalTraceStart = PlayerCameraComponent->GetComponentLocation();
	const FVector LocalTraceEnd = LocalTraceStart + PlayerCameraComponent->GetForwardVector() * InteractableLineTraceDistance;

	// Line trace params
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.bTraceComplex = true;

	// Line trace result
	FHitResult HitResult;
	DrawDebugLine(GetWorld(), LocalTraceStart, LocalTraceEnd, FColor::Red, false, 1.0f, 0, 0);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, LocalTraceStart, LocalTraceEnd, ECC_Visibility, CollisionQueryParams))
	{
		// Checks if the hit actor inherits from the interactable interface
		if (IGPRInteractable* LocalInteractableActor = Cast<IGPRInteractable>(HitResult.GetActor()))
		{
			// If this actor does inherit & implement this interface than the interact function on this hit actor will be called & executed
			LocalInteractableActor->Interact(this);

			// Gets this player's player controller & calls it's OnPlayerInteract event.
			if (TObjectPtr<AGPRPrimaryPlayerControllerBase> LocalPlayerControllerRef = Cast<AGPRPrimaryPlayerControllerBase>(GetController()))
			{
				LocalPlayerControllerRef->OnPlayerInteract();
			}
		}
	}
}

void AGPRPlayerCharacter::PlayerSwapWeapons(const FInputActionValue& InputValue)
{
	// Loops through each element inside the weapons inventory array to keep track of how many weapons the player has.
	int32 LocalValidActorCounter = 0;	
	for (AGPRWeaponBase* LocalWeapon : GetPlayerInventoryComponent()->WeaponInventoryArray)
	{
		// If the current element is valid, then the counter will be incremented.
		if (IsValid(LocalWeapon))
		{
			LocalValidActorCounter++;
		}
	}

	// Checks if the player has more than one weapon in their inventory.
	if (LocalValidActorCounter > 1)
	{
		// Declares an alias to the inventory components active weapon slot index.
		int32& LocalActiveSlotIndex = GetPlayerInventoryComponent()->ActiveWeaponSlotIndex;

		// Declares variables used to hold the max weapon inventory size & the next active weapon slot index.
		const int32 LocalMaxWeaponInventorySize = GetPlayerInventoryComponent()->MaxWeaponInventorySize;
		const int32 LocalNewActiveSlot = (LocalActiveSlotIndex + 1) % LocalMaxWeaponInventorySize;

		// Before swapping weapons, the current weapon will be hidden.
		GetPlayerInventoryComponent()->WeaponInventoryArray[LocalActiveSlotIndex]->SetActorHiddenInGame(true);

		// Changes the active weapon slot index to the next available slot using an alias variable.
		LocalActiveSlotIndex = LocalNewActiveSlot;

		// After swapping to the next available weapon, the now currently active weapon will be made visible.
		GetPlayerInventoryComponent()->WeaponInventoryArray[LocalActiveSlotIndex]->SetActorHiddenInGame(false);

		// Updates the player's weapon UI when swapping weapons
		PlayerControllerRef->OnPlayerSwappedWeapons();
	}
}

void AGPRPlayerCharacter::PlayerAttack(const FInputActionValue& InputValue)
{
	// Declares local variables for code readability
	const int32 LocalActiveWeaponSlotIndex = GetPlayerInventoryComponent()->ActiveWeaponSlotIndex;
	const TArray<TObjectPtr<AGPRWeaponBase>>& LocalWeaponInventoryArray = GetPlayerInventoryComponent()->WeaponInventoryArray;

	// Terminates this function early if there is no weapon available in the character's active weapon slot
	if (!IsValid(LocalWeaponInventoryArray[LocalActiveWeaponSlotIndex])) return;
	
	// Calls the fire logic on the character's currently active weapon
	LocalWeaponInventoryArray[LocalActiveWeaponSlotIndex]->FireWeapon();
}

void AGPRPlayerCharacter::PlayerStopAttack(const FInputActionValue& InputValue)
{
	// Declares local variables for code readability
	const int32 LocalActiveWeaponSlotIndex = GetPlayerInventoryComponent()->ActiveWeaponSlotIndex;
	const TArray<TObjectPtr<AGPRWeaponBase>> LocalWeaponInventoryArray = GetPlayerInventoryComponent()->WeaponInventoryArray;

	// Terminates this function early if there is no weapon available in the character's active weapon slot
	if (!IsValid(LocalWeaponInventoryArray[LocalActiveWeaponSlotIndex])) return;

	// Calls the fire logic on the character's currently active weapon
	LocalWeaponInventoryArray[LocalActiveWeaponSlotIndex]->StopFireWeapon();
}

void AGPRPlayerCharacter::PlayerInventory(const FInputActionValue& InputValue)
{
	
}

void AGPRPlayerCharacter::PlayerReloadWeapon(const FInputActionValue& InputValue)
{
	// Declares local variables for code readability
	const int32 LocalActiveWeaponSlotIndex = GetPlayerInventoryComponent()->ActiveWeaponSlotIndex;
	const TArray<TObjectPtr<AGPRWeaponBase>> LocalWeaponInventoryArray = GetPlayerInventoryComponent()->WeaponInventoryArray;

	// Terminates this function early if there is no weapon available in the character's active weapon slot
	if (!IsValid(LocalWeaponInventoryArray[LocalActiveWeaponSlotIndex])) return;

	// Calls the fire logic on the character's currently active weapon
	LocalWeaponInventoryArray[LocalActiveWeaponSlotIndex]->ReloadWeapon();
}

void AGPRPlayerCharacter::PlayerUseEquipment(const FInputActionValue& InputValue)
{
	if (!GetPlayerInventoryComponent()) return;

	const int32 LocalActiveEquipmentSlotIndex = GetPlayerInventoryComponent()->ActiveEquipmentSlotIndex;
	
	// Gets the first array element equipment for now
	if (AGPREquipmentBase* LocalSelectedEquipment = GetPlayerInventoryComponent()->EquipmentInventoryArray[LocalActiveEquipmentSlotIndex])
	{
		// Uses this equipment
		LocalSelectedEquipment->UseEquipment(this);
	}

	
}

void AGPRPlayerCharacter::PlayerSwapEquipment(const FInputActionValue& InputValue)
{
	// Loops through each element inside the equipment inventory array to keep track of how much equipment the player has.
	int32 LocalValidActorCounter = 0;	
	for (AGPREquipmentBase* LocalEquipment : GetPlayerInventoryComponent()->EquipmentInventoryArray)
	{
		// If the current element is valid, then the counter will be incremented.
		if (LocalEquipment)
		{
			LocalValidActorCounter++;
		}
	}

	// Checks if the player has more than one equipment in their inventory
	if (LocalValidActorCounter > 1)
	{
		// Declares an alias to the inventory components active equipment slot index.
		int32& LocalActiveSlotIndex = GetPlayerInventoryComponent()->ActiveEquipmentSlotIndex;

		// Declares variables used to hold the max weapon inventory size & the next active weapon slot index.
		const int32 LocalMaxEquipmentInventorySize = GetPlayerInventoryComponent()->MaxEquipmentInventorySize;
		const int32 LocalNewActiveSlot = (LocalActiveSlotIndex + 1) % LocalMaxEquipmentInventorySize;;

		// Changes the active weapon slot index to the next available slot using an alias variable.
		LocalActiveSlotIndex = LocalNewActiveSlot;

		// Update UI for equipment
		
	}
}

void AGPRPlayerCharacter::SetupFunctionBindings()
{
	PlayerInteractionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGPRPlayerCharacter::OnComponentBeginOverlapInteractionSphere);
	PlayerInteractionSphere->OnComponentEndOverlap.AddUniqueDynamic(this, &AGPRPlayerCharacter::OnComponentEndOverlapInteractionSphere);
}

const float AGPRPlayerCharacter::GetInteractableActorDotProduct(const FVector& DirectionToActor)
{
	// Returns the dot product between the interactable actor & the player camera
	return FVector::DotProduct(PlayerCameraComponent->GetForwardVector(), DirectionToActor);
}

void AGPRPlayerCharacter::OnComponentBeginOverlapInteractionSphere(UPrimitiveComponent* OverlappedComponent,
                                                                   AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                                   const FHitResult& SweepResult)
{
	// Checks if the actor implements the interactable interface
	if (Cast<IGPRInteractable>(OtherActor))
	{
		/* If the overlapped actor does implement this interface,
		 * then it will be added to the array of interactable actors that are in range of player */
		InteractableActorsInRangeArray.Add(OtherActor);
	}
}

void AGPRPlayerCharacter::OnComponentEndOverlapInteractionSphere(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/* If the interactable actor has moved out of range of the player's interaction radius,
	 * then the actor will be removed from the array of interactable actors */
	InteractableActorsInRangeArray.Remove(OtherActor);
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

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGPRPlayerCharacter::PlayerMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGPRPlayerCharacter::PlayerLook);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AGPRPlayerCharacter::PlayerStartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AGPRPlayerCharacter::PlayerStopJump);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AGPRPlayerCharacter::PlayerCrouch);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AGPRPlayerCharacter::PlayerSprint);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AGPRPlayerCharacter::PlayerInteract);
		EnhancedInputComponent->BindAction(SwapWeaponsAction, ETriggerEvent::Started, this, &AGPRPlayerCharacter::PlayerSwapWeapons);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AGPRPlayerCharacter::PlayerAttack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &AGPRPlayerCharacter::PlayerStopAttack);
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AGPRPlayerCharacter::PlayerInventory);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AGPRPlayerCharacter::PlayerReloadWeapon);
		EnhancedInputComponent->BindAction(UseEquipmentAction, ETriggerEvent::Started, this, &AGPRPlayerCharacter::PlayerUseEquipment);
		EnhancedInputComponent->BindAction(SwapEquipmentAction, ETriggerEvent::Started, this, &AGPRPlayerCharacter::PlayerSwapEquipment);
	}
}

void AGPRPlayerCharacter::AttachAddedWeaponToCharacter(AGPRWeaponBase* NewWeapon)
{
	NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
}

UGPRInventoryComponentBase* AGPRPlayerCharacter::GetPlayerInventoryComponent()
{
	return PlayerInventoryComponent;
}

UCameraComponent* AGPRPlayerCharacter::GetPlayerCameraComponent()
{
	return PlayerCameraComponent;
}

void AGPRPlayerCharacter::ApplyHealthToCharacter(float HealthAmount)
{
	// Updates the player's health & clamps it to the max float value of the player's max health var
	CurrentPlayerHealth = FMath::Clamp(CurrentPlayerHealth + HealthAmount, 0.0f, MaxPlayerHealth);

	// Update UI
}
