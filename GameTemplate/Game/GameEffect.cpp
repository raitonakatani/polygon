#include "stdafx.h"
#include "GameEffect.h"
// EffectEmitter���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "graphics/effect/EffectEmitter.h"

namespace {
	Vector3 SMOKEPOSIOTION = { 0.0f,150.0f,0.0f };		// �X���[�N�G�t�F�N�g�̍��W
}

bool GameEffect::Start()
{
	// �G�t�F�N�g��ǂݍ��ށB
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
	// �G�t�F�N�g�̑傫����ݒ肷��B
	m_effect->SetScale(Vector3::One * 8.0f);
	m_effect->Play();
}
