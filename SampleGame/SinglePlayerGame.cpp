#include "SinglePlayerGame.h"
#include "GameManager.h"
#include "PlayerControllers.h"

using namespace NCL;
using namespace CSC8599;

SinglePlayerGame::SinglePlayerGame(GameAssets * assets) : PaintingGame(assets) {
		GameManager::sConfig.playerControllerFactory = new Win32PlayerControllerFactory();
	AddPlayer(Vector3(13.0f, 4.2, 34.0f));
}

SinglePlayerGame::~SinglePlayerGame() {
	delete playerController;
}


Player* SinglePlayerGame::AddPlayer(Vector3 position) {
	player = CreatePlayer(position);
	activeCameras.push_back(player->GetCamera());
	playerController = GameManager::sConfig.playerControllerFactory->createPlayerController(player);
	return player;
}

void SinglePlayerGame::Update(float dt) {
	playerController->Update(dt);
	Window::GetWindow()->LockMouseToWindow(true);
	PaintingGame::Update(dt);
}