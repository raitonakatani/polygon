#include "stdafx.h"
#include "Floor.h"

namespace {
	const Vector3 MODEL_SCALE = { 1.5f,1.5f,1.5f };		// ���f���̑傫��
	const float	  YPOSI = 42.0f;						// Y���W
}

bool Floor::Start()
{
	// ���f����ǂݍ���
	m_modelRender.InitUVScroll("Assets/modelData/testModel/yuka.tkm");
	m_position.y += YPOSI;
	//���f���̍��W��ݒ�B
	m_modelRender.SetPosition(m_position);
	//���f���̉�]��ݒ�B
	m_modelRender.SetRotation(m_rotation);
	//���f���̑傫����ݒ�B
	m_modelRender.SetScale(MODEL_SCALE);
	//���f���̍X�V�����B
	m_modelRender.Update();

	return true;
}
void Floor::Update()
{
}
void Floor::Render(RenderContext& rc)
{
	// ���f����`�悷��B
	m_modelRender.Draw(rc);
}