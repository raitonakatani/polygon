#pragma once

class Game;

// �v���C���[�N���X�B
class Player : public IGameObject
{
public:
	enum EnPlayerState
	{
		enPlayerState_Idle,					//�ҋ@�X�e�[�g
		enPlayerState_Shot,					//���X�e�[�g
		enPlayerState_Win					//�N���A�X�e�[�g
	};
public:
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
	/// �n�_�̍��W���擾����B
	/// </summary>
	/// <returns>���W�B</returns>
	const Vector3& GetStartVector() const
	{
		return m_startVector;
	}


	/// <summary>
	/// �I�_�̍��W���擾����B
	/// </summary>
	/// <returns>���W�B</returns>
	const Vector3& GetEndVector() const
	{
		return m_endVector;
	}


	// �A�j���[�V�����N���b�v�̔ԍ���\���񋓌^�B
	enum EnAnimationClip {
		enAnimClip_Idle,			//�ҋ@�A�j���[�V����
		enAnimClip_Shot,			//���A�j���[�V����
		enAnimClip_Num,				//�A�j���[�V�����̐�
	};


private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// ��]����
	/// </summary>
	void Rotation();

	// �N���X IGameObject
	Game* m_game = nullptr;							// �Q�[���B
	// �N���X Engine
	ModelRender				m_modelRender;                              // ���f�������_�[

	ModelRender				m_testmodel;                              // ���f�������_�[

	CharacterController     m_charaCon;	                                // �L�����R��
	// �֐�
	Vector3 m_startVector;
	Vector3 m_endVector;


	Vector3                 m_forward = Vector3::AxisZ;                 // �O�����̃x�N�g��
	Vector3					m_position;					                // ���W
	Vector3                 m_moveSpeed;                                // �ړ����x
	Vector3					m_scale = g_vec3One;		                // �g�嗦
	Quaternion				m_rotation;					                // ��]

	Quaternion rotation;

	AnimationClip           m_animationClipArray[enAnimClip_Num];	    // �A�j���[�V�����N���b�v

};