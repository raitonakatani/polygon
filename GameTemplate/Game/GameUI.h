#pragma once

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

	SpriteRender			m_compass;					// コンパスの画像
	SpriteRender			m_compassguideline;			// 指針の画像
	SpriteRender			m_phase[10];					// フェーズの画像
	SpriteRender			m_directionPhase[10];				// 
//	SpriteRender			m_Render;					//	

	Vector3					m_forward;					// 前方向のベクトル
	Quaternion				m_rotation;					// 回転
	float					m_rot = 0.0f;				// 回転量
	float m_timer=0.0f;
	float m_x = 0.0f;
	float m_y = 675.0f;
	float m_y2 = 550.0f;
	Vector3 m_scale = Vector3::One;

};


