#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Background.h"
#include "Floor.h"
#include "Box.h"
#include "Cylinder.h"
#include "Triangle.h"
#include "Player.h"
#include "Enemy.h"

#include "Fade.h"
#include "GameUI.h"
#include "Result.h"

#include "SkyCube.h"

namespace
{
	const Vector3 PLAYER_SET_POSITION = { 0.0f,250.0f,-500.0f };	//プレイヤーのセットポジション
	const Vector3 FLOOR_SET_POSITION = { 00.0f,0.0f,00.0f };		//床のセットポジション


	const int PRIORITY_ZERO = 0;								//プライオリティ 優先権
	const float PLUS_COLOR = 0.015f;							//加算するカラーの値
	const float MAX_AMBIENT_COLOR = 2.0f;						//環境光の最大値
	const float SPRITE_COLOR = 1.0f;							//スプライトのカラー値
	const float PLUS_ALPHA = 0.2f;								//乗算するα値
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

	DeleteGO(m_gameCamera);
	DeleteGO(m_player);
	DeleteGO(m_floor);
	DeleteGO(m_background);

}
bool Game::Start()
{
	int i = 1;


	for (int i = 1;i < 5;i++) {
		//パス
		std::string number;
		//文字列に変換
		number = std::to_string(i);
		FILE[i] = "Assets/Level/testStage.phase";
		FILE[i] += number;
		FILE[i] += ".tkl";
	}

	SkyCube* m_sky = NewGO<SkyCube>(0, "sky");


	//レベルを構築する。
	m_levelRender[phase].Init(FILE[phase].c_str(), [&](LevelObjectData& objData) {
		
		if (objData.EqualObjectName(L"player") == true) {
			// プレイヤーのオブジェクトを生成する。
			m_player = NewGO<Player>(0, "player");
			m_player->SetPosition(objData.position);
			//m_player->SetRotation(objData.rotation);
			//m_player->SetScale(objData.scale);
			//trueにすると、レベルの方でモデルが読み込まれて配置される。
			return true;
		}

		//if (objData.EqualObjectName(L"floor") == true) {
		//	// 床のオブジェクトを生成する。
		//	m_floor = NewGO<Floor>(0, "floor");
		//	m_floor->SetPosition(objData.position);
		//	m_floor->SetRotation(objData.rotation);
		//	m_floor->SetScale(objData.scale);
		//	//trueにすると、レベルの方でモデルが読み込まれて配置される。
		//	return true;
		//}

		if (objData.EqualObjectName(L"stage") == true) {
			// 床のオブジェクトを生成する。
			m_background = NewGO<Background>(0, "background");
			m_background->SetPosition(objData.position);
			m_background->SetRotation(objData.rotation);
			m_background->SetScale(objData.scale);
			//trueにすると、レベルの方でモデルが読み込まれて配置される。
			return true;
		}

		if (objData.EqualObjectName(L"enemy") == true) {
			// 床のオブジェクトを生成する。
			m_enemy = NewGO<Enemy>(0, "enemy");
			m_enemy->SetPosition(objData.position);
			m_enemy->SetRotation(objData.rotation);
			m_number++;
			m_enemy->phase = 0;
		//	m_enemy->SetScale(objData.scale);
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
			m_cylinder->SetNumber(i);
			i++;
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

	m_ui = NewGO<GameUI>(0, "gameui");

	m_floor = NewGO<Floor>(0, "floor");

	// 当たり判定の描画
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();


	// カメラのオブジェクトを生成する。
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_fade = FindGO<Fade>("fade");
	m_fade->StartFadeIn();
	return true;
}

void Game::Update()
{
	const auto& enemys = FindGOs<Enemy>("enemy");
	for (auto enemy : enemys)
	{
		if (enemy->gameover == true)
		{
			NewGO<Result>(0, "result");
			DeleteGO(this);
			return;
		}
	}

	m_player = FindGO<Player>("player");
	if (m_number == m_player->m_enemynumber) {
		m_ui->m_number += 1;
		phase += 1;
		if (phase == 5) {
			NewGO<Result>(0, "result");
			DeleteGO(this);
			return;
		}
		m_levelRender[phase].Init(FILE[phase].c_str(), [&](LevelObjectData& objData) {
			if (objData.EqualObjectName(L"enemy") == true) {
				// 床のオブジェクトを生成する。
				m_enemy = NewGO<Enemy>(0, "enemy");
				m_enemy->SetPosition(objData.position);
				m_enemy->SetRotation(objData.rotation);
				m_number++;
				m_enemy->phase = 1;
				//	m_enemy->SetScale(objData.scale);
					//trueにすると、レベルの方でモデルが読み込まれて配置される。
				return true;
			}
			//phase += 1;
			return true;
			});
	}
}

void Game::Render(RenderContext& rc)
{

}