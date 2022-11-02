#include "stdafx.h"
#include "Box.h"
#include "Player.h"

namespace
{
}

bool Box::Start()
{
	// �ʏ탂�f��
	m_modelRender.Init("Assets/modelData/box.tkm", false);
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

//	m_sprite.Init("Assets/sprite/white.DDS",256.0f, 256.0f);

//	m_player = FindGO<Player>("player");

	//g_renderingEngine.SpriteInit(
	//	m_modelRender.GetTkm()->m_albedo,
	//	inkspriteinitdata,
	//	spriteinitdata,
	//	inksprite,
	//	sprite
	//	);

	return true;
}
void Box::Update()
{
	m_player = FindGO<Player>("player");
	startVector = m_player->GetStartVector();
	endVector = m_player->GetEndVector();




}
void Box::Render(RenderContext& rc)
{
	// �ʏ탂�f����`�悷��
	m_modelRender.Draw(rc);
	//	m_sprite.Draw(rc);
	//g_renderingEngine.SpriteDraw(m_modelRender,POS,UV,startVector,endVector,spriteinitdata,sprite);
}