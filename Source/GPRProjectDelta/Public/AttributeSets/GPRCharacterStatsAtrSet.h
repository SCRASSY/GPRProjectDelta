// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GPRCharacterStatsAtrSet.generated.h"

// -- Accessor Macro --
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// -- Delegate Declarations --
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeChangedEvent, UAttributeSet*, AttributeSet);

UCLASS()
class GPRPROJECTDELTA_API UGPRCharacterStatsAtrSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	// -- Constructor --
	UGPRCharacterStatsAtrSet();

	// -- Attributes --
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Thrust;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxThrust;

	// -- Accessors --
	ATTRIBUTE_ACCESSORS(UGPRCharacterStatsAtrSet, Health);
	ATTRIBUTE_ACCESSORS(UGPRCharacterStatsAtrSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UGPRCharacterStatsAtrSet, Stamina);
	ATTRIBUTE_ACCESSORS(UGPRCharacterStatsAtrSet, MaxStamina);
	ATTRIBUTE_ACCESSORS(UGPRCharacterStatsAtrSet, Thrust);
	ATTRIBUTE_ACCESSORS(UGPRCharacterStatsAtrSet, MaxThrust);

	// -- Function Overrides --
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// -- Delegate Events --
	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnStaminaChanged;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnThrustChanged;
};