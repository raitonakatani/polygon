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
	const Vector3 PLAYER_SET_POSITION = { 0.0f,350.0f,-500.0f };	//プレイヤーのセットポジション
	const Vector3 FLOOR_SET_POSITION = { 00.0f,0.0f,00.0f };		//床のセットポジション


	const int PRIORITY_ZERO = 0;								//プライオリティ 優先権
	const float PLUS_COLOR = 0.015f;							//加算するカラーの値
	const float MAX_AMBIENT_COLOR = 2.0f;						//環境光の最大値
	const float SPRITE_COLOR = 1.0f;							//スプライトのカラー値
	const float PLUS_ALPHA = 0.2f;								//乗算するα値
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
	// プレイヤーのオブジェクトを生成する
	m_player = NewGO<Player>(0, "player");
	m_player->SetPosition(PLAYER_SET_POSITION);

	// カメラのオブジェクトを生成する。
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	//レベルを構築する。
	m_levelRender.Init("Assets/Level/Model.tkl", [&](LevelObjectData& objData) {

		if (objData.EqualObjectName(L"stage") == true) {
			// 床のオブジェクトを生成する。
			m_floor = NewGO<Floor>(0, "floor");
			m_floor->SetPosition(objData.position);
			m_floor->SetRotation(objData.rotation);
			m_floor->SetScale(objData.scale);
			//trueにすると、レベルの方でモデルが読み込まれて配置される。
			return true;
		}

		if (objData.EqualObjectName(L"box") == true) {
			// 床のオブジェクトを生成する。
			m_box = NewGO<Box>(0, "box");
			m_box->SetPosition(objData.position);
			m_box->SetRotation(objData.rotation);
			m_box->SetScale(objData.scale);
			m_box->SetNumber(i);
			i++;
			//trueにすると、レベルの方でモデルが読み込まれて配置される。
			return true;
		}

		if (objData.EqualObjectName(L"cylinder") == true) {
			// 床のオブジェクトを生成する。
			m_cylinder = NewGO<Cylinder>(0, "cylinder");
			m_cylinder->SetPosition(objData.position);
			m_cylinder->SetRotation(objData.rotation);
			m_cylinder->SetScale(objData.scale);
			//trueにすると、レベルの方でモデルが読み込まれて配置される。
			return true;
		}

		if (objData.EqualObjectName(L"triangle") == true) {
			// 床のオブジェクトを生成する。
			m_triangle = NewGO<Triangle>(0, "triangle");
			m_triangle->SetPosition(objData.position);
			m_triangle->SetRotation(objData.rotation);
			m_triangle->SetScale(objData.scale);
			//trueにすると、レベルの方でモデルが読み込まれて配置される。
			return true;
		}


		return true;
		});

	// 当たり判定の描画
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