#pragma once

class Fade;

class Result : public IGameObject
{
public:
	Result();
	~Result();
	bool Start();
	//�X�V�����B
	void Update();
	//�`�揈���B
	void Render(RenderContext& rc);

private:
	//�����o�ϐ��B
	bool					m_isWaitFadeout = false;	//�t�F�[�h�B
	Fade*					m_fade = nullptr;           //�t�F�[�h�B
	SpriteRender			m_spriteRender;				//�X�v���C�g�����_�[�B
};

