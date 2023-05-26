#include "Player.h"
#include <Debug.h>

using namespace NCL;
using namespace CSC8599;

void Player::Update(float dt) {
	PlayerBase::Update(dt);
	AnimatedObject::Update(dt);
}

void Player::SetMemberVariables() {
	if (camera) {
		camera->SetBasicCameraParameters(this, 0.1f, 500.0f);
		camera->SetPerspectiveCameraParameters(Window::GetWindow()->GetScreenAspect());
		camera->SetThirdPersonCamera();
	}
	layer = Layer::Player;
}
