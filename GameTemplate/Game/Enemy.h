#pragma once
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"
#include "EnemyPath.h"

class Game;
class Player;
class GameSound;
class EnemyPath;
class Cylinder;

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
	~Enemy();


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
	int phase = 0;
	int m_hp = 50;
	int m_phaseNumber = 0;
	float m_timer = 0.0f;

	//void SetNumber(const int& number)
	//{
	//	m_number = number;
	//}
	bool gameover = false;

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
	/// プレイヤーを探索する
	/// </summary>
	void SearchPlayer();
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
	/// <summary>
	/// 当たり判定処理
	/// </summary>
	void Collision();


	// クラス IGameObject
	Game* m_game;
	Player*					m_player;									// プレイヤー
	GameSound*				m_gameSound;								// ゲームサウンド
	Cylinder*				m_cylinder;
	// クラス Engine
	ModelRender				m_modelRender;								// モデルレンダー
	CharacterController     m_charaCon;	                                // キャラコン
	SphereCollider			m_sphereCollider;							//スフィアコライダー
	EffectEmitter*			m_effect = nullptr;							// エフェクト
	CollisionObject*		m_collision;
	// パス
	EnemyPath				m_enemypath;								//パス
	// 関数
	Vector3					m_startVector;								// 開始線分
	Vector3					m_endVector;								// 終了線分
	Vector3                 m_forward = Vector3::AxisZ;                 // 前方向のベクトル
	Vector3                 m_moveSpeed;                                // 移動速度
	Vector3					m_scale = g_vec3One;		                // 拡大率
	Vector3					scale= g_vec3One;
	Vector3					paintposi = Vector3{ 0.0f,200.0f,0.0f };
	Quaternion				m_rotation;					                // 回転
	AnimationClip           m_animationClipArray[enAnimClip_Num];		// アニメーションクリップ
	EnEnemyState			m_enemyState = enEnemyState_Idle;			// プレイヤーステート
	float					m_move = 80.0f;								// 移動速度（加速度）
	float					m_lStick_x = 0.0f;							// Lスティックの入力量
	float					m_lStick_y = 0.0f;							// Lスティックの入力量
	int                     m_gunId = -1;								//「Gun」ボーンのID。
	nsAI::NaviMesh			m_nvmMesh;									// ナビメッシュ
	nsAI::Path				m_path;										// パス
	nsAI::PathFinding		m_pathFiding;								// パス検索
	Vector3					m_position;									// 座標
	Vector3					m_targetPointPosition = Vector3{ 0.0f,150.0f,200.0f };		// 目標地点の座標

	Vector3					m_diff;										// エネミーの座標から目標地点に向かうベクトル
	float					timer = 0.0f;								// タイマー
	Vector3					m_oldPosition;								// パス更新前の座標
	bool					m_isSearchPlayer = false;					//見るけているか？
	bool					m_death = false;
	float aaa;
	Vector3 m_targetposi = Vector3(0.0f, 150.0f, 200.0f);
	//int m_number = 0;
	float yposi = 0.0f;
	RenderingEngine* m_renderingEngine = &g_renderingEngine;

	int a = 0;
	int b = 0;

	float			ramtime = 0.0f;
	float			m_nowy;
	int				m_paintnaumber = 0;
	int				m_searchNumber = 0;
	bool			m_damage = false;
	float			m_damageTimer = 0.0f;
};

