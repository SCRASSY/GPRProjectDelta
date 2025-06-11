// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Controllers/GPRPrimaryPlayerControllerBase.h"
#include "EnhancedInputSubsystems.h"

void AGPRPrimaryPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}
