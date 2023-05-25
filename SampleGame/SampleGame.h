
#pragma once
#include "Player.h"
#include "GameAssets.h"
#include <Camera.h>
#include <GameWorld.h>
#include <DirectionalLight.h>
#include <SpotLight.h>
#include <PointLight.h>
#include "SceneNode.h"
#include "HudElement.h"

namespace NCL {
	namespace CSC8599 {
		class SampleGame : public SceneNode {
		public:
			SampleGame(GameAssets* assets);
			~SampleGame();
			virtual void Update(float dt);
			void Restart() { InitWorld(); }
			virtual GameWorld* GetWorld() const { return world; }
			virtual reactphysics3d::PhysicsWorld* GetPhysicsWorld() const override { return physicsWorld; }
			virtual void OperateOnCameras(CameraFunc f);

		protected:
			virtual void InitWorld();
			Player* CreatePlayer(Vector3 position);
			virtual Player* AddPlayer(Vector3 position) = 0;
			GameWorld* world;

		
			//Create a physics world 
			reactphysics3d::PhysicsCommon physicsCommon;
			reactphysics3d::PhysicsWorld* physicsWorld = NULL;
			GameAssets* assets;

			//containers for lights
			std::vector<DirectionalLight> directionalLights;
			std::vector<PointLight> pointLights;
			std::vector<SpotLight> spotLights;

			//container for cameras
			std::vector<Camera*> activeCameras;
			uint32_t seed;
		};
	}
}