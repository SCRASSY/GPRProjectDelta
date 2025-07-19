// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSets/GPRCharacterStatsAtrSet.h"
#include "GameplayEffectExtension.h"

UGPRCharacterStatsAtrSet::UGPRCharacterStatsAtrSet()
{
	// -- Initialize values --
	// Health
	InitHealth(100.f);
	InitMaxHealth(100.f);

	// Stamina
	InitStamina(100.f);
	InitMaxStamina(100.f);

	// Thrust
	InitThrust(50.f);
	InitMaxThrust(50.f);
}

void UGPRCharacterStatsAtrSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// Checks if the attribute being changed is the health attribute
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

	// Checks if the attribute being changed is the stamina attribute
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}

	Super::PreAttributeChange(Attribute, NewValue);
}

void UGPRCharacterStatsAtrSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	// Checks if the attribute that changed was the health attributes
	if (Attribute == GetHealthAttribute() || Attribute == GetMaxHealthAttribute())
	{
		// Broadcasts the health changed event
		OnHealthChanged.Broadcast(this);
	}

	// Checks if the attribute that changed was the stamina attributes
	if (Attribute == GetStaminaAttribute() || Attribute == GetMaxStaminaAttribute())
	{
		// Broadcasts the stamina changed event
		OnStaminaChanged.Broadcast(this);
	}

	// Checks if the attribute that changed was the thrust attributes
	if (Attribute == GetThrustAttribute() || Attribute == GetMaxThrustAttribute())
	{
		// Broadcasts the thrust changed event
		OnThrustChanged.Broadcast(this);
	}
}

void UGPRCharacterStatsAtrSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		if (GetStamina() >= GetMaxStamina())
		{
			UAbilitySystemComponent& ASC = Data.Target;
			ASC.RemoveActiveEffectsWithGrantedTags(FGameplayTag::RequestGameplayTag(FName("Ability.Regen.Stamina"), true).GetSingleTagContainer());

			SetStamina(GetMaxStamina());
		}
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		const float NewHealth = FMath::Clamp(GetHealth(), 0.f, GetMaxHealth());
		SetHealth(NewHealth);
	}

	// After the character's thrust has been changed it will be capped between 0 - max 
	if (Data.EvaluatedData.Attribute == GetThrustAttribute())
	{
		if (GetThrust() >= GetMaxThrust())
		{
			UAbilitySystemComponent& ASC = Data.Target;
			ASC.RemoveActiveEffectsWithGrantedTags(FGameplayTag::RequestGameplayTag(FName("Ability.Regen.Thrust"), true).GetSingleTagContainer());

			SetThrust(GetMaxThrust());
		}
	}
}
