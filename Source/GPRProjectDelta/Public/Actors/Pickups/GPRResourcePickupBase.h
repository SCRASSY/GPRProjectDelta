// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPRPickupBase.h"
#include "GPRResourcePickupBase.generated.h"

UCLASS()
class GPRPROJECTDELTA_API AGPRResourcePickupBase : public AGPRPickupBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGPRResourcePickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
