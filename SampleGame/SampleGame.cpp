#include "SampleGame.h"
#include <Terrain.h>
#include <Debug.h>
#include "Box.h"
#include "Floor.h"
#include "Assets.h"

#include "AnimationController.h"
#include "Ink.h"
#include <iostream>
#include "GameTimer.h"
#include "GameScreen.h"

using namespace NCL;
using namespace CSC8508;

PaintingGame::PaintingGame(GameAssets* assets) {
	this->assets = assets;
	physicsWorld = physicsCommon.createPhysicsWorld();
	physicsWorld->setIsGravityEnabled(true);
	seed = time(0);
	world = new GameWorld(physicsWorld);
	InitWorld();
	//renderer->settings.SetIsDebugRenderingModeEnabled(true);
	//renderer->settings.debugRendererSettings.SetIsCollisionShapeDisplayed(true);
	//renderer->settings.debugRendererSettings.SetIsBroadPhaseAABBDisplayed(true);
	//world->AddEventListener(new GameEventListener(&world->GetPhysicsWorld(), world));
}

PaintingGame::~PaintingGame() {
	delete world;
	physicsCommon.destroyPhysicsWorld(physicsWorld);
}

void PaintingGame::OperateOnCameras(CameraFunc f) {
	for (Camera* cam : activeCameras) {
		f(cam);
	}
}

void PaintingGame::InitWorld() {
	world->ClearAndErase();

	world->AddGameObject(new Floor(physicsCommon, physicsWorld, Vector3(0, 0, 0), assets->GetMesh("floorMesh"), assets->GetTexture("basicTex"), assets->GetShader("basicShader"), 1));
}

void PaintingGame::Update(float dt) {
	world->UpdateWorld(dt);
	physicsWorld->update(dt);
}

Player* PaintingGame::CreatePlayer(NCL::Maths::Vector3 position) {
	std::unordered_map<std::string, MeshAnimation*> animations;
	animations.insert(std::make_pair("idleAnimation", assets->GetMeshAnimation("mainCharIdleAnim")));
	animations.insert(std::make_pair("moveAnimation", assets->GetMeshAnimation("mainCharRunAnim")));
	Player* player = NULL;
	
	world->AddGameObject(player);
	return player;
}
