#pragma once
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;
class GameSound;


class Enemy : public IGameObject
{

public:
	enum EnEnemyState
	{
		enEnemyState_Idle,					//待機ステート
		enEnemyState_Shot,					//撃つステート
		enEnemyState_Walk,					//歩くステート
	};
public:

	Enemy() {}
	~Enemy() {}


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
		enAnimClip_Walk,			//歩くアニメーション
		enAnimClip_Num,				//アニメーションの数
	};

	/*bool IsAttack()
	{
		return m_isAttack;
	}*/
	bool m_isAttack = false;
	float yup = 0.0f;

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
	/// 攻撃処理
	/// </summary>
	void Attack();
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
	/// 攻撃ステート
	/// </summary>
	void ProcessAttackStateTransition();



	// クラス IGameObject
	Player*					m_player;									// プレイヤー
	GameSound*				m_gameSound;								// ゲームサウンド
	// クラス Engine
	ModelRender				m_modelRender;								// モデルレンダー
	CharacterController     m_charaCon;	                                // キャラコン
	EffectEmitter*			m_effect = nullptr;							// エフェクト
	// 関数
	Vector3					m_startVector;								// 開始線分
	Vector3					m_endVector;								// 終了線分
	Vector3                 m_forward = Vector3::AxisZ;                 // 前方向のベクトル
	Vector3                 m_moveSpeed;                                // 移動速度
	Vector3					m_scale = g_vec3One;		                // 拡大率
	Quaternion				m_rotation;					                // 回転
	Quaternion				rotation;
	AnimationClip           m_animationClipArray[enAnimClip_Num];		// アニメーションクリップ
	EnEnemyState			m_enemyState = enEnemyState_Idle;			// プレイヤーステート
	float					m_move = 80.0f;								// 移動速度（加速度）
	float					m_lStick_x = 0.0f;							// Lスティックの入力量
	float					m_lStick_y = 0.0f;							// Lスティックの入力量
	int                     m_gunId = -1;								//「Gun」ボーンのID。

	TknFile					m_tknFile;
	PhysicsStaticObject		m_bgObject;
	nsAI::NaviMesh			m_nvmMesh;
	nsAI::Path				m_path;
	nsAI::PathFinding		m_pathFiding;
	Vector3					m_position = {500.0f,250.0f,500.0f};
	Vector3					m_targetPointPosition;

	Vector3 m_diff;
	float timer = 0.0f;
//	bool m_isAttack = false;
};

