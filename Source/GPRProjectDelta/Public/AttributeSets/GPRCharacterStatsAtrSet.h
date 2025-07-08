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

	// -- Accessors --
	ATTRIBUTE_ACCESSORS(UGPRCharacterStatsAtrSet, Health);
	ATTRIBUTE_ACCESSORS(UGPRCharacterStatsAtrSet, MaxHealth);

	// -- Function Overrides --
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	// -- Delegate Events --
	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnHealthChanged;
};
