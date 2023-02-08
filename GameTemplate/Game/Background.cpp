#include "stdafx.h"
#include "Background.h"
#include "Player.h"
#include "Game.h"

Background::~Background()
{
}

bool Background::Start()
{
	m_modelRender.Init("Assets/modelData/testModel/floor.tkm", true);
	//モデルの座標を設定。
	m_modelRender.SetPosition(m_position);
	//モデルの回転を設定。
	m_modelRender.SetRotation(m_rotation);
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
	m_game = FindGO<Game>("game");

	return true;
}
void Background::Update()
{
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();

	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");
	startVector = m_player->GetStartVector();
	endVector = m_player->GetEndVector();

	if (g_pad[0]->IsPress(enButtonRB1) == true || m_game->m_paintnumber >= 41)
	{
		Vector3 posi = m_player->GetPosition();
		m_renderingEngine->SpriteDraw(posi, 1, m_modelRender, m_number, m_game->m_paintnumber, startVector, endVector);
	}

	
	return;
}
void Background::Render(RenderContext& rc)
{
	// モデルを描画する。
	m_modelRender.Draw(rc);
}