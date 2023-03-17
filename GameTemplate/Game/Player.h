#pragma once

class Game;
class GameSound;

// �v���C���[�N���X�B
class Player : public IGameObject
{
public:
	enum EnPlayerState
	{
		enPlayerState_Idle,					//�ҋ@�X�e�[�g
		enPlayerState_Shot,					//���X�e�[�g
		enPlayerState_LeftShot,				//���A�j���[�V����
		enPlayerState_RightShot,			//���A�j���[�V����
		enPlayerState_ForwardShot,			//���A�j���[�V����
		enPlayerState_BackShot,				//���A�j���[�V����
		enPlayerState_Walk,					//�����X�e�[�g
		enPlayerState_Jump,					//�؂�ւ����X�e�[�g
		enPlayerState_Victory,				//�����X�e�[�g
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
		enAnimClip_LeftShot,		//���A�j���[�V����
		enAnimClip_RightShot,		//���A�j���[�V����
		enAnimClip_ForwardShot,		//���A�j���[�V����
		enAnimClip_BackShot,		//���A�j���[�V����
		enAnimClip_Walk,			//�����A�j���[�V����
		enAnimClip_Jump,			//�؂�ւ����A�j���[�V����
		enAnimClip_Victory,			//�����A�j���[�V����
		enAnimClip_Num,				//�A�j���[�V�����̐�
	};

	int m_enemynumber = 0;
private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// ��]����
	/// </summary>
	void Rotation();
	/// <summary>
	/// �����蔻�菈���B
	/// </summary>
	void Collision();
	/// <summary>
	/// �A�j���[�V�����̍Đ�
	/// </summary>
	void PlayAnimation();
	/// <summary>
	/// �e�X�e�[�g�̑J�ڏ���
	/// </summary>
	void ManageState();
	/// <summary>
	/// �A�j���[�V�������O�C�x���g
	/// </summary>
	/// <param name="clipName">�A�j���[�V�����̖��O</param>
	/// <param name="eventName">�A�j���[�V�����L�[�̖��O</param>
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	/// <summary>
	/// ���ʂ̃X�e�[�g�̑J�ڏ���
	/// </summary>
	void ProcessCommonStateTransition();
	/// <summary>
	/// <summary>
	/// �ҋ@�X�e�[�g
	/// </summary>
	void ProcessIdleStateTransition();
	/// <summary>
	/// ����X�e�[�g
	/// </summary>
	void ProcessRunStateTransition();
	/// <summary>
	/// �W�����v�X�e�[�g
	/// </summary>
	void ProcessJumpStateTransition();
	/// <summary>
	/// �U���X�e�[�g
	/// </summary>
	void ProcessAttackStateTransition();

	void Search();


	// �N���X IGameObject
	Game*					m_game = nullptr;							// �Q�[���B
	GameSound*				m_gameSound = nullptr;						// �Q�[���T�E���h
	// �N���X Engine
	ModelRender				m_modelRender;								// ���f�������_�[
	ModelRender				m_clearmodel;								// ���f�������_�[
	CharacterController     m_charaCon;	                                // �L�����R��
	CollisionObject*		m_collision;
	EffectEmitter*			m_effect = nullptr;							// �G�t�F�N�g
	// �֐�
	Vector3					m_startVector;								// �J�n����
	Vector3					m_endVector;								// �I������
	Vector3                 m_forward = Vector3::AxisZ;                 // �O�����̃x�N�g��
	Vector3					m_position;					                // ���W
	Vector3                 m_moveSpeed;                                // �ړ����x
	Vector3					m_scale = g_vec3One;		                // �g�嗦
	Vector3					scale = { 2.5f,2.5f,1.0f };		                // �g�嗦
	Quaternion				m_rotation;					                // ��]
	AnimationClip           m_animationClipArray[enAnimClip_Num];		// �A�j���[�V�����N���b�v
	EnPlayerState           m_playerState = enPlayerState_Idle;			// �v���C���[�X�e�[�g
	float					m_move = 80.0f;								// �ړ����x�i�����x�j
	float					m_lStick_x = 0.0f;							// L�X�e�B�b�N�̓��͗�
	float					m_lStick_y = 0.0f;							// L�X�e�B�b�N�̓��͗�
	float					y = 0;										// R�X�e�B�b�N�̓��͗�
	float					y2 = 0;										// R�X�e�B�b�N�̓��͗�
	int                     m_gunId = -1;								//�uGun�v�{�[����ID�B

	int m_hp = 150;
	float lStick_x = 0.0f;
	float lStick_y = 0.0f;
	bool m_damage = false;
	float m_damageTimer = 0.0f;

};