#pragma once

//�N���X�錾�B
class Fade;
class Game;

/// <summary>
/// �^�C�g���B
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
	Fade*					m_fade = nullptr;				// �t�F�[�h�B
	SpriteRender			m_spriteRender;					// �^�C�g���̉摜�B
	float					m_alpha = 0.0f;					// pressbutton�̃��l�B
	float					m_timer = 0.0f;					// �^�C�}�[
	bool					m_isWaitFadeout = false;		// �t�F�[�h�A�E�g
};
