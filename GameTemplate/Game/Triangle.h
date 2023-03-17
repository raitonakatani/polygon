#pragma once

class Player;
class Magic;

class Triangle : public IGameObject
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

private:
	Player*						m_player;						// プレイヤー
	ModelRender					m_modelRender;					// ステージ
	PhysicsStaticObject			m_physicsStaticObject;			// 静的物理オブジェクト・
	Vector3						m_position;						// 座標。
	Quaternion					m_rotation;						// 回転。
	Vector3						m_scale = g_vec3One;			// 大きさ。
};