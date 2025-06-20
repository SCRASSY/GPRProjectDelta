// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GPRPrimaryPlayerControllerBase.generated.h"

class UInputMappingContext;

UCLASS()
class GPRPROJECTDELTA_API AGPRPrimaryPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerInteract();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerAttack();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerSwappedWeapons();
};
