#pragma once

class Game;
class Fade;

class GameUI : public IGameObject
{
public:
	GameUI() {}
	~GameUI() {}

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	int 	m_number = 1;
	int		m_reset = 2;
private:

	Game*				m_game;						// ゲーム
	Fade*				m_fade = nullptr;			// フェード
	SpriteRender		m_compass;					// コンパスの画像
	SpriteRender		m_compassguideline;			// 指針の画像
	SpriteRender		m_phase[5];					// フェーズの画像
	SpriteRender		m_directionPhase[5];		// 方向の画像
	SpriteRender		m_gameover;					// ゲームオーバーの画像
	Vector3				m_forward;					// 前方向のベクトル
	Vector3				m_scale = Vector3::One;		// 大きさ 
	Quaternion			m_rotation;					// 回転
	float				m_rot = 0.0f;				// 回転量
	float				m_timer=0.0f;				// タイマー
	float				m_x = 0.0f;					// X軸
	float				m_y = 675.0f;				// Y軸
	float				m_y2 = 550.0f;				// Y軸２
	float				m_yposi = 800.0f;			// Y座標
};