#include "stdafx.h"
#include "Triangle.h"
#include "Player.h"

namespace
{
}

bool Triangle::Start()
{
	m_position.y -= 30.0f;
	// ���f����ǂݍ���
	m_modelRender.Init("Assets/modelData/testModel/triangle.tkm", false);
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

	return true;
}
void Triangle::Update()
{
	// ���f���̍X�V����
	m_modelRender.Update();

}
void Triangle::Render(RenderContext& rc)
{
	// �ʏ탂�f����`�悷��
	m_modelRender.Draw(rc);
}