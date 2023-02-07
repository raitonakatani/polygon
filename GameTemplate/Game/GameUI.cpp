#include "stdafx.h"
#include "GameUI.h"
#include "Game.h"
#include "Fade.h"

bool GameUI::Start()
{
	//コンパスの画像を読み込む
	m_compass.Init("Assets/sprite/compass.DDS", 256, 256);
	//指針の画像を読み込む
	m_compassguideline.Init("Assets/sprite/guideline.DDS", 256, 256);

	m_yposi = 800.0f;
	m_gameover.Init("Assets/sprite/GameOver.DDS", 1024, 128);
	m_gameover.SetPosition({ 0.0f,m_yposi,1.0f });

	//フェーズの画像を読み込む
	m_directionPhase[0].Init("Assets/sprite/east.DDS", 1024, 128);
	m_directionPhase[2].Init("Assets/sprite/west.DDS", 1024, 128);
	m_directionPhase[1].Init("Assets/sprite/south.DDS", 1024, 128);
	m_directionPhase[3].Init("Assets/sprite/north.DDS", 1024, 128);
	for (int i = 1;i < 5;i++) {
		//パス
		std::string number;
		//文字列に変換
		number = std::to_string(i);
		std::string FILE = "Assets/sprite/phase";
		FILE += number;
		FILE += ".DDS";
		m_phase[i].Init(FILE.c_str(),512,128);
	}

	m_game = FindGO<Game>("game");
	m_fade = FindGO<Fade>("fade");

	return true;
}

void GameUI::Update()
{
	m_gameover.SetPosition({ 0.0f,m_yposi,0.0f });
	m_gameover.SetScale({ 1.5f,1.5f,1.5f });
	m_gameover.Update();


	//カメラの回転量をもとにコンパスを回す
	m_forward = g_camera3D->GetForward();
	m_rot = atan2f(m_forward.x, m_forward.z);
	//Z軸周りの回転
	m_rotation.SetRotationZ(m_rot);
	m_compass.SetPosition({ -650.0f,-300.0f,0.0f });
	m_compass.SetRotation(m_rotation);
	m_compass.Update();

	m_compassguideline.SetPosition({ -650.0f,-300.0f,0.0f });
	m_compassguideline.Update();

	if (m_reset ==m_number) {
		m_timer=0.0f;
		m_x = 0.0f;
		m_y = 675.0f;
		m_y2 = 550.0f;
		m_reset += 1;
		m_scale = Vector3::One;
	}

	m_timer += g_gameTime->GetFrameDeltaTime();

	if (m_timer >= 5.0f &&m_timer <= 5.5f) {
		m_y -= 16.0f;
		m_y2 -= 16.0f;
	}
	if (m_timer > 7.5f && m_timer <= 10.5f) {
		m_y += 1.2f;
		m_y2 += 1.6f;
		m_x += 3.25f;
		m_scale *= 0.995f;
	}
	m_phase[m_number].SetPosition({ m_x, m_y, 0.0f});
	m_phase[m_number].SetScale(m_scale);
	m_phase[m_number].Update();


	m_directionPhase[m_number-1].SetPosition({ m_x, m_y2, 0.0f });
	m_directionPhase[m_number-1].SetScale(m_scale);
	m_directionPhase[m_number-1].Update();

	float alpha = 1.0f - (m_fade->m_currentAlpha * 2.0f);

	m_directionPhase[m_number - 1].SetMulColor({ 1.0f,1.0f,1.0f,alpha });
	m_phase[m_number].SetMulColor({ 1.0f,1.0f,1.0f,alpha });
	m_compass.SetMulColor({ 1.0f,1.0f,1.0f,alpha });
	m_compassguideline.SetMulColor({ 1.0f,1.0f,1.0f,alpha });
	m_gameover.SetMulColor({ 1.0f,1.0f,1.0f,alpha });
}

void GameUI::Render(RenderContext& rc)
{
	//コンパスの描画
	m_compass.Draw(rc);
	//指針の描画
	m_compassguideline.Draw(rc);

	m_phase[m_number].Draw(rc);
	m_directionPhase[m_number - 1].Draw(rc);

	if (m_game->m_paintnumber >= 41) {
		m_yposi -= 5.0f;
		if (m_yposi <= 0.0f)
		{
			m_yposi = 0.0f;
			m_game->m_paintnumber = 42;
		}
		m_gameover.Draw(rc);
	}
}
