#pragma once

#include "tkFile/TkmFile.h"
#include "MeshParts.h"
#include "Skeleton.h"

namespace nsK2EngineLow {
	class IShaderResource;

	//���f���̏����
	enum EnModelUpAxis {
		enModelUpAxisY,		//���f���̏������Y���B
		enModelUpAxisZ,		//���f���̏������Z���B
	};



	/// <summary>
	/// ���f���̏������f�[�^
	/// </summary>
	struct ModelInitData {
		const char* m_tkmFilePath = nullptr;							// tkm�t�@�C���p�X�B
		const char* m_vsEntryPointFunc = "VSMain";						// ���_�V�F�[�_�[�̃G���g���[�|�C���g�B
		const char* m_vsSkinEntryPointFunc = "VSMain";					// �X�L������}�e���A���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g�B
		const char* m_psEntryPointFunc = "PSMain";						// �s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g�B
		const char* m_fxFilePath = nullptr;								// .fx�t�@�C���̃t�@�C���p�X�B
		void* m_expandConstantBuffer = nullptr;							// ���[�U�[�g���̒萔�o�b�t�@�B
		int m_expandConstantBufferSize = 0;								// ���[�U�[�g���̒萔�o�b�t�@�̃T�C�Y�B
		std::array<IShaderResource*, MAX_MODEL_EXPAND_SRV> m_expandShaderResoruceView = { nullptr };	// ���[�U�[�g���̃V�F�[�_�[���\�[�X�B
																										// t10���W�X�^���珇�ԂɊ��蓖�Ă��܂��B
		Skeleton* m_skeleton = nullptr;									// �X�P���g���B
		EnModelUpAxis m_modelUpAxis = enModelUpAxisZ;					// ���f���̏�����B
		AlphaBlendMode m_alphaBlendMode = AlphaBlendMode_None;			// �A���t�@�u�����f�B���O���[�h�B
		bool m_isDepthWrite = true;										// �[�x�o�b�t�@�ɏ������ށH
		bool m_isDepthTest = true;										// �[�x�e�X�g���s���H
		D3D12_CULL_MODE m_cullMode = D3D12_CULL_MODE_BACK;				// �J�����O���[�h�B
		std::array<DXGI_FORMAT, MAX_RENDERING_TARGET> m_colorBufferFormat = {
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_UNKNOWN,
		};	//�����_�����O����J���[�o�b�t�@�̃t�H�[�}�b�g�B
	};
	/// <summary>
	/// �}�e���A�����ď��������邽�߂̃f�[�^�B
	/// </summary>
	struct MaterialReInitData {
		std::array<IShaderResource*, MAX_MODEL_EXPAND_SRV> m_expandShaderResoruceView = { nullptr };
	};
	/// <summary>
	/// ���f���N���X�B
	/// </summary>
	class Model : public Noncopyable {

	public:

		/// <summary>
		/// tkm�t�@�C�����珉�����B
		/// </summary>
		/// <param name="initData">�������f�[�^</param>
		void Init(const ModelInitData& initData);
		/// <summary>
		/// ���[���h�s��̍X�V�B
		/// </summary>
		/// <param name="pos">���W</param>
		/// <param name="rot">��]</param>
		/// <param name="scale">�g�嗦</param>
		void UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale)
		{
			m_worldMatrix = CalcWorldMatrix(pos, rot, scale);
		}

