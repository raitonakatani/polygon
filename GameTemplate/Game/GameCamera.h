#pragma once


class Player;

//�Q�[�����̃J�����𐧌䂷��B
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/////////////////////////////////////
	//�����o�ϐ�
	/////////////////////////////////////

	/// <summary>
	/// ���W���擾����B
	/// </summary>
	/// <returns>���W�B</returns>
	const Vector3& GetPosition() const
	{
		return pos2;
	}

	/// <summary>
	/// ��]���擾����B
	/// </summary>
	/// <returns>��]�B</returns>
	const Quaternion& GetQuaternion() const
	{
		return qRot2;
	}

	/// <summary>
	/// �O�����̃x�N�g�����擾����B
	/// </summary>
	/// <returns>�O�����̃x�N�g���B</returns>
	const Vector3& GetForwardPosition() const
	{
		return m_forward;
	}

private:
	Player* m_player = nullptr;				//�v���C���[
	Vector3					m_toCameraPos = Vector3::One;	//�����_���王�_�Ɍ������x�N�g���B
	Vector3					m_forward;						//�O�����̃x�N�g��	
	Vector3					pos2;							//�J�����̈ʒu(���_)
	Vector3					toCameraPosOld2;				//�����_���王�_�Ɍ������x�N�g���B
	Vector3					m_toCameraPos2;					//�����_���王�_�Ɍ������x�N�g���B
	Quaternion              m_rotation;						//��]
	Quaternion qRot2;
	int						m_camera = 0;					//�J�����̐؂�ւ�����B
	float					m_timer = 0.0f;					//�^�C�}�[�B

};