#pragma once

class GameSound :public IGameObject
{
public:
	GameSound() {}
	~GameSound() {}

	bool Start();


	
	/// <summary>
	///	�v���C���[�̑���
	/// </summary>
	void PlayerStepSE(float volume);
	/// <summary>
	/// �v���C���[�̍U�����̉�
	/// </summary>
	/// <param name="volume"></param>
	void PlayerAttackSE(float volume);
};

