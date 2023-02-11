#pragma once

class Game;
class Player;
class Enemy;

class Cylinder : public IGameObject
{

public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//���W��ݒ�B
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	/// <param name="rotation">��]�B</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// �傫����ݒ�B
	/// </summary>
	/// <param name="scale">�傫���B</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	void SetNumber(const int& number)
	{
		m_number = number;
	}

	int m_number = 0;
	ModelRender					m_modelRender;								//�X�e�[�W
private:
	Game* m_game;
	Player* m_player;
	Enemy* m_enemy;
	EffectEmitter* m_effect = nullptr;							// �G�t�F�N�g
	PhysicsStaticObject			m_physicsStaticObject;						//�ÓI�����I�u�W�F�N�g�E
	Vector3						m_position;									//���W�B
	Quaternion					m_rotation;									//��]�B
	Vector3						m_scale = g_vec3One;						//�傫���B

	RenderingEngine*			m_renderingEngine = &g_renderingEngine;

	Vector3 m_startVector;
	Vector3 m_endVector;
	float m_timer = 0.0f;
	float m_falltimer = 0.0f;
};