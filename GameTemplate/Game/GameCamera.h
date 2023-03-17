#pragma once


class Player;
class Game;

//ゲーム中のカメラを制御する。
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/////////////////////////////////////
	//メンバ変数
	/////////////////////////////////////

	/// <summary>
	/// 座標を取得する。
	/// </summary>
	/// <returns>座標。</returns>
	const Vector3& GetPosition() const
	{
		return m_pos;
	}

	/// <summary>
	/// 回転を取得する。
	/// </summary>
	/// <returns>回転。</returns>
	const Quaternion& GetQuaternion() const
	{
		return m_xyRot;
	}

	/// <summary>
	/// 前方向のベクトルを取得する。
	/// </summary>
	/// <returns>前方向のベクトル。</returns>
	const Vector3& GetForwardPosition() const
	{
		return m_forward;
	}

private:
	Game* m_game;
	Player*					m_player = nullptr;				// プレイヤー
	Vector3					m_toCameraPos = Vector3::One;	// 注視点から視点に向かうベクトル。
	Vector3					m_forward;						// 前方向のベクトル	
	Vector3					m_pos;							// カメラの位置(視点)
	Vector3					m_toCameraPosOld;				// 注視点から視点に向かうベクトル。
	Quaternion              m_rotation;						// 回転
	Quaternion				m_xyRot;						// XY軸周りの回転
	int						m_camera = 0;					// カメラの切り替え判定。
	float					m_timer = 0.0f;					// タイマー。

};