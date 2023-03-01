#include "stdafx.h"
#include "Clearmodel.h"
#include "Game.h"

namespace
{
	Vector3 MODEL_POSITION = { 0.0f,150.0f,400.0f };		//�@�L�����N�^�[�̍��W
	int		PHASE = 5;										//���݂̃t�F�[�Y
}

bool Clearmodel::Start()
{
	// �A�j���[�V������ǂݍ���
	m_animationClipArray[enAnimClip_Victory].Load("Assets/aniData/victory.tka");
	m_animationClipArray[enAnimClip_Victory].SetLoopFlag(true);

	// ���f����ǂݍ���
	m_modelRender.Init("Assets/player/player.tkm", false, false, m_animationClipArray, enAnimClip_Num);
	// ���f���̍��W��ݒ�B
	m_modelRender.SetPosition(m_position);
	// ���f���̉�]��ݒ�B
	m_modelRender.SetRotation(m_rotation);
	// ���f���̑傫����ݒ�B
	m_modelRender.SetScale(m_scale);
	// ���f���̍X�V�����B
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

	// ���f���̍��W��ݒ�B
	m_position = MODEL_POSITION;
	m_modelRender.SetPosition(m_position);
	// ���f���̉�]��ݒ�B
	m_modelRender.SetRotation(m_rotation);
	// ���f���̑傫����ݒ�B
	m_modelRender.SetScale(m_scale);
	// ���f���̍X�V�����B
	m_modelRender.Update();
}

void Clearmodel::Render(RenderContext& rc)
{
	// �Q�[�����N���A���Ă��Ȃ�������B
	if (m_game->phase < PHASE)
	{
		// �������s��Ȃ��B
		return;
	}
	// ���f�����h���[�B
	m_modelRender.Draw(rc);
}