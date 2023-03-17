#pragma once

class Player;

class Stairs : public IGameObject
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

private:
	Player*						m_player;									// �v���C���[
	ModelRender					m_modelRender;								// �X�e�[�W
	PhysicsStaticObject			m_physicsStaticObject;						// �ÓI�����I�u�W�F�N�g�E
	Vector3						m_position;									// ���W�B
	Vector3						m_scale = g_vec3One;						// �傫���B
	Vector3						m_startVector;								// �J�n���W
	Vector3						m_endVector;								// �I�����W
	Quaternion					m_rotation;									// ��]�B
	RenderingEngine*			m_renderingEngine = &g_renderingEngine;		// �����_�����O�G���W��
	int							m_number = 0;								// �i���o�[
};
