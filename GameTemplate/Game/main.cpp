#include "stdafx.h"
#include "system/system.h"
#include "Title.h"
#include "Box.h"
#include "Player.h"
#include "GameSound.h"
#include "GameCamera.h"
#include "GameEffect.h"
#include "Fade.h"

// K2EngineLowのグローバルアクセスポイント。
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// メイン関数
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{



	// ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("waternto"));

	// k2EngineLowの初期化。
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


	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();
		// フレームの開始時に呼び出す必要がある処理を実行
		g_k2EngineLow->BeginFrame();

		// ゲームオブジェクトマネージャーの更新処理を呼び出す。
		g_k2EngineLow->ExecuteUpdate();

		g_renderingEngine.Execute(renderContext);

		// デバッグ描画処理を実行する。
		g_k2EngineLow->DebubDrawWorld();


		// フレームの終了時に呼び出す必要がある処理を実行。
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}