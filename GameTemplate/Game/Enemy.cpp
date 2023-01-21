#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "GameSound.h"
#include "Cylinder.h"

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

Enemy::~Enemy()
{
	//DeleteGO(this);
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

	// アニメーションを読み込む
//	m_animationClipArray[enAnimClip_Idle].Load("Assets/aniData/idle.tka");
//	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
//	m_animationClipArray[enAnimClip_Shot].Load("Assets/aniData/attack.tka");
//	m_animationClipArray[enAnimClip_Shot].SetLoopFlag(true);
//	m_animationClipArray[enAnimClip_Walk].Load("Assets/aniData/walk.tka");
//	m_animationClipArray[enAnimClip_Walk].SetLoopFlag(true);

	scale *= 6.0f;

	// モデルを読み込む
	m_modelRender.Init("Assets/enemy/enemy.tkm", false, false, m_animationClipArray, enAnimClip_Num);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(scale);
	m_modelRender.Update();

	// アニメーションイベント用の関数を設定する
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	// ナビメッシュを構築。
	m_nvmMesh.Init("Assets/tkn/teststage.tkn");

	// エフェクト
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/efk/shot.efk");

	// 「銃」のボーンID
	m_gunId = m_modelRender.FindBoneID(L"eff_muzzle");

	// ゲームのクラスを探してもってくる。
	m_gameSound = FindGO<GameSound>("gamesound");

	m_charaCon.Init(20.0f, 55.0f, m_position);

	//スフィアコライダーを初期化。
	m_sphereCollider.Create(1.0f);

	m_enemypath.Init("Assets/path/path.tkl");

	return true;
}

void Enemy::Update()
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	if (m_timer <= 12.0f) {
		return;
	}
	if (m_hp <= 0) {
		m_player->m_enemynumber += 1;
		DeleteGO(this);
	}
	// プレイヤーのクラスを探して持ってくる
	m_player = FindGO<Player>("player");
	if (m_isSearchPlayer == false) {
		m_targetPointPosition = m_targetposi;
		if (m_timer >= 15.0f) {

			//塗る場所（立つ場所）をランダムに設定
	/*		Quaternion rot;
			float ram = rand() % 360;
			rot.SetRotationY(ram);
			rot.Apply(m_forward);
			m_targetposi = m_forward * 400.0f;
			if (m_targetposi.x <= 300.0f && m_targetposi.x >= -300.0f) {
				m_targetposi.x = 300.0f;
			}
			if (m_targetposi.z <= 300.0f && m_targetposi.z >= -300.0f) {
				m_targetposi.z = 300.0f;
			}
			m_targetposi.y = 150.0f;*/
			int ram = rand() % 8;
			int ram2 = rand() % 4;
			m_targetposi = m_enemypath.m_pointlist[ram].s_position;
			paintposi = m_enemypath.m_pointlist[ram].s_paintposi[ram2];
			m_timer = 13.0f;
		}
	}
	else {
		m_timer = 13.0f;
		m_targetPointPosition = m_player->GetPosition();
	}
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
	// サーチ
	SearchPlayer();
	// 当たり判定
	Collision();

	// 座標、回転、大きさの更新
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(scale);
	// モデルの更新
	m_modelRender.Update();

	m_cylinder = FindGO<Cylinder>("cylinder");
}

