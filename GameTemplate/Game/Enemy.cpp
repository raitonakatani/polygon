#include "stdafx.h"
#include "Enemy.h"
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

bool Enemy::Start()
{
	m_animationClipArray[enAnimClip_Idle].Load("Assets/aniData/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Shot].Load("Assets/aniData/attack.tka");
	m_animationClipArray[enAnimClip_Shot].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Walk].Load("Assets/aniData/walk.tka");
	m_animationClipArray[enAnimClip_Walk].SetLoopFlag(true);

	// ���f���̓ǂݍ���
	m_modelRender.Init("Assets/modelData/testModel/player.tkm", false, m_animationClipArray, enAnimClip_Num);
	m_modelRender.SetPosition(500.0f, 250.0f, 500.0f);
	m_modelRender.Update();

	// �A�j���[�V�����C�x���g�p�̊֐���ݒ肷��
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	//	m_player = FindGO<Player>("player");


	// �i�r���b�V�����\�z�B
	m_nvmMesh.Init("Assets/tkn/stage.tkn");


	// �L�����R��
	m_charaCon.Init(CHARACON_RADIUS, CHARACON_HEIGHT, m_position);

	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/efk/shot.efk");

	m_gunId = m_modelRender.FindBoneID(L"eff_muzzle");

	// �Q�[���̃N���X��T���Ă����Ă���B
	m_gameSound = FindGO<GameSound>("gamesound");

	return true;
}

void Enemy::Update()
{

	m_targetPointPosition = { -100.0f,250.0f,0.0f };
	m_diff = m_targetPointPosition - m_position;

	// ��]����
	Rotation();
	// �ړ�����
	Move();
	// �U������
	Attack();
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

void Enemy::Move()
{
	Vector3 diff = m_diff;
	diff.Normalize();
	m_moveSpeed = diff * 3.0f;

	bool isEnd;
	// �p�X����
	if (m_isAttack == false) {
		m_pathFiding.Execute(
			m_path,							// �\�z���ꂽ�p�X�̊i�[��
			m_nvmMesh,						// �i�r���b�V��
			m_position,						// �J�n���W
			m_targetPointPosition,			// �ړ��ڕW���W
			PhysicsWorld::GetInstance(),	// �����G���W��	
			25.0f,							// AI�G�[�W�F���g�̔��a
			55.0f							// AI�G�[�W�F���g�̍����B
		);

		// �p�X����ړ�����B
		m_position = m_path.Move(
			m_position,
			3.0f,
			isEnd
		);
	}

	if (m_charaCon.IsOnGround() == false) {
		// �d��
		m_moveSpeed.y -= GRAVITY * g_gameTime->GetFrameDeltaTime();
	}
	// �L�����R�����g�p���āA���W���X�V����
	//m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	// ���W�̍X�V
	Vector3 modelPosition = m_position;
	m_modelRender.SetPosition(modelPosition);
}

void Enemy::Rotation()
{
	if (m_isAttack == true)
	{
		m_diff.Normalize();
		m_diff *= 2.0f;
		m_moveSpeed += m_diff;
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

void Enemy::Attack()
{
	yup += 0.5f;
	if (m_diff.Length() <= 300.0f) {
		m_isAttack = true;
		m_startVector = m_position;
		m_startVector.y += 100.0f;
		m_endVector = m_startVector;
		m_forward.Normalize();
		m_endVector += m_forward * 200.0f;
		m_endVector.y += yup;
	}
	else
	{
		m_isAttack = false;
		m_endVector = m_startVector = Vector3::Zero;
	}
}

void Enemy::ProcessCommonStateTransition()
{

	if (m_isAttack == true) {
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
//		m_effect->SetWorldMatrix(matrix);
		m_effect->Play();
			//�U���X�e�[�g�ɑJ��
		m_enemyState = enEnemyState_Shot;
		return;
	}

	// x��z�̈ړ����x����������
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//����X�e�[�g�ɑJ��
		m_enemyState = enEnemyState_Walk;
		return;
	}
	else {
		if (m_charaCon.IsOnGround() == true) {
			//�ҋ@�X�e�[�g�ɑJ��
			m_enemyState = enEnemyState_Idle;
			return;
		}
	}
}

void Enemy::ProcessIdleStateTransition()
{
	ProcessCommonStateTransition();

}

void Enemy::ProcessRunStateTransition()
{
	ProcessCommonStateTransition();
}

void Enemy::ProcessAttackStateTransition()
{
	ProcessCommonStateTransition();
}

void Enemy::PlayAnimation()
{
	switch (m_enemyState)
	{
		// �ҋ@�X�e�[�g�̎�
	case Enemy::enEnemyState_Idle:
		m_modelRender.PlayAnimation(enAnimClip_Idle, 0.1f);
		m_modelRender.SetAnimationSpeed(0.8f);
		break;
		// ����X�e�[�g�̎�
	case Enemy::enEnemyState_Walk:
		m_modelRender.PlayAnimation(enAnimClip_Walk, 0.1f);
		m_modelRender.SetAnimationSpeed(0.8f);
		break;
		// �U���X�e�[�g�̎�
	case Enemy::enEnemyState_Shot:
		m_modelRender.PlayAnimation(enAnimClip_Shot, 0.1f);
		m_modelRender.SetAnimationSpeed();
		break;
	default:
		break;
	}
}

void Enemy::ManageState()
{
	switch (m_enemyState)
	{
		// �ҋ@�X�e�[�g�̎�
	case Enemy::enEnemyState_Idle:
		ProcessIdleStateTransition();
		break;
		// ����X�e�[�g�̎�
	case Enemy::enEnemyState_Walk:
		ProcessRunStateTransition();
		break;
		// �U���X�e�[�g�̎�
	case Enemy::enEnemyState_Shot:
		ProcessAttackStateTransition();
		break;
	default:
		break;
	}
}


void Enemy::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
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

void Enemy::Render(RenderContext& rc)
{
	// ���f�����h���[�B
	m_modelRender.Draw(rc);
}