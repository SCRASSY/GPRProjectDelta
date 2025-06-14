// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GPRInteractable.h"
#include "GPRPickupBase.generated.h"

UCLASS()
class GPRPROJECTDELTA_API AGPRPickupBase : public AActor, public IGPRInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGPRPickupBase();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> RootSceneComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> PickupStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	TObjectPtr<USoundCue> PickupSFX;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interact(AActor* InstigatedActor) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};