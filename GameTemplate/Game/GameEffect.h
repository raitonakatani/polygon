#pragma once
class GameEffect : public IGameObject
{
public:
	GameEffect() {}
	~GameEffect() {}

	bool Start();

	void SmokeEffect();

private:
	EffectEmitter* m_effect = nullptr;							// エフェクト

};

