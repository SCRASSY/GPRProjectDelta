// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GPRPlayerCharacter.generated.h"

class AGPRWeaponBase;
class USphereComponent;
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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> PlayerCameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> PlayerInteractionSphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> SwapWeaponsAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> AttackAction;

	UFUNCTION()	void PlayerMove(const FInputActionValue& InputValue);
	UFUNCTION()	void PlayerLook(const FInputActionValue& InputValue);
	UFUNCTION()	void PlayerStartJump(const FInputActionValue& InputValue);
	UFUNCTION()	void PlayerStopJump(const FInputActionValue& InputValue);
	UFUNCTION()	void PlayerSprint(const FInputActionValue& InputValue);
	UFUNCTION()	void PlayerCrouch(const FInputActionValue& InputValue);
	UFUNCTION()	void PlayerInteract(const FInputActionValue& InputValue);
	UFUNCTION()	void PlayerSwapWeapons(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerAttack(const FInputActionValue& InputValue);
	UFUNCTION() void PlayerStopAttack(const FInputActionValue& InputValue);

	UFUNCTION()
	void SetupFunctionBindings();

	UFUNCTION()
	const float GetInteractableActorDotProduct(const FVector& DirectionToActor); 

#pragma region // Function Bindings
	UFUNCTION()
	void OnComponentBeginOverlapInteractionSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                              const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnComponentEndOverlapInteractionSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
#pragma endregion

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void AttachAddedWeaponToCharacter(AGPRWeaponBase* NewWeapon);

	UFUNCTION()
	UGPRInventoryComponentBase* GetPlayerInventoryComponent();

	UFUNCTION()
	UCameraComponent* GetPlayerCameraComponent();

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

	// The angle at which the player needs to be looking at an object to interact with it
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefaultInteractableRadius = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float InteractableLineTraceDistance = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> InteractableActorsInRangeArray;
};
