#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Background.h"
#include "Stairs.h"
#include "Floor.h"
#include "Box.h"
#include "Cylinder.h"
#include "Triangle.h"
#include "Player.h"
#include "Enemy.h"

#include "Fade.h"
#include "GameUI.h"
#include "Title.h"
#include "Result.h"

#include "SkyCube.h"
#include "Clearmodel.h"

namespace
{
	const Vector3 PLAYER_SET_POSITION = { 0.0f,250.0f,-500.0f };	//�v���C���[�̃Z�b�g�|�W�V����
	const Vector3 FLOOR_SET_POSITION = { 00.0f,0.0f,00.0f };		//���̃Z�b�g�|�W�V����
	const Vector3 CYLINDER_SET_POSI = { 0.0f,-200.0f,0.0f };		//���̃Z�b�g�|�W�V����


	const int PRIORITY_ZERO = 0;								//�v���C�I���e�B �D�挠
	const float PLUS_COLOR = 0.015f;							//���Z����J���[�̒l
	const float MAX_AMBIENT_COLOR = 2.0f;						//�����̍ő�l
	const float SPRITE_COLOR = 1.0f;							//�X�v���C�g�̃J���[�l
	const float PLUS_ALPHA = 0.2f;								//��Z���郿�l
}

Game::~Game()
{
	const auto& m_enemys = FindGOs<Enemy>("enemy");
	for (auto m_enemy : m_enemys)
	{
		DeleteGO(m_enemy);
	}
	const auto& m_boxs = FindGOs<Box>("box");
	for (auto m_box : m_boxs)
	{
		DeleteGO(m_box);
	}
	const auto& m_triangles = FindGOs<Triangle>("triangle");
	for (auto m_triangle : m_triangles)
	{
		DeleteGO(m_triangle);
	}
	const auto& m_cylinders = FindGOs<Cylinder>("cylinder");
	for (auto m_cylinder : m_cylinders)
	{
		DeleteGO(m_cylinder);
	}

	const auto& m_skys = FindGOs<SkyCube>("sky");
	for (auto m_sky: m_skys)
	{
		DeleteGO(m_sky);
	}
	const auto& m_backgrounds = FindGOs<Background>("background");
	for (auto m_background: m_backgrounds)
	{
		DeleteGO(m_background);
	}
	const auto& m_stairss = FindGOs<Stairs>("stairs");
	for (auto m_stairs : m_stairss)
	{
		DeleteGO(m_stairs);
	}

	DeleteGO(m_gameCamera);
	DeleteGO(m_player);
	DeleteGO(m_floor);
	DeleteGO(m_ui);

}
bool Game::Start()
{
	int i = 1;


	for (int i = 1;i < 5;i++) {
		//�p�X
		std::string number;
		//������ɕϊ�
		number = std::to_string(i);
		FILE[i] = "Assets/Level/testStage.phase";
		FILE[i] += number;
		FILE[i] += ".tkl";
	}

	SkyCube* m_sky = NewGO<SkyCube>(0, "sky");


	//���x�����\�z����B
	m_levelRender[phase].Init(FILE[phase].c_str(), [&](LevelObjectData& objData) {
		
		if (objData.EqualObjectName(L"player") == true) {
			// �v���C���[�̃I�u�W�F�N�g�𐶐�����B
			m_player = NewGO<Player>(0, "player");
			m_player->SetPosition(objData.position);
			//m_player->SetRotation(objData.rotation);
			//m_player->SetScale(objData.scale);
			//true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ĕz�u�����B
			return true;
		}

		if (objData.EqualObjectName(L"stage") == true) {
			// ���̃I�u�W�F�N�g�𐶐�����B
			m_background = NewGO<Background>(0, "background");
			m_background->SetPosition(objData.position);
			m_background->SetRotation(objData.rotation);
			m_background->SetScale(objData.scale);
			m_background->SetNumber(i);
			i++;
			//true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ĕz�u�����B
			return true;
		}
		if (objData.EqualObjectName(L"stairs") == true) {
			// ���̃I�u�W�F�N�g�𐶐�����B
			m_stairs = NewGO<Stairs>(0, "stairs");
			m_stairs->SetPosition(objData.position);
			m_stairs->SetRotation(objData.rotation);
			m_stairs->SetScale(objData.scale);
			m_stairs->SetNumber(i);
			i++;
			//true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ĕz�u�����B
			return true;
		}

		if (objData.EqualObjectName(L"enemy") == true) {
			// ���̃I�u�W�F�N�g�𐶐�����B
			m_enemy = NewGO<Enemy>(0, "enemy");
			m_enemy->SetPosition(objData.position);
			m_enemy->SetRotation(objData.rotation);
			m_number++;
			m_enemy->phase = 0;
		//	m_enemy->SetScale(objData.scale);
			//true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ĕz�u�����B
			return true;
		}

		if (objData.EqualObjectName(L"box") == true) {
			// ���̃I�u�W�F�N�g�𐶐�����B
			m_box = NewGO<Box>(0, "box");
			m_box->SetPosition(objData.position);
			m_box->SetRotation(objData.rotation);
			m_box->SetScale(objData.scale);
			m_box->SetNumber(i);
			i++;
			//true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ĕz�u�����B
			return true;
		}

		if (objData.EqualObjectName(L"cylinder") == true) {
			// ���̃I�u�W�F�N�g�𐶐�����B
			m_cylinder = NewGO<Cylinder>(0, "cylinder");
			m_cylinder->SetPosition(CYLINDER_SET_POSI);
			m_cylinder->SetRotation(objData.rotation);
			m_cylinder->SetScale(objData.scale);
			m_cylinder->SetNumber(i);
			i++;
			//true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ĕz�u�����B
			return true;
		}

		if (objData.EqualObjectName(L"triangle") == true) {
			// ���̃I�u�W�F�N�g�𐶐�����B
			m_triangle = NewGO<Triangle>(0, "triangle");
			m_triangle->SetPosition(objData.position);
			m_triangle->SetRotation(objData.rotation);
			m_triangle->SetScale(objData.scale);
			//true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ĕz�u�����B
			return true;
		}
		return true;
		});

	m_ui = NewGO<GameUI>(0, "gameui");

	m_floor = NewGO<Floor>(0, "floor");

	//m_player = NewGO<Player>(0, "player");
	//m_player->SetPosition({ 0.0f,150.0f,-300.0f });

	// �����蔻��̕`��
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//auto clearmodel = NewGO<Clearmodel>(0, "model");
	//clearmodel->SetPosition({ 0.0f,150.0f,-300.0f });

	// �J�����̃I�u�W�F�N�g�𐶐�����B
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_fade = FindGO<Fade>("fade");
	m_fade->StartFadeIn();
	return true;
}

