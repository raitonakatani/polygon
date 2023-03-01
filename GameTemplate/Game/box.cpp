#include "stdafx.h"
#include "Box.h"
#include "Player.h"

namespace
{
	int PAD = 0;		// ゲームパッドのナンバー
	int PLAYER = 1;		// キャラクターの番号 プレイヤーは1　エネミーは0
}

bool Box::Start()
{
	// モデルの読み込み
	m_modelRender.Init("Assets/modelData/testModel/box.tkm", false);
	// モデルの座標を設定。
	m_modelRender.SetPosition(m_position);
	// モデルの回転を設定。
	m_modelRender.SetRotation(m_rotation);
	// モデルの大きさを設定。
	m_modelRender.SetScale(m_scale);
	// モデルの更新処理。
	m_modelRender.Update();
	// 静的物理オブジェクトの初期化処理。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);

	m_renderingEngine = &g_renderingEngine;
	// レンダーターゲットを作成する。
	m_renderingEngine->InitTextureTarget(m_number);
	// テクスチャを初期化する。
	m_renderingEngine->SpriteInit(m_modelRender.GetTkm()->m_albedo, m_number);

	// オブジェクトのインスタンスを探して持ってくる。
	m_player = FindGO<Player>("player");

	return true;
}

void Box::Update()
{
	// インクのレンダリング処理
	InkRendering();
	// モデルの座標を設定。
	m_modelRender.SetPosition(m_position);
	// モデルの回転を設定。
	m_modelRender.SetRotation(m_rotation);
	// モデルの大きさを設定。
	m_modelRender.SetScale(m_scale);
	// モデルの更新処理。
	m_modelRender.Update();
}

void Box::InkRendering()
{
	// オブジェクトのインスタンスを探して持ってくる。
	m_player = FindGO<Player>("player");
	// 開始座標を取得する
	m_startVector = m_player->GetStartVector();
	// 終了座標を取得する
	m_endVector = m_player->GetEndVector();
	// RB1(攻撃)ボタンが押されていたら
	if (g_pad[PAD]->IsPress(enButtonRB1) == true)
	{
		// インクのテクスチャをオフスクリーンレンダリングする。
		m_renderingEngine->SpriteDraw(PLAYER, m_modelRender, m_number, m_startVector, m_endVector);
	}
}

void Box::Render(RenderContext& rc)
{
	// 通常モデルを描画する
	m_modelRender.Draw(rc);
}