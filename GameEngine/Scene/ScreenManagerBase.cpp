#include "ScreenManagerBase.h"

using namespace NCL;
using namespace CSC8599;


BaseScreen* NCL::CSC8599::ScreenManagerBase::GetScreen(ScreenType screenType) const {
	return screens.count(screenType) ? screens.at(screenType).get() : nullptr;
}

BaseScreen* ScreenManagerBase::GetActiveScreen() const {
	return (BaseScreen*)machine->GetActiveState();
}

bool ScreenManagerBase::Update(float dt) {
	return machine->Update(dt);
}

PushdownState::PushdownResult BaseScreen::OnUpdate(float dt, PushdownState** newState) {
	if (!isMenuDisplayed) {
		sceneNode->Update(dt);
	}
	return onStateChange(newState);
}

void BaseScreen::OnSleep() {
	command = ScreenCommand::None;
}