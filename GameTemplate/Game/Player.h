#pragma once

class Game;
class GameSound;

// プレイヤークラス。
class Player : public IGameObject
{
public:
	enum EnPlayerState
	{
		enPlayerState_Idle,					//待機ステート
		enPlayerState_Shot,					//撃つステート
		enPlayerState_LeftShot,				//撃つアニメーション
		enPlayerState_RightShot,			//撃つアニメーション
		enPlayerState_ForwardShot,			//撃つアニメーション
		enPlayerState_BackShot,				//撃つアニメーション
		enPlayerState_Walk,					//歩くステート
		enPlayerState_Jump,					//切り替えしステート
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
		enAnimClip_LeftShot,		//撃つアニメーション
		enAnimClip_RightShot,		//撃つアニメーション
		enAnimClip_ForwardShot,		//撃つアニメーション
		enAnimClip_BackShot,		//撃つアニメーション
		enAnimClip_Walk,			//歩くアニメーション
		enAnimClip_Jump,			//切り替えしアニメーション
		enAnimClip_Num,				//アニメーションの数
	};

	Vector3 cameraforward;
private:
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// 回転処理
	/// </summary>
	void Rotation();
	/// <summary>
	/// アニメーションの再生
	/// </summary>
	void PlayAnimation();
	/// <summary>
	/// 各ステートの遷移処理
	/// </summary>
	void ManageState();
	/// <summary>
	/// アニメーション名前イベント
	/// </summary>
	/// <param name="clipName">アニメーションの名前</param>
	/// <param name="eventName">アニメーションキーの名前</param>
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	/// <summary>
	/// 共通のステートの遷移処理
	/// </summary>
	void ProcessCommonStateTransition();
	/// <summary>
	/// <summary>
	/// 待機ステート
	/// </summary>
	void ProcessIdleStateTransition();
	/// <summary>
	/// 走りステート
	/// </summary>
	void ProcessRunStateTransition();
	/// <summary>
	/// ジャンプステート
	/// </summary>
	void ProcessJumpStateTransition();
	/// <summary>
	/// 攻撃ステート
	/// </summary>
	void ProcessAttackStateTransition();



	// クラス IGameObject
	Game*					m_game = nullptr;							// ゲーム。
	GameSound*				m_gameSound;								// ゲームサウンド
	// クラス Engine
	ModelRender				m_modelRender;								// モデルレンダー
	ModelRender				m_testmodel;								// モデルレンダー
	CharacterController     m_charaCon;	                                // キャラコン
	EffectEmitter*			m_effect = nullptr;							// エフェクト
	// 関数
	Vector3					m_startVector;								// 開始線分
	Vector3					m_endVector;								// 終了線分
	Vector3                 m_forward = Vector3::AxisZ;                 // 前方向のベクトル
	Vector3					m_position;					                // 座標
	Vector3                 m_moveSpeed;                                // 移動速度
	Vector3					m_scale = g_vec3One;		                // 拡大率
	Quaternion				m_rotation;					                // 回転
	Quaternion				rotation;
	AnimationClip           m_animationClipArray[enAnimClip_Num];		// アニメーションクリップ
	EnPlayerState           m_playerState = enPlayerState_Idle;			// プレイヤーステート
	float					m_move = 80.0f;								// 移動速度（加速度）
	float					m_lStick_x = 0.0f;							// Lスティックの入力量
	float					m_lStick_y = 0.0f;							// Lスティックの入力量
	int                     m_gunId = -1;								//「Gun」ボーンのID。
};