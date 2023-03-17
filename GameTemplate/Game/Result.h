#pragma once

class Fade;

class Result : public IGameObject
{
public:
	Result();
	~Result();
	bool Start();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	bool					m_isWaitFadeout = false;	//フェード。
	Fade*					m_fade = nullptr;           //フェード。
	SpriteRender			m_spriteRender;				//スプライトレンダー。
};

