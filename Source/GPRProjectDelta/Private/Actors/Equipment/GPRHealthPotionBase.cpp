// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Equipment/GPRHealthPotionBase.h"
#include "Actors/Characters/GPRPlayerCharacter.h"
#include "AttributeSets/GPRCharacterStatsAtrSet.h"
#include "DataAssets/GPRHealingPotionDataAssetBase.h"

// Sets default values
AGPRHealthPotionBase::AGPRHealthPotionBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGPRHealthPotionBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGPRHealthPotionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGPRHealthPotionBase::UseEquipment(AGPRPlayerCharacter* UsingPlayerCharacter)
{
	if (!EquipmentData && !OwningPlayerCharRef) return;

	// Gets a reference to the character's stats attribute set
	const TObjectPtr<UGPRCharacterStatsAtrSet> CharacterStatsAtrSet = UsingPlayerCharacter->CharacterStatsAtrSet;
	if (!CharacterStatsAtrSet) return;
	
	// If the player character already has the max health, then this function will terminate early
	if (CharacterStatsAtrSet->GetHealth() == CharacterStatsAtrSet->GetMaxHealth()) return;

	if (UGPRHealingPotionDataAssetBase* PotionData = Cast<UGPRHealingPotionDataAssetBase>(EquipmentData))
	{
		// Gets a reference to this equipment's owning player
		OwningPlayerCharRef = UsingPlayerCharacter;

		// Gets a reference to the owning player's ability system component
		if (TObjectPtr<UAbilitySystemComponent> PlayerASC = OwningPlayerCharRef->GetAbilitySystemComponent())
		{
			// Makes an effect spec handle for the healing effect
			FGameplayEffectSpecHandle EffectSpecHandle = PlayerASC->MakeOutgoingSpec(GameplayEffectClassToUse, 1.0f, PlayerASC->MakeEffectContext());

			// Valid check
			if (EffectSpecHandle.IsValid())
			{
				// Declares a gameplay tag & heal amount var
				//const FGameplayTag DataTag = FGameplayTag::RequestGameplayTag(FName("Data.HealingAmount"));
				const float HealAmount = PotionData->HealingAmount;

				// Sets effect spec handle magnitude value using this healing potions heal amount
				EffectSpecHandle.Data->SetSetByCallerMagnitude(HealthPotionTag, HealAmount);

				// Applies health to the player character
				PlayerASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);

				// 3. Destroy the potion actor
				this->Destroy();
			}
		}
	}
}

