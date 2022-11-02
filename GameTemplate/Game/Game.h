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


class Game : public IGameObject
{

public:
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);


private:
	LevelRender					m_levelRender;					//レベルレンダー。 
	GameCamera* m_gameCamera = nullptr;			//カメラ
	Background* m_background = nullptr;			//背景（ステージ）
	Floor* m_floor = nullptr;				//背景（床）
	Box* m_box = nullptr;				//背景（箱）
	Cylinder* m_cylinder = nullptr;			//背景（円柱）
	Triangle* m_triangle = nullptr;			//背景（円柱）
	Player* m_player = nullptr;				//プレイヤー

};
