#pragma once
#include "GameAssets.h"
#include <ScreenManagerBase.h>

namespace NCL::CSC8599 {
	
	class ScreenManager : public ScreenManagerBase {
	public:
		ScreenManager(GameAssets* assets, GuiObject* guiObject);
		void LoadScreens();
	};
}