#include "stdafx.h"
#include "Cylinder.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "GameEffect.h"

namespace
{
	// int�^
	int TOWER_HP = 40;				// �^���[��HP
	// float�^
	float DARWTIMER = 11.0f;		// �`�攻��
	float YPOSI = 149.0f;			// Y���W
}

bool Cylinder::Start()
{
	// �ʏ탂�f��
	m_modelRender.Init("Assets/modelData/testModel/cylinder.tkm", false);
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

	m_renderingEngine = &g_renderingEngine;
	//�����_�[�^�[�Q�b�g���쐬����B
	m_renderingEngine->InitTextureTarget(m_number);
	//�e�N�X�`��������������B
	m_renderingEngine->SpriteInit(m_modelRender.GetTkm()->m_albedo, m_number);

	// �G�t�F�N�g��ǂݍ���œo�^����B
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/efk/smoke.efk");

	// �Q�[���̃C���X�^���X��ǂݍ��ށB
	m_game = FindGO<Game>("game");

	return true;
}
void Cylinder::Update()
{
	// �^���[��HP��0�̏ꍇ
	if (m_game->m_paintnumber == TOWER_HP)
	{
		// �^�C�}�[���J�E���g����
		m_timer += g_gameTime->GetFrameDeltaTime();
		m_falltimer += g_gameTime->GetFrameDeltaTime();
		if (m_position.y >= -100.0f && m_timer >= 0.05f) {
			m_effect = NewGO <EffectEmitter>(0);
			Vector3 effectposi = m_position;
			effectposi.y = 150.0f;
			m_effect->Init(1);
			m_effect->SetPosition(effectposi);
			// �G�t�F�N�g�̑傫����ݒ肷��B
			m_effect->SetScale(m_scale * 8.0f);
			m_effect->Play();
			m_timer = 0.0f;
		}
		if (m_position.y >= -150.0f && m_falltimer >= 2.5f) {
			m_position.y -= 0.65f;
			m_physicsStaticObject.SetRotation(m_position, m_rotation);
		}
	}

	// �G�̃C���X�^���X��T���Ď����Ă���
	const auto& m_enemys = FindGOs<Enemy>("enemy");
	for (auto m_enemy : m_enemys)
	{
		// �G���`�悳��Ă��Ȃ�������
		if (m_enemy->m_timer <= DARWTIMER)
		{
			// �^���[�͉��ɂ���B
			m_towerUP = false;
		}
		// �G���`�悳��Ă�����B
		else {
			// �^���[�͏�ɂ���B
			m_towerUP = true;
		}
	}

	// �^���[��HP��1�ȏ�A���^���[�����ȏ�̍��W�ɂ���ꍇ�B
	if (m_game->m_paintnumber < TOWER_HP && m_towerUP == false && m_position.y > -200.0f) {
		// �^�C�}�[���J�E���g����
		m_timer += g_gameTime->GetFrameDeltaTime();
		// ��莞�Ԃ��������珈�����s���B
		if (m_timer >= 0.05f) {
			// �G�t�F�N�g���Đ�����B
			m_effect = NewGO <EffectEmitter>(0);
			// �G�t�F�N�g�ǂݍ��ށB
			m_effect->Init(1);
			// ���W��ݒ肷��B
			Vector3 effectposi = m_position;
			effectposi.y = 150.0f;
			m_effect->SetPosition(effectposi);
			// �G�t�F�N�g�̑傫����ݒ肷��B
			m_effect->SetScale(m_scale * 8.0f);
			// �G�t�F�N�g���Đ�����B
			m_effect->Play();
			// �^�C�}�[�����Z�b�g����
			m_timer = 0.0f;
		}
		float ramz = -10 - rand() % 21;
		float ramx = -10 - rand() % 21;

		m_position.x = ramx;
		m_position.z = ramz;

		m_position.y -= 2.0f;
		m_physicsStaticObject.SetRotation(m_position, m_rotation);
	}
	else if (m_towerUP == true && m_position.y < 150.0f) {
		m_timer += g_gameTime->GetFrameDeltaTime();
		if (m_position.y <= 140.0f && m_timer >= 0.05f) {
			m_effect = NewGO <EffectEmitter>(0);
			Vector3 effectposi = m_position;
			effectposi.y = 150.0f;
			m_effect->Init(1);
			m_effect->SetPosition(effectposi);
			// �G�t�F�N�g�̑傫����ݒ肷��B
			m_effect->SetScale(m_scale * 8.0f);
			m_effect->Play();
			m_timer = 0.0f;
		}
		float ramx = -10 - rand() % 21;
		float ramz = -10 - rand() % 21;

		m_position.x = ramx;
		m_position.z = ramz;
		m_position.y += 2.0f;
		m_physicsStaticObject.SetRotation(m_position, m_rotation);
		if (m_position.y >= 150.0f) { m_position.y = 150.0f; }
	}
	
	m_player = FindGO<Player>("player");
	m_startVector = m_player->GetStartVector();
	m_endVector = m_player->GetEndVector();

	if (g_pad[0]->IsPress(enButtonRB1) == true && m_position.y >= YPOSI)
	{
		m_renderingEngine->SpriteDraw( 1, m_modelRender, m_number, m_startVector, m_endVector);
	}

	//���f���̍��W��ݒ�B
	m_modelRender.SetPosition(m_position);
	//���f���̉�]��ݒ�B
	m_modelRender.SetRotation(m_rotation);
	//���f���̑傫����ݒ�B
	m_modelRender.SetScale(m_scale);
	//���f���̍X�V�����B
	m_modelRender.Update();
}
void Cylinder::Render(RenderContext& rc)
{
	// �ʏ탂�f����`�悷��
	m_modelRender.Draw(rc);
}