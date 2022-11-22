#pragma once
class Enemy : public IGameObject
{
public:
	Enemy() {}
	~Enemy() {}

	bool Start();
	void Update();
	void Render(RenderContext& rc);
};