		/// <summary>
		/// ���[���h�s����v�Z
		/// </summary>
		/// <remark>
		/// Model�N���X�̐ݒ�Ɋ�Â������[���h�s��̌v�Z���s���܂��B
		/// �v�Z���ꂽ���[���h�s�񂪖߂�l�Ƃ��ĕԂ���܂��B
		/// �{�֐���UpdateWorldMatrix����Ă΂�Ă��܂��B
		/// �{�֐��̓��[���h�s����v�Z���āA�߂������ł��B
		/// Model::m_worldMatrix���X�V�����킯�ł͂Ȃ��̂ŁA���ӂ��Ă��������B
		/// �{�N���X�̐ݒ�Ɋ�Â��Čv�Z���ꂽ���[���h�s�񂪕K�v�ȏꍇ�Ɏg�p���Ă�������
		/// </remark>
		/// <param name="pos">���W</param>
		/// <param name="rot">��]</param>
		/// <param name="scale">�g�嗦</param>
		/// <returns>���[���h�s��</returns>
		Matrix CalcWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale);
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="renderContext">�����_�����O�R���e�L�X�g</param>
		/// <param name="numInstance">�C���X�^���X�̐�</param>
		void Draw(
			RenderContext& renderContext,
			int numInstance = 1
		);
		/// <summary>
		/// �`��(�J�����w���)
		/// </summary>
		/// <param name="renderContext">�����_�����O�R���e�L�X�g</param>
		/// <param name="camera">�J����</param>
		/// <param name="numInstance">�C���X�^���X�̐�</param>
		void Draw(
			RenderContext& renderContext,
			Camera& camera,
			int numInstance = 1
		);
		/// <summary>
		/// �`��(�J�����s��w���)
		/// </summary>
		/// <param name="renderContext">�����_�����O�R���e�L�X�g</param>
		/// <param name="viewMatrix">�r���[�s��</param>
		/// <param name="projMatrix">�v���W�F�N�V�����s��</param>
		/// <param name="numInstance">�C���X�^���X�̐�</param>
		void Draw(
			RenderContext& renderContext,
			const Matrix& viewMatrix,
			const Matrix& projMatrix,
			int numInstance = 1
		);
		/// <summary>
		/// ���[���h�s����擾�B
		/// </summary>
		/// <returns></returns>
		const Matrix& GetWorldMatrix() const
		{
			return m_worldMatrix;
		}
		/// <summary>
		/// ���b�V���ɑ΂��Ė₢���킹���s���B
		/// </summary>
		/// <param name="queryFunc">�₢���킹�֐�</param>
		void QueryMeshs(std::function<void(const SMesh& mesh)> queryFunc)
		{
			m_meshParts.QueryMeshs(queryFunc);
		}
		void QueryMeshAndDescriptorHeap(std::function<void(const SMesh& mesh, const DescriptorHeap& ds)> queryFunc)
		{
			m_meshParts.QueryMeshAndDescriptorHeap(queryFunc);
		}
		/// <summary>
		/// �A���x�h�}�b�v��ύX�B
		/// </summary>
		/// <remarks>
		/// ���̊֐����Ăяo���ƃf�B�X�N���v�^�q�[�v�̍č\�z���s���邽�߁A�������ׂ�������܂��B
		/// ���t���[���Ăяo���K�v���Ȃ��ꍇ�͌Ăяo���Ȃ��悤�ɂ��Ă��������B
		/// </remarks>
		/// <param name="materialName">�ύX�������}�e���A���̖��O</param>
		/// <param name="albedoMap">�A���x�h�}�b�v</param>
		void ChangeAlbedoMap(const char* materialName, Texture& albedoMap);
		/// <summary>
		/// TKM�t�@�C�����擾�B
		/// </summary>
		/// <returns></returns>
		const TkmFile& GetTkmFile() const
		{
			return *m_tkmFile;
		}
		/// <summary>
		/// ����������Ă��邩����B
		/// </summary>
		/// <returns></returns>
		bool IsInited() const
		{
			return m_isInited;
		}
		/// <summary>
		/// �}�e���A�����ď������B
		/// </summary>
		/// <remark>
		/// ���f���ɓ\��t����e�N�X�`����ύX�������ꍇ�Ȃǂɗ��p���Ă��������B
		/// </remark>
		/// <param name="reInitData">�ď������f�[�^�B</param>
		void ReInitMaterials(MaterialReInitData& reInitData);


		TkmFile* GetTkmFile()
		{
			return m_tkmFile;
		}

		bool m_isHit;


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
			double dot_12 = c1.Dot(c2);
			double dot_13 = c1.Dot(c3);

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

			int n = 0;
			Vector3 posi;
			float a = 0.0f;
			float b = 0.0f;
			Vector3 diff;
			Vector3 diff2;
			Vector2 Huv0, Huv1, Huv2;

			std::vector<nsK2EngineLow::TkmFile::VectorBuffer> polygon;

			for (int i = 0;i < vectorBuffer.size();i++)
			{

				Matrix matrix;

				//���[���h�s����擾
				matrix = GetWorldMatrix();

				TkmFile::VectorBuffer vertexBuffer = vectorBuffer[i];
				matrix.Apply(vertexBuffer.buffer[0]);
				matrix.Apply(vertexBuffer.buffer[1]);
				matrix.Apply(vertexBuffer.buffer[2]);

				matrix.Inverse();
				matrix.Transpose();

				matrix.Apply(vertexBuffer.normal);
				

				//���ʏ�̓_P
				//�_P�P�����_�P�iVector3�j
				Vector3 P = Vector3(vertexBuffer.buffer[0]);

				//PA PB�x�N�g��
				Vector3 PA = Vector3(P.x - A.x, P.y - A.y, P.z - A.z);
				Vector3 PB = Vector3(P.x - B.x, P.y - B.y, P.z - B.z);

				//PA PB���ꂼ��𕽖ʖ@���Ɠ���
				double dot_PA = PA.Dot(vertexBuffer.normal);
				double dot_PB = PB.Dot(vertexBuffer.normal);


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
				vertexBuffer.Rushpoint.x = A.x + (AB.x * hiritu);
				vertexBuffer.Rushpoint.y = A.y + (AB.y * hiritu);
				vertexBuffer.Rushpoint.z = A.z + (AB.z * hiritu);

				if (hittest_polygon_3d(vertexBuffer.buffer[0], vertexBuffer.buffer[1], vertexBuffer.buffer[2], vertexBuffer.Rushpoint) == false)
				{
					continue;
				}

				polygon.push_back(vertexBuffer);

				HitFlag();

			}

			if (polygon.size() == 0) {
				return false;
			}

			nsK2EngineLow::TkmFile::VectorBuffer rushPoint;
			for (int v = 0; v < polygon.size();v++) {


				if (v == 0)
				{
					rushPoint = polygon[v];
					posi = polygon[v].Rushpoint;
					diff = A - posi;
					a = diff.Length();
				}
				else {
					diff2 = A - polygon[v].Rushpoint;
					b = diff2.Length();
					if (a > b) {
						posi = polygon[v].Rushpoint;
						rushPoint = polygon[v];
					}
				}
			}


			auto v0v1 = rushPoint.buffer[1] - rushPoint.buffer[0];
			auto v0h = rushPoint.Rushpoint - rushPoint.buffer[0];
			Vector3 z;
			z.Cross(v0v1, v0h);
			float zarea = z.Length();
			zarea *= 0.5f;

			auto v1v2 = rushPoint.buffer[2] - rushPoint.buffer[1];
			auto v1h = rushPoint.Rushpoint - rushPoint.buffer[1];
			Vector3 x;
			x.Cross(v1v2, v1h);
			float xarea = x.Length();
			xarea *= 0.5f;

			auto v2v0 = rushPoint.buffer[0] - rushPoint.buffer[2];
			auto v2h = rushPoint.Rushpoint - rushPoint.buffer[2];
			Vector3 y;
			y.Cross(v2v0, v2h);
			float yarea = y.Length();
			yarea *= 0.5f;

			float xyz = xarea + yarea + zarea;
			float uvx, uvy, uvz;

			//�ʐς̔䗦�����߂�
			uvx = xarea / xyz;
			uvy = yarea / xyz;
			uvz = zarea / xyz;


			Huv0.x = rushPoint.uv[0].x * uvx;
			Huv0.y = rushPoint.uv[0].y * uvx;

			Huv1.x = rushPoint.uv[1].x * uvy;
			Huv1.y = rushPoint.uv[1].y * uvy;

			Huv2.x = rushPoint.uv[2].x * uvz;
			Huv2.y = rushPoint.uv[2].y * uvz;

			out = rushPoint.Rushpoint;
			//�Փ˓_��UV���W�����߂�B
			uv.x = Huv0.x + Huv1.x + Huv2.x;
			uv.y = Huv0.y + Huv1.y + Huv2.y;

			int ab = 0;

			return true;
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



