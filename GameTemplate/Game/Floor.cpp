#include "stdafx.h"
#include "Floor.h"

namespace {
	const Vector3 MODEL_SCALE = { 1.5f,1.5f,1.5f };		// モデルの大きさ
	const float	  YPOSI = 42.0f;						// Y座標
}

bool Floor::Start()
{
	// モデルを読み込む
	m_modelRender.InitUVScroll("Assets/modelData/testModel/yuka.tkm");
	m_position.y += YPOSI;
	//モデルの座標を設定。
	m_modelRender.SetPosition(m_position);
	//モデルの回転を設定。
	m_modelRender.SetRotation(m_rotation);
	//モデルの大きさを設定。
	m_modelRender.SetScale(MODEL_SCALE);
	//モデルの更新処理。
	m_modelRender.Update();

	return true;
}
void Floor::Update()
{
}
void Floor::Render(RenderContext& rc)
{
	// モデルを描画する。
	m_modelRender.Draw(rc);
}