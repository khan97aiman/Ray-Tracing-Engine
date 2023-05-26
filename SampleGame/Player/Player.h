#pragma once
#include <PlayerBase.h>
#include "Window.h"
#include "Utils.h"
#include "Vector3.h"
#include "AnimationController.h"


namespace NCL {
	using namespace Rendering;
	using namespace CSC8599;
	class Player : public PlayerBase {
	public:
		//TextureBase Constructor
		Player(reactphysics3d::PhysicsCommon& physicsCommon, reactphysics3d::PhysicsWorld* physicsWorld, Vector3 position, MeshGeometry* mesh, 
			TextureBase* texture, ShaderBase* shader, const std::unordered_map<std::string, MeshAnimation*>& animations, int size,
			std::string objectName = "player")
			: PlayerBase(physicsCommon, physicsWorld, position, mesh, texture, shader, animations, size, objectName) {
			SetMemberVariables();
		}
		//Mesh Material Constructor
		Player(reactphysics3d::PhysicsCommon& physicsCommon, reactphysics3d::PhysicsWorld* physicsWorld, Vector3 position, MeshGeometry* mesh,
			MeshMaterial* meshMaterial, ShaderBase* shader, const std::unordered_map<std::string, MeshAnimation*>& animations, int size,
			std::string objectName = "player")
			: PlayerBase(physicsCommon, physicsWorld, position, mesh, meshMaterial, shader, animations, size, objectName) {
			SetMemberVariables();
		}
		virtual void Update(float dt);

		bool GetHasRespawned() { return hasRespawned; }
		void SetHasRespawnedTrue() { hasRespawned = true; }
		void SetHasRespawnedFalse() { hasRespawned = false; }
		float GetRespawnTimer() { return respawnTimer; }
		void SetRespawnTimer(float dt) { respawnTimer += dt; }
		void ResetSpawnTimer() { respawnTimer = 0.0f; }
	protected:
		void SetMemberVariables();
		int playerTeam; // 0 is Red, 1 is Blue
		const Vector3 gunOffset = Vector3(0.5, 1, -4);
		bool hasRespawned = false;
		float respawnTimer = 0.0f;
	};
}