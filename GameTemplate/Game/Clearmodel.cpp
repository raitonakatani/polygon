#include "stdafx.h"
#include "Clearmodel.h"
#include "Player.h"
#include "Game.h"

namespace
{
	// Vector3
	const Vector3 MODEL_SCALE = { 1.0f, 1.0f, 1.0f };						//���f���̑傫��
	const Vector3 COLLISION_SCALE = { 20.0f, 20.0f, 120.0f };				//�R���W�����̑傫��
	const Vector3 COLLISION_PORK_SCALE = { 40.0f, 30.0f, 140.0f };			//�R���W�����i�|�[�N�j�̑傫��
	// float													
	const float CHARACON_RADIUS = 20.0f;						// �L�����R���̔��a
	const float CHARACON_HEIGHT = 55.0f;						// �L�����R���̍���
	const float MOVE_SPEED_MINIMUMVALUE = 0.001f;				// �ړ����x�̍Œ�l
	const float WALK_MOVESPEED = 300.0f;						// �����X�e�[�g�̈ړ����x
}

Clearmodel::~Clearmodel()
{
	//DeleteGO(this);
}
bool Clearmodel::Start()
{
	m_animationClipArray[enAnimClip_Victory].Load("Assets/aniData/victory.tka");
	m_animationClipArray[enAnimClip_Victory].SetLoopFlag(true);

	// ���f����ǂݍ���
	m_modelRender.Init("Assets/player/player.tkm", false, false, m_animationClipArray, enAnimClip_Num);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();

//	m_charaCon.Init(20.0f, 55.0f, m_position);

	return true;
}

void Clearmodel::Update()
{
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

	if (m_game->phase < 5)
	{
		return;
	}

	m_position = m_player->GetPosition();

	// ���W�A��]�A�傫���̍X�V
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	// ���f���̍X�V
	m_modelRender.Update();
}

void Clearmodel::Render(RenderContext& rc)
{
	if (m_game->phase < 5)
	{
		return;
	}
	// ���f�����h���[�B
	m_modelRender.Draw(rc);
}