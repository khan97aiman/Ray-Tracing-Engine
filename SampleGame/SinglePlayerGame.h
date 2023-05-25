#pragma once
#include "SampleGame.h"
#include <PlayerController.h>

namespace NCL {
	namespace CSC8599 {

		class SinglePlayerGame : public SampleGame {
		public:
			SinglePlayerGame(GameAssets* assets);
			virtual ~SinglePlayerGame();
			void Update(float dt) override;
		protected:
			Player* AddPlayer(Vector3 position) override;
			Player* player = NULL;
			PlayerController* playerController;
		};
	}
}
