#include "stdafx.h"
#include "Cylinder.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "GameEffect.h"

namespace
{
	// int型
	const int	TOWER_HP = 40;				// タワーのHP
	const int	RANDOM = 10;				// 乱数
	const int	MAX_RANDOM = 21;			// 最大乱数
	// float型
	const float DARWTIMER = 11.0f;			// 描画判定
	const float STANDARD_POSI = 150.0f;		// 標準時のY座標
	const float STANDBY_POSI = 100.0f;		// 待機時のY座標
	const float END_POSI = 200.0f;			// 終了時のY座標
	const float RESET_TIMER = 0.0f;			// タイマーのリセット
	const float LIMIT_TIMER = 0.05f;		// 制限時間
	const float EFFECT_SCALE = 8.0f;		// エフェクトの大きさ
	const float FALL_SPEED = 0.65f;			// 落下速度
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
		//m_falltimer += g_gameTime->GetFrameDeltaTime();
		// モデルのY座標が一定以上かつ時間がたっていた場合
		if (m_position.y >= -STANDBY_POSI && m_timer >= LIMIT_TIMER) {
			// エフェクトのインスタンスを作成する
			m_effect = NewGO <EffectEmitter>(0);
			Vector3 effectposi = m_position;
			effectposi.y = STANDARD_POSI;
			// エフェクトを読み込む
			m_effect->Init(1);
			// エフェクトの座標を設定する
			m_effect->SetPosition(effectposi);
			// エフェクトの大きさを設定する。
			m_effect->SetScale(m_scale * EFFECT_SCALE);
			// エフェクトを再生する。
			m_effect->Play();
			m_timer = RESET_TIMER;
		}
		if (m_position.y >= -STANDARD_POSI) {
			m_position.y -= FALL_SPEED;
			m_physicsStaticObject.SetRotation(m_position, m_rotation);
		}
	}

	// 敵のインスタンスを探して持ってくる
	const auto& m_enemys = FindGOs<Enemy>("enemy");
	for (auto m_enemy : m_enemys)
	{
		// 敵が描画されていなかったら
		if (m_enemy->GetTimer() <= DARWTIMER || m_game->m_paintnumber >= TOWER_HP)
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
	if (m_game->m_paintnumber < TOWER_HP && m_towerUP == false && m_position.y > -END_POSI) {
		// タイマーをカウントする
		m_timer += g_gameTime->GetFrameDeltaTime();
		// 一定時間がたったら処理を行う。
		if (m_timer >= LIMIT_TIMER) {
			// エフェクトを再生する。
			m_effect = NewGO <EffectEmitter>(0);
			// エフェクト読み込む。
			m_effect->Init(1);
			// 座標を設定する。
			Vector3 effectposi = m_position;
			effectposi.y = STANDARD_POSI;
			m_effect->SetPosition(effectposi);
			// エフェクトの大きさを設定する。
			m_effect->SetScale(m_scale * EFFECT_SCALE);
			// エフェクトを再生する。
			m_effect->Play();
			// タイマーをリセットする
			m_timer = RESET_TIMER;
		}
		float ramz = -RANDOM - rand() % MAX_RANDOM;
		float ramx = -RANDOM - rand() % MAX_RANDOM;

		m_position.x = ramx;
		m_position.z = ramz;
		// モデルの座標を下げる
		m_position.y -= 2.0f;
		m_physicsStaticObject.SetRotation(m_position, m_rotation);
	}
	// モデルの座標が一定以下だった場合
	else if (m_towerUP == true && m_position.y < STANDARD_POSI) {
		// タイマーを加算する
		m_timer += g_gameTime->GetFrameDeltaTime();
		if (m_position.y <= STANDARD_POSI && m_timer >= LIMIT_TIMER) {
			// エフェクトを再生する
			m_effect = NewGO <EffectEmitter>(0);
			Vector3 effectposi = m_position;
			effectposi.y = STANDARD_POSI;
			// エフェクトを読み込む
			m_effect->Init(1);
			// エフェクトの座標を設定する
			m_effect->SetPosition(effectposi);
			// エフェクトの大きさを設定する。
			m_effect->SetScale(m_scale * EFFECT_SCALE);
			// エフェクトを再生する
			m_effect->Play();
			// タイマーをリセットする
			m_timer = RESET_TIMER;
		}
		float ramx = -RANDOM - rand() % MAX_RANDOM;
		float ramz = -RANDOM - rand() % MAX_RANDOM;

		m_position.x = ramx;
		m_position.z = ramz;
		// モデルの座標を上げる
		m_position.y += 2.0f;
		m_physicsStaticObject.SetRotation(m_position, m_rotation);
		if (m_position.y >= STANDARD_POSI) { m_position.y = STANDARD_POSI; }
	}
	
	// プレイヤーを探す
	m_player = FindGO<Player>("player");
	// 開始座標と終了座標を設定する
	m_startVector = m_player->GetStartVector();
	m_endVector = m_player->GetEndVector();

	// 攻撃されていた場合
	if (g_pad[0]->IsPress(enButtonRB1) == true && m_position.y >= STANDARD_POSI)
	{
		// インクの処理を行う
		m_renderingEngine->SpriteDraw( 1, m_modelRender, m_number, m_startVector, m_endVector);
	}

	// モデルの座標を設定。
	m_modelRender.SetPosition(m_position);
	// モデルの回転を設定。
	m_modelRender.SetRotation(m_rotation);
	// モデルの大きさを設定。
	m_modelRender.SetScale(m_scale);
	//モデルの更新処理。
	m_modelRender.Update();
}
void Cylinder::Render(RenderContext& rc)
{
	// 通常モデルを描画する
	m_modelRender.Draw(rc);
}