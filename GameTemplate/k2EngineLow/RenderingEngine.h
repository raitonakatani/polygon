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
		Matrix mlvp; // ���C�g�r���[�v���W�F�N�V�����s��B
		float ObjectCameraLength; //�f�B�U�����O�ŕK�v�Ȃ�B

	};
	class RenderingEngine :public Noncopyable
	{
	public:
		void Init();

		void InitTextureTarget();

		void SpriteInit(const char* aldeboMap);

		void SpriteDraw(
			ModelRender& Model,
			Vector3& out,	//�߂�l�@��_��������Ίi�[����� �Փ˓_
			Vector2& uv,	//�߂�l�@��_��������Ίi�[����� �Փ˂����|���S���̂R���_��UV���W
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

		RenderTarget offscreenRenderTarget;
	private:
		std::vector<IRenderer*> m_renderobject;
		ShadowMapRender m_shadowMapRender;
		PostEffect* m_postEffect = &g_postEffect;
		ModelRenderCB m_modelRenderCB;
		RenderTarget m_mainRenderTarget;

		SpriteInitData inkspriteinitdata;
		Sprite inksprite;
		SpriteInitData spriteinitdata;
		Sprite sprite;

	};

	extern RenderingEngine g_renderingEngine;

}