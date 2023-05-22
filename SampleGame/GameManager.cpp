#include "GameManager.h"
#include "SplashScreen.h"
#include "MainMenuScreen.h"

using namespace NCL;
using namespace CSC8599;

Configurations GameManager::sConfig = Configurations();

GameManager::GameManager(Window* window) {
	renderer = sConfig.rendererFactory->createRenderer(*window);
	assetLoader = sConfig.assetLoaderFactory->createAssetLoader();
	guiInterface = sConfig.guiFactory->CeateGuiObject();
	gameAssets = new GameAssets(assetLoader);
	screenManager = new ScreenManager(gameAssets);
	renderer->BindDebugShader(gameAssets->GetShader("debugShader")); //find a way to omit this
}

GameManager::~GameManager() {
	delete renderer;
	delete screenManager;
	delete assetLoader;
	delete gameAssets;
	delete guiInterface;
}

bool GameManager::RunGame(float dt) {
	bool isRunning =  screenManager->Update(dt);
	renderer->BindScreen(screenManager->GetActiveScreen());
	renderer->Render();
	Debug::UpdateRenderables(dt);
	return isRunning;
}

