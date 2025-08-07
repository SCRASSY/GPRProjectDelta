#include "StateMachineCollection/GPRStateMachineBase.h"
#include "StateMachineCollection/States/GPRStateBase.h"

void GPRStateMachineBase::Initialize(GPRStateBase* InitialState)
{
	if (InitialState)
	{
		// Sets the npc's initial state & enters it
		CurrentState = InitialState;
		CurrentState->EnterState(this);
		UE_LOG(LogTemp, Warning, TEXT("InitialState: %hs"), typeid(*InitialState).name());
	}
}

void GPRStateMachineBase::Update(const float DeltaTime)
{
	if (CurrentState)
	{
		// If we have a current state, update it
		CurrentState->UpdateState(this, DeltaTime);
	}
}

void GPRStateMachineBase::ChangeState(GPRStateBase* NewState)
{
	// Checks if the new state is valid or if the state is trying to change to the same state
	if (!NewState || NewState == CurrentState) return;
	
	if (CurrentState)
	{
		// Exit the current state
		CurrentState->ExitState(this);
	}

	// Store current state as previous
	PreviousState = CurrentState;

	// Set and enter the new state
	CurrentState = NewState;
	CurrentState->EnterState(this);
}
