// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/GPREnemyCharacter.h"
#include "AIController.h"
#include "StateMachineCollection/GPRStateMachineBase.h"


// Sets default values
AGPREnemyCharacter::AGPREnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGPREnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Setup functions
	SetupStateMachine();
	SetupStates();

	// Initializes this state machine to start with the patrol state
	StateMachine->Initialize(PatrolState);
}

// Called every frame
void AGPREnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Checks if the enemy AI should change states
	CheckForStateChange(DeltaTime);
}

void AGPREnemyCharacter::SetupStateMachine()
{
	StateMachine = new GPRStateMachineBase();
	StateMachine->SetOwner(this);
}

void AGPREnemyCharacter::SetupStates()
{
	// Creates a new state object for each state ptr
	PatrolState = new GPRPatrolState();
	AlertState = new GPRAlertState();
	FollowPlayerState = new GPRFollowPlayerState();
	HostileState = new GPRHostileState();
}

void AGPREnemyCharacter::CheckForStateChange(float DeltaTime)
{
	if (!StateMachine) return;

	// Updates the current state
	StateMachine->Update(DeltaTime);

	if (GetPlayerPawn())
	{
		const FVector PlayerDirection = GetPlayerPawn()->GetActorLocation() - GetActorLocation().GetSafeNormal();
		const float PlayerDistance = PlayerDirection.Size();

		// Checks if the player is out of the enemy AI's detection range
		if (PlayerDistance > DetectionRange)
		{
			StateMachine->ChangeState(PatrolState);
		}
		else if (PlayerDistance <= DetectionRange)
		{
			StateMachine->ChangeState(AlertState);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Pawn is null"));
		StateMachine->ChangeState(PatrolState);
	}
}

void AGPREnemyCharacter::MoveToNewLocation(const FVector& NewLocation)
{
	if (AAIController* AI_Controller = Cast<AAIController>(GetController()))
	{
		EPathFollowingRequestResult::Type PathfindingResult = AI_Controller->MoveToLocation(NewLocation);
	}
}
