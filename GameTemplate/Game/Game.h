#pragma once


#include "LevelRender.h"

// �O���錾�B
class Player;
class GameCamera;
class Background;
class Stairs;
class Floor;
class Box;
class Cylinder;
class Triangle;
class Enemy;
class GameUI;
class Fade;
class Clearmodel;


class Game : public IGameObject
{

public:
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	struct PaintList {
		bool m_paint[5];
	};
	PaintList m_paintlist[8];
	int m_paintnumber = 0;

	Vector3 m_enemyposi;
	Vector3 m_enemypaint;
	int m_phase = 1;
private:
	LevelRender			m_levelRender[5];				// ���x�������_�[�B 
	GameCamera*			m_gameCamera = nullptr;			// �J����
	Background*			m_background = nullptr;			// �w�i�i�X�e�[�W�j
	Stairs*				m_stairs = nullptr;				// �w�i�i�X�e�[�W�j
	Floor*				m_floor = nullptr;				// �w�i�i���j
	Box*				m_box = nullptr;				// �w�i�i���j
	Cylinder*			m_cylinder = nullptr;			// �w�i�i�~���j
	Triangle*			m_triangle = nullptr;			// �w�i�i�O�p�`�j
	Player*				m_player = nullptr;				// �v���C���[
	Enemy*				m_enemy = nullptr;				// �G�l�~�[
	Fade*				m_fade = nullptr;				// �t�F�[�h
	GameUI*				m_ui = nullptr;					// UI
	Clearmodel*			m_clearmodel = nullptr;			// �N���A���f��
	std::string			m_file[5];
	int					m_number = 0;					// �G�̐�
	float				m_timer = 0.0f;					// �^�C�}�[
	bool				m_isWaitFadeout = false;		// �t�F�[�h�B
};
