#pragma once
#include "ScreenManager.h"

namespace NCL {
	namespace CSC8599 {
		class MainMenuScreen : public BaseScreen
		{
		public:
			MainMenuScreen(ScreenManager* screenManager, SceneNode* sceneNode) : BaseScreen(screenManager, sceneNode) {
				screenType = ScreenType::MainMenuScreen;
			}
		protected:
			virtual void GuiWindow() override;
			virtual PushdownResult onStateChange(PushdownState** newState);
		};

	}
}
