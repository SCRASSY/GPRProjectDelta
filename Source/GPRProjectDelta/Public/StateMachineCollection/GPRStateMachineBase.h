#pragma once

class GPRStateBase;

class GPRStateMachineBase
{
public:
	// Custom functions
	void Initialize(GPRStateBase* InitialState); // Initializes the starting state
	void Update(const float DeltaTime); // Updates the current state every frame
	void ChangeState(GPRStateBase* NewState); // Changes the current state to a new state

	// Getters
	GPRStateBase* GetCurrentState() const { return CurrentState; } // Returns the current state
	GPRStateBase* GetPreviousState() const { return PreviousState; } // Returns the Previous state
	AActor* GetOwner() const { return Owner; } // Returns the owning object

	// Setters
	void SetOwner(AActor* NewOwner) { Owner = NewOwner; } // Sets the owning object	

private:
	// States
	GPRStateBase* CurrentState = nullptr;
	GPRStateBase* PreviousState = nullptr;

	// Owning object
	TObjectPtr<AActor> Owner;
};
