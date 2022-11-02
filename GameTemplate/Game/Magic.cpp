#include "stdafx.h"
#include "Magic.h"

#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"


//EffectEmitter���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "graphics/effect/EffectEmitter.h"


Magic::Magic()
{

}

Magic::~Magic()
{
	//�G�t�F�N�g���~����B
	m_effectEmitter->Stop();
	//�R���W�����I�u�W�F�N�g���폜����B
	DeleteGO(m_collisionObject);
	DeleteGO(m_effectEmitter);
}

bool Magic::Start()
{
	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/efk/Magic.efk");

	//�G�t�F�N�g��ǂݍ��ށB
	//EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/efk/enemy.efk");

	//�G�t�F�N�g�̃I�u�W�F�N�g���쐬����B
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(0);
	//�G�t�F�N�g�̑傫����ݒ肷��B
	//m_effectEmitter->SetScale(m_scale * 20.0f);
//�ړ����x���v�Z�B
	m_moveSpeed = Vector3::AxisZ;
	m_rotation.Apply(m_moveSpeed);
	m_position += m_moveSpeed * 50.0f;
	m_moveSpeed *= 1200.0f;
	m_rotation.AddRotationDegY(360.0f);
	//��]��ݒ肷��B
	m_effectEmitter->SetRotation(m_rotation);
	m_effectEmitter->Play();


	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);

	if (m_enMagician == enMagician_Enemy2)
	{
		//�G�t�F�N�g�̑傫����ݒ肷��B
		m_effectEmitter->SetScale(m_scale * 20.0f);

		//����̃R���W�������쐬����B
		m_collisionObject->CreateSphere(m_position, Quaternion::Identity, 50.0f * m_scale.z);
	}

	else if (m_enMagician == enMagician_Enemy3)
	{
		//�G�t�F�N�g�̑傫����ݒ肷��B
		m_effectEmitter->SetScale(m_scale * 30.0f);

		//����̃R���W�������쐬����B
		m_collisionObject->CreateSphere(m_position, Quaternion::Identity, 75.0f * m_scale.z);
	}

	else if (m_enMagician == enMagician_Enemy4)
	{
		//�G�t�F�N�g�̑傫����ݒ肷��B
		m_effectEmitter->SetScale(m_scale * 20.0f);

		//����̃R���W�������쐬����B
		m_collisionObject->CreateSphere(m_position, Quaternion::Identity, 50.0f * m_scale.z);
	}


	//���O��enemy_fireball�ɂ���B
	m_collisionObject->SetName("Magic");

	//���菊�I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���B
	m_collisionObject->SetIsEnableAutoDelete(false);
	return true;
}

void Magic::Update()
{
	//���W���ړ�������B
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
	//�G�t�F�N�g�̍��W��ݒ肷��B
	m_effectEmitter->SetPosition(m_position);
	//�R���W�����I�u�W�F�N�g�ɍ��W��ݒ肷��B
	m_collisionObject->SetPosition(m_position);

	//�^�C�}�[�����Z����B
	m_timer += g_gameTime->GetFrameDeltaTime();

	//�^�C�}�[��1.0f�ȏゾ������B
	if (m_timer >= 1.0f)
	{
		//���g���폜����B
		DeleteGO(this);
	}
}