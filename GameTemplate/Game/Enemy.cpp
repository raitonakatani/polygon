#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "GameSound.h"
#include "Cylinder.h"

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

Enemy::~Enemy()
{
	//DeleteGO(this);
}
bool Enemy::Start()
{
	// �A�j���[�V������ǂݍ���
	m_animationClipArray[enAnimClip_Idle].Load("Assets/aniData/enemy/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Shot].Load("Assets/aniData/enemy/shot.tka");
	m_animationClipArray[enAnimClip_Shot].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Walk].Load("Assets/aniData/enemy/run.tka");
	m_animationClipArray[enAnimClip_Walk].SetLoopFlag(true);

	// �A�j���[�V������ǂݍ���
//	m_animationClipArray[enAnimClip_Idle].Load("Assets/aniData/idle.tka");
//	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
//	m_animationClipArray[enAnimClip_Shot].Load("Assets/aniData/attack.tka");
//	m_animationClipArray[enAnimClip_Shot].SetLoopFlag(true);
//	m_animationClipArray[enAnimClip_Walk].Load("Assets/aniData/walk.tka");
//	m_animationClipArray[enAnimClip_Walk].SetLoopFlag(true);

	scale *= 6.0f;

	// ���f����ǂݍ���
	m_modelRender.Init("Assets/enemy/enemy.tkm", false, false, m_animationClipArray, enAnimClip_Num);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(scale);
	m_modelRender.Update();

	// �A�j���[�V�����C�x���g�p�̊֐���ݒ肷��
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	// �i�r���b�V�����\�z�B
	m_nvmMesh.Init("Assets/tkn/teststage.tkn");

	// �G�t�F�N�g
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/efk/shot.efk");

	// �u�e�v�̃{�[��ID
	m_gunId = m_modelRender.FindBoneID(L"eff_muzzle");

	// �Q�[���̃N���X��T���Ă����Ă���B
	m_gameSound = FindGO<GameSound>("gamesound");

	m_charaCon.Init(20.0f, 55.0f, m_position);

	//�X�t�B�A�R���C�_�[���������B
	m_sphereCollider.Create(1.0f);

	m_enemypath.Init("Assets/path/path.tkl");

	return true;
}

void Enemy::Update()
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	if (m_timer <= 12.0f) {
		return;
	}
	if (m_hp <= 0) {
		m_player->m_enemynumber += 1;
		DeleteGO(this);
	}
	// �v���C���[�̃N���X��T���Ď����Ă���
	m_player = FindGO<Player>("player");
	if (m_isSearchPlayer == false) {
		m_targetPointPosition = m_targetposi;
		if (m_timer >= 15.0f) {

			//�h��ꏊ�i���ꏊ�j�������_���ɐݒ�
	/*		Quaternion rot;
			float ram = rand() % 360;
			rot.SetRotationY(ram);
			rot.Apply(m_forward);
			m_targetposi = m_forward * 400.0f;
			if (m_targetposi.x <= 300.0f && m_targetposi.x >= -300.0f) {
				m_targetposi.x = 300.0f;
			}
			if (m_targetposi.z <= 300.0f && m_targetposi.z >= -300.0f) {
				m_targetposi.z = 300.0f;
			}
			m_targetposi.y = 150.0f;*/
			int ram = rand() % 8;
			int ram2 = rand() % 4;
			m_targetposi = m_enemypath.m_pointlist[ram].s_position;
			paintposi = m_enemypath.m_pointlist[ram].s_paintposi[ram2];
			m_timer = 13.0f;
		}
	}
	else {
		m_timer = 13.0f;
		m_targetPointPosition = m_player->GetPosition();
	}
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
	// �T�[�`
	SearchPlayer();
	// �����蔻��
	Collision();

	// ���W�A��]�A�傫���̍X�V
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(scale);
	// ���f���̍X�V
	m_modelRender.Update();

	m_cylinder = FindGO<Cylinder>("cylinder");
}

void Enemy::Move()
{
	timer += g_gameTime->GetFrameDeltaTime();
	bool isEnd;
	Vector3 diff;
	// �p�X����
	if (m_isAttack == false && timer >= 0.3f) {
		timer = 0.0f;
		m_oldPosition = m_position;
		m_pathFiding.Execute(
			m_path,							// �\�z���ꂽ�p�X�̊i�[��
			m_nvmMesh,						// �i�r���b�V��
			m_position,						// �J�n���W
			m_targetPointPosition,			// �ړ��ڕW���W
			PhysicsWorld::GetInstance(),	// �����G���W��	
			25.0f,							// AI�G�[�W�F���g�̔��a
			55.0f							// AI�G�[�W�F���g�̍����B
		);
	}
	if (m_diff.Length() >= 100.0f && timer < 0.3f) {
		// �p�X����ړ�����B
		m_position = m_path.Move(
			m_position,
			4.0f,
			isEnd
		);
		m_position* m_forward;
		diff = m_position - m_oldPosition;
		diff.Normalize();
		m_moveSpeed = diff;
		m_timer = 13.0f;
	}

	// �d��
	m_moveSpeed.y -= GRAVITY * g_gameTime->GetFrameDeltaTime();
	m_charaCon.SetPosition(m_position);
	m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	// ���W�̍X�V
	Vector3 modelPosition = m_position;
	m_modelRender.SetPosition(modelPosition);
}

