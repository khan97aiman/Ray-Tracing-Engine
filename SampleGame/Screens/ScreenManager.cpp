#include "ScreenManager.h"
#include "SplashScreen.h"
#include "MainMenuScreen.h"
#include "GameScreen.h"

using namespace NCL;
using namespace CSC8599;


ScreenManager::ScreenManager(GameAssets* assets, GuiObject* guiObject) : ScreenManagerBase(assets, guiObject) {
	LoadScreens();
	machine = std::make_unique<PushdownMachine>((PushdownState*)GetScreen(ScreenType::SplashScreen));
}

void ScreenManager::LoadScreens() {
	screenSceneNodes.emplace(std::make_pair(ScreenType::SplashScreen, std::make_unique<SceneNode>(assets->GetMesh("quadMesh"), assets->GetShader("screenShader"), assets->GetTexture("splashScreenTex"))));
	screenSceneNodes.emplace(std::make_pair(ScreenType::MainMenuScreen, std::make_unique<SceneNode>(assets->GetMesh("quadMesh"), assets->GetShader("screenShader"), assets->GetTexture("mainMenuScreenTex"))));
	screenSceneNodes.emplace(std::make_pair(ScreenType::GameOverScreen, std::make_unique<SceneNode>(assets->GetMesh("quadMesh"), assets->GetShader("screenShader"), assets->GetTexture("gameOverScreenTex"))));

	screens.insert(std::make_pair(ScreenType::SplashScreen, std::make_unique<SplashScreen>(this, screenSceneNodes.at(ScreenType::SplashScreen).get())));
	screens.insert(std::make_pair(ScreenType::MainMenuScreen, std::make_unique<MainMenuScreen>(this, screenSceneNodes.at(ScreenType::MainMenuScreen).get())));
	screens.insert(std::make_pair(ScreenType::GameScreen, std::make_unique<GameScreen>(this)));
}