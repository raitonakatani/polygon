#pragma once


#include "LevelRender.h"

// 前方宣言。
class Player;
class GameCamera;
class Background;
class Stairs;
class Floor;
class Box;
class Cylinder;
class Triangle;
class Enemy;
class GameUI;
class Fade;
class Clearmodel;


class Game : public IGameObject
{

public:
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	struct PaintList {
		bool m_paint[5];
	};
	PaintList m_paintlist[8];
	int m_paintnumber = 0;

	Vector3 m_enemyposi;
	Vector3 m_enemypaint;
	int m_phase = 1;
private:
	LevelRender			m_levelRender[5];				// レベルレンダー。 
	GameCamera*			m_gameCamera = nullptr;			// カメラ
	Background*			m_background = nullptr;			// 背景（ステージ）
	Stairs*				m_stairs = nullptr;				// 背景（ステージ）
	Floor*				m_floor = nullptr;				// 背景（床）
	Box*				m_box = nullptr;				// 背景（箱）
	Cylinder*			m_cylinder = nullptr;			// 背景（円柱）
	Triangle*			m_triangle = nullptr;			// 背景（三角形）
	Player*				m_player = nullptr;				// プレイヤー
	Enemy*				m_enemy = nullptr;				// エネミー
	Fade*				m_fade = nullptr;				// フェード
	GameUI*				m_ui = nullptr;					// UI
	Clearmodel*			m_clearmodel = nullptr;			// クリアモデル
	std::string			m_file[5];
	int					m_number = 0;					// 敵の数
	float				m_timer = 0.0f;					// タイマー
	bool				m_isWaitFadeout = false;		// フェード。
};
