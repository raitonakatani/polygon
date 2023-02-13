#include "stdafx.h"
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
	const float CHARACON_RADIUS = 18.0f;						// キャラコンの半径
	const float CHARACON_HEIGHT = 55.0f;						// キャラコンの高さ
	const float MOVE_SPEED_MINIMUMVALUE = 0.001f;				// 移動速度の最低値
	const float WALK_MOVESPEED = 300.0f;						// 歩きステートの移動速度
	const float GRAVITY = 100.0f;								// 重力
	const float START_MOVE = 0.0f;								// 初期設定のスピード
}

bool Player::Start()
{
	m_animationClipArray[enAnimClip_Idle].Load("Assets/aniData/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Shot].Load("Assets/aniData/attack.tka");
	m_animationClipArray[enAnimClip_Shot].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_LeftShot].Load("Assets/aniData/leftattack.tka");
	m_animationClipArray[enAnimClip_LeftShot].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_RightShot].Load("Assets/aniData/rightattack.tka");
	m_animationClipArray[enAnimClip_RightShot].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_ForwardShot].Load("Assets/aniData/forwardattack.tka");
	m_animationClipArray[enAnimClip_ForwardShot].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_BackShot].Load("Assets/aniData/backattack.tka");
	m_animationClipArray[enAnimClip_BackShot].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Walk].Load("Assets/aniData/walk.tka");
	m_animationClipArray[enAnimClip_Walk].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Jump].Load("Assets/aniData/walk.tka");
	m_animationClipArray[enAnimClip_Jump].SetLoopFlag(true);

	// モデルの読み込み
	m_modelRender.Init("Assets/player/player2.tkm", false,false,m_animationClipArray,enAnimClip_Num);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();

	// アニメーションイベント用の関数を設定する
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	// キャラコン
	Vector3 posi = m_position;
	posi.y += 5.0f;
	m_charaCon.Init(CHARACON_RADIUS, CHARACON_HEIGHT, m_position);

	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/efk/shot.efk");
	
	m_gunId = m_modelRender.FindBoneID(L"eff_muzzle");

	// ゲームのクラスを探してもってくる。
	m_game = FindGO<Game>("game");
	m_gameSound = FindGO<GameSound>("gamesound");

	return true;
}

void Player::Update()
{
	if (m_game->phase >= 5)
	{
		return;
	}
	if (m_game->m_paintnumber >= 40) {
		m_playerState = enPlayerState_Idle;
		return;
	}
	if (g_pad[0]->IsPress(enButtonRB1)) {
		m_startVector = m_position;
		m_startVector.y += 70.0f;
		m_endVector = m_startVector;
		m_forward = g_camera3D->GetForward();
		m_endVector += m_forward * 250.0f;
		if (m_endVector.y <= -200.0f) { m_endVector.y = -200.0f; }
		m_collision = NewGO<CollisionObject>(0, "collision");
		// コリジョンオブジェクトを作成する。
		Vector3 collisionPosition = m_position;
		collisionPosition += m_forward * 200.0f;
		collisionPosition.y += 50.0f;
		Quaternion rot;
		rot = m_rotation;
		Vector3 m_right = Vector3::AxisX;
		rot.Apply(m_right);
		collisionPosition += m_right * -7.5f;
		// ボックス状のコリジョンを作成する。
		m_collision->CreateBox(collisionPosition,		 // 座標。
			m_rotation,                                      // 回転。
			Vector3(40.0f, 20.0f, 250.0f)                    // 大きさ。
		);
		m_collision->SetName("player");
	}
	else
	{
		m_endVector = m_startVector = Vector3::Zero;
	}

	Search();
	// 回転処理
	Rotation();
	// 移動処理
	Move();
	// アニメーションの再生
	PlayAnimation();
	// 各ステートの遷移処理
	ManageState();
	// 当たり判定処理
	Collision();

	// 座標、回転、大きさの更新
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(MODEL_SCALE);


	// モデルの更新
	m_modelRender.Update();

}

void Player::Search()
{
}

