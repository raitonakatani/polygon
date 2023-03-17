#include "stdafx.h"
#include "Triangle.h"
#include "Player.h"

namespace
{
}

bool Triangle::Start()
{
	m_position.y -= 30.0f;
	// モデルを読み込む
	m_modelRender.Init("Assets/modelData/testModel/triangle.tkm", false);
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

	return true;
}
void Triangle::Update()
{
	// モデルの更新処理
	m_modelRender.Update();

}
void Triangle::Render(RenderContext& rc)
{
	// 通常モデルを描画する
	m_modelRender.Draw(rc);
}