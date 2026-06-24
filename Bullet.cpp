#include "Bullet.h"
#include "Engine\\Model.h"
#include <assert.h>
#include "Engine\\Input.h"
#include "Engine\\Debug.h"

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"),hModel_(-1), move_(XMFLOAT3(0, 0, 0))
{
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Bullet.fbx");
	assert(hModel_ >= 0);
}

void Bullet::Update()
{
	transform_.position_.y -= 0.08f;
	//transform_.position_ = transform_.position_ + move_;//弾の進行方向に移動する
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//ロード：読み込み
	XMVECTOR vMove = XMLoadFloat3(&move_);//ロード：読み込み
	vPos = vPos + vMove;//弾の進行方向に移動する
	XMStoreFloat3(&transform_.position_, vPos);//ストア：書き込み
	//transform_.position_.x += move_.x;
	//transform_.position_.y += move_.y;
	//transform_.position_.z += move_.z;
	if (transform_.position_.y < -50.0f) {
		KillMe();
	}


}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}
