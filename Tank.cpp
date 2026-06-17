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
	const float CAM_HEIGHT_BIAS = 0.2f;//カメラの高さのバイアス
	const float TPS_CAM_HEIGHT_BIAS = 5.0f;//カメラの高さのバイアス
	const float TPS_CAM_DEPTH_BIAS = 9.0f;

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
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//Load：読み込み
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//Y軸回転行列を作る
	//XMConvertTransformCordは、ベクトルを行列変換で変換する関数。回転行列をベクトルにかけると、回転したベクトルを得られる。
	XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);//

	if (Input::IsKeyDown(DIK_C))
	{
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;
		//0,1,2が切り替わってるか確認
	}
	switch (camType_)
	{
	case FIXED_CAM:
		//固定カメラの処理
		SetFixedCam();
		break;
	case TPS_CAM:
	{
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = camPos.y + TPS_CAM_HEIGHT_BIAS;
		camPos.z = camPos.z - TPS_CAM_DEPTH_BIAS;
		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);
		//三人称視点カメラの処理
	}
		break;
	case TPS_CAMROT:
	{
		XMFLOAT3 camPos;
		XMVECTOR vCAM = { 0.0f, 5.0f, -10.0f, 0.0f };//カメラの位置
		vCAM = XMVector3TransformCoord(vCAM, matRot);
		XMStoreFloat3(&camPos, vPos + vCAM);
		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);

	}
		//三人称視点カメラ(回転)の処理
		break;
	case FPS_CAM:
		//一人称視点カメラ処理
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = camPos.y + CAM_HEIGHT_BIAS;
		Camera::SetPosition(camPos);//カメラの位置をタンクと同じにする
		XMFLOAT3 camTarget;//カメラの注視点
		XMStoreFloat3(&camTarget, vPos + vMove);//カメラの注視点をタンク前方にする
		Camera::SetTarget(camTarget);
		break;
	}
	if (Input::IsKey(DIK_A)) {
		transform_.rotate_.y -= 2.0f;
	}
	if (Input::IsKey(DIK_D)) {
		transform_.rotate_.y += 2.0f;
	}

	if (Input::IsKey(DIK_W)) {
	
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
	int hGroundModel{};//groundオブジェクトのモデルハンドルを得る
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

void Tank::SetFixedCam()
{
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 20, -30));
}
