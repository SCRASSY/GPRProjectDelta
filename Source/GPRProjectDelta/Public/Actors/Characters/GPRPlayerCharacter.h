// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GPRPlayerCharacter.generated.h"

// -- Forward Declarations --
class UGPRAbilitySystemComponent;
class UGPRCharacterStatsAtrSet;
class AGPRWeaponBase;
class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputComponent;
class UGPRInventoryComponentBase;
class AGPRPrimaryPlayerControllerBase;
struct FInputActionValue;

UCLASS(Config=Game)
class GPRPROJECTDELTA_API AGPRPlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// -- Constructor --
	AGPRPlayerCharacter();

#pragma region Interfaces
	UFUNCTION(BlueprintCallable, Category = "GAS")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
#pragma endregion

#pragma region Custom Functions
	void AttachAddedWeaponToCharacter(AGPRWeaponBase* NewWeapon);
	UGPRInventoryComponentBase* GetPlayerInventoryComponent();
	UCameraComponent* GetPlayerCameraComponent();
#pragma endregion

#pragma region Properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsPlayerSprinting = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsPlayerCrouching = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefaultWalkSpeed = 250.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefaultSprintSpeed = 450.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefaultCrouchSpeed = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float InteractableLineTraceDistance = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> InteractableActorsInRangeArray;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AGPRPrimaryPlayerControllerBase> PlayerControllerRef;

	// Character stats attribute set
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UGPRCharacterStatsAtrSet> CharacterStatsAtrSet;
#pragma endregion

#pragma region Components
	// GAS
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS")
	TObjectPtr<UGPRAbilitySystemComponent> AbilitySystemComp;
#pragma endregion
	
protected:
#pragma region Function Overrides
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
#pragma endregion

#pragma region Components
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> PlayerCameraSpringArmComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> PlayerCameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> PlayerInteractionSphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UGPRInventoryComponentBase> PlayerInventoryComponent;

#pragma endregion

#pragma region Properties
	// Input Actions
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> SwapWeaponsAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> InventoryAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> ReloadAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> UseEquipmentAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> SwapEquipmentAction;
#pragma endregion

#pragma region Custom Functions
	UFUNCTION()
	void SetupFunctionBindings();
	
	UFUNCTION()
	const float GetInteractableActorDotProduct(const FVector& DirectionToActor);
#pragma endregion

#pragma region Function Bindings
	// Delegate Bindings
	UFUNCTION()
	void OnComponentBeginOverlapInteractionSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
												  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
												  const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentEndOverlapInteractionSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
												UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	// Input Callbacks
	UFUNCTION() void PlayerMove(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerLook(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerStartJump(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerStopJump(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerSprint(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerCrouch(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerInteract(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerSwapWeapons(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerAttack(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerStopAttack(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerInventory(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerReloadWeapon(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerUseEquipment(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerSwapEquipment(const FInputActionValue& InputValue);
#pragma endregion
	
};