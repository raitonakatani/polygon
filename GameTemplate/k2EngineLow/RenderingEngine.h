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
			Vector3& position,
			int target,
			ModelRender& Model,
			int i,
			int reset,
			Vector3& A,		//�����n�_
			Vector3& B		//�����I�_
		);

		void ClearRenderTarget(
			int i,
			ModelRender& Model
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


		void SpriteRelease()
		{
			inksprite.clear();
			sprite.clear();
		}

		RenderTarget offscreenRenderTarget[70];
	private:
		std::vector<IRenderer*> m_renderobject;
		ShadowMapRender m_shadowMapRender;
		PostEffect* m_postEffect = &g_postEffect;
		ModelRenderCB m_modelRenderCB;
		RenderTarget m_mainRenderTarget;

		std::unordered_map<int, std::unique_ptr<Sprite>> inksprite;
		std::unordered_map<int, std::unique_ptr<Sprite>> sprite;

	};

	extern RenderingEngine g_renderingEngine;

}