#include "stdafx.h"
#include "Result.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"


namespace
{
	const float SMALL_ALPHA = 0.0f;			//最小のα値
	const float PLUS_ALPHA = 0.005f;			//乗算されるα値
	const float SPRITE_COLOR = 1.0f;		//スプライトのカラー値
}

Result::Result()
{

}

Result::~Result()
{

}

bool Result::Start()
{
	//ゲームクリアの画像を読み込む。
	m_spriteRender.Init("Assets/sprite/Result.dds");

	m_fade = FindGO<Fade>("fade");
	m_fade->StartFadeIn();

	return true;
}

//更新処理。
void Result::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Title>(0, "title");
			//自身を削除する。
			DeleteGO(this);
		}
	}
	else {
		//Aボタンを押したら。
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
}

//描画処理。
void Result::Render(RenderContext& rc)
{
	if (m_isWaitFadeout == false) {
		m_spriteRender.Draw(rc);
	}
}
