#pragma once

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

	ModelRender					m_modelRender;					//�X�e�[�W
private:
	Player* m_player;						//�v���C���[
//	Enemy* m_enemy;
	PhysicsStaticObject			m_physicsStaticObject;			//�ÓI�����I�u�W�F�N�g�E
	Vector3						m_position;						//���W�B
	Quaternion					m_rotation;						//��]�B
	Vector3						m_scale = g_vec3One;						//�傫���B


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