#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"

namespace
{

	const int PAD_NUMBER = 0;									//�Q�[���p�b�h�̃i���o�[


	const float TARGET_YPOSITION = 150.0f;
	const float ANGLE = 2.0f;					//��]�p�x
	const float MAX_ANGLE = 0.7f;
	const float SET_NEAR = 1.0f;				// �ߕ���
	const float SET_FAR = 40000.0f;				// ������

	const Vector3 NOMAL_CAMERA_POSI = { 0.0f, 80.0f, -250.0f };
}

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
	//�C���X�^���X���폜����B
	DeleteGO(this);
}
bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(NOMAL_CAMERA_POSI);
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("player");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	g_camera3D->SetNear(SET_NEAR);
	g_camera3D->SetFar(SET_FAR);

	m_game = FindGO<Game>("game");

	return true;
}
void GameCamera::Update()
{

	if (m_game->m_paintnumber == 40 && m_timer <= 15.0f)
	{
		m_timer += g_gameTime->GetFrameDeltaTime();
		m_pos = m_game->enemyposi;
		Vector3 target = m_game->enemypaint;
		if (m_timer <= 13.0f) {
			int ramx = -5 - rand() % 11;
			int ramz = -5 - rand() % 11;
			int ramy = -3 - rand() % 7;
			m_pos.x += ramx;
			m_pos.z += ramz;
			m_pos.y += ramz;

			int targetx = -5 - rand() % 11;
			int targetz = -5 - rand() % 11;
			int targety = -3 - rand() % 7;
			target.x += targetx;
			target.z += targetz;
			target.y += targety;
		}

		//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
		g_camera3D->SetPosition(m_pos);
		g_camera3D->SetTarget(target);

		g_camera3D->Update();

		return;
	}
	else if (m_game->m_paintnumber == 40 && m_timer >= 15.0f) {
		m_game->m_paintnumber = 41;
	}



	//�ʏ�J����
	Vector3 target = m_player->GetPosition();
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += TARGET_YPOSITION;
	m_toCameraPosOld = m_toCameraPos;

	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	float x2 = g_pad[PAD_NUMBER]->GetRStickXF();
	float y2 = g_pad[PAD_NUMBER]->GetRStickYF();


	//Y������̉�]
	m_xyRot.SetRotationDeg(Vector3::AxisY, ANGLE * x2);
	m_xyRot.Apply(m_toCameraPos);
	//X������̉�]�B
	Vector3 axisX2;
	axisX2.Cross(Vector3::AxisY, m_toCameraPos);
	axisX2.Normalize();
	m_xyRot.SetRotationDeg(axisX2, ANGLE * y2);
	m_xyRot.Apply(m_toCameraPos);
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir2 = m_toCameraPos;
	toPosDir2.Normalize();
	if (toPosDir2.y < -MAX_ANGLE) {
		//�J����������������B
		m_toCameraPos = m_toCameraPosOld;
	}
	else if (toPosDir2.y > MAX_ANGLE) {
		//�J�����������������B
		m_toCameraPos = m_toCameraPosOld;
	}

	//���_���v�Z����B
	m_pos = target + m_toCameraPos;

	if (m_game->phase == 5) {
		Vector3 cameraposi = m_toCameraPos;
		cameraposi.x *= -1.0f;
		cameraposi.z *= -1.0f;
		m_pos = target + m_toCameraPos;
	}

	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	g_camera3D->SetPosition(m_pos);
	g_camera3D->SetTarget(target);

	//�J�����̍X�V�B
	g_camera3D->Update();

}

void GameCamera::Render(RenderContext& rc)
{

}
