// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Actors/AI_Collection/GPREnemyAiPatrolSpline.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "StateMachineCollection/GPRStateMachineBase.h"
#include "StateMachineCollection/States/GPRStateBase.h"
#include "GPREnemyCharacter.generated.h"

class GPRStateMachineBase;
class GPRStateMachineManager;

UCLASS()
class GPRPROJECTDELTA_API AGPREnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGPREnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly)
	float DetectionRange = 1000.0f;

	// Holds a ref to the selected spline this enemy AI should follow when in patrol mode
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AGPREnemyAiPatrolSpline> AI_PatrolSpline;

	// The target the enemy AI needs to move towards
	FVector TargetLocation = FVector::ZeroVector;

	// Custom functions
	void MoveToNewLocation(const FVector& NewLocation);

private:
	// State machine
	GPRStateMachineBase* StateMachine = nullptr;

	// States
	GPRStateBase* PatrolState = nullptr;
	GPRStateBase* AlertState = nullptr;
	GPRStateBase* FollowPlayerState = nullptr;
	GPRStateBase* HostileState = nullptr;

	// Setup functions
	void SetupStateMachine();
	void SetupStates();

	// Custom functions
	void CheckForStateChange(float DeltaTime);

	// Getters
	APawn* GetPlayerPawn() const
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		return PC ? PC->GetPawn() : nullptr;
	}
};

// -- Patrol State --
class GPRPatrolState : public GPRStateBase
{
	virtual void EnterState(GPRStateMachineBase* StateMachineRef) override
	{
		if (AGPREnemyCharacter* AI_EnemyChar = Cast<AGPREnemyCharacter>(StateMachineRef->GetOwner()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Patrol State Entered!"));
			// Gets the spline's current location on the patrol spline
			AI_EnemyChar->TargetLocation = AI_EnemyChar->AI_PatrolSpline->GetAI_SplineCurrentTransform().GetLocation();
			
			// Moves this enemy AI character to a new location
			AI_EnemyChar->MoveToNewLocation(AI_EnemyChar->TargetLocation);
		}
	}
	virtual void UpdateState(GPRStateMachineBase* StateMachineRef, const float DeltaTime) override
	{
		if (AGPREnemyCharacter* AI_EnemyChar = Cast<AGPREnemyCharacter>(StateMachineRef->GetOwner()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Patrol State Update"));
			
			// Gets the spline's current location on the patrol spline
			AI_EnemyChar->TargetLocation = AI_EnemyChar->AI_PatrolSpline->GetAI_SplineCurrentTransform().GetLocation();
			
			// Moves this enemy AI character to a new location
			AI_EnemyChar->MoveToNewLocation(AI_EnemyChar->TargetLocation);
		}
	}
	virtual void ExitState(GPRStateMachineBase* StateMachineRef) override
	{
		
	}
};

// -- Alert State --
class GPRAlertState : public GPRStateBase
{
	virtual void EnterState(GPRStateMachineBase* StateMachineRef) override
	{
		// Gets a reference to the AI enemy owner
		if (AGPREnemyCharacter* AI_EnemyChar = Cast<AGPREnemyCharacter>(StateMachineRef->GetOwner()))
		{
			// Gets a reference to the AI controller used for the AI enemy character
			if (AAIController* AIC = Cast<AAIController>(AI_EnemyChar->GetController()))
			{
				// Stops the enemy AI from moving
				AIC->StopMovement();
			}
		}
	}
	virtual void UpdateState(GPRStateMachineBase* StateMachineRef, const float DeltaTime) override
	{
		
	}
	virtual void ExitState(GPRStateMachineBase* StateMachineRef) override
	{
		
	}
};

// -- FollowPlayer State --
class GPRFollowPlayerState : public GPRStateBase
{
	virtual void EnterState(GPRStateMachineBase* StateMachineRef) override
	{
		
	}
	virtual void UpdateState(GPRStateMachineBase* StateMachineRef, const float DeltaTime) override
	{
		
	}
	virtual void ExitState(GPRStateMachineBase* StateMachineRef) override
	{
		
	}
};

// -- Hostile State --
class GPRHostileState : public GPRStateBase
{
	virtual void EnterState(GPRStateMachineBase* StateMachineRef) override
	{
		
	}
	virtual void UpdateState(GPRStateMachineBase* StateMachineRef, const float DeltaTime) override
	{
		
	}
	virtual void ExitState(GPRStateMachineBase* StateMachineRef) override
	{
		
	}
};
