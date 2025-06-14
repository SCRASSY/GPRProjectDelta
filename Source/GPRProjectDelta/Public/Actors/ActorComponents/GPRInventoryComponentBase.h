// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/GPRResourceDataBase.h"
#include "GPRInventoryComponentBase.generated.h"

class AGPRWeaponBase;
class AGPREquipmentBase;
class AGPRPlayerCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GPRPROJECTDELTA_API UGPRInventoryComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGPRInventoryComponentBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<AGPRPlayerCharacter> PlayerCharRef;

	// Used to determine how many weapons the inventory component can hold
	UPROPERTY(EditDefaultsOnly)
	int32 MaxWeaponInventorySize = 0;

	// Used to determine how much equipment the inventory component can hold
	UPROPERTY(EditDefaultsOnly)
	int32 MaxEquipmentInventorySize = 0;

	// Used to determine how many items the inventory component can hold
	UPROPERTY(EditDefaultsOnly)
	int32 MaxResourceInventorySize = 0;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	// Used to hold the player's weapons
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<TObjectPtr<AGPRWeaponBase>> WeaponInventoryArray;

	// Used to hold the player's equipment like grenades
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<TObjectPtr<AGPREquipmentBase>> EquipmentInventoryArray;

	// Used to hold the player's resources like weapon parts, currency, etc.
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<FGPRResourceDataBase> ResourceInventoryArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ActiveWeaponSlotIndex = 0;

	// Used to add items to the player's inventory
	UFUNCTION() void AddWeaponToInventory(AGPRWeaponBase* NewWeapon);
	UFUNCTION() void AddEquipmentToInventory(AGPREquipmentBase* NewEquipment);
	UFUNCTION() void AddResourceToInventory(const FGPRResourceDataBase& NewResource);

	// Used to check if the player can add items to their inventory
	UFUNCTION() void CanAddWeaponToInventory(bool& bCanAddItem, int32& AvailableSlotIndex);
	UFUNCTION() void CanAddEquipmentToInventory(bool& bCanAddItem, int32& AvailableSlotIndex);
	UFUNCTION() void CanAddResourceToInventory(bool& bCanAddItem, int32& AvailableSlotIndex);

	UFUNCTION()
	void DropWeapon(AGPRWeaponBase* WeaponToRemove);

	UFUNCTION()
	void SetupCharacterReference();

	UFUNCTION()
	void SetInventoryArraySize();
};