#include "GameScreen.h"
#include "SinglePlayerGame.h"
#include "GameOverScreen.h"
#include "Window.h"

using namespace NCL;
using namespace CSC8508;

bool GameScreen::sPauseCallback = false;

void NCL::CSC8508::GameScreen::OnAwake()
{
	isMenuDisplayed = false;
	isDebugDisplayed = false;
	LoadGame(screenManager->GetGameAssets());

	if (sceneNode)
	{
		sceneNode->GetPhysicsWorld()->setIsDebugRenderingEnabled(isDebugRenderingEnabled);
		sceneNode->GetPhysicsWorld()->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
		sceneNode->GetPhysicsWorld()->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB, true);

		Window::GetWindow()->LockMouseToWindow(true);
	}
}

void NCL::CSC8508::GameScreen::OnSleep()
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
		bisNetworkedGame = false;
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

void GameScreen::MenuFrame() {
#ifdef _WIN32
	ImGui::Begin("Painting Game");
	if (ImGui::Button("Resume")) {
		isMenuDisplayed = false;
	}
	if (ImGui::Button("Toggle Debug Lines")) {
		isDebugRenderingEnabled = !isDebugRenderingEnabled;
		sceneNode->GetPhysicsWorld()->setIsDebugRenderingEnabled(isDebugRenderingEnabled);
		isMenuDisplayed = false;
	}
	if (ImGui::Button("Debug Window")) {
		isDebugDisplayed = true;
		isMenuDisplayed = false;
	}
	if (ImGui::Button("Quit to Main Menu")) {
		command = ScreenCommand::TransitionToPreviousScreen;
	}
	if (ImGui::Button("Quit Game")) {
		command = ScreenCommand::Exit;
	}
	ImGui::End();
#endif
}

PushdownState::PushdownResult GameScreen::onStateChange(PushdownState** newState) {
	//add game-over game-win checks here:
	switch (command) {
		case ScreenCommand::TransitionToNextScreen:
			*newState = screenManager->GetScreen(ScreenType::GameOverScreen);
			//((GameOverScreen*)*newState)->SetWinner(((PaintingGame*)sceneNode)->GetWinner());
			return PushdownResult::Push;
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
