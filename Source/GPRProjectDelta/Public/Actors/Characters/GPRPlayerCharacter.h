// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GPRPlayerCharacter.generated.h"

struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UGPRInventoryComponentBase;

UCLASS()
class GPRPROJECTDELTA_API AGPRPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGPRPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> PlayerCameraSpringArmComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> PlayerCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<UGPRInventoryComponentBase> PlayerInventoryComponent;

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

	UFUNCTION()
	void PlayerMove(const FInputActionValue& InputValue);

	UFUNCTION()
	void PlayerLook(const FInputActionValue& InputValue);

	UFUNCTION()
	void PlayerStartJump(const FInputActionValue& InputValue);

	UFUNCTION()
	void PlayerStopJump(const FInputActionValue& InputValue);

	UFUNCTION()
	void PlayerSprint(const FInputActionValue& InputValue);

	UFUNCTION()
	void PlayerCrouch(const FInputActionValue& InputValue);

	UFUNCTION()
	void PlayerInteract(const FInputActionValue& InputValue);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
};
