#include "stdafx.h"
#include "Floor.h"

namespace {
	const float YPOSI = 42.0f; //Y���W
}

bool Floor::Start()
{
	m_modelRender.InitUVScroll("Assets/modelData/testModel/yuka.tkm");
	m_position.y += YPOSI;
	//���f���̍��W��ݒ�B
	m_modelRender.SetPosition(m_position);
	//���f���̉�]��ݒ�B
	m_modelRender.SetRotation(m_rotation);
	//���f���̑傫����ݒ�B
	m_modelRender.SetScale(Vector3::One*1.5f);
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