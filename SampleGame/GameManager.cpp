#include "GameManager.h"
#include "SplashScreen.h"
#include "MainMenuScreen.h"

using namespace NCL;
using namespace CSC8599;

Configurations GameManager::sConfig = Configurations();

GameManager::GameManager(Window* window) {
	renderer = sConfig.rendererFactory->CreateRenderer(*window);
	assetLoader = sConfig.assetLoaderFactory->CreateAssetLoader();
	guiObject = sConfig.guiFactory->CeateGuiObject();
	gameAssets = new SampleGameAssets(assetLoader);
	screenManager = new ScreenManager(gameAssets, guiObject);
	renderer->BindDebugShader(gameAssets->GetShader("debugShader"));
}

GameManager::~GameManager() {
	delete renderer;
	delete screenManager;
	delete assetLoader;
	delete gameAssets;
	delete guiObject;
}

bool GameManager::RunGame(float dt) {
	bool isRunning =  screenManager->Update(dt);
	renderer->BindScreen(screenManager->GetActiveScreen());
	renderer->Render();
	Debug::UpdateRenderables(dt);
	return isRunning;
}

