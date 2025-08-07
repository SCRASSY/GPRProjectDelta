// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GPRMainMenu.generated.h"

class UButton;

UCLASS()
class GPRPROJECTDELTA_API UGPRMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

public:
	// -- Components --
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> PlayButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

	// -- Properties --
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<ULevel> MainGameLevelToLoad;

	// -- Custom Functions --
	void SetupFunctionBindings();

	// -- Function bindings --
	UFUNCTION() void OnPlayButtonClicked();
	UFUNCTION() void OnExitButtonClicked();
};
