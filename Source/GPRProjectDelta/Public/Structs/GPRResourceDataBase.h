// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPRResourceDataBase.generated.h"

USTRUCT(BlueprintType)
struct GPRPROJECTDELTA_API FGPRResourceDataBase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ResourceName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ResourceDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> ResourceIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ResourceQuantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ResourceMaxStackSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsStackable;
};
