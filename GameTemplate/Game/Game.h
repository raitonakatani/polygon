#pragma once


#include "LevelRender.h"

// 前方宣言。
class Player;
class GameCamera;
class Background;
class Floor;
class Box;
class Cylinder;
class Triangle;
class Enemy;
class GameUI;
class Fade;


class Game : public IGameObject
{

public:
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	int m_number = 0;
private:
	LevelRender			m_levelRender[5];				//レベルレンダー。 
	GameCamera*			m_gameCamera = nullptr;			//カメラ
	Background*			m_background = nullptr;			//背景（ステージ）
	Floor*				m_floor = nullptr;				//背景（床）
	Box*				m_box = nullptr;				//背景（箱）
	Cylinder*			m_cylinder = nullptr;			//背景（円柱）
	Triangle*			m_triangle = nullptr;			//背景（円柱）
	Player*				m_player = nullptr;				//プレイヤー
	Enemy*				m_enemy = nullptr;				//エネミー
	Fade*				m_fade = nullptr;				//フェード
	GameUI*				m_ui = nullptr;					//UI
	float				m_timer = 0.0f;					//タイマー

	int phase=1;
	std::string FILE[5];
};
