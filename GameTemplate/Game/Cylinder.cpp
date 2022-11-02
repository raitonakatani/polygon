#include "stdafx.h"
#include "Cylinder.h"
#include "Player.h"

namespace
{
}

bool Cylinder::Start()
{
	// 通常モデル
	m_modelRender.Init("Assets/modelData/Cylinder.tkm", false);
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
void Cylinder::Update()
{
	//三角形の座標が入っているリストを持ってくる。
	std::vector<nsK2EngineLow::TkmFile::VectorBuffer> bufferList = m_modelRender.GetTkm()->GetBuffer();


	Vector3 startVector;
	Vector3 endVector;
	m_player = FindGO<Player>("player");
	startVector = m_player->GetStartVector();
	endVector = m_player->GetEndVector();

	//平面と線分の交点を求める。　POS（交点の座標）、vector3d(線分始点)、vector3dend(線分終点)、ポリゴンの3頂点
	m_modelRender.IntersectPlaneAndLine(POS, m_uv, startVector, endVector, bufferList);
	auto Vector = POS;
	auto Vector2 = POS;

}
void Cylinder::Render(RenderContext& rc)
{
	// 通常モデルを描画する
	m_modelRender.Draw(rc);
}