void Player::Move()
{
	// 移動速度
	m_moveSpeed.x = START_MOVE;
	m_moveSpeed.z = START_MOVE;
	// ステックの入力量を取得
	lStick_x = g_pad[0]->GetLStickXF();
	lStick_y = g_pad[0]->GetLStickYF();
	// cameraの前方向と右方向を取得
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	// XZ平面での前方方向、右方向に変換する
	cameraForward.y = START_MOVE;
	cameraForward.Normalize();
	cameraRight.y = START_MOVE;
	cameraRight.Normalize();

	m_moveSpeed += cameraForward * lStick_y * m_move;
	m_moveSpeed += cameraRight * lStick_x * m_move;

	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f) {
		if (m_move <= 300.0f) {
			m_move *= 1.1f;
		}
			m_lStick_y = lStick_y;
			m_lStick_x = lStick_x;

	}
	else {
		if (m_move >= 100.0f) {
			m_move /= 1.08f;
			m_moveSpeed += cameraForward * m_lStick_y * m_move;
			m_moveSpeed += cameraRight * m_lStick_x * m_move;
		}
	}


	/*if (g_pad[0]->IsTrigger(enButtonB)) {
		m_moveSpeed.y += 500.0f;
	}*/


	// 重力
	m_moveSpeed.y -= GRAVITY;


	// キャラコンを使用して、座標を更新する
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	if (m_position.y <= -55.0f || m_hp <= 0) {
		m_position = { 0.0f,200.0f,-500.0f };
		m_hp = 50;
		Vector3 posi = m_position;
		posi.y += 5.0f;
		m_charaCon.SetPosition(posi);
	}

	// 座標の更新
	Vector3 modelPosition = m_position;
	m_modelRender.SetPosition(modelPosition);
}

