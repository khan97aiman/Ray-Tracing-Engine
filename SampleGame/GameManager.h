#pragma once
#include "ScreenManager.h"
#include "Configurations.h"
#include "GameAssets.h"
#include <PushdownMachine.h>

namespace NCL::CSC8599 {
	class GameManager {
	public:
		GameManager(Window* window);
		~GameManager();
		bool RunGame(float dt);

		static Configurations sConfig;
	protected:

		RendererBase* renderer;
		Assets::AssetLoader* assetLoader;
		GameAssets* gameAssets;
		ScreenManager* screenManager;
	};
}