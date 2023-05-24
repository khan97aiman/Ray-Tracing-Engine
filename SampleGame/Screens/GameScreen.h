#pragma once
#include "ScreenManager.h"

namespace NCL {
	namespace CSC8599 {
		class GameScreen : public BaseScreen
		{
		public:
			GameScreen(ScreenManager* screenManager, SceneNode* sceneNode = NULL) : BaseScreen(screenManager, sceneNode) {
				screenType = ScreenType::GameScreen;
			}
			void OnAwake() override;
			void OnSleep() override;
			PushdownResult OnUpdate(float dt, PushdownState** newState) override;

			static void GamePauseCallback();
		protected:
			void LoadGame(GameAssets* assets);
			virtual void GuiWindow() override;
			virtual PushdownResult onStateChange(PushdownState** newState);
			

		protected:
			bool isDebugRenderingEnabled = false;
			static bool sPauseCallback;
		};

	}
}
