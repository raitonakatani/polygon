#include "stdafx.h"
#include "Cylinder.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"

// EffectEmitter���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "graphics/effect/EffectEmitter.h"


namespace
{
	float DARWTIMER = 11.0f; 
	float YPOSI = 149.0f;
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

	m_renderingEngine->InitTextureTarget(m_number);
	m_renderingEngine->SpriteInit(m_modelRender.GetTkm()->m_albedo, m_number);

	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/efk/smoke.efk");

	m_game = FindGO<Game>("game");

	return true;
}
void Cylinder::Update()
{
	if (m_game->m_paintnumber == 40)
	{
		m_timer += g_gameTime->GetFrameDeltaTime();
		m_falltimer += g_gameTime->GetFrameDeltaTime();
		if (m_position.y >= 0.0f && m_timer >= 0.05f) {
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

	const auto& m_enemys = FindGOs<Enemy>("enemy");
	for (auto m_enemy : m_enemys)
	{
		if (m_enemy->m_timer <= DARWTIMER)
		{
			m_towerUP = false;
		}
		else {
			m_towerUP = true;
		}
	}

	if (m_game->m_paintnumber < 40) {
		if (m_towerUP == false && m_position.y > -200.0f)
		{
			m_timer += g_gameTime->GetFrameDeltaTime();
			m_falltimer += g_gameTime->GetFrameDeltaTime();
			if (m_position.y >= -200.0f && m_timer >= 0.05f) {
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
			int ramz = -10 - rand() % 21;
			int ramx = -10 - rand() % 21;

			m_position.x = ramx;
			m_position.z = ramz;

			m_position.y -= 2.0f;
			m_physicsStaticObject.SetRotation(m_position, m_rotation);
		}
		else if (m_towerUP == true && m_position.y < 150.0f) {
			m_timer += g_gameTime->GetFrameDeltaTime();
			m_falltimer += g_gameTime->GetFrameDeltaTime();
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
			int ramx = -10 - rand() % 21;
			int ramz = -10 - rand() % 21;

			m_position.x = ramx;
			m_position.z = ramz;
			m_position.y += 2.0f;
			m_physicsStaticObject.SetRotation(m_position, m_rotation);
			if (m_position.y >= 150.0f) { m_position.y = 150.0f; }
		}
	}
	m_player = FindGO<Player>("player");
	m_startVector = m_player->GetStartVector();
	m_endVector = m_player->GetEndVector();

	if (g_pad[0]->IsPress(enButtonRB1) == true && m_position.y >= YPOSI)
	{
		Vector3 posi = m_player->GetPosition();
		m_renderingEngine->SpriteDraw(posi, 1, m_modelRender, m_number, 0, m_startVector, m_endVector);
	}

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
}
void Cylinder::Render(RenderContext& rc)
{
	// �ʏ탂�f����`�悷��
	m_modelRender.Draw(rc);
}