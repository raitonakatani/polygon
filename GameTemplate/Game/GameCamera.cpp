#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"


namespace
{

	const int PAD_NUMBER = 0;									//�Q�[���p�b�h�̃i���o�[
	const int NOMAL_CAMERA = 0;
	const int SPECIAL_CAMERA = 1;

	const float TARGET_YPOSITION = 150.0f;
	const float ANGLE = 2.0f;					//��]�p�x
	const float MAX_ANGLE = 0.8f;
	const float SET_NEAR = 1.0f;				// �ߕ���
	const float SET_FAR = 4000.0f;				// ������

	const float RESET_TIMER = 0.0f;
	const float PLUS_TIMER = 0.01f;
	const float MAX_TIMER = 1.5f;


	const Vector3 SPECIAL_CAMERA_POSI = { 0.0f, 80.0f, 400.0f };
	const Vector3 NOMAL_CAMERA_POSI = { 0.0f, 80.0f, -350.0f };
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

	m_toCameraPos.Set(SPECIAL_CAMERA_POSI);
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos2.Set(NOMAL_CAMERA_POSI);
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("player");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	g_camera3D->SetNear(SET_NEAR);
	g_camera3D->SetFar(SET_FAR);



	return true;
}
void GameCamera::Update()
{

	//�ʏ�J����
	Vector3 target2 = m_player->GetPosition();
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target2.y += TARGET_YPOSITION;
	toCameraPosOld2 = m_toCameraPos2;

	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	float x2 = g_pad[PAD_NUMBER]->GetRStickXF();
	float y2 = g_pad[PAD_NUMBER]->GetRStickYF();
	//Y������̉�]

	qRot2.SetRotationDeg(Vector3::AxisY, ANGLE * x2);
	qRot2.Apply(m_toCameraPos2);
	//X������̉�]�B
	Vector3 axisX2;
	axisX2.Cross(Vector3::AxisY, m_toCameraPos2);
	axisX2.Normalize();
	qRot2.SetRotationDeg(axisX2, ANGLE * y2);
	qRot2.Apply(m_toCameraPos2);
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir2 = m_toCameraPos2;
	toPosDir2.Normalize();
	if (toPosDir2.y < -MAX_ANGLE) {
		//�J����������������B
		m_toCameraPos2 = toCameraPosOld2;
	}
	else if (toPosDir2.y > MAX_ANGLE) {
		//�J�����������������B
		m_toCameraPos2 = toCameraPosOld2;
	}


	//���_���v�Z����B
	pos2 = target2 + m_toCameraPos2;

	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	g_camera3D->SetPosition(pos2);
	g_camera3D->SetTarget(target2);

	//�J�����̍X�V�B
	g_camera3D->Update();

}

void GameCamera::Render(RenderContext& rc)
{

}
