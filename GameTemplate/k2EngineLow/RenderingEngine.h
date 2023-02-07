#pragma once
#include "LightALL.h"
#include "ShadowMapRender.h"
#include "PostEffect.h"

namespace nsK2EngineLow
{
	struct ModelRenderCB
	{
	public:
		Light m_light;          // ライト
		float uvscroll;
		Matrix mlvp; // ライトビュープロジェクション行列。
		float ObjectCameraLength; //ディザリングで必要なやつ。

	};
	class RenderingEngine :public Noncopyable
	{
	public:
		void Init();

		void InitTextureTarget(int i);

		void SpriteInit(const char* albedoMap,int i);

		void SpriteDraw(
			Vector3& position,
			int target,
			ModelRender& Model,
			int i,
			int reset,
			Vector3& A,		//線分始点
			Vector3& B		//線分終点
		);

		void AddRenderObject(IRenderer* renderobj)
		{
			m_renderobject.push_back(renderobj);
		}

		void Render2DDraw(RenderContext& rc);



		void ShadowMapDraw(RenderContext& rc);

		void Execute(RenderContext& rc);

		Texture& GetShadowMap()
		{
			return m_shadowMapRender.GetShadowMap();
		}
		Camera& GetLightCamera()
		{
			return m_shadowMapRender.GetLightCamera();
		}
		ModelRenderCB& GetModelRenderCB()
		{
			return m_modelRenderCB;
		}

		void IsUVScroll(const float& uv)
		{
			m_modelRenderCB.uvscroll = uv;
		}

		RenderTarget offscreenRenderTarget[70];
	private:
		std::vector<IRenderer*> m_renderobject;
		ShadowMapRender m_shadowMapRender;
		PostEffect* m_postEffect = &g_postEffect;
		ModelRenderCB m_modelRenderCB;
		RenderTarget m_mainRenderTarget;

		SpriteInitData inkspriteinitdata[70];
		Sprite inksprite[70];
		SpriteInitData spriteinitdata[70];
		Sprite sprite[70];

	};

	extern RenderingEngine g_renderingEngine;

}