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

	SpriteRender			m_compass;					// �R���p�X�̉摜
	SpriteRender			m_compassguideline;			// �w�j�̉摜
	SpriteRender			m_phase[5];					// �t�F�[�Y�̉摜
	SpriteRender			m_directionPhase[5];		// �����̉摜
	SpriteRender			m_gameover;					//	

	Vector3					m_forward;					// �O�����̃x�N�g��
	Quaternion				m_rotation;					// ��]
	float					m_rot = 0.0f;				// ��]��
	float m_timer=0.0f;
	float m_x = 0.0f;
	float m_y = 675.0f;
	float m_y2 = 550.0f;
	Vector3 m_scale = Vector3::One;

	float m_yposi = 800.0f;

//	bool				m_isWaitFadeout = false;		//�t�F�[�h�B
	Fade* m_fade = nullptr;				//�t�F�[�h

};


