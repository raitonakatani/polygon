#include "stdafx.h"
#include "Title.h"

#include "Game.h"
#include "Fade.h"

namespace
{
	// int
	const int PRIORITY = 0;								//プライオリティ 優先権
}

Title::Title()
{

}

Title::~Title()
{

}

bool Title::Start()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/Title.dds");

	m_fade = FindGO<Fade>("fade");
	m_fade->StartFadeIn();

	g_renderingEngine.SpriteRelease();

	return true;
}

void Title::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			auto game = NewGO<Game>(0, "game");
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

void Title::Render(RenderContext& rc)
{
	if (m_isWaitFadeout == false) {
		m_spriteRender.Draw(rc);
	}
}