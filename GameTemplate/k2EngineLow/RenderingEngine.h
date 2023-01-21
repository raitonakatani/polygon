#pragma once
#include "LightALL.h"
#include "ShadowMapRender.h"
#include "PostEffect.h"

namespace nsK2EngineLow
{
	struct ModelRenderCB
	{
	public:
		Light m_light;          // ���C�g
		float uvscroll;
		Matrix mlvp; // ���C�g�r���[�v���W�F�N�V�����s��B
		float ObjectCameraLength; //�f�B�U�����O�ŕK�v�Ȃ�B

	};
	class RenderingEngine :public Noncopyable
	{
	public:
		void Init();

		void InitTextureTarget(int i);

		void SpriteInit(const char* albedoMap,int i);

		void SpriteDraw(
			ModelRender& Model,
			int i,
			int reset,
			Vector3& A,		//�����n�_
			Vector3& B		//�����I�_
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

		void IsHitEnemy(
			ModelRender& Model,
			Vector3& startVector,		//�����n�_
			Vector3& endVector,		//�����I�_
			bool& hit
		);

		RenderTarget offscreenRenderTarget[20];
	private:
		std::vector<IRenderer*> m_renderobject;
		ShadowMapRender m_shadowMapRender;
		PostEffect* m_postEffect = &g_postEffect;
		ModelRenderCB m_modelRenderCB;
		RenderTarget m_mainRenderTarget;

		SpriteInitData inkspriteinitdata[20];
		Sprite inksprite[20];
		SpriteInitData spriteinitdata[20];
		Sprite sprite[20];

	};

	extern RenderingEngine g_renderingEngine;

}