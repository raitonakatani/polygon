#include "stdafx.h"
#include "Floor.h"

bool Floor::Start()
{
	m_modelRender.InitUVScroll("Assets/modelData/testModel/yuka.tkm");
	m_position.y += 42.0f;
	//モデルの座標を設定。
	m_modelRender.SetPosition(m_position);
	//モデルの回転を設定。
	m_modelRender.SetRotation(m_rotation);
	//モデルの大きさを設定。
	m_modelRender.SetScale(Vector3::One*1.5f);
	//モデルの更新処理。
	m_modelRender.Update();
	//静的物理オブジェクトの初期化処理。
//	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
//	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Ground);




	return true;
}
void Floor::Update()
{
	return;
}
void Floor::Render(RenderContext& rc)
{
	// モデルを描画する。
	m_modelRender.Draw(rc);
}