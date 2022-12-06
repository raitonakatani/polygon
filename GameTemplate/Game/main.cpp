#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "Box.h"
#include "Player.h"
#include "GameSound.h"
#include "GameCamera.h"


// K2EngineLowのグローバルアクセスポイント。
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// メイン関数
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{



	// ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Splatoon"));

	// k2EngineLowの初期化。
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);


	g_postEffect.Init();
	g_Light.Init();
	g_bloom.Init();
	g_renderingEngine.Init();
	g_renderingEngine.InitTextureTarget(0);
	auto gamesound = NewGO<GameSound>(0, "gamesound");


	auto game = NewGO<Game>(0, "game");

	GameCamera* m_gameCamera;


	SpriteRender compass;
	compass.Init("Assets/sprite/compass.DDS",256,256);

	SpriteRender compassguideline;
	compassguideline.Init("Assets/sprite/guideline.DDS", 256, 256);
	//guideline

//	Box* box;
//	box = NewGO<Box>(0, "box");

	ModelRender modelrender;
	modelrender.Init("Assets/modelData/testModel/box.tkm",false);

	g_renderingEngine.SpriteInit(modelrender.GetTkm()->m_albedo,0);

	Quaternion rot;
	Vector3 startVector = Vector3::Zero;
	Vector3 endVector = Vector3::Zero;
	Player* m_player;
	m_player = FindGO<Player>("player");

	float m_rot = 0.0f;

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();
		// フレームの開始時に呼び出す必要がある処理を実行
		g_k2EngineLow->BeginFrame();

		// ゲームオブジェクトマネージャーの更新処理を呼び出す。
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
		// step-7 画面に表示されるレンダリングターゲットに各種モデルを描画する
		modelrender.Draw(renderContext);

	//	Vector3 cameraforward = g_camera3D->GetForward();
	//	m_gameCamera = FindGO<GameCamera>("gameCamera");
	//	Vector3 forward  = m_gameCamera->GetForwardPosition();
	//	Vector2 camera;
	//	camera.x = cameraforward.x;
	//	camera.y = cameraforward.z;
	//	Vector2 camera2;
	//	camera2.x = forward.x;
	//	camera2.y = forward.y;
	//	m_rot = camera2.Dot(camera);
	//	m_rot = acos(m_rot);


		//パッドの入力を使ってコンパスを回す。
		m_rot += g_pad[0]->GetRStickXF() * 2.0f;
		//Z軸周りの回転
		rot.SetRotationDegZ(m_rot);
		compass.SetPosition({ -650.0f,-300.0f,0.0f });
		compass.SetRotation(rot);
		compass.Update();
		compass.Draw(renderContext);
		
		compassguideline.SetPosition({ -650.0f,-300.0f,0.0f });
		compassguideline.Update();
		compassguideline.Draw(renderContext);

		// デバッグ描画処理を実行する。
		g_k2EngineLow->DebubDrawWorld();


		// フレームの終了時に呼び出す必要がある処理を実行。
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}