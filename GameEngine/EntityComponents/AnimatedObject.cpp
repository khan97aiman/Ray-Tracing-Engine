#include "AnimatedObject.h"

using namespace NCL;
using namespace CSC8599;


AnimatedObject::~AnimatedObject()
{
	delete animationController;
}



void AnimatedObject::Update(float dt) {
	animationController->Update(dt);
}

void NCL::AnimatedObject::SetAnimControler(const std::unordered_map<std::string, MeshAnimation*>& animations) {
	animationController = new AnimationController(this, animations);
	renderObject->SetAnimationController(animationController);
	renderObject->SetRigged(true);
}
