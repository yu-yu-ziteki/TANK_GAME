#include "TankHead.h"
#include "Engine\\Model.h"
#include <assert.h>
#include "Engine\\Input.h"
#include "Engine\\Debug.h"
#include "Tank.h"
#include "Bullet.h"
TankHead::TankHead(GameObject* parent)
	:GameObject(parent, "TankHead"), hModel_(-1)
{
}

void TankHead::Initialize()
{
	hModel_ = Model::Load("TankHead.fbx");
	assert(hModel_ >= 0);
}

void TankHead::Update()
{
	//Tank* pTank = (Tank*)FindObject("Tank");//Tankオブジェクトを探す
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= 2.0f;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += 2.0f;
	}
	if (Input::IsKeyDown(DIK_SPACE)) {
		const float BULLET_SPEED = 0.2f;//弾のスピード
		XMFLOAT3 cannotTop = Model::GetBonePosition(hModel_, "Top");
		XMFLOAT3 cannotRoot = Model::GetBonePosition(hModel_, "Root");
		XMVECTOR vTop = XMLoadFloat3(&cannotTop);
		XMVECTOR vRoot = XMLoadFloat3(&cannotRoot);
		XMVECTOR vMove = XMVectorSubtract(vTop, vRoot);//法大の向きベクトルを作る
		//XMVECTOR vMove = vTop - vRoot; //砲台の向きベクトルを作る
		vMove = 0.2f * vMove;
		XMFLOAT3 move;
		XMStoreFloat3(&move, vMove); //


		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());//親をタンクにして弾を出す
		pBullet->SetMoveVector(move);
		pBullet->SetPosition(cannotTop);//弾の位置を砲台の先端に持ってくる

	}


}

void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
