#include "stdafx.h"
#include "GameEffect.h"
// EffectEmitter���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "graphics/effect/EffectEmitter.h"

namespace {
	Vector3 SMOKE_POSIOTION = { 0.0f,150.0f,0.0f };		// �X���[�N�G�t�F�N�g�̍��W
	Vector3 EFFECT_SCALE = { 8.0f,8.0f,8.0f };			// �G�t�F�N�g�̑傫��
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
	// �G�t�F�N�g���Đ�����
	m_effect = NewGO <EffectEmitter>(0);
	Vector3 effectposi = SMOKE_POSIOTION;
	// �G�t�F�N�g��ǂݍ���
	m_effect->Init(1);
	// �G�t�F�N�g�̍��W��ݒ肷
	m_effect->SetPosition(effectposi);
	// �G�t�F�N�g�̑傫����ݒ肷��B
	m_effect->SetScale(EFFECT_SCALE);
	// �G�t�F�N�g���Đ�����
	m_effect->Play();
}
