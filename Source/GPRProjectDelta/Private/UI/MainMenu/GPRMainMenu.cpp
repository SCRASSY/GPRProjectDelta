// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/GPRMainMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGPRMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	// Sets up function button bindings
	SetupFunctionBindings();
}

void UGPRMainMenu::SetupFunctionBindings()
{
	PlayButton->OnClicked.AddUniqueDynamic(this, &UGPRMainMenu::OnPlayButtonClicked);
	ExitButton->OnClicked.AddUniqueDynamic(this, &UGPRMainMenu::OnExitButtonClicked);
}

void UGPRMainMenu::OnPlayButtonClicked()
{
	// If the level to open is valid, open it
	if (MainGameLevelToLoad) UGameplayStatics::OpenLevelBySoftObjectPtr(this, MainGameLevelToLoad);
}

void UGPRMainMenu::OnExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
