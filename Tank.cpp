#include "Tank.h"
#include "Engine\\Model.h"
#include <assert.h>
#include "Engine\\Input.h"

Tank::Tank(GameObject* parent)
	:GameObject(parent, "GameObject"), hModel_(-1)
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
	assert(hModel_ >= 0);
}

void Tank::Update()
{
	if (Input::IsKey(DIK_W)) {
		transform_.position_.z += 0.5f;
	}
	if (Input::IsKey(DIK_A)) {
		transform_.rotate_.y -= 0.2f;
	}

	if (Input::IsKey(DIK_D)) {
		transform_.rotate_.y += 0.2f;
	}
}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}
