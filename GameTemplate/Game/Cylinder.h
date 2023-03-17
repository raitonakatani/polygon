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

	const int& GetNumber()
	{
		return m_number;
	}

	/// <summary>
	/// ���f�����擾����B
	/// </summary>
	/// <returns>���f���B</returns>
	ModelRender& GetModel()
	{
		return m_modelRender;
	}

private:
	ModelRender				m_modelRender;								// �X�e�[�W
	Game*					m_game;										// �Q�[��
	GameEffect*				m_gameeffect;								// �G�t�F�N�g
	Player*					m_player;									// �v���C���[
	Enemy*					m_enemy;									// �G
	EffectEmitter*			m_effect = nullptr;							// �G�t�F�N�g
	PhysicsStaticObject		m_physicsStaticObject;						// �ÓI�����I�u�W�F�N�g�E
	Vector3					m_position;									// ���W�B
	Quaternion				m_rotation;									// ��]�B
	Vector3					m_scale = g_vec3One;						// �傫���B
	RenderingEngine*		m_renderingEngine = &g_renderingEngine;		// �����_�����O�G���W��
	Vector3					m_startVector;								// �J�n���W
	Vector3					m_endVector;								// �I�����W
	float					m_timer = 0.0f;								// �^�C�}�[
	float					m_falltimer = 0.0f;							// �^���[�������鎞��
	int						m_number = 0;								// �o�^�i���o�[
	bool					m_towerUP = false;							// �^���[�̏ꏊ
};