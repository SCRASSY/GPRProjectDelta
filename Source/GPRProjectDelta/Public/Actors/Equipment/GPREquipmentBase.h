// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "GPREquipmentBase.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;
class AGPREquipmentPickupBase;
class AGPRPlayerCharacter;
class UGPREquipmentDataAssetBase;

UCLASS()
class GPRPROJECTDELTA_API AGPREquipmentBase : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGPREquipmentBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> EquipmentStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComp;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UseEquipment(AGPRPlayerCharacter* UsingPlayerCharacter);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UGPREquipmentDataAssetBase> EquipmentData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftClassPtr<AGPREquipmentPickupBase> EquipmentPickupClassToDrop;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGPRPlayerCharacter> OwningPlayerCharRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> GameplayAbilityClassToUse;
};