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

	Game* m_game;

	SpriteRender			m_compass;					// コンパスの画像
	SpriteRender			m_compassguideline;			// 指針の画像
	SpriteRender			m_phase[5];					// フェーズの画像
	SpriteRender			m_directionPhase[5];		// 方向の画像
	SpriteRender			m_gameover;					//	

	Vector3					m_forward;					// 前方向のベクトル
	Quaternion				m_rotation;					// 回転
	float					m_rot = 0.0f;				// 回転量
	float m_timer=0.0f;
	float m_x = 0.0f;
	float m_y = 675.0f;
	float m_y2 = 550.0f;
	Vector3 m_scale = Vector3::One;

	float m_yposi = 800.0f;

//	bool				m_isWaitFadeout = false;		//フェード。
	Fade* m_fade = nullptr;				//フェード

};


