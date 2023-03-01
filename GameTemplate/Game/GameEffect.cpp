#include "stdafx.h"
#include "GameEffect.h"
// EffectEmitterを使用するために、ファイルをインクルードする。
#include "graphics/effect/EffectEmitter.h"

namespace {
	Vector3 SMOKEPOSIOTION = { 0.0f,150.0f,0.0f };		// スモークエフェクトの座標
}

bool GameEffect::Start()
{
	// エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/efk/shot.efk");
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/efk/smoke.efk");
	return true;
}

void GameEffect::SmokeEffect()
{
	m_effect = NewGO <EffectEmitter>(0);
	Vector3 effectposi = SMOKEPOSIOTION;
	m_effect->Init(1);
	m_effect->SetPosition(effectposi);
	// エフェクトの大きさを設定する。
	m_effect->SetScale(Vector3::One * 8.0f);
	m_effect->Play();
}
