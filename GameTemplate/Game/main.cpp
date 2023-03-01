#include "stdafx.h"
#include "system/system.h"
#include "Title.h"
#include "Box.h"
#include "Player.h"
#include "GameSound.h"
#include "GameCamera.h"
#include "GameEffect.h"
#include "Fade.h"

// K2EngineLow�̃O���[�o���A�N�Z�X�|�C���g�B
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{



	// �Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("waternto"));

	// k2EngineLow�̏������B
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);


	g_postEffect.Init();
	g_Light.Init();
	g_bloom.Init();
	g_renderingEngine.Init();
	auto gamesound = NewGO<GameSound>(0, "gamesound");
	auto gameeffect = NewGO<GameEffect>(0, "gameeffect");
	auto fade = NewGO<Fade>(0, "fade");
	auto title = NewGO<Title>(0, "title");


	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();
		// �t���[���̊J�n���ɌĂяo���K�v�����鏈�������s
		g_k2EngineLow->BeginFrame();

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�������Ăяo���B
		g_k2EngineLow->ExecuteUpdate();

		g_renderingEngine.Execute(renderContext);

		// �f�o�b�O�`�揈�������s����B
		g_k2EngineLow->DebubDrawWorld();


		// �t���[���̏I�����ɌĂяo���K�v�����鏈�������s�B
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}