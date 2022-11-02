#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "Box.h"
#include "Player.h"



// K2EngineLowのグローバルアクセスポイント。
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// メイン関数
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{



	// ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("SpecialSense"));

	// k2EngineLowの初期化。
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);


//	g_postEffect.Init();
	g_Light.Init();
////	g_bloom.Init();
//	//	g_DrawTexture.Init();
	g_renderingEngine.Init();

	auto game = NewGO<Game>(0, "game");



	//箱
	ModelInitData boxModelInitData;
	boxModelInitData.m_tkmFilePath = "Assets/modelData/testModel/testbox2.tkm";
	boxModelInitData.m_fxFilePath = "Assets/shader/sample3D.fx";
	Model boxModel;
	boxModel.Init(boxModelInitData);
	Quaternion	rotation;
	rotation.SetRotationDegY(90.f);
	//boxModel.UpdateWorldMatrix({ 500.0f,350.0f,0.0f }, rotation, g_vec3One);

	//boxModel.UpdateWorldMatrix(Vector3::Zero, g_quatIdentity, g_vec3One);
	boxModel.UpdateWorldMatrix({ 500.0f,300.0f,0.0f }, g_quatIdentity, g_vec3One);

	g_renderingEngine.SpriteInit(boxModel.GetTkmFile()->m_albedo);


	Vector3 startVector = Vector3::Zero;
	Vector3 endVector = Vector3::Zero;
	//0.223011225
	//    0.313250005

	Vector3 position;
	position = { 0.0f,0.0f,300.0f };

	Player* m_player;
	m_player = FindGO<Player>("player");

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();
		// フレームの開始時に呼び出す必要がある処理を実行
		g_k2EngineLow->BeginFrame();

		// ゲームオブジェクトマネージャーの更新処理を呼び出す。
		g_k2EngineLow->ExecuteUpdate();


		// step-7 画面に表示されるレンダリングターゲットに各種モデルを描画する
		boxModel.Draw(renderContext);


		Vector3 POS;
		Vector2 UV;



		m_player = FindGO<Player>("player");

		startVector = m_player->GetStartVector();
		endVector = m_player->GetEndVector();
	

		g_renderingEngine.SpriteDraw(boxModel,POS,UV,startVector,endVector);


		g_renderingEngine.Execute(renderContext);

		// デバッグ描画処理を実行する。
		g_k2EngineLow->DebubDrawWorld();


		// フレームの終了時に呼び出す必要がある処理を実行。
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}