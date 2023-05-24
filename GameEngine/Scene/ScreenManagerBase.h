#pragma once
#include "SceneNode.h"
#include "PushdownState.h"
#include "PushdownMachine.h"
#include <GuiObject.h>
#include "GameAssets.h"

namespace NCL::CSC8599 {
	class BaseScreen;
	enum class ScreenType {
		None,
		SplashScreen,
		LoadingScreen,
		MainMenuScreen,
		GameScreen,
		GameOverScreen,
	};
	enum class ScreenCommand {
		None,
		TransitionToNextScreen,
		TransitionToPreviousScreen,
		CreateSinglePlayerGame,
		CreateSplitScreenGame,
		CreateNetworkedGameAsServer,
		CreateNetworkedGameAsClient,
		Exit,
	};
	class ScreenManagerBase {
	public:
		ScreenManagerBase(GameAssets* assets, GuiObject* guiObject) : assets(assets), guiObject(guiObject) {};
		BaseScreen* GetScreen(ScreenType screenType) const;
		GameAssets* GetGameAssets() const { return assets; }
		GuiObject* GetGuiObject() const { return guiObject; }
		BaseScreen* GetActiveScreen() const;
		bool Update(float dt);
	protected:
		std::unordered_map<ScreenType, std::unique_ptr<BaseScreen>> screens;
		std::unordered_map<ScreenType, std::unique_ptr<SceneNode>> screenSceneNodes;
		std::unique_ptr<PushdownMachine> machine;
		GameAssets* assets = NULL;
		GuiObject* guiObject = NULL;
	};
	class BaseScreen : public PushdownState
	{
	public:
		BaseScreen(ScreenManagerBase* screenManager, SceneNode* sceneNode = NULL) : screenManager(screenManager), sceneNode(sceneNode) {}
		virtual ~BaseScreen() {}
		PushdownResult OnUpdate(float dt, PushdownState** newState) override;
		void OnAwake() override {};
		virtual void OnSleep();
		void SetCommand(ScreenCommand command) { this->command = command; };
		SceneNode* GetSceneNode() const { return sceneNode; }
		ScreenType GetScreenType() const { return screenType; }
		void RenderGui() { screenManager->GetGuiObject()->Render([&]() { this->GuiWindow(); }); }
	protected:
		virtual void GuiWindow() = 0;
		virtual PushdownResult onStateChange(PushdownState** newState) = 0;
		SceneNode* sceneNode = NULL;
		bool isMenuDisplayed = true;
		ScreenCommand command = ScreenCommand::None;
		ScreenManagerBase* screenManager;
		ScreenType screenType = ScreenType::None;
	};
}