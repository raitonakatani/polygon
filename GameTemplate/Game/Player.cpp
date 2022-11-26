#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "GameSound.h"

// EffectEmitter���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "graphics/effect/EffectEmitter.h"

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
	const float GRAVITY = 1000.0f;								// �d��
	const float START_MOVE = 0.0f;								// �����ݒ�̃X�s�[�h
}

bool Player::Start()
{
	m_animationClipArray[enAnimClip_Idle].Load("Assets/aniData/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Shot].Load("Assets/aniData/attack.tka");
	m_animationClipArray[enAnimClip_Shot].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_LeftShot].Load("Assets/aniData/leftattack.tka");
	m_animationClipArray[enAnimClip_LeftShot].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_RightShot].Load("Assets/aniData/rightattack.tka");
	m_animationClipArray[enAnimClip_RightShot].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_ForwardShot].Load("Assets/aniData/forwardattack.tka");
	m_animationClipArray[enAnimClip_ForwardShot].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_BackShot].Load("Assets/aniData/backattack.tka");
	m_animationClipArray[enAnimClip_BackShot].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Walk].Load("Assets/aniData/walk.tka");
	m_animationClipArray[enAnimClip_Walk].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Jump].Load("Assets/aniData/walk.tka");
	m_animationClipArray[enAnimClip_Jump].SetLoopFlag(true);

	// ���f���̓ǂݍ���
	m_modelRender.Init("Assets/modelData/testModel/player.tkm", false,m_animationClipArray,enAnimClip_Num);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();

	// �A�j���[�V�����C�x���g�p�̊֐���ݒ肷��
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});


	m_testmodel.Init("Assets/modelData/unityChan.tkm", false);
	m_testmodel.SetPosition(m_position);
	m_testmodel.Update();

	// �L�����R��
	Vector3 posi = m_position;
	posi.y += 10.0f;
	m_charaCon.Init(CHARACON_RADIUS, CHARACON_HEIGHT, posi);

	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/efk/shot.efk");
	
	m_gunId = m_modelRender.FindBoneID(L"eff_muzzle");

	// �Q�[���̃N���X��T���Ă����Ă���B
	m_game = FindGO<Game>("game");
	m_gameSound = FindGO<GameSound>("gamesound");

	return true;
}

void Player::Update()
{
	if (g_pad[0]->IsPress(enButtonA)) {
		m_startVector = m_position;
		m_startVector.y += 100.0f;
		m_endVector = m_startVector;
		Vector3 forward = Vector3::AxisZ;
		rotation.Apply(m_rotation);
		cameraforward.Normalize();
		m_forward.y = cameraforward.y;
		m_endVector += m_forward * 200.0f;
	}
	else
	{
		m_endVector = m_startVector = Vector3::Zero;
	}
	rotation = m_rotation;
	m_testmodel.SetPosition(m_endVector);
	m_testmodel.SetRotation(rotation);
	m_testmodel.SetScale({ 0.2f,0.2f,0.2f });
	m_testmodel.Update();


	// ��]����
	Rotation();
	// �ړ�����
	Move();
	// �A�j���[�V�����̍Đ�
	PlayAnimation();
	// �e�X�e�[�g�̑J�ڏ���
	ManageState();

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

	m_moveSpeed += cameraForward * lStick_y * m_move;
	m_moveSpeed += cameraRight * lStick_x * m_move;

	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f) {
		if (m_move <= 300.0f) {
			m_move *= 1.1f;
		}
			m_lStick_y = lStick_y;
			m_lStick_x = lStick_x;

	}
	else {
		if (m_move >= 100.0f) {
			m_move /= 1.08f;
			m_moveSpeed += cameraForward * m_lStick_y * m_move;
			m_moveSpeed += cameraRight * m_lStick_x * m_move;
		}
	}


	if (g_pad[0]->IsTrigger(enButtonB)) {
		m_moveSpeed.y += 500.0f;
	}

	if (m_charaCon.IsOnGround() == false) {
		// �d��
		m_moveSpeed.y -= GRAVITY * g_gameTime->GetFrameDeltaTime();
	}


	// �L�����R�����g�p���āA���W���X�V����
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	if (m_position.y <= -45.0f) {
		m_position = { 0.0f,350.0f,-500.0f };
		m_charaCon.SetPosition(m_position);
	}

	// ���W�̍X�V
	Vector3 modelPosition = m_position;
	m_modelRender.SetPosition(modelPosition);
}

