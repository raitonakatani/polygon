#include "stdafx.h"
#include "Player.h"
#include "Game.h"


// EffectEmitter���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "graphics/effect/EffectEmitter.h"

namespace
{
	// Vector3
	const Vector3 MODEL_SCALE = { 1.0f, 1.0f, 1.0f };						//���f���̑傫��
	const Vector3 COLLISION_SCALE = { 20.0f, 20.0f, 120.0f };				//�R���W�����̑傫��
	const Vector3 COLLISION_PORK_SCALE = { 40.0f, 30.0f, 140.0f };			//�R���W�����i�|�[�N�j�̑傫��
	// float													
	const float CHARACON_RADIUS = 30.0f;						// �L�����R���̔��a
	const float CHARACON_HEIGHT = 75.0f;						// �L�����R���̍���
	const float MOVE_SPEED_MINIMUMVALUE = 0.001f;				// �ړ����x�̍Œ�l
	const float WALK_MOVESPEED = 400.0f;						// �����X�e�[�g�̈ړ����x
	const float GRAVITY = 1000.0f;								// �d��
	const float START_MOVE = 0.0f;								// �����ݒ�̃X�s�[�h
}

bool Player::Start()
{
	m_animationClipArray[enAnimClip_Idle].Load("Assets/aniData/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Shot].Load("Assets/aniData/shot.tka");
	m_animationClipArray[enAnimClip_Shot].SetLoopFlag(true);

	// ���f���̓ǂݍ���
	m_modelRender.Init("Assets/modelData/unityChan.tkm", false,m_animationClipArray,enAnimClip_Num);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();

	m_testmodel.Init("Assets/modelData/unityChan.tkm", false);
	m_testmodel.SetPosition(m_position);
	m_testmodel.Update();

	// �L�����R��
	m_charaCon.Init(CHARACON_RADIUS, CHARACON_HEIGHT, m_position);

	// �Q�[���̃N���X��T���Ă����Ă���B
	m_game = FindGO<Game>("game");
	return true;
}

void Player::Update()
{

	if (g_pad[0]->IsTrigger(enButtonA)) {

		m_startVector = m_position;
		m_startVector.y += 100.0f;

		m_endVector = m_startVector;
		Vector3 forward = Vector3::AxisZ;
		rotation.Apply(forward);
		m_endVector += forward * 200.0f;
		//m_endVector.y += 100.0f;
		//forward *= 1200.0f;
		rotation.AddRotationDegY(360.0f);

		//m_endVector += forward * 1000.0f;

	//	m_startVector.y = 500.0f;
	//	m_endVector.y = 500.0f;


	}
	rotation = m_rotation;
	m_testmodel.SetPosition(m_endVector);
	m_testmodel.SetRotation(rotation);
	m_testmodel.SetScale({ 0.2f,0.2f,0.2f });
	m_testmodel.Update();


	// �ړ�����
	Move();
	// ��]����
	Rotation();

	// ���W�A��]�A�傫���̍X�V
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(MODEL_SCALE);





	// ���f���̍X�V
	m_modelRender.Update();

}

void Player::Move()
{
	// �ړ����x
	m_moveSpeed.x = START_MOVE;
	m_moveSpeed.z = START_MOVE;
	// �X�e�b�N�̓��͗ʂ��擾
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();
	// camera�̑O�����ƉE�������擾
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	// XZ���ʂł̑O�������A�E�����ɕϊ�����
	cameraForward.y = START_MOVE;
	cameraForward.Normalize();
	cameraRight.y = START_MOVE;
	cameraRight.Normalize();

	m_moveSpeed += cameraForward * lStick_y * WALK_MOVESPEED;
	m_moveSpeed += cameraRight * lStick_x * WALK_MOVESPEED;

	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f){
		m_modelRender.PlayAnimation(enAnimClip_Shot, 0.1f);
		m_modelRender.SetAnimationSpeed(2.0f);
	}
	else {
		m_modelRender.PlayAnimation(enAnimClip_Idle, 0.1f);
		m_modelRender.SetAnimationSpeed();
	}

	if (g_pad[0]->IsTrigger(enButtonB)) {
		m_moveSpeed.y += 500.0f;
	}

	// �d��
	m_moveSpeed.y -= GRAVITY * g_gameTime->GetFrameDeltaTime();
	// �L�����R�����g�p���āA���W���X�V����
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	// ���W�̍X�V
	Vector3 modelPosition = m_position;
	m_modelRender.SetPosition(modelPosition);
}

void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) < MOVE_SPEED_MINIMUMVALUE
		&& fabsf(m_moveSpeed.z) < MOVE_SPEED_MINIMUMVALUE) {
		return;
	}
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotationY(-angle);
	// ��]��ݒ肷��
	m_modelRender.SetRotation(m_rotation);
	// �v���C���[�̐��ʃx�N�g�����v�Z����
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Player::Render(RenderContext& rc)
{
	// ���f�����h���[�B
	m_modelRender.Draw(rc);

	m_testmodel.Draw(rc);

}