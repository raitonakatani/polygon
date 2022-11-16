#pragma once

namespace nsK2EngineLow {

	class ModelRender : public IRenderer
	{
	public:

		ModelRender();
		~ModelRender();

		void Init(
			const char* filePath,
			bool shadowRecieve,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			bool isShadowReciever = true,
			int maxInstance = 1
		);

		void SetCasterShadow(const bool castershadow)
		{
			m_isShadowCaster = castershadow;
		}

	private:
		RenderTarget albedRT;
		RenderTarget normalRT;
		RenderTarget worldPosRT;
		SpriteInitData spriteInitData;
		Sprite defferdLightinSpr;
	public:


		void InitModel(const char* filePath);

		void InitTestModel(const char* filePath);


		void modelUpdate();

		Model m_testmodel;

		ModelInitData transModelInitData;
		Model sphereModel;
		Vector3 planePos = { 0.0f, 160.0f, 20.0f };

		void Draw(RenderContext& rc);

		/// <summary>
		/// 座標を設定。
		/// </summary>
		/// <remark>
		/// インスタンシング描画が有効の場合は、この設定は無視されます。
		/// </remark>
		/// <param name="pos">座標。</param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// 座標を設定。
		/// </summary>
		/// <param name="x">x座標</param>
		/// <param name="y">y座標</param>
		/// <param name="z">z座標</param>
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}
		/// <summary>
		/// 回転を設定。
		/// </summary>
		/// <remark>
		/// インスタンシング描画が有効の場合は、この設定は無視されます。
		/// </remark>
		/// <param name="rotation">回転。</param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		/// <summary>
		/// 拡大率を設定。
		/// </summary>
		/// <remark>
		/// インスタンシング描画が有効の場合は、この設定は無視されます。
		/// </remark>
		/// <param name="scale">拡大率。</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		void SetScale(float x, float y, float z)
		{
			SetScale({ x, y, z });
		}

		void Update();


