#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "Playerscene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Ground>(this);//親をPlaySceneにしてじめんを生成
	Instantiate<Tank>(this);//親をPlaySceneにして洗車を生成
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
