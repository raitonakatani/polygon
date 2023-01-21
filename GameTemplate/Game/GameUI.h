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

	SpriteRender			m_compass;					// �R���p�X�̉摜
	SpriteRender			m_compassguideline;			// �w�j�̉摜
	SpriteRender			m_phase[10];					// �t�F�[�Y�̉摜
	SpriteRender			m_directionPhase[10];				// 
//	SpriteRender			m_Render;					//	

	Vector3					m_forward;					// �O�����̃x�N�g��
	Quaternion				m_rotation;					// ��]
	float					m_rot = 0.0f;				// ��]��
	float m_timer=0.0f;
	float m_x = 0.0f;
	float m_y = 675.0f;
	float m_y2 = 550.0f;
	Vector3 m_scale = Vector3::One;

};


