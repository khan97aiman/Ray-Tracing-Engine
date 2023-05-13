#pragma once
#include "ScreenManager.h"

namespace NCL {
	namespace CSC8599 {
		class SplashScreen : public BaseScreen
		{
		public:
			SplashScreen(ScreenManager* screenManager, SceneNode* sceneNode) : BaseScreen(screenManager, sceneNode) {
				screenType = ScreenType::SplashScreen;
			}
		protected:
			virtual void MenuFrame();
			virtual PushdownResult onStateChange(PushdownState** newState);
		};

	}
}
