#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"

namespace
{

	const int PAD_NUMBER = 0;									//ゲームパッドのナンバー


	const float TARGET_YPOSITION = 150.0f;
	const float ANGLE = 2.0f;					//回転角度
	const float MAX_ANGLE = 0.7f;
	const float SET_NEAR = 1.0f;				// 近平面
	const float SET_FAR = 40000.0f;				// 遠平面

	const Vector3 NOMAL_CAMERA_POSI = { 0.0f, 80.0f, -250.0f };
}

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
	//インスタンスを削除する。
	DeleteGO(this);
}
bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(NOMAL_CAMERA_POSI);
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("player");

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(SET_NEAR);
	g_camera3D->SetFar(SET_FAR);

	m_game = FindGO<Game>("game");

	return true;
}
void GameCamera::Update()
{

	if (m_game->m_paintnumber == 40 && m_timer <= 15.0f)
	{
		m_timer += g_gameTime->GetFrameDeltaTime();
		m_pos = m_game->enemyposi;
		Vector3 target = m_game->enemypaint;
		if (m_timer <= 13.0f) {
			int ramx = -5 - rand() % 11;
			int ramz = -5 - rand() % 11;
			int ramy = -3 - rand() % 7;
			m_pos.x += ramx;
			m_pos.z += ramz;
			m_pos.y += ramz;

			int targetx = -5 - rand() % 11;
			int targetz = -5 - rand() % 11;
			int targety = -3 - rand() % 7;
			target.x += targetx;
			target.z += targetz;
			target.y += targety;
		}

		//メインカメラに注視点と視点を設定する。
		g_camera3D->SetPosition(m_pos);
		g_camera3D->SetTarget(target);

		g_camera3D->Update();

		return;
	}
	else if (m_game->m_paintnumber == 40 && m_timer >= 15.0f) {
		m_game->m_paintnumber = 41;
	}



	//通常カメラ
	Vector3 target = m_player->GetPosition();
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += TARGET_YPOSITION;
	m_toCameraPosOld = m_toCameraPos;

	//パッドの入力を使ってカメラを回す。
	float x2 = g_pad[PAD_NUMBER]->GetRStickXF();
	float y2 = g_pad[PAD_NUMBER]->GetRStickYF();


	//Y軸周りの回転
	m_xyRot.SetRotationDeg(Vector3::AxisY, ANGLE * x2);
	m_xyRot.Apply(m_toCameraPos);
	//X軸周りの回転。
	Vector3 axisX2;
	axisX2.Cross(Vector3::AxisY, m_toCameraPos);
	axisX2.Normalize();
	m_xyRot.SetRotationDeg(axisX2, ANGLE * y2);
	m_xyRot.Apply(m_toCameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir2 = m_toCameraPos;
	toPosDir2.Normalize();
	if (toPosDir2.y < -MAX_ANGLE) {
		//カメラが上向きすぎ。
		m_toCameraPos = m_toCameraPosOld;
	}
	else if (toPosDir2.y > MAX_ANGLE) {
		//カメラが下向きすぎ。
		m_toCameraPos = m_toCameraPosOld;
	}

	//視点を計算する。
	m_pos = target + m_toCameraPos;

	if (m_game->phase == 5) {
		Vector3 cameraposi = m_toCameraPos;
		cameraposi.x *= -1.0f;
		cameraposi.z *= -1.0f;
		m_pos = target + m_toCameraPos;
	}

	//メインカメラに注視点と視点を設定する。
	g_camera3D->SetPosition(m_pos);
	g_camera3D->SetTarget(target);

	//カメラの更新。
	g_camera3D->Update();

}

void GameCamera::Render(RenderContext& rc)
{

}
