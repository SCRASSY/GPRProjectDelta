// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GPRInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGPRInteractable : public UInterface
{
	GENERATED_BODY()
};
class GPRPROJECTDELTA_API IGPRInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(AActor* InstigatedActor) = 0;
};