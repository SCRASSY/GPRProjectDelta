// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/GPRResourceDataBase.h"
#include "GPRInventoryComponentBase.generated.h"

class AGPRWeaponBase;
class AGPREquipmentBase;

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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	// Used to hold the player's weapons
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	TArray<TObjectPtr<AGPRWeaponBase>> WeaponInventoryArray;

	// Used to hold the player's equipment like grenades
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	TArray<TObjectPtr<AGPREquipmentBase>> EquipmentInventoryArray;

	// Used to hold the player's resources like weapon parts, currency, etc.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	TArray<FGPRResourceDataBase> ResourceInventoryArray;

	// Used to add items to the player's inventory
	UFUNCTION() void AddWeaponToInventory(AGPRWeaponBase* NewWeapon);
	UFUNCTION() void AddEquipmentToInventory(AGPREquipmentBase* NewEquipment);
	UFUNCTION() void AddResourceToInventory(const FGPRResourceDataBase& NewResource);

	// Used to check if the player can add items to their inventory
	UFUNCTION() bool CanAddWeaponToInventory();
	UFUNCTION() bool CanAddEquipmentToInventory();
	UFUNCTION() bool CanAddResourceToInventory();
};