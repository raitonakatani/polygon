#include "stdafx.h"
#include "Stairs.h"
#include "Player.h"


bool Stairs::Start()
{
	// モデルを読み込む。
	m_modelRender.Init("Assets/modelData/testModel/stairs.tkm", true);
	//モデルの座標を設定。
	m_modelRender.SetPosition(m_position);
	//モデルの回転を設定。
	//	m_modelRender.SetRotation(m_rotation);
	//モデルの大きさを設定。
	m_modelRender.SetScale(m_scale);
	//モデルの更新処理。
	m_modelRender.Update();
	//静的物理オブジェクトの初期化処理。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);


	m_renderingEngine = &g_renderingEngine;

	m_renderingEngine->InitTextureTarget(m_number);
	m_renderingEngine->SpriteInit(m_modelRender.GetTkm()->m_albedo, m_number);

	m_player = FindGO<Player>("player");


	return true;
}
void Stairs::Update()
{
	// モデルの座標を設定する
	m_modelRender.SetPosition(m_position);
	// モデルの大きさを設定する
	m_modelRender.SetScale(m_scale);
	// モデルを更新する
	m_modelRender.Update();

	// プレイヤーを探す
	m_player = FindGO<Player>("player");
	// 開始座標と終了座標を設定する
	m_startVector = m_player->GetStartVector();
	m_endVector = m_player->GetEndVector();

	// 攻撃されていた場合
	if (g_pad[0]->IsPress(enButtonRB1) == true)
	{
		// インクの処理を行う
		m_renderingEngine->SpriteDraw(1, m_modelRender, m_number, m_startVector, m_endVector);
	}
}
void Stairs::Render(RenderContext& rc)
{
	// モデルを描画する。
	m_modelRender.Draw(rc);
}