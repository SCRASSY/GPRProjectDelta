// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AI_Collection/GPREnemyAiPatrolSpline.h"
#include "Components/SplineComponent.h"


// Sets default values
AGPREnemyAiPatrolSpline::AGPREnemyAiPatrolSpline()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AI_SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("AI_SplineComponent"));
	AI_SplineComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGPREnemyAiPatrolSpline::BeginPlay()
{
	Super::BeginPlay();

	// Sets the spline current location to the start of the spline if the spline component is valid
	if (AI_SplineComponent) AI_SplineCurrentTransform = AI_SplineComponent->GetTransformAtDistanceAlongSpline(0.0f, ESplineCoordinateSpace::World);
	UE_LOG(LogTemp, Warning, TEXT("AI_SplineCurrentTransform: %s"), *AI_SplineCurrentTransform.ToString());

	// Stores the length of the spline if the spline component is valid
	if (AI_SplineComponent) AI_SplineLength = AI_SplineComponent->GetSplineLength();
	UE_LOG(LogTemp, Warning, TEXT("AI_SplineLength: %f"), AI_SplineLength);
}

// Called every frame
void AGPREnemyAiPatrolSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Moves the spline current location vector along the spline
	MoveVectorAlongSpline(DeltaTime);
}

void AGPREnemyAiPatrolSpline::MoveVectorAlongSpline(float DeltaTime)
{
	// Updates the float position on the spline using modulas to wrap the value back to 0 once the position has reached the spline length value
	AI_PosOnSpline = FMath::Fmod(AI_PosOnSpline + AI_MoveSpeed * DeltaTime, AI_SplineLength);

	// Updates the current spline transform to the new position on the spline
	AI_SplineCurrentTransform = AI_SplineComponent->GetTransformAtDistanceAlongSpline(AI_PosOnSpline, ESplineCoordinateSpace::World);
}

