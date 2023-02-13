#pragma once

class Game;
class Player;

class Clearmodel : public IGameObject
{
public:
	enum EnEnemyState
	{
		enEnemyState_Victory,					//�ҋ@�X�e�[�g
	};
public:

	Clearmodel() {}
	~Clearmodel();


	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// ���W��ݒ肷��B
	/// </summary>
	/// <param name="position">���W�B</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// ���W���擾����B
	/// </summary>
	/// <returns>���W�B</returns>
	const Vector3& GetPosition() const
	{
		return m_position;
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

	// �A�j���[�V�����N���b�v�̔ԍ���\���񋓌^�B
	enum EnAnimationClip {
		enAnimClip_Victory,				//�A�j���[�V�����̐�
		enAnimClip_Num				//�A�j���[�V�����̐�
	};
	float m_timer = 0.0f;


private:

	// �N���X IGameObject
	Game* m_game;
	Player* m_player;									// �v���C���[
	// �N���X Engine
	ModelRender				m_modelRender;								// ���f�������_�[
	CharacterController     m_charaCon;	                                // �L�����R��
	Vector3                 m_forward = Vector3::AxisZ;                 // �O�����̃x�N�g��
	Vector3                 m_moveSpeed;                                // �ړ����x
	Vector3					m_scale = g_vec3One;		                // �g�嗦
	Vector3					m_position;
	Quaternion				m_rotation;					                // ��]
	AnimationClip           m_animationClipArray[enAnimClip_Num];		// �A�j���[�V�����N���b�v
	EnEnemyState			m_enemyState = enEnemyState_Victory;			// �v���C���[�X�e�[�g

};

