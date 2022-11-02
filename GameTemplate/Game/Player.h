#pragma once

class Game;

// プレイヤークラス。
class Player : public IGameObject
{
public:
	enum EnPlayerState
	{
		enPlayerState_Idle,					//待機ステート
		enPlayerState_Shot,					//撃つステート
		enPlayerState_Win					//クリアステート
	};
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// 座標を設定する。
	/// </summary>
	/// <param name="position">座標。</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// 座標を取得する。
	/// </summary>
	/// <returns>座標。</returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}


	/// <summary>
	/// 始点の座標を取得する。
	/// </summary>
	/// <returns>座標。</returns>
	const Vector3& GetStartVector() const
	{
		return m_startVector;
	}


	/// <summary>
	/// 終点の座標を取得する。
	/// </summary>
	/// <returns>座標。</returns>
	const Vector3& GetEndVector() const
	{
		return m_endVector;
	}


	// アニメーションクリップの番号を表す列挙型。
	enum EnAnimationClip {
		enAnimClip_Idle,			//待機アニメーション
		enAnimClip_Shot,			//撃つアニメーション
		enAnimClip_Num,				//アニメーションの数
	};


private:
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// 回転処理
	/// </summary>
	void Rotation();

	// クラス IGameObject
	Game* m_game = nullptr;							// ゲーム。
	// クラス Engine
	ModelRender				m_modelRender;                              // モデルレンダー

	ModelRender				m_testmodel;                              // モデルレンダー

	CharacterController     m_charaCon;	                                // キャラコン
	// 関数
	Vector3 m_startVector;
	Vector3 m_endVector;


	Vector3                 m_forward = Vector3::AxisZ;                 // 前方向のベクトル
	Vector3					m_position;					                // 座標
	Vector3                 m_moveSpeed;                                // 移動速度
	Vector3					m_scale = g_vec3One;		                // 拡大率
	Quaternion				m_rotation;					                // 回転

	Quaternion rotation;

	AnimationClip           m_animationClipArray[enAnimClip_Num];	    // アニメーションクリップ

};