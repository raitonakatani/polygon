#pragma once

//クラス宣言。
class Fade;
class Game;

/// <summary>
/// タイトル。
/// </summary>
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	//private:
	Fade*					m_fade = nullptr;				// フェード。
	SpriteRender			m_spriteRender;					// タイトルの画像。
	float					m_alpha = 0.0f;					// pressbuttonのα値。
	float					m_timer = 0.0f;					// タイマー
	bool					m_isWaitFadeout = false;		// フェードアウト
};
