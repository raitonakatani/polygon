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
		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̕`�揈�����Ăяo���B
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

	void RenderingEngine::InitTextureTarget()
	{
		offscreenRenderTarget.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	void RenderingEngine::SpriteInit(const char* aldeboMap)
	{
		//�C���N�̃e�N�X�`��
		//��������f���̃e�N�X�`���ɓh�肽��
		//DDS�t�@�C��(�摜�f�[�^)�̃t�@�C���p�X���w�肷��B
		inkspriteinitdata.m_ddsFilePath[0] = "Assets/sprite/inku2.DDS";
		//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
		inkspriteinitdata.m_fxFilePath = "Assets/shader/sprite.fx";
		//�X�v���C�g�̕��ƍ������w�肷��B
		inkspriteinitdata.m_width = FRAME_BUFFER_W;
		inkspriteinitdata.m_height = FRAME_BUFFER_W;
		//Sprite�������I�u�W�F�N�g���g�p���āASprite������������B
		inksprite.Init(inkspriteinitdata);

		//���f���̃e�N�X�`��
		//����ɃC���N��h���ăe�N�X�`���؂�ւ���������
		//DDS�t�@�C��(�摜�f�[�^)�̃t�@�C���p�X���w�肷��B
		spriteinitdata.m_ddsFilePath[0] = aldeboMap;
		//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
		spriteinitdata.m_fxFilePath = "Assets/shader/Splatoon/inksprite.fx";
		//�X�v���C�g�̕��ƍ������w�肷��B
		spriteinitdata.m_width = FRAME_BUFFER_W;
		spriteinitdata.m_height = FRAME_BUFFER_H;
		spriteinitdata.m_expandShaderResoruceView[0] = &inksprite.GetTexture(0);
	//	spriteinitdata.m_expandShaderResoruceView[1] = &offscreenRenderTarget.GetRenderTargetTexture();
		sprite.Init(spriteinitdata);
		//	spriteinitdata.m_posi = { 0.125f,0.125f };
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������B
		//	sprite.Init(spriteinitdata);
	}


	void RenderingEngine::SpriteDraw(
		ModelRender& Model,
		Vector3& POS,	//�߂�l�@��_��������Ίi�[����� �Փ˓_
		Vector2& UV,	//�߂�l�@��_��������Ίi�[����� �Փ˂����|���S���̂R���_��UV���W
		Vector3& startVector,		//�����n�_
		Vector3& endVector		//�����I�_
	)
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		//�O�p�`�̍��W�������Ă��郊�X�g�������Ă���B
		std::vector<nsK2EngineLow::TkmFile::VectorBuffer> bufferList = Model.GetTkm()->GetBuffer();

		Vector3 pos;
		Vector2 uv;
		//���ʂƐ����̌�_�����߂�B�@POS�i��_�̍��W�j�Avector3d(�����n�_)�Avector3dend(�����I�_)�A�|���S����3���_
		if (Model.IntersectPlaneAndLine(pos, uv, startVector, endVector, bufferList) == true) {

			Model.Change(
				"",
				offscreenRenderTarget.GetRenderTargetTexture()
			);

			// step-4 �����_�����O�^�[�Q�b�g��offscreenRenderTarget�ɕύX����
			RenderTarget* rtArray[] = { &offscreenRenderTarget };
			renderContext.WaitUntilToPossibleSetRenderTargets(1, rtArray);
			renderContext.SetRenderTargets(1, rtArray);
			renderContext.ClearRenderTargetViews(1, rtArray);

			// step-5 offscreenRenderTarget�ɔw�i�A�v���C���[��`�悷��
			if (g_pad[0]->IsPress(enButtonA)) {
				sprite.InitUVPosition(uv);
			}
			sprite.Draw(renderContext);

			renderContext.WaitUntilFinishDrawingToRenderTargets(1, rtArray);
			// step-6 ��ʂɕ\������郌���_�����O�^�[�Q�b�g�ɖ߂�
			renderContext.SetRenderTarget(
				g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
				g_graphicsEngine->GetCurrentFrameBuffuerDSV()
			);

			spriteinitdata.m_hit = 1;
		}
	}
}