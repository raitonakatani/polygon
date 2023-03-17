#include "stdafx.h"
#include "GameEffect.h"
// EffectEmitterを使用するために、ファイルをインクルードする。
#include "graphics/effect/EffectEmitter.h"

namespace {
	Vector3 SMOKE_POSIOTION = { 0.0f,150.0f,0.0f };		// スモークエフェクトの座標
	Vector3 EFFECT_SCALE = { 8.0f,8.0f,8.0f };			// エフェクトの大きさ
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
	// エフェクトを再生する
	m_effect = NewGO <EffectEmitter>(0);
	Vector3 effectposi = SMOKE_POSIOTION;
	// エフェクトを読み込む
	m_effect->Init(1);
	// エフェクトの座標を設定す
	m_effect->SetPosition(effectposi);
	// エフェクトの大きさを設定する。
	m_effect->SetScale(EFFECT_SCALE);
	// エフェクトを再生する
	m_effect->Play();
}
