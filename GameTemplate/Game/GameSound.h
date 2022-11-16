#pragma once

class GameSound :public IGameObject
{
public:
	GameSound() {}
	~GameSound() {}

	bool Start();


	
	/// <summary>
	///	プレイヤーの足音
	/// </summary>
	void PlayerStepSE(float volume);
	/// <summary>
	/// プレイヤーの攻撃時の音
	/// </summary>
	/// <param name="volume"></param>
	void PlayerAttackSE(float volume);
};

