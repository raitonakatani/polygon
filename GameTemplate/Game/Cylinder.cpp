#include "stdafx.h"
#include "Cylinder.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "GameEffect.h"

namespace
{
	// int型
	int TOWER_HP = 40;				// タワーのHP
	// float型
	float DARWTIMER = 11.0f;		// 描画判定
	float YPOSI = 149.0f;			// Y座標
}

bool Cylinder::Start()
{
	// 通常モデル
	m_modelRender.Init("Assets/modelData/testModel/cylinder.tkm", false);
	// モデルの座標を設定。
	m_modelRender.SetPosition(m_position);
	// モデルの回転を設定。
	m_modelRender.SetRotation(m_rotation);
	// モデルの大きさを設定。
	m_modelRender.SetScale(m_scale);
	// モデルの更新処理。
	m_modelRender.Update();
	// 静的物理オブジェクトの初期化処理。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);

	m_renderingEngine = &g_renderingEngine;
	//レンダーターゲットを作成する。
	m_renderingEngine->InitTextureTarget(m_number);
	//テクスチャを初期化する。
	m_renderingEngine->SpriteInit(m_modelRender.GetTkm()->m_albedo, m_number);

	// エフェクトを読み込んで登録する。
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/efk/smoke.efk");

	// ゲームのインスタンスを読み込む。
	m_game = FindGO<Game>("game");

	return true;
}
void Cylinder::Update()
{
	// タワーのHPが0の場合
	if (m_game->m_paintnumber == TOWER_HP)
	{
		// タイマーをカウントする
		m_timer += g_gameTime->GetFrameDeltaTime();
		m_falltimer += g_gameTime->GetFrameDeltaTime();
		if (m_position.y >= -100.0f && m_timer >= 0.05f) {
			m_effect = NewGO <EffectEmitter>(0);
			Vector3 effectposi = m_position;
			effectposi.y = 150.0f;
			m_effect->Init(1);
			m_effect->SetPosition(effectposi);
			// エフェクトの大きさを設定する。
			m_effect->SetScale(m_scale * 8.0f);
			m_effect->Play();
			m_timer = 0.0f;
		}
		if (m_position.y >= -150.0f && m_falltimer >= 2.5f) {
			m_position.y -= 0.65f;
			m_physicsStaticObject.SetRotation(m_position, m_rotation);
		}
	}

	// 敵のインスタンスを探して持ってくる
	const auto& m_enemys = FindGOs<Enemy>("enemy");
	for (auto m_enemy : m_enemys)
	{
		// 敵が描画されていなかったら
		if (m_enemy->m_timer <= DARWTIMER)
		{
			// タワーは下にある。
			m_towerUP = false;
		}
		// 敵が描画されていたら。
		else {
			// タワーは上にある。
			m_towerUP = true;
		}
	}

	// タワーのHPが1以上、かつタワーが一定以上の座標にいる場合。
	if (m_game->m_paintnumber < TOWER_HP && m_towerUP == false && m_position.y > -200.0f) {
		// タイマーをカウントする
		m_timer += g_gameTime->GetFrameDeltaTime();
		// 一定時間がたったら処理を行う。
		if (m_timer >= 0.05f) {
			// エフェクトを再生する。
			m_effect = NewGO <EffectEmitter>(0);
			// エフェクト読み込む。
			m_effect->Init(1);
			// 座標を設定する。
			Vector3 effectposi = m_position;
			effectposi.y = 150.0f;
			m_effect->SetPosition(effectposi);
			// エフェクトの大きさを設定する。
			m_effect->SetScale(m_scale * 8.0f);
			// エフェクトを再生する。
			m_effect->Play();
			// タイマーをリセットする
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
			// エフェクトの大きさを設定する。
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

	//モデルの座標を設定。
	m_modelRender.SetPosition(m_position);
	//モデルの回転を設定。
	m_modelRender.SetRotation(m_rotation);
	//モデルの大きさを設定。
	m_modelRender.SetScale(m_scale);
	//モデルの更新処理。
	m_modelRender.Update();
}
void Cylinder::Render(RenderContext& rc)
{
	// 通常モデルを描画する
	m_modelRender.Draw(rc);
}