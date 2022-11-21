#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "Box.h"
#include "Player.h"
#include "GameSound.h"



// K2EngineLow�̃O���[�o���A�N�Z�X�|�C���g�B
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{



	// �Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Splatoon"));

	// k2EngineLow�̏������B
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);


	g_postEffect.Init();
	g_Light.Init();
	g_bloom.Init();
	g_renderingEngine.Init();
	g_renderingEngine.InitTextureTarget(0);
	auto gamesound = NewGO<GameSound>(0, "gamesound");


	auto game = NewGO<Game>(0, "game");

//	Box* box;
//	box = NewGO<Box>(0, "box");

	ModelRender modelrender;
	modelrender.Init("Assets/modelData/testModel/testbox2.tkm",false);

	g_renderingEngine.SpriteInit(modelrender.GetTkm()->m_albedo,0);


	Vector3 startVector = Vector3::Zero;
	Vector3 endVector = Vector3::Zero;
	Player* m_player;
	m_player = FindGO<Player>("player");

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();
		// �t���[���̊J�n���ɌĂяo���K�v�����鏈�������s
		g_k2EngineLow->BeginFrame();

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�������Ăяo���B
		g_k2EngineLow->ExecuteUpdate();

		g_renderingEngine.Execute(renderContext);


		modelrender.SetPosition({ 500.0f,300.0f,0.0f });
		modelrender.SetScale(g_vec3One);
		modelrender.Update();

		Vector3 POS;
		Vector2 UV;
		m_player = FindGO<Player>("player");
		startVector = m_player->GetStartVector();
		endVector = m_player->GetEndVector();
		g_renderingEngine.SpriteDraw(modelrender,0,startVector,endVector);
		// step-7 ��ʂɕ\������郌���_�����O�^�[�Q�b�g�Ɋe�탂�f����`�悷��
		modelrender.Draw(renderContext);



		// �f�o�b�O�`�揈�������s����B
		g_k2EngineLow->DebubDrawWorld();


		// �t���[���̏I�����ɌĂяo���K�v�����鏈�������s�B
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}