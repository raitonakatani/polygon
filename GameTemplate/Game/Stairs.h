#pragma once

class Player;

class Stairs : public IGameObject
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

private:
	Player*						m_player;									// プレイヤー
	ModelRender					m_modelRender;								// ステージ
	PhysicsStaticObject			m_physicsStaticObject;						// 静的物理オブジェクト・
	Vector3						m_position;									// 座標。
	Vector3						m_scale = g_vec3One;						// 大きさ。
	Vector3						m_startVector;								// 開始座標
	Vector3						m_endVector;								// 終了座標
	Quaternion					m_rotation;									// 回転。
	RenderingEngine*			m_renderingEngine = &g_renderingEngine;		// レンダリングエンジン
	int							m_number = 0;								// ナンバー
};
