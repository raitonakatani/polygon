#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "GameSound.h"

// EffectEmitterを使用するために、ファイルをインクルードする。
#include "graphics/effect/EffectEmitter.h"

namespace
{
	// Vector3
	const Vector3 MODEL_SCALE = { 1.0f, 1.0f, 1.0f };						//モデルの大きさ
	const Vector3 COLLISION_SCALE = { 20.0f, 20.0f, 120.0f };				//コリジョンの大きさ
	const Vector3 COLLISION_PORK_SCALE = { 40.0f, 30.0f, 140.0f };			//コリジョン（ポーク）の大きさ
	// float													
	const float CHARACON_RADIUS = 20.0f;						// キャラコンの半径
	const float CHARACON_HEIGHT = 55.0f;						// キャラコンの高さ
	const float MOVE_SPEED_MINIMUMVALUE = 0.001f;				// 移動速度の最低値
	const float WALK_MOVESPEED = 300.0f;						// 歩きステートの移動速度
	const float GRAVITY = 1000.0f;								// 重力
	const float START_MOVE = 0.0f;								// 初期設定のスピード
}

bool Enemy::Start()
{
	// アニメーションを読み込む
	m_animationClipArray[enAnimClip_Idle].Load("Assets/aniData/enemy/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Shot].Load("Assets/aniData/enemy/shot.tka");
	m_animationClipArray[enAnimClip_Shot].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Walk].Load("Assets/aniData/enemy/run.tka");
	m_animationClipArray[enAnimClip_Walk].SetLoopFlag(true);

	scale *= 8.0f;

	// モデルを読み込む
	m_modelRender.Init("Assets/enemy/enemy.tkm", false,false ,m_animationClipArray, enAnimClip_Num);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(scale);
	m_modelRender.Update();

	// アニメーションイベント用の関数を設定する
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	// ナビメッシュを構築。
	m_nvmMesh.Init("Assets/tkn/stage2.tkn");

	// エフェクト
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/efk/shot.efk");

	// 「銃」のボーンID
	m_gunId = m_modelRender.FindBoneID(L"eff_muzzle");

	// ゲームのクラスを探してもってくる。
	m_gameSound = FindGO<GameSound>("gamesound");

	return true;
}

void Enemy::Update()
{
	// プレイヤーのクラスを探して持ってくる
	m_player = FindGO<Player>("player");
	m_targetPointPosition = { -0.0f,250.0f,0.0f };
	m_diff = m_targetPointPosition - m_position;

	// 回転処理
	Rotation();
	// 移動処理
	Move();
	// 攻撃処理
	Attack();
	// アニメーションの再生
	PlayAnimation();
	// 各ステートの遷移処理
	ManageState();

	// 座標、回転、大きさの更新
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(scale);
	// モデルの更新
	m_modelRender.Update();
}

void Enemy::Move()
{
	timer += g_gameTime->GetFrameDeltaTime();
	bool isEnd;
	Vector3 diff;
	// パス検索
	if (m_isAttack == false && timer >= 0.5f) {
		timer = 0.0f;
		m_oldPosition = m_position;
		m_pathFiding.Execute(
			m_path,							// 構築されたパスの格納先
			m_nvmMesh,						// ナビメッシュ
			m_position,						// 開始座標
			m_targetPointPosition,			// 移動目標座標
			PhysicsWorld::GetInstance(),	// 物理エンジン	
			25.0f,							// AIエージェントの半径
			55.0f							// AIエージェントの高さ。
		);
	}
	if (m_diff.Length() >= 300.0f && timer < 0.5f) {
		// パス上を移動する。
		m_position = m_path.Move(
			m_position,
			6.0f,
			isEnd
		);
		m_position* m_forward;
		diff = m_position - m_oldPosition;
		diff.Normalize();
		m_moveSpeed = diff;
	}

	// 重力
	m_moveSpeed.y -= GRAVITY * g_gameTime->GetFrameDeltaTime();
	
	// 座標の更新
	Vector3 modelPosition = m_position;
	m_modelRender.SetPosition(modelPosition);
}

