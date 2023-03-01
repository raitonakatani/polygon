#pragma once

class Player;

class Box : public IGameObject
{
public:
	Box() {}
	~Box() {}

	bool Start();
	void Update();
	// �C���N�̃����_�����O����
	void InkRendering();
	void Render(RenderContext& rc);

	// ���W��ݒ�B
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
	/// <summary>
	/// �ԍ���ݒ�B
	/// </summary>
	/// <param name="scale">�ԍ��B</param>
	void SetNumber(const int& number)
	{
		m_number = number;
	}

private:
	ModelRender				m_modelRender;								// �X�e�[�W
	Player*					m_player;									// �v���C���[
	PhysicsStaticObject		m_physicsStaticObject;						// �ÓI�����I�u�W�F�N�g
	Vector3					m_position;									// ���W�B
	Quaternion				m_rotation;									// ��]�B
	Vector3					m_scale = g_vec3One;						// �傫���B
	RenderingEngine*		m_renderingEngine = &g_renderingEngine;		// �����_�����O�G���W��
	Vector3					m_startVector;								// �J�n���W
	Vector3					m_endVector;								// �I�����W
	int						m_number = 0;								// �I�u�W�F�N�g�̔ԍ�
};