void Player::Rotation()
{
	if (g_pad[0]->IsPress(enButtonA) == true)
	{
	/*	if (m_moveSpeed.x >= 0.001f|| m_moveSpeed.x <= -0.001f||
			m_moveSpeed.z >= 0.001f || m_moveSpeed.z <= -0.001f) {
			return;
		}*/
		m_moveSpeed += g_camera3D->GetForward();
	}

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

void Player::ProcessCommonStateTransition()
{

	if (g_pad[0]->IsPress(enButtonA)) {
		Matrix matrix = m_modelRender.GetBone(m_gunId)->GetWorldMatrix();
		m_effect = NewGO <EffectEmitter>(0);
		Vector3 effectposi = m_position;
		effectposi.y += 35.0f;
		effectposi += m_forward * 50.0f;

		Vector3 m_right = Vector3::AxisX;
		m_rotation.Apply(m_right);
		effectposi += m_right * -7.5f;
		
		m_effect->Init(0);
		m_effect->SetPosition(effectposi);
		m_effect->SetRotation(m_rotation);
		// �G�t�F�N�g�̑傫����ݒ肷��B
		m_effect->SetScale(m_scale * 10.0f);
		m_effect->Play();
	//	m_effect->SetWorldMatrix(matrix);
		//�U���X�e�[�g�ɑJ��
		m_playerState = enPlayerState_Shot;
		return;
	}

	if (g_pad[0]->IsTrigger(enButtonB)) {
		//�W�����v�X�e�[�g�ɑJ��
		m_playerState = enPlayerState_Jump;
		return;
	}

	// x��z�̈ړ����x����������
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
	/*	if (g_pad[0]->IsPress(enButtonA)==true) {
			if (Lstick_x<= -0.1f) {
				m_playerState = enPlayerState_LeftShot;
				return;
			}
			else if (Lstick_x >= 0.1f)
			{
				m_playerState = enPlayerState_RightShot;
				return;
			}
			else if (Lstick_y >= 0.1f)
			{
				m_playerState = enPlayerState_ForwardShot;
				return;
			}
			else if (Lstick_y <= -0.1f)
			{
				m_playerState = enPlayerState_BackShot;
				return;
			}
		}
		else {*/
			//����X�e�[�g�ɑJ��
			m_playerState = enPlayerState_Walk;
			return;
	//	}
	}
	else {

		if (m_charaCon.IsOnGround() == true) {
			//�ҋ@�X�e�[�g�ɑJ��
			m_playerState = enPlayerState_Idle;
			return;
		}
	}

}

void Player::ProcessIdleStateTransition()
{
	ProcessCommonStateTransition();
	
}

void Player::ProcessRunStateTransition()
{
		ProcessCommonStateTransition();
}

void Player::ProcessJumpStateTransition()
{
		ProcessCommonStateTransition();
}

void Player::ProcessAttackStateTransition()
{
		ProcessCommonStateTransition();
}

void Player::PlayAnimation()
{
	switch (m_playerState)
	{
		// �ҋ@�X�e�[�g�̎�
	case Player::enPlayerState_Idle:
		m_modelRender.PlayAnimation(enAnimClip_Idle, 0.1f);
		m_modelRender.SetAnimationSpeed(0.8f);
		break;
		// �W�����v�X�e�[�g�̎�
	case Player::enPlayerState_Jump:
		m_modelRender.PlayAnimation(enAnimClip_Jump, 0.1f);
		m_modelRender.SetAnimationSpeed(1.2f);
		break;
		// ����X�e�[�g�̎�
	case Player::enPlayerState_Walk:
		m_modelRender.PlayAnimation(enAnimClip_Walk, 0.1f);
		m_modelRender.SetAnimationSpeed(1.2f);
		break;
		// �U���X�e�[�g�̎�
	case Player::enPlayerState_Shot:
		m_modelRender.PlayAnimation(enAnimClip_Shot, 0.1f);
		m_modelRender.SetAnimationSpeed();
		break;
		// �U���X�e�[�g�̎���
	case Player::enPlayerState_LeftShot:
		m_modelRender.PlayAnimation(enAnimClip_LeftShot, 0.1f);
		m_modelRender.SetAnimationSpeed();
		break;
		// �U���X�e�[�g�̎�
	case Player::enPlayerState_RightShot:
		m_modelRender.PlayAnimation(enAnimClip_RightShot, 0.1f);
		m_modelRender.SetAnimationSpeed();
		break;
		// �U���X�e�[�g�̎���
	case Player::enPlayerState_ForwardShot:
		m_modelRender.PlayAnimation(enAnimClip_ForwardShot, 0.1f);
		m_modelRender.SetAnimationSpeed();
		break;
		// �U���X�e�[�g�̎�
	case Player::enPlayerState_BackShot:
		m_modelRender.PlayAnimation(enAnimClip_ForwardShot, 0.1f);
		m_modelRender.SetAnimationSpeed();
		break;
	default:
		break;
	}
}

void Player::ManageState()
{
	switch (m_playerState)
	{
		// �ҋ@�X�e�[�g�̎�
	case Player::enPlayerState_Idle:
		ProcessIdleStateTransition();
		break;
		// �W�����v�X�e�[�g�̎�
	case Player::enPlayerState_Jump:
		ProcessJumpStateTransition();
		break;
		// ����X�e�[�g�̎�
	case Player::enPlayerState_Walk:
		ProcessRunStateTransition();
		break;
		// �U���X�e�[�g�̎�
	case Player::enPlayerState_Shot:
		ProcessAttackStateTransition();
		break;
		// �U���X�e�[�g�̎�
	case Player::enPlayerState_LeftShot:
		ProcessAttackStateTransition();
		break;
		// �U���X�e�[�g�̎�
	case Player::enPlayerState_RightShot:
		ProcessAttackStateTransition();
		break;	
	case Player::enPlayerState_ForwardShot:
		ProcessAttackStateTransition();
		break;
		// �U���X�e�[�g�̎�
	case Player::enPlayerState_BackShot:
		ProcessAttackStateTransition();
		break;
	default:
		break;
	}
}


void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName, L"Run_step") == 0 && m_charaCon.IsOnGround() == true) {
		// �����B
		// ���ʉ����Đ�����B
		m_gameSound->PlayerStepSE(0.4f);
	}

	if (wcscmp(eventName, L"attack") == 0) {
		// �����B
		// ���ʉ����Đ�����B
		m_gameSound->PlayerAttackSE(0.3f);
	}
}