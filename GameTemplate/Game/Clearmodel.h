#pragma once

class Game;
class Player;

class Clearmodel : public IGameObject
{
public:
	enum EnEnemyState
	{
		enEnemyState_Victory,					//待機ステート
	};
public:

	Clearmodel() {}
	~Clearmodel();


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
	/// 回転を設定。
	/// </summary>
	/// <param name="rotation">回転。</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// 大きさを設定。
	/// </summary>
	/// <param name="scale">大きさ。</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	// アニメーションクリップの番号を表す列挙型。
	enum EnAnimationClip {
		enAnimClip_Victory,				//アニメーションの数
		enAnimClip_Num				//アニメーションの数
	};
	float m_timer = 0.0f;


private:

	// クラス IGameObject
	Game* m_game;
	Player* m_player;									// プレイヤー
	// クラス Engine
	ModelRender				m_modelRender;								// モデルレンダー
	CharacterController     m_charaCon;	                                // キャラコン
	Vector3                 m_forward = Vector3::AxisZ;                 // 前方向のベクトル
	Vector3                 m_moveSpeed;                                // 移動速度
	Vector3					m_scale = g_vec3One;		                // 拡大率
	Vector3					m_position;
	Quaternion				m_rotation;					                // 回転
	AnimationClip           m_animationClipArray[enAnimClip_Num];		// アニメーションクリップ
	EnEnemyState			m_enemyState = enEnemyState_Victory;			// プレイヤーステート

};