void Enemy::Rotation()
{
	if (m_isAttack == true)
	{
		//timer = 0.0f;
		auto diff = m_diff;
		diff.Normalize();
		m_moveSpeed = diff;
	}

	if (fabsf(m_moveSpeed.x) < MOVE_SPEED_MINIMUMVALUE
		&& fabsf(m_moveSpeed.z) < MOVE_SPEED_MINIMUMVALUE) {
		return;
	}

	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotationY(-angle);


	// 回転を設定する
	m_modelRender.SetRotation(m_rotation);
	// プレイヤーの正面ベクトルを計算する
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Enemy::Attack()
{
	yup += 0.5f;
	if (m_diff.Length() <= 300.0f) {
		m_isAttack = true;
		m_startVector = m_position;
		m_startVector.y += 50.0f;
		m_endVector = m_startVector;
		m_forward.Normalize();
		m_endVector += m_forward * 300.0f;
		//m_endVector.y += yup;
	}
	else	if (m_diff.Length() >= 350.0f) 
	{
		m_isAttack = false;
		m_endVector = m_startVector = Vector3::Zero;
	}
}

void Enemy::ProcessCommonStateTransition()
{
	if (timer >= 4.0f)
	{
		timer = 0.0f;
	}
	if (m_isAttack == true && timer <= 1.0f) {
		Matrix matrix = m_modelRender.GetBone(m_gunId)->GetWorldMatrix();
		m_effect = NewGO <EffectEmitter>(0);
		Vector3 effectposi = m_position;
		effectposi.y += 35.0f;
		effectposi += m_forward * 50.0f;

		Vector3 m_right = Vector3::AxisX;
		m_rotation.Apply(m_right);
		effectposi += m_right * -7.5f;

		m_effect->Init(0);
		m_effect->SetPosition(effectposi);
		m_effect->SetRotation(m_rotation);
		// エフェクトの大きさを設定する。
		m_effect->SetScale(m_scale * 10.0f);
		//m_effect->SetWorldMatrix(matrix);
		m_effect->Play();
		//攻撃ステートに遷移
		m_enemyState = enEnemyState_Shot;
		return;
	}
	else if (m_isAttack == true && timer > 1.0f) {
		m_enemyState = enEnemyState_Idle;
		return;
	}

	// xかzの移動速度があったら
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//走りステートに遷移
		m_enemyState = enEnemyState_Walk;
		return;
	}
	else {
		//待機ステートに遷移
		m_enemyState = enEnemyState_Idle;
		return;
	}
}

void Enemy::ProcessIdleStateTransition()
{
	ProcessCommonStateTransition();

}

void Enemy::ProcessRunStateTransition()
{
	ProcessCommonStateTransition();
}

void Enemy::ProcessAttackStateTransition()
{
	ProcessCommonStateTransition();
}

void Enemy::PlayAnimation()
{
	switch (m_enemyState)
	{
		// 待機ステートの時
	case Enemy::enEnemyState_Idle:
		m_modelRender.PlayAnimation(enAnimClip_Idle, 0.1f);
		m_modelRender.SetAnimationSpeed(0.8f);
		break;
		// 走りステートの時
	case Enemy::enEnemyState_Walk:
		m_modelRender.PlayAnimation(enAnimClip_Walk, 0.1f);
		m_modelRender.SetAnimationSpeed(1.2f);
		break;
		// 攻撃ステートの時
	case Enemy::enEnemyState_Shot:
		m_modelRender.PlayAnimation(enAnimClip_Shot, 0.1f);
		m_modelRender.SetAnimationSpeed();
		break;
	default:
		break;
	}
}

void Enemy::ManageState()
{
	switch (m_enemyState)
	{
		// 待機ステートの時
	case Enemy::enEnemyState_Idle:
		ProcessIdleStateTransition();
		break;
		// 走りステートの時
	case Enemy::enEnemyState_Walk:
		ProcessRunStateTransition();
		break;
		// 攻撃ステートの時
	case Enemy::enEnemyState_Shot:
		ProcessAttackStateTransition();
		break;
	default:
		break;
	}
}


void Enemy::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//(void)clipName;
	//if (wcscmp(eventName, L"Run_step") == 0) {
	//	// 足音。
	//	// 効果音を再生する。
	//	m_gameSound->PlayerStepSE(0.4f);
	//}

	//if (wcscmp(eventName, L"attack") == 0) {
	//	// 足音。
	//	// 効果音を再生する。
	//	m_gameSound->PlayerAttackSE(0.3f);
	//}
}

void Enemy::Render(RenderContext& rc)
{
	// モデルをドロー。
	m_modelRender.Draw(rc);
}