void Enemy::Move()
{
	timer += g_gameTime->GetFrameDeltaTime();
	bool isEnd;
	Vector3 diff;
	// パス検索
	if (m_isAttack == false && timer >= 0.3f) {
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
	if (m_diff.Length() >= 100.0f && timer < 0.3f) {
		// パス上を移動する。
		m_position = m_path.Move(
			m_position,
			4.0f,
			isEnd
		);
		m_position* m_forward;
		diff = m_position - m_oldPosition;
		diff.Normalize();
		m_moveSpeed = diff;
		m_timer = 13.0f;
	}

	// 重力
	m_moveSpeed.y -= GRAVITY * g_gameTime->GetFrameDeltaTime();
	m_charaCon.SetPosition(m_position);
	m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

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
		if (m_isSearchPlayer == false) {
			diff = Vector3{0.0f,150.0f,0.0f} - m_position;
		}
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
	//float ram = rand() % 200;
	//yup = ram;
	if (m_diff.Length() <= 100.0f && m_timer >= 14.0f) {
		m_isAttack = true;
		m_startVector = m_position;
		m_startVector.y += 50.0f;
		m_endVector = m_startVector;
		Vector3 paint = paintposi - m_startVector;
		paint.Normalize();
		m_endVector += paint * 300.0f;
	//	m_endVector.y += yup;

		m_renderingEngine->SpriteDraw(m_cylinder->m_modelRender, m_cylinder->m_number,0, m_startVector, m_endVector);
	}
	else if (m_diff.Length() <= 100.0f && m_timer < 14.0f)
	{
		//yup = 0.0f;
		m_enemyState = enEnemyState_Idle;
		return;
	}
	if (m_diff.Length() >= 100.0f)
	{
	//	yup = 0.0f;
		m_isAttack = false;
		m_endVector = m_startVector = Vector3::Zero;
	}
}

//衝突したときに呼ばれる関数オブジェクト(壁用)
struct SweepResultWall :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;						//衝突フラグ。

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		//壁とぶつかってなかったら。
		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall) {
			//衝突したのは壁ではない。
			return 0.0f;
		}

		//壁とぶつかったら。
		//フラグをtrueに。
		isHit = true;
		return 0.0f;
	}
};

void Enemy::SearchPlayer()
{
	m_isSearchPlayer = false;

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	Vector3 playerPosition = m_player->GetPosition();
	Vector3 diff = playerPosition - m_position;

	diff.Normalize();
	float angle = acosf(diff.Dot(m_forward));


	//プレイヤーが視界内に居なかったら。
	if (Math::PI * 0.35f <= fabsf(angle) && diff.Length() <= 500.0f)
	{
		//プレイヤーは見つかっていない。
		return;
	}

	btTransform start, end;
	start.setIdentity();
	end.setIdentity();
	//始点はエネミーの座標。
	start.setOrigin(btVector3(m_position.x, m_position.y + 70.0f, m_position.z));
	//終点はプレイヤーの座標。
	end.setOrigin(btVector3(playerPosition.x, playerPosition.y + 70.0f, playerPosition.z));

	SweepResultWall callback;
	//コライダーを始点から終点まで動かして。
	//衝突するかどうかを調べる。
	PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(), start, end, callback);
	//壁と衝突した！
	if (callback.isHit == true)
	{
		//プレイヤーは見つかっていない。
		return;
	}

	//壁と衝突してない！！
	//プレイヤー見つけたフラグをtrueに。
	m_isSearchPlayer = false;
}

void Enemy::Collision()
{
	// エネミー（タンク）の攻撃用のコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player");
	// コリジョンの配列をfor文で回す。
	for (auto collision : collisions)
	{
		// コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_charaCon))
		{
			m_hp -= 1;
			return;
		}
	}
}

void Enemy::ProcessCommonStateTransition()
{
	if (timer >= 4.0f)
	{
		timer = 0.0f;
	}
	if (m_isAttack == true && m_timer >= 14.0f) {
	//	Matrix matrix = m_modelRender.GetBone(m_gunId)->GetWorldMatrix();
		m_effect = NewGO <EffectEmitter>(0);
		Vector3 effectposi = m_position;
		effectposi.y += 50.0f;
		//effectposi += m_forward * 100.0f;

		//Vector3 m_right = Vector3::AxisX;
		//m_rotation.Apply(m_right);
		//effectposi += m_right * -7.5f;
		Vector3 effectDir = m_endVector - m_startVector;
		effectDir.Normalize();
		Quaternion effectRot;
		effectRot.SetRotation(Vector3::AxisZ, effectDir);
	//	m_rotation = effectRot;
		m_effect->Init(0);
		m_effect->SetPosition(effectposi);
		m_effect->SetRotation(m_rotation);
		// エフェクトの大きさを設定する。
		Vector3 sca = Vector3{ 10.0f,10.0f,10.0f };
		m_effect->SetScale(sca);
		//m_effect->SetWorldMatrix(matrix);
		m_effect->Play();
		//攻撃ステートに遷移
		m_enemyState = enEnemyState_Shot;
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
	if (m_timer <= 11.5f) {
		return;
	}
		// モデルをドロー。
		m_modelRender.Draw(rc);
}