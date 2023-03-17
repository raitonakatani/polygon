#pragma once
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"
#include "EnemyPath.h"

class Game;
class Player;
class GameSound;
class EnemyPath;
class Cylinder;
class GameEffect;

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
	~Enemy();


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
	/// �^�C�}�[���擾����B
	/// </summary>
	/// <returns>�^�C�}�[�B</returns>
	const float& GetTimer() const
	{
		return m_timer;
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
	/// �v���C���[��T������
	/// </summary>
	void SearchPlayer();
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
	/// <summary>
	/// �����蔻�菈��
	/// </summary>
	void Collision();


	// �N���X IGameObject
	Game*					m_game;										// �Q�[��
	Player*					m_player;									// �v���C���[
	GameSound*				m_gameSound;								// �Q�[���T�E���h
	Cylinder*				m_cylinder;									// �^���[
	GameEffect*				m_gameEffect;								// �G�t�F�N�g
	// �N���X Engine
	ModelRender				m_modelRender;								// ���f�������_�[
	CharacterController     m_charaCon;	                                // �L�����R��
	SphereCollider			m_sphereCollider;							// �X�t�B�A�R���C�_�[
	EffectEmitter*			m_effect = nullptr;							// �G�t�F�N�g
	CollisionObject*		m_collision;						        // �R���W����
	RenderingEngine*		m_renderingEngine = &g_renderingEngine;     // �����_�����O�G���W��
	// �p�X
	EnemyPath				m_enemypath;								//�p�X
	// �֐�
	Vector3					m_startVector;								// �J�n����
	Vector3					m_endVector;								// �I������
	Vector3                 m_forward = Vector3::AxisZ;                 // �O�����̃x�N�g��
	Vector3                 m_moveSpeed;                                // �ړ����x
	Vector3					m_scale = g_vec3One;		                // �g�嗦
	Vector3					m_paintposi = Vector3{ 0.0f,200.0f,0.0f };
	Vector3					m_position;									// ���W
	Vector3					m_targetPointPosition = Vector3{ 0.0f,150.0f,200.0f };		// �ڕW�n�_�̍��W
	Vector3					m_diff;										// �G�l�~�[�̍��W����ڕW�n�_�Ɍ������x�N�g��
	Vector3					m_oldPosition;								// �p�X�X�V�O�̍��W
	Vector3					m_targetposi = Vector3(0.0f, 150.0f, 200.0f);				// �y�C���g�n�_�̍��W
	Quaternion				m_rotation;					                // ��]
	AnimationClip           m_animationClipArray[enAnimClip_Num];		// �A�j���[�V�����N���b�v
	EnEnemyState			m_enemyState = enEnemyState_Idle;			// �v���C���[�X�e�[�g
	nsAI::NaviMesh			m_nvmMesh;									// �i�r���b�V��
	nsAI::Path				m_path;										// �p�X
	nsAI::PathFinding		m_pathFiding;								// �p�X����
	int						a = 0;										// �z��i���o�[
	int						b = 0;										// �z��i���o�[
	int						m_hp = 150;									// �̗�
	float					timer = 0.0f;								// �^�C�}�[
	float					m_ramtime = 0.0f;							// �����_���^�C�}�[
	float					m_timer = 0.0f;								// �^�C�}�[
	float					m_damageTimer = 0.0f;						// ��_������
	bool					m_damage = false;							// �_���[�W���菈��
	bool					m_isAttack = false;							// �U�����菈��
	bool					m_isSearchPlayer = false;					// �����Ă��邩�H

};

