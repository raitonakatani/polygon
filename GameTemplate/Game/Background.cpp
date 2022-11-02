#include "stdafx.h"
#include "Background.h"
#include "Player.h"

namespace
{
}

bool Background::Start()
{
	// �ʏ탂�f��
	m_modelRender.Init("Assets/modelData/box.tkm", true);
	// ���f���̍��W��ݒ�B
	m_modelRender.SetPosition(m_position);
	// ���f���̉�]��ݒ�B
	m_modelRender.SetRotation(m_rotation);
	// ���f���̑傫����ݒ�B
	m_modelRender.SetScale(m_scale);
	// ���f���̍X�V�����B
	m_modelRender.Update();
	// �ÓI�����I�u�W�F�N�g�̏����������B
//	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
//	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);


	m_player = FindGO<Player>("player");

	return true;
}
void Background::Update()
{
	//�O�p�`�̍��W�������Ă��郊�X�g�������Ă���B
	std::vector<nsK2EngineLow::TkmFile::VectorBuffer> bufferList = m_modelRender.GetTkm()->GetBuffer();


	Vector3 startVector;
	Vector3 endVector;

	//���ʂƐ����̌�_�����߂�B�@POS�i��_�̍��W�j�Avector3d(�����n�_)�Avector3dend(�����I�_)�A�|���S����3���_
//	m_modelRender.IntersectPlaneAndLine(POS, startVector, endVector, bufferList);
	auto Vector = POS;
	auto Vector2 = POS;

}
void Background::Render(RenderContext& rc)
{
	// �ʏ탂�f����`�悷��
	m_modelRender.Draw(rc);
}