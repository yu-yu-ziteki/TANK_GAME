#pragma once
#include "Engine/GameObject.h"

//テストシーンを管理するクラス
class Bullet
	: public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Bullet(GameObject* parent);
	~Bullet(){}

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	void SetMoveVector(XMFLOAT3 move) { move_ = move; }//弾の進行方向をリセットする関数

private:
	int hModel_;    //タンクモデルのハンドル
	XMFLOAT3 move_;//弾の進行方向

};