#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	RenderingEngine g_renderingEngine;
	void RenderingEngine::Render2DDraw(RenderContext& rc)
	{
		for (auto& renderObj : m_renderobject) {
			renderObj->OnRenderFont2D(rc);
		}
		for (auto& renderObj : m_renderobject) {
			renderObj->OnRenderSprite2D(rc);
		}


	}

	void RenderingEngine::ShadowMapDraw(RenderContext& rc)
	{
		Vector3 dir = { g_Light.GetDirectionLightDirection().x,g_Light.GetDirectionLightDirection().y,g_Light.GetDirectionLightDirection().z };
		m_shadowMapRender.Render(rc, dir, m_renderobject);
	}
	void RenderingEngine::Execute(RenderContext& rc)
	{
		g_Light.Update();
		m_modelRenderCB.m_light = g_Light.GetLight();
		m_modelRenderCB.mlvp = GetLightCamera().GetViewProjectionMatrix();
		// ゲームオブジェクトマネージャーの描画処理を呼び出す。
		g_engine->ExecuteRender();
		ShadowMapDraw(rc);

		m_postEffect->Render(rc);

		Render2DDraw(rc);
		m_renderobject.clear();
	}
	void RenderingEngine::Init()
	{
		m_postEffect = &g_postEffect;
		m_shadowMapRender.Init();
		m_modelRenderCB.m_light = g_Light.GetLight();
		m_modelRenderCB.mlvp = GetLightCamera().GetViewProjectionMatrix();
	}

	void RenderingEngine::InitTextureTarget(int i)
	{
			offscreenRenderTarget[i].Create(
				FRAME_BUFFER_W,
				FRAME_BUFFER_H,
				1,
				1,
				DXGI_FORMAT_R8G8B8A8_UNORM,
				DXGI_FORMAT_D32_FLOAT
			);
	}

	void RenderingEngine::SpriteInit(const char* albedoMap,int i)
	{
		//インクのテクスチャ
		//これをモデルのテクスチャに塗りたい
		//DDSファイル(画像データ)のファイルパスを指定する。
		inkspriteinitdata[i].m_ddsFilePath[0] = "Assets/sprite/inku2.DDS";
		//Sprite表示用のシェーダーのファイルパスを指定する。
		inkspriteinitdata[i].m_fxFilePath = "Assets/shader/sprite.fx";
		//スプライトの幅と高さを指定する。
		inkspriteinitdata[i].m_width = FRAME_BUFFER_W;
		inkspriteinitdata[i].m_height = FRAME_BUFFER_W;
		//Sprite初期化オブジェクトを使用して、Spriteを初期化する。
		inksprite[i].Init(inkspriteinitdata[i]);

		//モデルのテクスチャ
		//これにインクを塗ってテクスチャ切り替えをしたい
		//DDSファイル(画像データ)のファイルパスを指定する。
		spriteinitdata[i].m_ddsFilePath[0] = albedoMap;
		//Sprite表示用のシェーダーのファイルパスを指定する。
		spriteinitdata[i].m_fxFilePath = "Assets/shader/Splatoon/inksprite.fx";
		//スプライトの幅と高さを指定する。
		spriteinitdata[i].m_width = FRAME_BUFFER_W;
		spriteinitdata[i].m_height = FRAME_BUFFER_H;
		spriteinitdata[i].m_expandShaderResoruceView[0] = &inksprite[i].GetTexture(0);
		spriteinitdata[i].m_expandShaderResoruceView[1] = &offscreenRenderTarget[i].GetRenderTargetTexture();
		sprite[i].Init(spriteinitdata[i]);
	}


	void RenderingEngine::SpriteDraw(
		ModelRender& Model,
		int i,
		Vector3& startVector,		//線分始点
		Vector3& endVector		//線分終点
	)
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		//三角形の座標が入っているリストを持ってくる。
		std::vector<nsK2EngineLow::TkmFile::VectorBuffer> bufferList = Model.GetTkm()->GetBuffer();

		Vector3 pos;
		Vector2 uv;
		//平面と線分の交点を求める。　POS（交点の座標）、vector3d(線分始点)、vector3dend(線分終点)、ポリゴンの3頂点
		if (Model.IntersectPlaneAndLine(pos, uv, startVector, endVector, bufferList) == true) {		
			Model.Change(
				"",
				offscreenRenderTarget[i].GetRenderTargetTexture()
			);
			// step-4 レンダリングターゲットをoffscreenRenderTargetに変更する
			RenderTarget* rtArray[] = { &offscreenRenderTarget[i] };
			renderContext.WaitUntilToPossibleSetRenderTargets(1, rtArray);
			renderContext.SetRenderTargets(1, rtArray);
//			renderContext.ClearRenderTargetViews(1, rtArray);

			// step-5 offscreenRenderTargetに背景、プレイヤーを描画する
				sprite[i].InitUVPosition(uv);
				sprite[i].Draw(renderContext);
			
			renderContext.WaitUntilFinishDrawingToRenderTargets(1, rtArray);
			// step-6 画面に表示されるレンダリングターゲットに戻す
			renderContext.SetRenderTarget(
				g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
				g_graphicsEngine->GetCurrentFrameBuffuerDSV()
			);

			sprite[i].IsHit(1);
		}
	}
}