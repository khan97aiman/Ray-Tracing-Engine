#include "GameScreen.h"
#include "SinglePlayerGame.h"
#include "Window.h"

using namespace NCL;
using namespace CSC8599;

bool GameScreen::sPauseCallback = false;

void NCL::CSC8599::GameScreen::OnAwake()
{
	isMenuDisplayed = false;
	LoadGame(screenManager->GetGameAssets());

	if (sceneNode)
	{
		sceneNode->GetPhysicsWorld()->setIsDebugRenderingEnabled(isDebugRenderingEnabled);
		sceneNode->GetPhysicsWorld()->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
		sceneNode->GetPhysicsWorld()->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB, true);

		Window::GetWindow()->LockMouseToWindow(true);
	}
}

void NCL::CSC8599::GameScreen::OnSleep()
{
	delete sceneNode;
	sceneNode = nullptr;
}


void GameScreen::LoadGame(GameAssets* assets) {

	delete sceneNode;
	switch (command)
	{
	case ScreenCommand::CreateSinglePlayerGame:
		sceneNode = new SinglePlayerGame(assets);
		break;
#ifdef BUILD_NETWORKING
	case ScreenCommand::CreateNetworkedGameAsServer:
		sceneNode = new NetworkedGame(assets);
		((NetworkedGame*)(sceneNode))->StartAsServer();
		bisNetworkedGame = true;
		break;
	case ScreenCommand::CreateNetworkedGameAsClient:
		sceneNode = new NetworkedGame(assets);
		((NetworkedGame*)(sceneNode))->StartAsClient(127, 0, 0, 1);
		bisNetworkedGame = true;
		break;
#endif
	default:
		std::cout << "No instance of game could be created: No appropriate Command Selected." << std::endl;
	}
}

PushdownState::PushdownResult GameScreen::OnUpdate(float dt, PushdownState** newState) {
	if (sPauseCallback) {
		isMenuDisplayed = true;
		sPauseCallback = false;
	}


	return BaseScreen::OnUpdate(dt, newState);
}

void GameScreen::GuiWindow() {
	GuiObject* guiObject = screenManager->GetGuiObject();
	guiObject->CreateGuiWindow("Painting Game");
	guiObject->CreateButton("Resume", [&]() { isMenuDisplayed = false; });
	guiObject->CreateButton("Toggle Debug Lines", [&]() { 
		isDebugRenderingEnabled = !isDebugRenderingEnabled;
		sceneNode->GetPhysicsWorld()->setIsDebugRenderingEnabled(isDebugRenderingEnabled);
		isMenuDisplayed = false;
	});
	guiObject->CreateButton("Debug Window", [&]() {
		//isDebugDisplayed = true;
		isMenuDisplayed = false;
	});
	guiObject->CreateButton("Quit to Main Menu", [&]() {
		command = ScreenCommand::TransitionToPreviousScreen;
	});
	guiObject->CreateButton("Quit Game", [&]() {
		command = ScreenCommand::Exit;
	});
	guiObject->CloseGuiWindow();
}

PushdownState::PushdownResult GameScreen::onStateChange(PushdownState** newState) {
	switch (command) {
		case ScreenCommand::TransitionToPreviousScreen:
			return PushdownResult::Pop;
		case ScreenCommand::Exit:
			return PushdownResult::Reset1;
		default:
			return PushdownResult::NoChange;
	}
}

void GameScreen::GamePauseCallback() {
	sPauseCallback = true;
}
