#include "stdafx.h"
#include "Result.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"


namespace
{
	const float SMALL_ALPHA = 0.0f;			//�ŏ��̃��l
	const float PLUS_ALPHA = 0.005f;			//��Z����郿�l
	const float SPRITE_COLOR = 1.0f;		//�X�v���C�g�̃J���[�l
}

Result::Result()
{

}

Result::~Result()
{

}

bool Result::Start()
{
	//�Q�[���N���A�̉摜��ǂݍ��ށB
	m_spriteRender.Init("Assets/sprite/Result.dds");

	m_fade = FindGO<Fade>("fade");
	m_fade->StartFadeIn();

	return true;
}

//�X�V�����B
void Result::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Title>(0, "title");
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

//�`�揈���B
void Result::Render(RenderContext& rc)
{
	if (m_isWaitFadeout == false) {
		m_spriteRender.Draw(rc);
	}
}
