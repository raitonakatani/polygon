#include "stdafx.h"
#include "Box.h"
#include "Player.h"

namespace
{
}

bool Box::Start()
{
	// 通常モデル
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

	m_renderingEngine->InitTextureTarget(m_number);
	m_renderingEngine->SpriteInit(m_modelRender.GetTkm()->m_albedo,m_number);

	m_player = FindGO<Player>("player");

	return true;
}
void Box::Update()
{
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();

	m_player = FindGO<Player>("player");
	startVector = m_player->GetStartVector();
	endVector = m_player->GetEndVector();

	if (g_pad[0]->IsPress(enButtonRB1) == true)
	{
		Vector3 posi = m_player->GetPosition();
		m_renderingEngine->SpriteDraw(posi,1, m_modelRender, m_number, reset, startVector, endVector);
	}
}
void Box::Render(RenderContext& rc)
{
	// 通常モデルを描画する
	m_modelRender.Draw(rc);
}