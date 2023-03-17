#include "stdafx.h"
#include "Stairs.h"
#include "Player.h"


bool Stairs::Start()
{
	// ���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/testModel/stairs.tkm", true);
	//���f���̍��W��ݒ�B
	m_modelRender.SetPosition(m_position);
	//���f���̉�]��ݒ�B
	//	m_modelRender.SetRotation(m_rotation);
	//���f���̑傫����ݒ�B
	m_modelRender.SetScale(m_scale);
	//���f���̍X�V�����B
	m_modelRender.Update();
	//�ÓI�����I�u�W�F�N�g�̏����������B
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);


	m_renderingEngine = &g_renderingEngine;

	m_renderingEngine->InitTextureTarget(m_number);
	m_renderingEngine->SpriteInit(m_modelRender.GetTkm()->m_albedo, m_number);

	m_player = FindGO<Player>("player");


	return true;
}
void Stairs::Update()
{
	// ���f���̍��W��ݒ肷��
	m_modelRender.SetPosition(m_position);
	// ���f���̑傫����ݒ肷��
	m_modelRender.SetScale(m_scale);
	// ���f�����X�V����
	m_modelRender.Update();

	// �v���C���[��T��
	m_player = FindGO<Player>("player");
	// �J�n���W�ƏI�����W��ݒ肷��
	m_startVector = m_player->GetStartVector();
	m_endVector = m_player->GetEndVector();

	// �U������Ă����ꍇ
	if (g_pad[0]->IsPress(enButtonRB1) == true)
	{
		// �C���N�̏������s��
		m_renderingEngine->SpriteDraw(1, m_modelRender, m_number, m_startVector, m_endVector);
	}
}
void Stairs::Render(RenderContext& rc)
{
	// ���f����`�悷��B
	m_modelRender.Draw(rc);
}