// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/GPRPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Actors/ActorComponents/GPRInventoryComponentBase.h"
#include "Actors/Weapons/GPRWeaponBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/GPRInteractable.h"
#include "Kismet/KismetMathLibrary.h"

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
	if (GetWorld()->LineTraceSingleByChannel(HitResult, LocalTraceStart, LocalTraceEnd, ECC_Visibility, CollisionQueryParams))
	{
		if (IGPRInteractable* LocalInteractableActor = Cast<IGPRInteractable>(HitResult.GetActor()))
		{
			LocalInteractableActor->Interact(this);
		}
	}

	DrawDebugLine(GetWorld(), LocalTraceStart, LocalTraceEnd, FColor::Red, false, 1.0f, 0, 0);
	
	// ------------------------------------------------------------------- Old dot product method
	// for (TObjectPtr InteractableActor : InteractableActorsInRangeArray)
	// {
	// 	const FVector LocalDirectionToActor = (InteractableActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	// 	const float LocalActorDotProductInDegrees = UKismetMathLibrary::DegAcos(GetInteractableActorDotProduct(LocalDirectionToActor));
	//
	// 	// Only allows the player to interact with an object if the object is within the players interactable radius
	// 	if (LocalActorDotProductInDegrees <= DefaultInteractableRadius)
	// 	{
	// 		/* Checks if the actor implements the interactable interface,
	// 		 * this is done again to call the interact function & pass in a param */
	// 		if (IGPRInteractable* LocalInteractableActor = Cast<IGPRInteractable>(InteractableActor))
	// 		{				
	// 			// Calls the interact function on the interactable actor
	// 			LocalInteractableActor->Interact(this);
	//
	// 			// If an object is interacted with, then this function will be terminated early
	// 			return;
	// 		}
	// 	}
	// }
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

