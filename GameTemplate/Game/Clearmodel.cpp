#include "stdafx.h"
#include "Clearmodel.h"
#include "Game.h"

namespace
{
	Vector3 MODEL_POSITION = { 0.0f,150.0f,400.0f };		//　キャラクターの座標
	int		PHASE = 5;										//現在のフェーズ
}

bool Clearmodel::Start()
{
	// アニメーションを読み込む
	m_animationClipArray[enAnimClip_Victory].Load("Assets/aniData/victory.tka");
	m_animationClipArray[enAnimClip_Victory].SetLoopFlag(true);

	// モデルを読み込む
	m_modelRender.Init("Assets/player/player.tkm", false, false, m_animationClipArray, enAnimClip_Num);
	// モデルの座標を設定。
	m_modelRender.SetPosition(m_position);
	// モデルの回転を設定。
	m_modelRender.SetRotation(m_rotation);
	// モデルの大きさを設定。
	m_modelRender.SetScale(m_scale);
	// モデルの更新処理。
	m_modelRender.Update();

	return true;
}

void Clearmodel::Update()
{
	m_game = FindGO<Game>("game");
	if (m_game->phase < PHASE)
	{
		return;
	}
	m_modelRender.SetAnimationSpeed(0.5f);

	// モデルの座標を設定。
	m_position = MODEL_POSITION;
	m_modelRender.SetPosition(m_position);
	// モデルの回転を設定。
	m_modelRender.SetRotation(m_rotation);
	// モデルの大きさを設定。
	m_modelRender.SetScale(m_scale);
	// モデルの更新処理。
	m_modelRender.Update();
}

void Clearmodel::Render(RenderContext& rc)
{
	// ゲームをクリアしていなかったら。
	if (m_game->phase < PHASE)
	{
		// 処理を行わない。
		return;
	}
	// モデルをドロー。
	m_modelRender.Draw(rc);
}