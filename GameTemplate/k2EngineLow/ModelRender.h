#pragma once

namespace nsK2EngineLow {

	class ModelRender : public IRenderer
	{
	public:

		ModelRender();
		~ModelRender();

		void Init(
			const char* filePath,
			bool shadowRecieve,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			bool isShadowReciever = true,
			int maxInstance = 1
		);

		void SetCasterShadow(const bool castershadow)
		{
			m_isShadowCaster = castershadow;
		}

	private:
		RenderTarget albedRT;
		RenderTarget normalRT;
		RenderTarget worldPosRT;
		SpriteInitData spriteInitData;
		Sprite defferdLightinSpr;
	public:


		void InitModel(const char* filePath);

		void InitTestModel(const char* filePath);


		void modelUpdate();

		Model m_testmodel;

		ModelInitData transModelInitData;
		Model sphereModel;
		Vector3 planePos = { 0.0f, 160.0f, 20.0f };

		void Draw(RenderContext& rc);

		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		/// <remark>
		/// �C���X�^���V���O�`�悪�L���̏ꍇ�́A���̐ݒ�͖�������܂��B
		/// </remark>
		/// <param name="pos">���W�B</param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		/// <param name="x">x���W</param>
		/// <param name="y">y���W</param>
		/// <param name="z">z���W</param>
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}
		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <remark>
		/// �C���X�^���V���O�`�悪�L���̏ꍇ�́A���̐ݒ�͖�������܂��B
		/// </remark>
		/// <param name="rotation">��]�B</param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		/// <summary>
		/// �g�嗦��ݒ�B
		/// </summary>
		/// <remark>
		/// �C���X�^���V���O�`�悪�L���̏ꍇ�́A���̐ݒ�͖�������܂��B
		/// </remark>
		/// <param name="scale">�g�嗦�B</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		void SetScale(float x, float y, float z)
		{
			SetScale({ x, y, z });
		}

		void Update();


