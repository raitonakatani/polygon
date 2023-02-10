#include "stdafx.h"
#include "Title.h"

#include "Game.h"
#include "Fade.h"

namespace
{
	// int
	const int PRIORITY = 0;								//�v���C�I���e�B �D�挠
}

Title::Title()
{

}

Title::~Title()
{

}

bool Title::Start()
{
	//�摜��ǂݍ��ށB
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
			//���g���폜����B
			DeleteGO(this);
		}
	}
	else {
		//A�{�^������������B
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