//		/// <summary>
///// �V���h�E���V�[�o�[�̃t���O��ݒ�
///// </summary>
///// <param name="isFlag"></param>
//		void SetShadowReciever(bool isFlag)
//		{
//			m_meshParts.SetShadowReciever(isFlag);
//		}
//		/// <summary>
//		/// �V���h�E���V�[�o�[���ǂ������擾
//		/// </summary>
//		/// <returns></returns>
//		bool GetShadowReciever()
//		{
//			return m_meshParts.GetShadowReciever();
//		}
		/// <summary>
		/// �V���h�E�L���X�^�[�̃t���O��ݒ�
		/// </summary>
		/// <param name="isFlag"></param>
		void SetShadowCaster(bool isFlag)
		{
			m_isShadowCaster = isFlag;
		}
		/// <summary>
		/// �V���h�E�L���X�^�[���ǂ������擾
		/// </summary>
		/// <returns></returns>
		bool GetShadowCaster()
		{
			return m_isShadowCaster;
		}

	private:
		bool m_isInited = false;						//����������Ă���H
		Matrix m_worldMatrix;							//���[���h�s��B
		TkmFile* m_tkmFile;								//tkm�t�@�C���B
		Skeleton m_skeleton;							//�X�P���g���B
		MeshParts m_meshParts;							//���b�V���p�[�c�B
		EnModelUpAxis m_modelUpAxis = enModelUpAxisY;	//���f���̏�����B

		bool m_isShadowCaster = true;

	};
}
