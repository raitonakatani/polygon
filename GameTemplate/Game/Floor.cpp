#include "stdafx.h"
#include "Floor.h"

bool Floor::Start()
{
	m_modelRender.InitUVScroll("Assets/modelData/testModel/yuka.tkm");
	//モデルの座標を設定。
	m_modelRender.SetPosition(m_position);
	//モデルの回転を設定。
	m_modelRender.SetRotation(m_rotation);
	//モデルの大きさを設定。
	m_modelRender.SetScale(Vector3::One);
	//モデルの更新処理。
	m_modelRender.Update();
	//静的物理オブジェクトの初期化処理。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Ground);




	return true;
}
void Floor::Update()
{
	Vector3 BufferPosition[3];

	//三角形の座標持ってくる。
	const auto& bufferList = m_modelRender.GetTkm()->GetBuffer();

	BufferPosition[0] = bufferList[0].buffer[0];
	BufferPosition[1] = bufferList[0].buffer[1];
	BufferPosition[2] = bufferList[0].buffer[2];


	return;
}
void Floor::Render(RenderContext& rc)
{
	// モデルを描画する。
	m_modelRender.Draw(rc);
}