void Enemy::Rotation()
{
	if (m_isAttack == true)
	{
		//timer = 0.0f;
		auto diff = m_diff;
		if (m_isSearchPlayer == false) {
			diff = Vector3{0.0f,150.0f,0.0f} - m_position;
		}
		diff.Normalize();
		m_moveSpeed = diff;
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
	//float ram = rand() % 200;
	//yup = ram;
	if (m_diff.Length() <= 100.0f && m_timer >= 14.0f) {
		m_isAttack = true;
		m_startVector = m_position;
		m_startVector.y += 50.0f;
		m_endVector = m_startVector;
		Vector3 paint = paintposi - m_startVector;
		paint.Normalize();
		m_endVector += paint * 300.0f;
	//	m_endVector.y += yup;

		m_renderingEngine->SpriteDraw(m_cylinder->m_modelRender, m_cylinder->m_number,0, m_startVector, m_endVector);
	}
	else if (m_diff.Length() <= 100.0f && m_timer < 14.0f)
	{
		//yup = 0.0f;
		m_enemyState = enEnemyState_Idle;
		return;
	}
	if (m_diff.Length() >= 100.0f)
	{
	//	yup = 0.0f;
		m_isAttack = false;
		m_endVector = m_startVector = Vector3::Zero;
	}
}

//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�Ǘp)
struct SweepResultWall :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;						//�Փ˃t���O�B

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		//�ǂƂԂ����ĂȂ�������B
		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall) {
			//�Փ˂����͕̂ǂł͂Ȃ��B
			return 0.0f;
		}

		//�ǂƂԂ�������B
		//�t���O��true�ɁB
		isHit = true;
		return 0.0f;
	}
};

void Enemy::SearchPlayer()
{
	m_isSearchPlayer = false;

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	Vector3 playerPosition = m_player->GetPosition();
	Vector3 diff = playerPosition - m_position;

	diff.Normalize();
	float angle = acosf(diff.Dot(m_forward));


	//�v���C���[�����E���ɋ��Ȃ�������B
	if (Math::PI * 0.35f <= fabsf(angle) && diff.Length() <= 500.0f)
	{
		//�v���C���[�͌������Ă��Ȃ��B
		return;
	}

	btTransform start, end;
	start.setIdentity();
	end.setIdentity();
	//�n�_�̓G�l�~�[�̍��W�B
	start.setOrigin(btVector3(m_position.x, m_position.y + 70.0f, m_position.z));
	//�I�_�̓v���C���[�̍��W�B
	end.setOrigin(btVector3(playerPosition.x, playerPosition.y + 70.0f, playerPosition.z));

	SweepResultWall callback;
	//�R���C�_�[���n�_����I�_�܂œ������āB
	//�Փ˂��邩�ǂ����𒲂ׂ�B
	PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(), start, end, callback);
	//�ǂƏՓ˂����I
	if (callback.isHit == true)
	{
		//�v���C���[�͌������Ă��Ȃ��B
		return;
	}

	//�ǂƏՓ˂��ĂȂ��I�I
	//�v���C���[�������t���O��true�ɁB
	m_isSearchPlayer = false;
}

void Enemy::Collision()
{
	// �G�l�~�[�i�^���N�j�̍U���p�̃R���W�������擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player");
	// �R���W�����̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		// �R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_charaCon))
		{
			m_hp -= 1;
			return;
		}
	}
}

void Enemy::ProcessCommonStateTransition()
{
	if (timer >= 4.0f)
	{
		timer = 0.0f;
	}
	if (m_isAttack == true && m_timer >= 14.0f) {
	//	Matrix matrix = m_modelRender.GetBone(m_gunId)->GetWorldMatrix();
		m_effect = NewGO <EffectEmitter>(0);
		Vector3 effectposi = m_position;
		effectposi.y += 50.0f;
		//effectposi += m_forward * 100.0f;

		//Vector3 m_right = Vector3::AxisX;
		//m_rotation.Apply(m_right);
		//effectposi += m_right * -7.5f;
		Vector3 effectDir = m_endVector - m_startVector;
		effectDir.Normalize();
		Quaternion effectRot;
		effectRot.SetRotation(Vector3::AxisZ, effectDir);
	//	m_rotation = effectRot;
		m_effect->Init(0);
		m_effect->SetPosition(effectposi);
		m_effect->SetRotation(m_rotation);
		// �G�t�F�N�g�̑傫����ݒ肷��B
		Vector3 sca = Vector3{ 10.0f,10.0f,10.0f };
		m_effect->SetScale(sca);
		//m_effect->SetWorldMatrix(matrix);
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
		//�ҋ@�X�e�[�g�ɑJ��
		m_enemyState = enEnemyState_Idle;
		return;
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
		m_modelRender.SetAnimationSpeed(1.2f);
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
	//(void)clipName;
	//if (wcscmp(eventName, L"Run_step") == 0) {
	//	// �����B
	//	// ���ʉ����Đ�����B
	//	m_gameSound->PlayerStepSE(0.4f);
	//}

	//if (wcscmp(eventName, L"attack") == 0) {
	//	// �����B
	//	// ���ʉ����Đ�����B
	//	m_gameSound->PlayerAttackSE(0.3f);
	//}
}

void Enemy::Render(RenderContext& rc)
{
	if (m_timer <= 11.5f) {
		return;
	}
		// ���f�����h���[�B
		m_modelRender.Draw(rc);
}