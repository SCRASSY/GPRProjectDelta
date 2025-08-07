#pragma once

class GPRStateMachineBase;

// This class is abstract
class GPRStateBase
{
public:
	// Destructor
	virtual ~GPRStateBase() = default;
	
	virtual void EnterState(GPRStateMachineBase* StateMachineRef) = 0; // Called when the enemy is entering this state
	virtual void UpdateState(GPRStateMachineBase* StateMachineRef, const float DeltaTime) = 0; // Called every frame while in this state
	virtual void ExitState(GPRStateMachineBase* StateMachineRef) = 0; // Called when the enemy leaves this state
};
