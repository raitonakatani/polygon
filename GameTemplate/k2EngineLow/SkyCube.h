#pragma once

namespace nsK2EngineLow {
	enum EnSkyCubeType {
		enSkyCubeType_Day,		// 昼間
		enSkyCubeType_Num,
	};
	/// <summary>
	/// ?
	/// </summary>
	class SkyCube : public IGameObject{
	public:
		SkyCube();
		~SkyCube();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	public:
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
			m_isDirty = true;
		}

		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
			m_isDirty = true;
		}
		void SetScale(const float scale)
		{
			m_scale = g_vec3One;
			m_scale.Scale(scale);
			m_isDirty = true;
		}
		/// <summary>
		/// スカイキューブのタイプを設定。
		/// </summary>
		/// <param name="type"></param>
		void SetType(EnSkyCubeType type)
		{
			m_type = type;
		}
		/// <summary>
		/// 明るさを設定。
		/// </summary>
		/// <param name="lum"></param>
		void SetLuminance(float lum)
		{
			m_luminance = lum;
		}
		const wchar_t* GetTextureFilePath()
		{
			return m_textureFilePaths[m_type];
		}

		Texture& GetSkyCubeTexture()
		{
			return m_texture[m_type];
		}
	//private:
		Model m_modelRender;

		Texture m_texture[enSkyCubeType_Num];
		const wchar_t* m_textureFilePaths[enSkyCubeType_Num];
		Vector3 m_position = g_vec3Zero;
		Vector3 m_scale = g_vec3One * 2000.0f;
		float m_luminance = 1.0f;
		bool m_isDirty = false;
		EnSkyCubeType m_type = enSkyCubeType_Day;
	};
}

