#pragma once

class Player;
class Enemy;

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

	ModelRender					m_modelRender;					//ステージ
private:
	Player* m_player;						//プレイヤー
//	Enemy* m_enemy;
	PhysicsStaticObject			m_physicsStaticObject;			//静的物理オブジェクト・
	Vector3						m_position;						//座標。
	Quaternion					m_rotation;						//回転。
	Vector3						m_scale = g_vec3One;						//大きさ。


	Vector3 POS;
	Vector2 UV;


	SpriteInitData inkspriteinitdata;
	Sprite inksprite;
	SpriteInitData spriteinitdata;
	Sprite sprite;

	RenderingEngine* m_renderingEngine = &g_renderingEngine;


	Vector3 startVector;
	Vector3 endVector;

	int m_number = 0;

};