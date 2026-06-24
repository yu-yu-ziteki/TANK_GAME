#include "Enemy.h"
#include "Engine\\Model.h"
#include <assert.h>
#include "Engine\\Input.h"
#include "Engine\\Debug.h"
#include "Engine\\Camera.h"
#include "Ground.h"


Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1)
{
	transform_.position_.x = (rand() % 50) - 25;
	transform_.position_.z = (rand() % 50) - 25;

}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);
	
}

void Enemy::Update()
{
	//レイキャストして、浮いてたら、地面に落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;//地面は０より下に掘られて作られている。そうじゃないときはもっと上から
	data.dir = { 0, -1, 0 };//真下に飛ばす
	Ground* pGround = (Ground*)FindObject("Gruond");//Groundオブジェクトを探す
	int hGroundModel{};//groundオブジェクトのモデルハンドルを得る
	Model::RayCast(hGroundModel, &data);//レイキャストして、地面に当たったかどうか、あたったときの距離や
	if (data.hit == true)
	{
		transform_.position_.y = -data.dist;
		//レイの発射位置から、地面までの距離を引いて、地面にピッタリつける
	}

}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

