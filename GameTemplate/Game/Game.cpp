#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Background.h"
#include "Floor.h"
#include "Box.h"
#include "Cylinder.h"
#include "Triangle.h"
#include "Player.h"

#include "SkyCube.h"

namespace
{
	const Vector3 PLAYER_SET_POSITION = { 0.0f,350.0f,-500.0f };	//�v���C���[�̃Z�b�g�|�W�V����
	const Vector3 FLOOR_SET_POSITION = { 00.0f,0.0f,00.0f };		//���̃Z�b�g�|�W�V����


	const int PRIORITY_ZERO = 0;								//�v���C�I���e�B �D�挠
	const float PLUS_COLOR = 0.015f;							//���Z����J���[�̒l
	const float MAX_AMBIENT_COLOR = 2.0f;						//�����̍ő�l
	const float SPRITE_COLOR = 1.0f;							//�X�v���C�g�̃J���[�l
	const float PLUS_ALPHA = 0.2f;								//��Z���郿�l
}

Game::~Game()
{
	const auto& m_gameCameras = FindGOs<GameCamera>("gameCamera");
	for (auto m_gameCamera : m_gameCameras)
	{
		DeleteGO(m_gameCamera);
	}


	DeleteGO(m_player);
	DeleteGO(m_floor);

}
bool Game::Start()
{
	int i = 1;
	// �v���C���[�̃I�u�W�F�N�g�𐶐�����
	m_player = NewGO<Player>(0, "player");
	m_player->SetPosition(PLAYER_SET_POSITION);

	// �J�����̃I�u�W�F�N�g�𐶐�����B
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	//���x�����\�z����B
	m_levelRender.Init("Assets/Level/Model.tkl", [&](LevelObjectData& objData) {

		if (objData.EqualObjectName(L"stage") == true) {
			// ���̃I�u�W�F�N�g�𐶐�����B
			m_floor = NewGO<Floor>(0, "floor");
			m_floor->SetPosition(objData.position);
			m_floor->SetRotation(objData.rotation);
			m_floor->SetScale(objData.scale);
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
			m_cylinder->SetPosition(objData.position);
			m_cylinder->SetRotation(objData.rotation);
			m_cylinder->SetScale(objData.scale);
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

	// �����蔻��̕`��
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	SkyCube* m_sky = NewGO<SkyCube>(0, "sky");


	return true;
}

void Game::Update()
{
}

void Game::Render(RenderContext& rc)
{

}