		/// <summary>
		/// �A�j���[�V�����̏������B
		/// </summary>
		/// <param name="animationClips">�A�j���[�V�����N���b�v�B</param>
		/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐��B</param>
		/// <param name="enModelUpAxis">���f���̏�����B</param>
		void InitAnimation(AnimationClip* animationClips,
			int numAnimationClips,
			EnModelUpAxis enModelUpAxis);
		/// <summary>
		/// �A�j���[�V�����Đ��B
		/// </summary>
		/// <param name="animNo">�A�j���[�V�����N���b�v�̔ԍ��B</param>
		/// <param name="interpolateTime">�⊮����(�P�ʁF�b�B)</param>
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}
		/// <summary>
		/// �A�j���[�V�����̍Đ����H
		/// </summary>
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}
		/// <summary>
		/// �A�j���[�V�����̍Đ����x��ݒ肷��
		/// </summary>
		/// <param name="animationSpeed">���l�̕������{�ɂ���</param>
		void SetAnimationSpeed(const float animationSpeed = 1.0f)
		{
			m_animationSpeed = animationSpeed;
		}
		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}
		/// <summary>
		/// �{�[���̖��O����{�[���ԍ��������B
		/// </summary>
		/// <param name="boneName">�{�[���̖��O</param>
		/// <returns>�{�[���ԍ��B������Ȃ������ꍇ��-1���Ԃ��Ă��܂��B</returns>
		int FindBoneID(const wchar_t* boneName) const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		/// <summary>
		/// �{�[���ԍ�����{�[�����擾�B
		/// </summary>
		/// <param name="boneNo">�{�[���ԍ�</param>
		/// <returns>�{�[��</returns>
		Bone* GetBone(int boneNo) const
		{
			return m_skeleton.GetBone(boneNo);
		}
		/// <summary>
		/// ���f�����擾�B
		/// </summary>
		/// <returns>���f��</returns>
		Model& GetModel()
		{
			return m_model;
		}

		/// <summary>
		/// ���W�A��]�A�g���S�Đݒ�B
		/// </summary>
		/// <remark>
		/// �C���X�^���V���O�`�悪�L���̏ꍇ�́A���̐ݒ�͖�������܂��B
		/// </remark>
		/// <param name="pos">���W�B</param>
		/// <param name="rotation">��]�B</param>
		/// <param name="scale">�g��B</param>
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}
		/// <summary>
		/// �C���X�^���V���O�`����s���H
		/// </summary>
		/// <returns></returns>
		bool IsInstancingDraw() const
		{
			return m_isEnableInstancingDraw;
		}
		/// <summary>
		/// ���[���h�s����擾�B
		/// </summary>
		/// <param name="instanceId">
		/// �C���X�^���XID�B
		/// ���̈����̓C���X�^���V���O�`�悪�������̏ꍇ�͖�������܂��B
		/// </param>
		/// <returns></returns>
		const Matrix& GetWorldMatrix(int instanceId) const
		{
			if (IsInstancingDraw()) {
				return m_worldMatrixArray[instanceId];
			}
			return m_model.GetWorldMatrix();
		}
		/// <summary>
		/// �C���X�^���V���O�f�[�^�̍X�V�B
		/// </summary>
		/// <param name="pos">���W</param>
		/// <param name="rot">��]</param>
		/// <param name="scale">�g�嗦</param>
		void UpdateInstancingData(const Vector3& pos, const Quaternion& rot, const Vector3& scale);

		void Change(const char* materialName, Texture& albedoMap) {
			m_model.ChangeAlbedoMap(materialName, albedoMap);
		}

		TkmFile* GetTkm()
		{
			return m_model.GetTkmFile();
		}

		bool m_isHit;

		//�x�N�g������
		double dot_product(const Vector3& vl, const Vector3 vr) {
			return vl.x * vr.x + vl.y * vr.y + vl.z * vr.z;
		}

		//�O�p�`�Ɠ_�̓����蔻��
		bool hittest_polygon_3d(
			Vector3& A,
			Vector3& B,
			Vector3& C,
			Vector3& P)
		{
			Vector3 AB, BP, BC, CP, CA, AP;

			//�x�N�g���̌��Z
			AB.Subtract(B, A);
			BP.Subtract(P, B);

			BC.Subtract(C, B);
			CP.Subtract(P, C);

			CA.Subtract(A, C);
			AP.Subtract(P, A);

			Vector3 c1, c2, c3;

			//�O�ς����߂�
			c1.Cross(AB, BP);
			c2.Cross(BC, CP);
			c3.Cross(CA, AP);

			//���ςŏ��������t���������ׂ�
			double dot_12 = dot_product(c1, c2);
			double dot_13 = dot_product(c1, c3);

			if (dot_12 > 0 && dot_13 > 0) {

				int hit = 0;
				//�O�p�`�̓����ɓ_������
				return true;
			}

			int nohit = 0;
			//�O�p�`�̊O���ɓ_������
			return false;
		}



		//����AB�ƕ��ʂ̌�_���v�Z����
		bool IntersectPlaneAndLine(
			Vector3& out,	//�߂�l�@��_��������Ίi�[����� �Փ˓_
			Vector2& uv,	//�߂�l�@��_��������Ίi�[����� �Փ˂����|���S���̂R���_��UV���W
			Vector3& A,		//�����n�_
			Vector3& B,		//�����I�_
			std::vector<nsK2EngineLow::TkmFile::VectorBuffer>& vectorBuffer
		) //����
		{
			for (int i = 0;i < vectorBuffer.size();i++)
			{

				Matrix matrix;

				//���[���h�s����擾
				matrix = m_model.GetWorldMatrix();

				//���_���W�����[���h���W�ɕϊ�
				matrix.Apply(vectorBuffer[i].buffer[0]);
				matrix.Apply(vectorBuffer[i].buffer[1]);
				matrix.Apply(vectorBuffer[i].buffer[2]);

				////�@�������[���h���W�ɕϊ�
				//matrix.Apply(vectorBuffer[i].normal);
				//vectorBuffer[i].normal.Normalize();

				//���ʏ�̓_P
				//�_P�P�����_�P�iVector3�j
				Vector3 P = Vector3(vectorBuffer[i].buffer[0]);

				//PA PB�x�N�g��
				Vector3 PA = Vector3(P.x - A.x, P.y - A.y, P.z - A.z);
				Vector3 PB = Vector3(P.x - B.x, P.y - B.y, P.z - B.z);

				//PA PB���ꂼ��𕽖ʖ@���Ɠ���
				double dot_PA = PA.Dot(vectorBuffer[i].normal);
				double dot_PB = PB.Dot(vectorBuffer[i].normal);

				//����͐��[�����ʏ�ɂ��������̌v�Z�̌덷���z�����Ă��܂��B�������Ďg���Ă��������B
				if (abs(dot_PA) < 0.000001) { dot_PA = 0.0; }
				if (abs(dot_PB) < 0.000001) { dot_PB = 0.0; }

				//��������
				if (dot_PA == 0.0 && dot_PB == 0.0) {
					//���[�����ʏ�ɂ���A��_���v�Z�ł��Ȃ��B
					continue;
				}
				if ((dot_PA >= 0.0 && dot_PB <= 0.0) ||
					(dot_PA <= 0.0 && dot_PB >= 0.0)) {
					//���ς̕Е����v���X�ŕЕ����}�C�i�X�Ȃ̂ŁA�������Ă���

				}
				else {
					NOHit();
					//�������Ă��Ȃ�
					continue;
				}

				//�ȉ��A��_�����߂� 

				Vector3 AB = Vector3(B.x - A.x, B.y - A.y, B.z - A.z);

				//��_��A�̋��� : ��_��B�̋��� = dot_PA : dot_PB
				double hiritu = abs(dot_PA) / (abs(dot_PA) + abs(dot_PB));

				//�Փ˓_�̍��W�����߂�B
				out.x = A.x + (AB.x * hiritu);
				out.y = A.y + (AB.y * hiritu);
				out.z = A.z + (AB.z * hiritu);

				/*	if (hittest_polygon_3d(vectorBuffer[i].buffer[0], vectorBuffer[i].buffer[1], vectorBuffer[i].buffer[2], out) == false)
					{
						continue;
					}*/


				auto v0v1 = vectorBuffer[i].buffer[1] - vectorBuffer[i].buffer[0];
				auto v0h = out - vectorBuffer[i].buffer[0];
				float z = dot_product(v0v1, v0h);
				z *= 0.5f;

				auto v1v2 = vectorBuffer[i].buffer[2] - vectorBuffer[i].buffer[1];
				auto v1h = out - vectorBuffer[i].buffer[1];
				float x = dot_product(v1v2, v1h);
				x *= 0.5f;

				auto v2v0 = vectorBuffer[i].buffer[0] - vectorBuffer[i].buffer[2];
				auto v2h = out - vectorBuffer[i].buffer[2];
				float y = dot_product(v2v0, v2h);
				y *= 0.5f;


				float xyz = x + y + z;
				float uvx, uvy, uvz;


				uvx = x / xyz;
				uvy = y / xyz;
				uvz = z / xyz;

				//���v���P�ɂȂ�
				float a = uvx + uvy + uvz;

				Vector2 Huv0;
				Huv0.x = vectorBuffer[i].uv[0].x * uvx;
				Huv0.y = vectorBuffer[i].uv[0].y * uvx;
				Vector2 Huv1;
				Huv1.x = vectorBuffer[i].uv[1].x * uvy;
				Huv1.y = vectorBuffer[i].uv[1].y * uvy;
				Vector2 Huv2;
				Huv2.x = vectorBuffer[i].uv[2].x * uvz;
				Huv2.y = vectorBuffer[i].uv[2].y * uvz;

				//�Փ˓_��UV���W�����߂�B
				uv.x = Huv0.x + Huv1.x + Huv2.x;
				uv.y = Huv0.y + Huv1.y + Huv2.y;


				HitFlag();

				int ai = 0;
				return true;
			}

			return false;
		}


		void NOHit()
		{
			m_isHit = false;
		}

		void HitFlag()
		{
			m_isHit = true;
		}

		bool IsHitFlag()
		{
			return m_isHit;
		}

		///��肽�����ƃ��X�g�i���Ȃ���΂Ȃ�Ȃ��j
		///���̂P�@���������ꏊ�����߂�@�@�@�@�@�@�@						�ł���		modelRender.h�ōs���Ă���
		///�@�@�@�@�Փ˂����|���S���̂R���_��UV���W�������Ă���				�ł���
		///���̂Q�@�����������ǂ����̔���									�ł���		modelRender.h�ōs���Ă���
		///���̂R�@�C���N���e�N�X�`���ɃI�t�X�N���[�������_�����O			�o���ĂȂ��@�@DrawTexture�N���X�ōs��
		///�@�@�@�@���C�������@�@�@���̎��Ƀe�N�X�`�������ւ�				�ł���
		///�@�@�@�@�V�F�[�_�[�����@�Փ˓_��UV���W�����߂�@�@�@�@�@�@�@�@�@
		///���̂S�@�ł�������I���X�N���[�������_�����O
		///        ���C�������@�@�@�����ւ����e�N�X�`�������ɖ߂�			


		///���̌�@�C���Q�[������
		/// �v���C���[�̃A�j���[�V���������̍쐬
		/// �A�C�h���i�_�����j�@����@���i�~�܂�Ȃ���j�@���i����Ȃ���j
		/// �X�v���Q�̃C�N�����[�h��z�肵�ă}�b�v�����
		/// �Q�[�����e�̓K�`�G���A�@�G�Ɉ��ȏ�w�n��h��ꂽ��Q�[���I�[�o�[
		/// �E�F�[�u�����z������Q�[���N���A
		/// ���X�g��ւ�Ń��b�V�������
		/// 
		/// 
		/// 




	private:
		/// <summary>
		/// �X�P���g���̏������B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X�B</param>
		void InitSkeleton(const char* filePath);

		void InitShadowModel(
			const char* tkmFilePath,
			EnModelUpAxis modelUpAxis);
		/// <summary>
		/// �V���h�E�}�b�v�ւ̕`��p�X����Ă΂�鏈���B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="ligNo">���C�g�ԍ�</param>
		/// <param name="lvpMatrix">���C�g�r���[�v���W�F�N�V�����s��</param>
		void OnRenderShadowMap(
			RenderContext& rc,
			const Matrix& lvpMatrix
		);

		//		const  GetVertexBuffer();


	private:
		Model						m_model;
		Model					m_shadowmodel;							//�V���h�E���f���B
		Skeleton					m_skeleton;							// �X�P���g��
		float						m_animationSpeed = 1.0f;
		AnimationClip* m_animationClips = nullptr;			// �A�j���[�V�����N���b�v�B
		int							m_numAnimationClips = 0;			// �A�j���[�V�����N���b�v�̐��B
		Animation					m_animation;						// �A�j���[�V�����B
		Vector3 					m_position;			// ���W�B
		Quaternion	 				m_rotation;	// ��]�B
		Vector3						m_scale;				// �g�嗦�B
		Model						m_zprepassModel;					// ZPrepass�ŕ`�悳��郂�f��
		int							m_numInstance = 0;					// �C���X�^���X�̐��B
		int							m_maxInstance = 1;					// �ő�C���X�^���X���B
		//int							m_fixNumInstanceOnFrame = 0;		// ���̃t���[���ɕ`�悷��C���X�^���X�̐��̊m�萔�B�B
		bool						m_isEnableInstancingDraw = false;	// �C���X�^���V���O�`�悪�L���H
		std::unique_ptr<Matrix[]>	m_worldMatrixArray;					// ���[���h�s��̔z��B
		StructuredBuffer			m_worldMatrixArraySB;				// ���[���h�s��̔z��̃X�g���N�`���[�h�o�b�t�@�B
		EnModelUpAxis			m_enFbxUpAxis = enModelUpAxisZ;			// FBX�̏�����B
		bool					m_isShadowCaster = true;

		//TkmFile m_tkm;
		//		ModelRenderCB* m_modelCB;

	};
}