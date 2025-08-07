// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPREnemyAiPatrolSpline.generated.h"

class USplineComponent;

UCLASS()
class GPRPROJECTDELTA_API AGPREnemyAiPatrolSpline : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGPREnemyAiPatrolSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// -- Properties --
	// Moves along the spline which the enemy AI follows,
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(MakeEditWidget = true))
	FTransform AI_SplineCurrentTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AI_PosOnSpline = 0.0f;

	// The length of the spline
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float AI_SplineLength = 0.0f;

	// The speed of the spline current location vector in seconds (default value will move the vector around the spline, making a full lap in 10 seconds)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float AI_MoveSpeed = 10.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// -- Components --
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USplineComponent> AI_SplineComponent;

	// -- Custom Functions --
	void MoveVectorAlongSpline(float DeltaTime);

	// -- Getters --
	float GetSplineLength() const { return AI_SplineLength; }                                                                                                                                                                         
	float GetMoveSpeed() const { return AI_MoveSpeed; }
	FTransform GetAI_SplineCurrentTransform() const { return AI_SplineCurrentTransform; }
};
