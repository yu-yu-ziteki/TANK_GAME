#include "Tank.h"
#include "Engine\\Model.h"
#include <assert.h>
#include "Engine\\Input.h"
#include "Engine\\Debug.h"
#include "Engine\\Camera.h"
#include "Ground.h"

namespace
{
	XMVECTOR vFront = { 0, 0, 1, 0 }; //タンクの前方向ベクトル
	const float moveSpeed = 0.5f;
	enum CAM_TYPE
	{
		FIXED_CAM,//固定カメラ
		TPS_CAM,//三人称移転
		TPS_CAMROT,//三人称視点カメラ（回転）
		FPS_CAM, //一人称視点カメラ
		CAM_TYPE_MAX
	};
}
//タンクのボディを表すクラス

Tank::Tank(GameObject* parent)
	:GameObject(parent, "Tank"), hModel_(-1), camType_(FIXED_CAM)
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
	assert(hModel_ >= 0);
}

void Tank::Update()
{
	if (Input::IsKeyDown(DIK_C))
	{
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;
		//0,1,2が切り替わってるか確認
	}
	switch (camType_)
	{
	case FIXED_CAM:
		Camera::SetTarget(XMFLOAT3(0, 0, 0));
		Camera::SetPosition(XMFLOAT3(0, 20, -30));
		//固定カメラの処理
		break;
	case TPS_CAM:
		//三人称視点カメラの処理
		break;
	case TPS_CAMROT:
		//三人称視点カメラ(回転)の処理
		break;
	case FPS_CAM:
		//一人称視点カメラ処理
		break;
	}
	if (Input::IsKey(DIK_A)) {
		transform_.rotate_.y -= 1.0f;
	}
	if (Input::IsKey(DIK_D)) {
		transform_.rotate_.y += 1.0f;
	}

	if (Input::IsKey(DIK_W)) {
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//Load：読み込み
		XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//Y軸回転行列を作る
		//XMConvertTransformCordは、ベクトルを行列変換で変換する関数。回転行列をベクトルにかけると、回転したベクトルを得られる。
		XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);//
		vPos = vPos + moveSpeed * vMove;
		XMStoreFloat3(&transform_.position_, vPos);//Store：書き込み
	}
	if (Input::IsKey(DIK_S)) {
		//	transform_.position_.z -= 0.3f;
	}
	Debug::Log("camType = ");
	Debug::Log("camType, ", true);
	//レイキャストして、浮いてたら、地面に落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;//地面は０より下に掘られて作られている。そうじゃないときはもっと上から
	data.dir = { 0, -1, 0 };//真下に飛ばす
	Ground* pGround = (Ground*)FindObject("Gruond");//Groundオブジェクトを探す
	int hGroundModel;//groundオブジェクトのモデルハンドルを得る
	Model::RayCast(hGroundModel, &data);//レイキャストして、地面に当たったかどうか、あたったときの距離や
	if (data.hit == true)
	{
		transform_.position_.y = - data.dist;
		//レイの発射位置から、地面までの距離を引いて、地面にピッタリつける
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
