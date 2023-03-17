#pragma once

class Game;
class Player;
class Enemy;
class GameEffect;

class Cylinder : public IGameObject
{

public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//座標を設定。
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// 回転を設定。
	/// </summary>
	/// <param name="rotation">回転。</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// 大きさを設定。
	/// </summary>
	/// <param name="scale">大きさ。</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	void SetNumber(const int& number)
	{
		m_number = number;
	}

	const int& GetNumber()
	{
		return m_number;
	}

	/// <summary>
	/// モデルを取得する。
	/// </summary>
	/// <returns>モデル。</returns>
	ModelRender& GetModel()
	{
		return m_modelRender;
	}

private:
	ModelRender				m_modelRender;								// ステージ
	Game*					m_game;										// ゲーム
	GameEffect*				m_gameeffect;								// エフェクト
	Player*					m_player;									// プレイヤー
	Enemy*					m_enemy;									// 敵
	EffectEmitter*			m_effect = nullptr;							// エフェクト
	PhysicsStaticObject		m_physicsStaticObject;						// 静的物理オブジェクト・
	Vector3					m_position;									// 座標。
	Quaternion				m_rotation;									// 回転。
	Vector3					m_scale = g_vec3One;						// 大きさ。
	RenderingEngine*		m_renderingEngine = &g_renderingEngine;		// レンダリングエンジン
	Vector3					m_startVector;								// 開始座標
	Vector3					m_endVector;								// 終了座標
	float					m_timer = 0.0f;								// タイマー
	float					m_falltimer = 0.0f;							// タワーが落ちる時間
	int						m_number = 0;								// 登録ナンバー
	bool					m_towerUP = false;							// タワーの場所
};