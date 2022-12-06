#pragma once
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;
class GameSound;


class Enemy : public IGameObject
{

public:
	enum EnEnemyState
	{
		enEnemyState_Idle,					//�ҋ@�X�e�[�g
		enEnemyState_Shot,					//���X�e�[�g
		enEnemyState_Walk,					//�����X�e�[�g
	};
public:

	Enemy() {}
	~Enemy() {}


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
		enAnimClip_Walk,			//�����A�j���[�V����
		enAnimClip_Num,				//�A�j���[�V�����̐�
	};

	/*bool IsAttack()
	{
		return m_isAttack;
	}*/
	bool m_isAttack = false;
	float yup = 0.0f;

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
	/// �U������
	/// </summary>
	void Attack();
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
	/// �U���X�e�[�g
	/// </summary>
	void ProcessAttackStateTransition();



	// �N���X IGameObject
	Player*					m_player;									// �v���C���[
	GameSound*				m_gameSound;								// �Q�[���T�E���h
	// �N���X Engine
	ModelRender				m_modelRender;								// ���f�������_�[
//	CharacterController     m_charaCon;	                                // �L�����R��
	EffectEmitter*			m_effect = nullptr;							// �G�t�F�N�g
	// �֐�
	Vector3					m_startVector;								// �J�n����
	Vector3					m_endVector;								// �I������
	Vector3                 m_forward = Vector3::AxisZ;                 // �O�����̃x�N�g��
	Vector3                 m_moveSpeed;                                // �ړ����x
	Vector3					m_scale = g_vec3One;		                // �g�嗦
	Vector3 scale= g_vec3One;
	Quaternion				m_rotation;					                // ��]
	AnimationClip           m_animationClipArray[enAnimClip_Num];		// �A�j���[�V�����N���b�v
	EnEnemyState			m_enemyState = enEnemyState_Idle;			// �v���C���[�X�e�[�g
	float					m_move = 80.0f;								// �ړ����x�i�����x�j
	float					m_lStick_x = 0.0f;							// L�X�e�B�b�N�̓��͗�
	float					m_lStick_y = 0.0f;							// L�X�e�B�b�N�̓��͗�
	int                     m_gunId = -1;								//�uGun�v�{�[����ID�B
	nsAI::NaviMesh			m_nvmMesh;									// �i�r���b�V��
	nsAI::Path				m_path;										// �p�X
	nsAI::PathFinding		m_pathFiding;								// �p�X����
	Vector3					m_position;									// ���W
	Vector3					m_targetPointPosition;						// �ڕW�n�_�̍��W

	Vector3					m_diff;										// �G�l�~�[�̍��W����ڕW�n�_�Ɍ������x�N�g��
	float					timer = 0.0f;								// �^�C�}�[
	Vector3					m_oldPosition;								// �p�X�X�V�O�̍��W
};

