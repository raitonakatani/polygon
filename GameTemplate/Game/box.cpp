#include "stdafx.h"
#include "Box.h"
#include "Player.h"

namespace
{
}

bool Box::Start()
{
	// 通常モデル
	m_modelRender.Init("Assets/modelData/box.tkm", false);
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

//	m_sprite.Init("Assets/sprite/white.DDS",256.0f, 256.0f);

//	m_player = FindGO<Player>("player");

	//g_renderingEngine.SpriteInit(
	//	m_modelRender.GetTkm()->m_albedo,
	//	inkspriteinitdata,
	//	spriteinitdata,
	//	inksprite,
	//	sprite
	//	);

	return true;
}
void Box::Update()
{
	m_player = FindGO<Player>("player");
	startVector = m_player->GetStartVector();
	endVector = m_player->GetEndVector();




}
void Box::Render(RenderContext& rc)
{
	// 通常モデルを描画する
	m_modelRender.Draw(rc);
	//	m_sprite.Draw(rc);
	//g_renderingEngine.SpriteDraw(m_modelRender,POS,UV,startVector,endVector,spriteinitdata,sprite);
}