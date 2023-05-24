#include "MainMenuScreen.h"

using namespace NCL;
using namespace CSC8599;

void MainMenuScreen::GuiWindow() {
	GuiObject* guiObject = screenManager->GetGuiObject();
	guiObject->CreateGuiWindow("Painting Game");
	guiObject->CreateButton("Start Game", [&]() { command = ScreenCommand::CreateSinglePlayerGame; });
	guiObject->CreateButton("Exit", [&]() { command = ScreenCommand::TransitionToPreviousScreen; });
	guiObject->CloseGuiWindow();
}

PushdownState::PushdownResult MainMenuScreen::onStateChange(PushdownState** newState) {
	switch (command)
	{
	case ScreenCommand::CreateSinglePlayerGame:
	case ScreenCommand::CreateSplitScreenGame:
	case ScreenCommand::CreateNetworkedGameAsServer:
	case ScreenCommand::CreateNetworkedGameAsClient:
	{
		*newState = screenManager->GetScreen(ScreenType::GameScreen);
		((BaseScreen*)(*newState))->SetCommand(command);
		return PushdownResult::Push;
	}
	case  ScreenCommand::TransitionToPreviousScreen:
	{
		return PushdownResult::Pop;
	}
	default:
	{
		return PushdownResult::NoChange;
	}
	}
}
