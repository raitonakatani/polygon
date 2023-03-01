#include "stdafx.h"
#include "Box.h"
#include "Player.h"

namespace
{
	int PAD = 0;		// �Q�[���p�b�h�̃i���o�[
	int PLAYER = 1;		// �L�����N�^�[�̔ԍ� �v���C���[��1�@�G�l�~�[��0
}

bool Box::Start()
{
	// ���f���̓ǂݍ���
	m_modelRender.Init("Assets/modelData/testModel/box.tkm", false);
	// ���f���̍��W��ݒ�B
	m_modelRender.SetPosition(m_position);
	// ���f���̉�]��ݒ�B
	m_modelRender.SetRotation(m_rotation);
	// ���f���̑傫����ݒ�B
	m_modelRender.SetScale(m_scale);
	// ���f���̍X�V�����B
	m_modelRender.Update();
	// �ÓI�����I�u�W�F�N�g�̏����������B
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);

	m_renderingEngine = &g_renderingEngine;
	// �����_�[�^�[�Q�b�g���쐬����B
	m_renderingEngine->InitTextureTarget(m_number);
	// �e�N�X�`��������������B
	m_renderingEngine->SpriteInit(m_modelRender.GetTkm()->m_albedo, m_number);

	// �I�u�W�F�N�g�̃C���X�^���X��T���Ď����Ă���B
	m_player = FindGO<Player>("player");

	return true;
}

void Box::Update()
{
	// �C���N�̃����_�����O����
	InkRendering();
	// ���f���̍��W��ݒ�B
	m_modelRender.SetPosition(m_position);
	// ���f���̉�]��ݒ�B
	m_modelRender.SetRotation(m_rotation);
	// ���f���̑傫����ݒ�B
	m_modelRender.SetScale(m_scale);
	// ���f���̍X�V�����B
	m_modelRender.Update();
}

void Box::InkRendering()
{
	// �I�u�W�F�N�g�̃C���X�^���X��T���Ď����Ă���B
	m_player = FindGO<Player>("player");
	// �J�n���W���擾����
	m_startVector = m_player->GetStartVector();
	// �I�����W���擾����
	m_endVector = m_player->GetEndVector();
	// RB1(�U��)�{�^����������Ă�����
	if (g_pad[PAD]->IsPress(enButtonRB1) == true)
	{
		// �C���N�̃e�N�X�`�����I�t�X�N���[�������_�����O����B
		m_renderingEngine->SpriteDraw(PLAYER, m_modelRender, m_number, m_startVector, m_endVector);
	}
}

void Box::Render(RenderContext& rc)
{
	// �ʏ탂�f����`�悷��
	m_modelRender.Draw(rc);
}