// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GPRInteractable.h"
#include "GPRDoorBase.generated.h"

UCLASS()
class GPRPROJECTDELTA_API AGPRDoorBase : public AActor, public IGPRInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGPRDoorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> DoorFrameStaticMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> DoorStaticMesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* InstigatedActor) override;
};
