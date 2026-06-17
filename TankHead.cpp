#include "TankHead.h"
#include "Engine\\Model.h"
#include <assert.h>
#include "Engine\\Input.h"
#include "Engine\\Debug.h"
#include "Tank.h"

TankHead::TankHead(GameObject* parent)
	:GameObject(parent, "Tank"), hModel_(-1)
{
}

void TankHead::Initialize()
{
	hModel_ = Model::Load("TankHead.fbx");
	assert(hModel_ >= 0);
}

void TankHead::Update()
{
	transform_.position_ = {5.0f, 3.0f, 5.0f};
	Tank* pTank = (Tank*)FindObject("Tank");//Tankオブジェクトを探す
	
	
}

void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
