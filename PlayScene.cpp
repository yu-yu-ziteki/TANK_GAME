#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "TankHead.h"
#include "Enemy.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "Playerscene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Ground>(this);//親をPlaySceneにしてじめんを生成
	Instantiate<Tank>(this);//親をPlaySceneにして洗車を生成
	for (int i = 0;i <= 10;i++) {
		Instantiate<Enemy>(this);
	}
	//Instantiate<TankHead>(this);
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