void Game::Update()
{

	if (m_paintnumber == 42 || phase >= 5)
	{
		m_timer += g_gameTime->GetFrameDeltaTime();
	}

	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Title>(0, "title");
			//���g���폜����B
			DeleteGO(this);
		}
	}
	else {
		//A�{�^������������B
		if (m_paintnumber >= 42 && m_timer >= 3.0f ||
			phase >= 5 && m_timer >= 3.0f) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}

	m_player = FindGO<Player>("player");
	if (m_number == m_player->m_enemynumber) {
		if (phase <= 4) {
			m_ui->m_number += 1;
			phase += 1;
		}
		if (phase == 5) {
			//phase += 1;
			//NewGO<Title>(0, "title");
			////���g���폜����B
			//DeleteGO(this);
			return;
		}
		if (phase < 4) {
			m_levelRender[phase].Init(FILE[phase].c_str(), [&](LevelObjectData& objData) {
				if (objData.EqualObjectName(L"enemy") == true) {
					// ���̃I�u�W�F�N�g�𐶐�����B
					m_enemy = NewGO<Enemy>(0, "enemy");
					m_enemy->SetPosition(objData.position);
					m_enemy->SetRotation(objData.rotation);
					m_number++;
					m_enemy->phase = 1;
					//true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ĕz�u�����B
					return true;
				}
				return true;
				});
		}
	}
}

void Game::Render(RenderContext& rc)
{

}