void Player::Rotation()
{
	if (g_pad[0]->IsPress(enButtonRB1) == true)
	{
		m_moveSpeed = g_camera3D->GetForward();
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

void Player::Collision()
{
	// エネミー（タンク）の攻撃用のコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("enemy");
	// コリジョンの配列をfor文で回す。
	for (auto collision : collisions)
	{
		// コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_charaCon) == true)
		{
			m_damage = true;
			m_hp -= 1;
			return;
		}
		else {
			m_damage = false;
		}
	}
}

void Player::Render(RenderContext& rc)
{
	if (m_game->phase >= 5)
	{
		return;
	}
	if (m_damage == true) {
		m_damageTimer += g_gameTime->GetFrameDeltaTime();
		if (m_damageTimer >= 0.1f) {
			m_damageTimer = 0.0f;
			// モデルをドロー。
			m_modelRender.Draw(rc);
		}
	}
	else {
		// モデルをドロー。
		m_modelRender.Draw(rc);
	}
}

void Player::ProcessCommonStateTransition()
{
	if (g_pad[0]->IsPress(enButtonRB1)) {

		Quaternion rot;
		rot = m_rotation;
		Matrix matrix = m_modelRender.GetBone(m_gunId)->GetWorldMatrix();
		m_effect = NewGO <EffectEmitter>(0);
		Vector3 effectposi = m_position;
		effectposi.y += 35.0f;
		m_forward=g_camera3D->GetForward();
		effectposi += m_forward * 50.0f;

		Vector3 m_right = Vector3::AxisX;
		rot.Apply(m_right);
		effectposi += m_right * -7.5f;

		Vector3 effectDir = m_endVector - m_startVector;
		effectDir.Normalize();
		Quaternion effectRot;
		effectRot.SetRotation(Vector3::AxisZ, effectDir);
		m_effect->Init(0);
		m_effect->SetPosition(effectposi);
		m_effect->SetRotation(effectRot);
		// エフェクトの大きさを設定する。
		m_effect->SetScale(m_scale * 12.0f);
		m_effect->Play();
		//	m_effect->SetWorldMatrix(matrix);

		if (lStick_x <= -0.1f) {
			m_playerState = enPlayerState_LeftShot;
			return;
		}
		else if (lStick_x >= 0.1f)
		{
			m_playerState = enPlayerState_RightShot;
			return;
		}
		else if (lStick_y >= 0.1f)
		{
			m_playerState = enPlayerState_ForwardShot;
			return;
		}
		else if (lStick_y <= -0.1f)
		{
			m_playerState = enPlayerState_BackShot;
			return;
		}
		//攻撃ステートに遷移
		m_playerState = enPlayerState_Shot;
		return;
	}

	//if (g_pad[0]->IsTrigger(enButtonB)) {
	//	//ジャンプステートに遷移
	//	m_playerState = enPlayerState_Jump;
	//	return;
	//}


	// xかzの移動速度があったら
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
			//走りステートに遷移
			m_playerState = enPlayerState_Walk;
			return;
	}
	else {

		if (m_charaCon.IsOnGround() == true) {
			//待機ステートに遷移
			m_playerState = enPlayerState_Idle;
			return;
		}
	}

}

void Player::ProcessIdleStateTransition()
{
	ProcessCommonStateTransition();
	
}

void Player::ProcessRunStateTransition()
{
		ProcessCommonStateTransition();
}

void Player::ProcessJumpStateTransition()
{
		ProcessCommonStateTransition();
}

void Player::ProcessAttackStateTransition()
{
		ProcessCommonStateTransition();
}

void Player::PlayAnimation()
{
	switch (m_playerState)
	{
		// 待機ステートの時
	case Player::enPlayerState_Idle:
		m_modelRender.PlayAnimation(enAnimClip_Idle, 0.1f);
		m_modelRender.SetAnimationSpeed(0.8f);
		break;
		// ジャンプステートの時
	case Player::enPlayerState_Jump:
		m_modelRender.PlayAnimation(enAnimClip_Jump, 0.1f);
		m_modelRender.SetAnimationSpeed(1.2f);
		break;
		// 走りステートの時
	case Player::enPlayerState_Walk:
		m_modelRender.PlayAnimation(enAnimClip_Walk, 0.1f);
		m_modelRender.SetAnimationSpeed(1.2f);
		break;
		// 攻撃ステートの時
	case Player::enPlayerState_Shot:
		m_modelRender.PlayAnimation(enAnimClip_Shot, 0.1f);
		m_modelRender.SetAnimationSpeed();
		break;
		// 攻撃ステートの時左
	case Player::enPlayerState_LeftShot:
		m_modelRender.PlayAnimation(enAnimClip_LeftShot, 0.1f);
		m_modelRender.SetAnimationSpeed();
		break;
		// 攻撃ステートの時
	case Player::enPlayerState_RightShot:
		m_modelRender.PlayAnimation(enAnimClip_RightShot, 0.1f);
		m_modelRender.SetAnimationSpeed();
		break;
		// 攻撃ステートの時左
	case Player::enPlayerState_ForwardShot:
		m_modelRender.PlayAnimation(enAnimClip_ForwardShot, 0.1f);
		m_modelRender.SetAnimationSpeed();
		break;
		// 攻撃ステートの時
	case Player::enPlayerState_BackShot:
		m_modelRender.PlayAnimation(enAnimClip_ForwardShot, 0.1f);
		m_modelRender.SetAnimationSpeed();
		break;
	default:
		break;
	}
}

void Player::ManageState()
{
	switch (m_playerState)
	{
		// 待機ステートの時
	case Player::enPlayerState_Idle:
		ProcessIdleStateTransition();
		break;
		// ジャンプステートの時
	case Player::enPlayerState_Jump:
		ProcessJumpStateTransition();
		break;
		// 走りステートの時
	case Player::enPlayerState_Walk:
		ProcessRunStateTransition();
		break;
		// 攻撃ステートの時
	case Player::enPlayerState_Shot:
		ProcessAttackStateTransition();
		break;
		// 攻撃ステートの時
	case Player::enPlayerState_LeftShot:
		ProcessAttackStateTransition();
		break;
		// 攻撃ステートの時
	case Player::enPlayerState_RightShot:
		ProcessAttackStateTransition();
		break;	
	case Player::enPlayerState_ForwardShot:
		ProcessAttackStateTransition();
		break;
		// 攻撃ステートの時
	case Player::enPlayerState_BackShot:
		ProcessAttackStateTransition();
		break;
	default:
		break;
	}
}


void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName, L"Run_step") == 0 && m_charaCon.IsOnGround() == true) {
		// 足音。
		// 効果音を再生する。
		m_gameSound->PlayerStepSE(0.4f);
	}

	if (wcscmp(eventName, L"attack") == 0) {
		// 足音。
		// 効果音を再生する。
		m_gameSound->PlayerAttackSE(0.3f);
	}
}