		/// <summary>
		/// アニメーションの初期化。
		/// </summary>
		/// <param name="animationClips">アニメーションクリップ。</param>
		/// <param name="numAnimationClips">アニメーションクリップの数。</param>
		/// <param name="enModelUpAxis">モデルの上向き。</param>
		void InitAnimation(AnimationClip* animationClips,
			int numAnimationClips,
			EnModelUpAxis enModelUpAxis);
		/// <summary>
		/// アニメーション再生。
		/// </summary>
		/// <param name="animNo">アニメーションクリップの番号。</param>
		/// <param name="interpolateTime">補完時間(単位：秒。)</param>
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}
		/// <summary>
		/// アニメーションの再生中？
		/// </summary>
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}
		/// <summary>
		/// アニメーションの再生速度を設定する
		/// </summary>
		/// <param name="animationSpeed">数値の分だけ倍にする</param>
		void SetAnimationSpeed(const float animationSpeed = 1.0f)
		{
			m_animationSpeed = animationSpeed;
		}
		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}
		/// <summary>
		/// ボーンの名前からボーン番号を検索。
		/// </summary>
		/// <param name="boneName">ボーンの名前</param>
		/// <returns>ボーン番号。見つからなかった場合は-1が返ってきます。</returns>
		int FindBoneID(const wchar_t* boneName) const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		/// <summary>
		/// ボーン番号からボーンを取得。
		/// </summary>
		/// <param name="boneNo">ボーン番号</param>
		/// <returns>ボーン</returns>
		Bone* GetBone(int boneNo) const
		{
			return m_skeleton.GetBone(boneNo);
		}
		/// <summary>
		/// モデルを取得。
		/// </summary>
		/// <returns>モデル</returns>
		Model& GetModel()
		{
			return m_model;
		}

		/// <summary>
		/// 座標、回転、拡大を全て設定。
		/// </summary>
		/// <remark>
		/// インスタンシング描画が有効の場合は、この設定は無視されます。
		/// </remark>
		/// <param name="pos">座標。</param>
		/// <param name="rotation">回転。</param>
		/// <param name="scale">拡大。</param>
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}
		/// <summary>
		/// インスタンシング描画を行う？
		/// </summary>
		/// <returns></returns>
		bool IsInstancingDraw() const
		{
			return m_isEnableInstancingDraw;
		}
		/// <summary>
		/// ワールド行列を取得。
		/// </summary>
		/// <param name="instanceId">
		/// インスタンスID。
		/// この引数はインスタンシング描画が向こうの場合は無視されます。
		/// </param>
		/// <returns></returns>
		const Matrix& GetWorldMatrix(int instanceId) const
		{
			if (IsInstancingDraw()) {
				return m_worldMatrixArray[instanceId];
			}
			return m_model.GetWorldMatrix();
		}
		/// <summary>
		/// インスタンシングデータの更新。
		/// </summary>
		/// <param name="pos">座標</param>
		/// <param name="rot">回転</param>
		/// <param name="scale">拡大率</param>
		void UpdateInstancingData(const Vector3& pos, const Quaternion& rot, const Vector3& scale);

		void Change(const char* materialName, Texture& albedoMap) {
			m_model.ChangeAlbedoMap(materialName, albedoMap);
		}

		TkmFile* GetTkm()
		{
			return m_model.GetTkmFile();
		}

		bool m_isHit;

		//三角形と点の当たり判定
		bool hittest_polygon_3d(
			Vector3& A,
			Vector3& B,
			Vector3& C,
			Vector3& P)
		{
			Vector3 AB, BP, BC, CP, CA, AP;

			//ベクトルの減算
			AB.Subtract(B, A);
			BP.Subtract(P, B);

			BC.Subtract(C, B);
			CP.Subtract(P, C);

			CA.Subtract(A, C);
			AP.Subtract(P, A);

			Vector3 c1, c2, c3;

			//外積を求める
			c1.Cross(AB, BP);
			c2.Cross(BC, CP);
			c3.Cross(CA, AP);

			//内積で順方向か逆方向か調べる
			double dot_12 = c1.Dot(c2);
			double dot_13 = c1.Dot(c3);

			if (dot_12 > 0 && dot_13 > 0) {
				int hit = 0;
				//三角形の内側に点がある
				return true;
			}

			int nohit = 0;
			//三角形の外側に点がある
			return false;
		}


		//線分ABと平面の交点を計算する
		bool IntersectPlaneAndLine(
			Vector3& out,	//戻り値　交点が見つかれば格納される 衝突点
			Vector2& uv,	//戻り値　交点が見つかれば格納される 衝突したポリゴンの３頂点のUV座標
			Vector3& A,		//線分始点
			Vector3& B,		//線分終点
			std::vector<nsK2EngineLow::TkmFile::VectorBuffer>& vectorBuffer
		) //平面
		{

			int n = 0;
			Vector3 posi;
			float a = 0.0f;
			float b = 0.0f;
			Vector3 diff;
			Vector3 diff2;
			Vector2 Huv0, Huv1, Huv2;

			std::vector<nsK2EngineLow::TkmFile::VectorBuffer> polygon;

			for (int i = 0;i < vectorBuffer.size();i++)
			{

				Matrix matrix;

				//ワールド行列を取得
				matrix = m_model.GetWorldMatrix();

				TkmFile::VectorBuffer vertexBuffer = vectorBuffer[i];
				matrix.Apply(vertexBuffer.buffer[0]);
				matrix.Apply(vertexBuffer.buffer[1]);
				matrix.Apply(vertexBuffer.buffer[2]);

				matrix.Inverse();
				matrix.Transpose();

				matrix.Apply(vertexBuffer.normal);


				//平面上の点P
				//点P１＝頂点１（Vector3）
				Vector3 P = Vector3(vertexBuffer.buffer[0]);

				//PA PBベクトル
				Vector3 PA = Vector3(P.x - A.x, P.y - A.y, P.z - A.z);
				Vector3 PB = Vector3(P.x - B.x, P.y - B.y, P.z - B.z);

				//PA PBそれぞれを平面法線と内積
				double dot_PA = PA.Dot(vertexBuffer.normal);
				double dot_PB = PB.Dot(vertexBuffer.normal);


				//これは線端が平面上にあった時の計算の誤差を吸収しています。調整して使ってください。
				if (abs(dot_PA) < 0.000001) { dot_PA = 0.0; }
				if (abs(dot_PB) < 0.000001) { dot_PB = 0.0; }

				//交差判定
				if (dot_PA == 0.0 && dot_PB == 0.0) {
					//両端が平面上にあり、交点を計算できない。
					continue;
				}
				if ((dot_PA >= 0.0 && dot_PB <= 0.0) ||
					(dot_PA <= 0.0 && dot_PB >= 0.0)) {
					//内積の片方がプラスで片方がマイナスなので、交差している

				}
				else {
					NOHit();
					//交差していない
					continue;
				}

				//以下、交点を求める 
				Vector3 AB = Vector3(B.x - A.x, B.y - A.y, B.z - A.z);

				//交点とAの距離 : 交点とBの距離 = dot_PA : dot_PB
				double hiritu = abs(dot_PA) / (abs(dot_PA) + abs(dot_PB));


				//衝突点の座標を求める。
				vertexBuffer.Rushpoint.x = A.x + (AB.x * hiritu);
				vertexBuffer.Rushpoint.y = A.y + (AB.y * hiritu);
				vertexBuffer.Rushpoint.z = A.z + (AB.z * hiritu);

				if (hittest_polygon_3d(vertexBuffer.buffer[0], vertexBuffer.buffer[1], vertexBuffer.buffer[2], vertexBuffer.Rushpoint) == false)
				{
					continue;
				}

				polygon.push_back(vertexBuffer);

				HitFlag();

			}

			if (polygon.size() == 0) {
				return false;
			}

			nsK2EngineLow::TkmFile::VectorBuffer rushPoint;
			for (int v = 0; v < polygon.size();v++) {


				if (v == 0)
				{
					rushPoint = polygon[v];
					posi = polygon[v].Rushpoint;
					diff = A - posi;
					a = diff.Length();
				}
				else {
					diff2 = A - polygon[v].Rushpoint;
					b = diff2.Length();
					if (a > b) {
						posi = polygon[v].Rushpoint;
						rushPoint = polygon[v];
					}
				}
			}


			auto v0v1 = rushPoint.buffer[1] - rushPoint.buffer[0];
			auto v0h = rushPoint.Rushpoint - rushPoint.buffer[0];
			Vector3 z;
			z.Cross(v0v1, v0h);
			float zarea = z.Length();
			zarea *= 0.5f;

			auto v1v2 = rushPoint.buffer[2] - rushPoint.buffer[1];
			auto v1h = rushPoint.Rushpoint - rushPoint.buffer[1];
			Vector3 x;
			x.Cross(v1v2, v1h);
			float xarea = x.Length();
			xarea *= 0.5f;

			auto v2v0 = rushPoint.buffer[0] - rushPoint.buffer[2];
			auto v2h = rushPoint.Rushpoint - rushPoint.buffer[2];
			Vector3 y;
			y.Cross(v2v0, v2h);
			float yarea = y.Length();
			yarea *= 0.5f;

			float xyz = xarea + yarea + zarea;
			float uvx, uvy, uvz;

			//面積の比率を求める
			uvx = xarea / xyz;
			uvy = yarea / xyz;
			uvz = zarea / xyz;


			Huv0.x = rushPoint.uv[0].x * uvx;
			Huv0.y = rushPoint.uv[0].y * uvx;

			Huv1.x = rushPoint.uv[1].x * uvy;
			Huv1.y = rushPoint.uv[1].y * uvy;

			Huv2.x = rushPoint.uv[2].x * uvz;
			Huv2.y = rushPoint.uv[2].y * uvz;

			out = rushPoint.Rushpoint;
			//衝突点のUV座標を求める。
			uv.x = Huv0.x + Huv1.x + Huv2.x;
			uv.y = Huv0.y + Huv1.y + Huv2.y;

			int ab = 0;

			return true;
		}


		void NOHit()
		{
			m_isHit = false;
		}

		void HitFlag()
		{
			m_isHit = true;
		}

		bool IsHitFlag()
		{
			return m_isHit;
		}

		///やりたいことリスト（やらなければならない）
		///その１　当たった場所を求める　　　　　　　						できた		modelRender.hで行っている
		///　　　　衝突したポリゴンの３頂点のUV座標を持ってくる				できた
		///その２　当たったかどうかの判定									できた		modelRender.hで行っている
		///その３　インクをテクスチャにオフスクリーンレンダリング			出来てない　　DrawTextureクラスで行う
		///　　　　メイン部分　　　その時にテクスチャ差し替え				できた
		///　　　　シェーダー部分　衝突点のUV座標を求める　　　　　　　　　
		///その４　できたやつをオンスクリーンレンダリング
		///        メイン部分　　　差し替えたテクスチャを元に戻す			


		///その後　インゲーム部分
		/// プレイヤーのアニメーション部分の作成
		/// アイドル（棒立ち）　走る　撃つ（止まりながら）　撃つ（走りながら）
		/// スプラ２のイクラモードを想定してマップを作る
		/// ゲーム内容はガチエリア　敵に一定以上陣地を塗られたらゲームオーバー
		/// ウェーブを乗り越えたらゲームクリア
		/// ラストらへんでラッシュを作る
		/// 
		/// 
		/// 




	private:
		/// <summary>
		/// スケルトンの初期化。
		/// </summary>
		/// <param name="filePath">ファイルパス。</param>
		void InitSkeleton(const char* filePath);

		void InitShadowModel(
			const char* tkmFilePath,
			EnModelUpAxis modelUpAxis);
		/// <summary>
		/// シャドウマップへの描画パスから呼ばれる処理。
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト</param>
		/// <param name="ligNo">ライト番号</param>
		/// <param name="lvpMatrix">ライトビュープロジェクション行列</param>
		void OnRenderShadowMap(
			RenderContext& rc,
			const Matrix& lvpMatrix
		);

		//		const  GetVertexBuffer();


	private:
		Model						m_model;
		Model					m_shadowmodel;							//シャドウモデル。
		Skeleton					m_skeleton;							// スケルトン
		float						m_animationSpeed = 1.0f;
		AnimationClip* m_animationClips = nullptr;			// アニメーションクリップ。
		int							m_numAnimationClips = 0;			// アニメーションクリップの数。
		Animation					m_animation;						// アニメーション。
		Vector3 					m_position;			// 座標。
		Quaternion	 				m_rotation;	// 回転。
		Vector3						m_scale;				// 拡大率。
		Model						m_zprepassModel;					// ZPrepassで描画されるモデル
		int							m_numInstance = 0;					// インスタンスの数。
		int							m_maxInstance = 1;					// 最大インスタンス数。
		//int							m_fixNumInstanceOnFrame = 0;		// このフレームに描画するインスタンスの数の確定数。。
		bool						m_isEnableInstancingDraw = false;	// インスタンシング描画が有効？
		std::unique_ptr<Matrix[]>	m_worldMatrixArray;					// ワールド行列の配列。
		StructuredBuffer			m_worldMatrixArraySB;				// ワールド行列の配列のストラクチャードバッファ。
		EnModelUpAxis			m_enFbxUpAxis = enModelUpAxisZ;			// FBXの上方向。
		bool					m_isShadowCaster = true;

		//TkmFile m_tkm;
		//		ModelRenderCB* m_modelCB;

	};
}