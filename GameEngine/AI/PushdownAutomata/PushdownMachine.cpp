#include "PushdownMachine.h"
#include "PushdownState.h"

using namespace NCL::CSC8599;

PushdownMachine::PushdownMachine(PushdownState* initialState)
{
	this->initialState = initialState;
}

PushdownMachine::~PushdownMachine()
{
}

bool PushdownMachine::Update(float dt) {
	if (activeState) {
		PushdownState* newState = nullptr;
		PushdownState::PushdownResult result = activeState->OnUpdate(dt, &newState);

		switch (result) {
			case PushdownState::Pop: {
				activeState->OnSleep();
				//delete activeState;
				stateStack.pop();
				if (stateStack.empty()) {
					return false;
				}
				else {
					activeState = stateStack.top();
					activeState->OnAwake();
				}					
			}break;
			case PushdownState::Push: {
				activeState->OnSleep();		

				stateStack.push(newState);
				activeState = newState;
				activeState->OnAwake();
			}break;
			case PushdownState::Reset: {
				Reset();
			} break;
		}
	}
	else {
		stateStack.push(initialState);
		activeState = initialState;
		activeState->OnAwake();
	}
	return true;
}

void PushdownMachine::Reset(uint32_t minsize)
{
	while (stateStack.size() > minsize)
	{
		activeState->OnSleep();
		//delete activeState;
		stateStack.pop();
		if (!stateStack.empty()) {
			activeState = stateStack.top();
			activeState->OnAwake();
		}
	}
}

