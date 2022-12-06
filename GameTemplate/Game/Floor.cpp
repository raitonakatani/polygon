#include "stdafx.h"
#include "Floor.h"

bool Floor::Start()
{
	m_modelRender.InitUVScroll("Assets/modelData/testModel/yuka.tkm");
	//���f���̍��W��ݒ�B
	m_modelRender.SetPosition(m_position);
	//���f���̉�]��ݒ�B
	m_modelRender.SetRotation(m_rotation);
	//���f���̑傫����ݒ�B
	m_modelRender.SetScale(Vector3::One);
	//���f���̍X�V�����B
	m_modelRender.Update();
	//�ÓI�����I�u�W�F�N�g�̏����������B
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Ground);




	return true;
}
void Floor::Update()
{
	Vector3 BufferPosition[3];

	//�O�p�`�̍��W�����Ă���B
	const auto& bufferList = m_modelRender.GetTkm()->GetBuffer();

	BufferPosition[0] = bufferList[0].buffer[0];
	BufferPosition[1] = bufferList[0].buffer[1];
	BufferPosition[2] = bufferList[0].buffer[2];


	return;
}
void Floor::Render(RenderContext& rc)
{
	// ���f����`�悷��B
	m_modelRender.Draw(rc);
}