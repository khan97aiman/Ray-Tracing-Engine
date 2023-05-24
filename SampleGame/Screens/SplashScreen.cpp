#include "SplashScreen.h"
#include "Debug.h"

using namespace NCL;
using namespace CSC8599;

void SplashScreen::GuiWindow() {
	GuiObject* guiObject = screenManager->GetGuiObject();
	guiObject->CreateGuiWindow("Painting Game");
	guiObject->CreateButton("Play Game", [&]() { command = ScreenCommand::TransitionToNextScreen; });
	guiObject->CreateButton("Exit", [&]() { command = ScreenCommand::Exit; });
	guiObject->CloseGuiWindow();
}

PushdownState::PushdownResult SplashScreen::onStateChange(PushdownState** newState) {
	switch (command)
	{
		case ScreenCommand::TransitionToNextScreen: 
			*newState = screenManager->GetScreen(ScreenType::MainMenuScreen);
			return PushdownResult::Push;
		case ScreenCommand::Exit: 
			return PushdownResult::Pop;
		default: 
			return PushdownResult::NoChange;
	}
}