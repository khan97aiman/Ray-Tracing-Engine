#pragma once
#include "GameObject.h"
#include "AnimationController.h"

namespace NCL {
	using namespace Rendering;
	using namespace CSC8599;

	class AnimatedObject : public GameObject {
	public:
		AnimatedObject(reactphysics3d::PhysicsCommon& physicsCommon, reactphysics3d::PhysicsWorld* physicsWorld, std::string objectName) : GameObject(physicsCommon, physicsWorld, objectName) {}
		virtual ~AnimatedObject();
		virtual void Update(float dt);
		void SetIsMoving(bool val) { isMoving = val; }
		bool GetIsMoving() const { return isMoving; }

		void SetAnimControler(const std::unordered_map<std::string, MeshAnimation*>& animations);

	protected:
		AnimationController* animationController = NULL;
		bool isMoving = false;
	};









}
