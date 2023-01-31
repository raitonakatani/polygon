#include "stdafx.h"
#include "Cylinder.h"
#include "Game.h"

namespace
{
}

bool Cylinder::Start()
{
	// �ʏ탂�f��
	m_modelRender.Init("Assets/modelData/testModel/cylinder.tkm", false);
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

	m_renderingEngine->InitTextureTarget(m_number);
	m_renderingEngine->SpriteInit(m_modelRender.GetTkm()->m_albedo, m_number);

	m_game = FindGO<Game>("game");

	return true;
}
void Cylinder::Update()
{
	if (m_game->m_paintnumber == 40 && m_position.y >= -150.0f)
	{
		int ramx = -3 - rand() % 7;
		int ramy = -3 - rand() % 7;

		m_position.x = ramx;
		m_position.z = ramy;
		m_position.y -= 0.5f;

		m_physicsStaticObject.SetRotation(m_position, m_rotation);
	}


	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
}
void Cylinder::Render(RenderContext& rc)
{
	// �ʏ탂�f����`�悷��
	m_modelRender.Draw(rc);
}