#pragma once


#include "LevelRender.h"

// �O���錾�B
class Player;
class GameCamera;
class Background;
class Floor;
class Box;
class Cylinder;
class Triangle;
class Enemy;
class GameUI;
class Fade;


class Game : public IGameObject
{

public:
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	int m_number = 0;
private:
	LevelRender			m_levelRender[5];				//���x�������_�[�B 
	GameCamera*			m_gameCamera = nullptr;			//�J����
	Background*			m_background = nullptr;			//�w�i�i�X�e�[�W�j
	Floor*				m_floor = nullptr;				//�w�i�i���j
	Box*				m_box = nullptr;				//�w�i�i���j
	Cylinder*			m_cylinder = nullptr;			//�w�i�i�~���j
	Triangle*			m_triangle = nullptr;			//�w�i�i�~���j
	Player*				m_player = nullptr;				//�v���C���[
	Enemy*				m_enemy = nullptr;				//�G�l�~�[
	Fade*				m_fade = nullptr;				//�t�F�[�h
	GameUI*				m_ui = nullptr;					//UI
	float				m_timer = 0.0f;					//�^�C�}�[

	int phase=1;
	std::string FILE[5];
};
