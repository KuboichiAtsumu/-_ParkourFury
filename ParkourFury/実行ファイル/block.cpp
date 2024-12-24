//==============================================================================================================================================
//
// ブロックに関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "block.h"

//===========================================================================================================
// 静的メンバ変数初期化
//===========================================================================================================
float CBlock::m_fKickPowerWidth = 30.0f;
float CBlock::m_fKickPowerHeight = 7.0f;

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	//メンバ変数初期化
	m_pPrev = nullptr;//前のブロック情報
	m_pNext = nullptr;//次のブロック情報
	m_Type = CBlock::TYPE::NONE;//ブロックタイプ
	m_Normal = { 0.0f, 0.0f, 0.0f };//垂直ベクトル
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CBlock::~CBlock()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CBlock::Init()
{
	//モデル生成
	CXfile* pModel = CXfile::GetInstance();//インスタンスを取得
	BindModel(pModel->GetAddress(CTag::TAG::BLOCK, static_cast<int>(m_Type)));//設定
	SetSize();//サイズ設定

	//基底クラス初期化処理
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CBlock::Uninit()
{
	//基底クラス終了処理
	CObjectX::Uninit();
}

//===========================================================================================================
// 解放処理
//===========================================================================================================
void CBlock::Release()
{
	//基底クラス解放処理
	CObjectX::Release();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CBlock::Update()
{
	//基底クラス更新処理
	CObjectX::Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CBlock::Draw()
{
	//エディタモードの場合
	if (CManager::GetInstance()->GetScene()->GetSceneState() == CScene::SCENE::EDIT_3D)
	{//描画せずに処理を抜ける
		return;
	}

	//基底クラス描画処理
	CObjectX::Draw();
}

//===========================================================================================================
// 当たり判定
//===========================================================================================================
CBlock::CollisionFlag CBlock::Collision(CollisionParam& aParam)
{
	//情報を取得
	CollisionFlag aFlag = {};//当たり判定フラグ構造体
	D3DXVECTOR3 Pos = GetPos();//座標
	D3DXVECTOR3 Size = GetSize();//サイズ

	//=======================================================================
	// Y軸
	//=======================================================================

	//上側の判定
	if (aParam.pos.y < Pos.y + Size.y * 0.5f
		&& aParam.oldpos.y >= Pos.y + Size.y * 0.5f)
	{
		//XZ間の範囲内にいる場合
		if ((aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
			&& aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f)
			&& (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
				&& aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f))
		{
			//座標を修正
			aParam.pos.y = Pos.y + Size.y * 0.5f;

			//Y軸の移動量をリセット
			aParam.move.y = 0.0f;

			//Y軸の上側の当たり判定をtrueにする
			aFlag.Y_UP = true;

			//自分自身のタイプを保存
			aParam.type = m_Type;
		}
	}

	//下側の判定
	if (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
		&& aParam.oldpos.y + aParam.size.y <= Pos.y - Size.y * 0.5f)
	{
		//XZ間の範囲内にいる場合
		if ((aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
			&& aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f)
			&& (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
				&& aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f))
		{
			//座標を修正
			aParam.pos.y = Pos.y - Size.y * 0.5f - aParam.size.y;

			//Y軸の移動量をリセット
			aParam.move.y = 0.0f;

			//Y軸の下側の当たり判定をtrueにする
			aFlag.Y_DOWN = true;

			//自分自身のタイプを保存
			aParam.type = m_Type;
		}
	}

	//=======================================================================
	// X軸
	//=======================================================================

	//左側の判定
	if (aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
		&& aParam.oldpos.x + aParam.size.x * 0.5f <= Pos.x - Size.x * 0.5f)
	{
		//YZ間の範囲内にいる場合
		if ((aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
			&& aParam.pos.y < Pos.y + Size.y * 0.5f)
			&& (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
			&& aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f))
		{
			//座標を修正
			aParam.pos.x = Pos.x - Size.x * 0.5f - aParam.size.x * 0.5f;

			//X軸の当たり判定
			aFlag.X = true;

			//自分自身のタイプを保存
			aParam.type = m_Type;
		}
	}

	//右側の判定
	if (aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f
		&& aParam.oldpos.x - aParam.size.x * 0.5f >= Pos.x + Size.x * 0.5f)
	{
		//YZ間の範囲内にいる場合
		if ((aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
			&& aParam.pos.y < Pos.y + Size.y * 0.5f)
			&& (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
			&& aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f))
		{
			//座標を修正
			aParam.pos.x = Pos.x + Size.x * 0.5f + aParam.size.x * 0.5f;

			//X軸の当たり判定をtrueにする
			aFlag.X = true;

			//自分自身のタイプを保存
			aParam.type = m_Type;
		}
	}

	//=======================================================================
	// Z軸
	//=======================================================================

	//手前側の判定
	if (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
		&& aParam.oldpos.z + aParam.size.z * 0.5f <= Pos.z - Size.z * 0.5f)
	{
		//XY間の範囲内にいる場合
		if ((aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
			&& aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f)
			&& (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
			&& aParam.pos.y < Pos.y + Size.y * 0.5f))
		{
			//座標を修正
			aParam.pos.z = Pos.z - Size.z * 0.5f - aParam.size.z * 0.5f;

			//Z軸の当たり判定をtrueにする
			aFlag.Z = true;

			//自分自身のタイプを保存
			aParam.type = m_Type;
		}
	}

	//奥側の判定
	if (aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f
		&& aParam.oldpos.z - aParam.size.z * 0.5f >= Pos.z + Size.z * 0.5f)
	{
		//XY間の範囲内にいる場合
		if ((aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
			&& aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f)
			&& (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f))
		{
			//座標を修正
			aParam.pos.z = Pos.z + Size.z * 0.5f + aParam.size.z * 0.5f;

			//Z軸の当たり判定をtrueにする
			aFlag.Z = true;

			//自分自身のタイプを保存
			aParam.type = m_Type;
		}
	}

	return aFlag;
}

//===========================================================================================================
// 壁キック処理
//===========================================================================================================
CBlock::WallState CBlock::WallKick(CBlock::CollisionParam& aParam)
{
	//坂道の場合
	if (m_Type == TYPE::SLONE)
	{
		//処理を終了
		return WallState::NONE;
	}

	//ローカル変数宣言
	CManager* pManager = CManager::GetInstance();//マネージャーへのポインタ
	WallState wallstate = WallState::NONE;//壁の接触状態
	D3DXVECTOR3 Pos = GetPos();//位置情報
	D3DXVECTOR3 Size = GetSize();//サイズ情報
	bool bCollision = false;//壁との接触判定フラグ
	bool bCliff = false;//崖掴まり判定
	WallLine Line = WallLine::NONE;

	//移動キーが押されている場合
	if (pManager->GetKeyboard()->GetPress(DIK_D)
		|| pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY::JOYKEY_RIGHT)
		|| pManager->GetKeyboard()->GetPress(DIK_A)
		|| pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY::JOYKEY_LEFT))
	{
		//左側の判定
		if ((aParam.pos.x + aParam.size.x * 0.5f >= Pos.x - Size.x * 0.5f
			&& aParam.oldpos.x + aParam.size.x * 0.5f <= Pos.x - Size.x * 0.5f)
			&& (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f)
			&& (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
				&& aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f))
		{
			//ブロックの垂直ベクトルを求める
			SEGMENT_XY(Pos.x, Pos.y - Size.y * 0.5f, Pos.x, Pos.y + Size.y * 0.5f);

			//接触判定をtrueにする
			bCollision = true;

			//触れた線上をXYに設定
			Line = WallLine::XY;

			//プレイヤーの頂点がブロックよりも高い場合
			if (aParam.pos.y + aParam.size.y >= Pos.y + Size.y * 0.5f - 10.0f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f - 10.0f)
			{
				//崖掴まり判定をtrueにする
				bCliff = true;

				//カメラの角度を取得
				float fCamera_Rot_Y = pManager->GetCamera()->GetRot().y;

				//角度の加算量
				float fAddRot_Y = 0.0f;

				//カメラの角度の値が正の値の場合
				if (fCamera_Rot_Y >= 0.0f)
				{
					//加算量を設定
					fAddRot_Y =  -D3DX_PI * 0.5f;
				}
				//カメラの角度の値が負の値の場合
				else
				{
					//加算量を設定
					fAddRot_Y = D3DX_PI * 0.5f;
				}

				//角度を右向きに調整
				aParam.rot.y = pManager->GetCamera()->GetRot().y + fAddRot_Y;
			}
		}

		//右側の判定
		else if ((aParam.pos.x - aParam.size.x * 0.5f <= Pos.x + Size.x * 0.5f
			&& aParam.oldpos.x - aParam.size.x * 0.5f >= Pos.x + Size.x * 0.5f)
			&& (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f)
			&& (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
				&& aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f))
		{
			//ブロックの垂直ベクトルを求める
			SEGMENT_XY(Pos.x, Pos.y + Size.y * 0.5f, Pos.x, Pos.y - Size.y * 0.5f);

			//接触判定をtrueにする
			bCollision = true;

			//触れた線上をXYに設定
			Line = WallLine::XY;

			//プレイヤーの頂点がブロックよりも高い場合
			if (aParam.pos.y + aParam.size.y >= Pos.y + Size.y * 0.5f - 10.0f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f - 10.0f)
			{
				//崖掴まり判定をtrueにする
				bCliff = true;

				//カメラの角度を取得
				float fCamera_Rot_Y = pManager->GetCamera()->GetRot().y;

				//角度の加算量
				float fAddRot_Y = 0.0f;

				//カメラの角度の値が正の値の場合
				if (fCamera_Rot_Y >= 0.0f)
				{
					//加算量を設定
					fAddRot_Y =  D3DX_PI * 0.5f;
				}
				//カメラの角度の値が負の値の場合
				else
				{
					//加算量を設定
					fAddRot_Y = -D3DX_PI * 0.5f;
				}

				//角度を右向きに調整
				aParam.rot.y = pManager->GetCamera()->GetRot().y + fAddRot_Y;
			}
		}

		//手前側の判定
		else if ((aParam.pos.z + aParam.size.z * 0.5f >= Pos.z - Size.z * 0.5f
			&& aParam.oldpos.z + aParam.size.z * 0.5f <= Pos.z - Size.z * 0.5f)
			&& (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f)
			&& (aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
				&& aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f))
		{
			//ブロックの垂直ベクトルを求める
			SEGMENT_YZ(Pos.y - Size.y * 0.5f, Pos.z, Pos.y + Size.y * 0.5f, Pos.z);

			//接触判定をtrueにする
			bCollision = true;

			//触れた線上をYZに設定
			Line = WallLine::YZ;

			//プレイヤーの頂点がブロックよりも高い場合
			if (aParam.pos.y + aParam.size.y >= Pos.y + Size.y * 0.5f - 10.0f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f - 10.0f)
			{
				//崖掴まり判定をtrueにする
				bCliff = true;

				//カメラの角度を取得
				float fCamera_Rot_Y = pManager->GetCamera()->GetRot().y;

				//角度の加算量
				float fAddRot_Y = 0.0f;

				//カメラの角度の値が正の値の場合
				if (fCamera_Rot_Y >= 0.0f)
				{
					//加算量を設定
					fAddRot_Y = D3DX_PI * 0.5f;
				}
				//カメラの角度の値が負の値の場合
				else
				{
					//加算量を設定
					fAddRot_Y = -D3DX_PI * 0.5f;
				}

				//角度を右向きに調整
				aParam.rot.y = pManager->GetCamera()->GetRot().y + fAddRot_Y;
			}
		}

		//奥側の判定
		else if ((aParam.pos.z - aParam.size.z * 0.5f <= Pos.z + Size.z * 0.5f
			&& aParam.oldpos.z - aParam.size.z * 0.5f >= Pos.z + Size.z * 0.5f)
			&& (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f)
			&& (aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
				&& aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f))
		{
			//ブロックの垂直ベクトルを求める
			SEGMENT_YZ(Pos.y + Size.y * 0.5f, Pos.z, Pos.y - Size.y * 0.5f, Pos.z);

			//接触判定をtrueにする
			bCollision = true;

			//触れた線上をYZに設定
			Line = WallLine::YZ;

			//プレイヤーの頂点がブロックよりも高い場合
			if (abs((aParam.pos.y + aParam.size.y) - (Pos.y + Size.y * 0.5f)) <= 10.0f)
			{
				//崖掴まり判定をtrueにする
				bCliff = true;

				//カメラの角度を取得
				float fCamera_Rot_Y = pManager->GetCamera()->GetRot().y;

				//角度の加算量
				float fAddRot_Y = 0.0f;

				//カメラの角度の値が正の値の場合
				if (fCamera_Rot_Y >= 0.0f)
				{
					//加算量を設定
					fAddRot_Y = -D3DX_PI * 0.5f;
				}
				//カメラの角度の値が負の値の場合
				else
				{
					//加算量を設定
					fAddRot_Y = D3DX_PI * 0.5f;
				}

				//角度を右向きに調整
				aParam.rot.y = pManager->GetCamera()->GetRot().y + fAddRot_Y;
			}
		}
	}

	//接触判定がtrueの場合
	if (bCollision)
	{
		//反射ベクトル計算処理
		ReflectAngleCalculate(aParam, Line, wallstate);
	}

	////崖掴まり判定がtrueの場合
	//if (bCliff)
	//{
	//	//崖掴まり状態に設定
	//	wallstate = WallState::NONE;

	//	//移動量を0にする
	//	aParam.move = { 0.0f, 0.0f, 0.0f };

	//	//位置を調整する
	//	aParam.pos.y = Pos.y + Size.y * 0.5f - aParam.size.y - 10.0f;
	//}

	return wallstate;
}

//===========================================================================================================
// 反射ベクトル計算処理
//===========================================================================================================
#include "particle.h"
void CBlock::ReflectAngleCalculate(CollisionParam& aParam, WallLine Line, WallState& wallstate)
{
	//ローカル変数宣言
	CManager* pManager = CManager::GetInstance();//マネージャーへのポインタ
	float fReflectAngle = 0.0f;//反射ベクトルの角度

	//方向ベクトルを求める
	D3DXVECTOR3 Direction = aParam.pos - aParam.oldpos;

	//進行ベクトルを正規化
	D3DXVec3Normalize(&Direction, &Direction);

	//係数を求める
	D3DXVECTOR3 Factor(-Direction.x * m_Normal.x, -Direction.y * m_Normal.y, -Direction.z * m_Normal.z);

	//係数を正規化
	D3DXVec3Normalize(&Factor, &Factor);

	//平行ベクトルを求める
	D3DXVECTOR3 Parallel(Direction.x + Factor.x * m_Normal.x, Direction.y + Factor.y * m_Normal.y, Direction.z + Factor.z * m_Normal.z);

	//平行ベクトルを正規化
	D3DXVec3Normalize(&Parallel, &Parallel);

	//反射ベクトルを求める
	D3DXVECTOR3 Reflect(Direction.x + 2.0f * Factor.x * m_Normal.x, Direction.y + 2.0f * Factor.y * m_Normal.y, Direction.z + 2.0f * Factor.z * m_Normal.z);

	//反射ベクトルを正規化
	D3DXVec3Normalize(&Reflect, &Reflect);

	//ジャンプボタンが押された場合
	if (pManager->GetKeyboard()->GetTrigger(DIK_SPACE)
		|| pManager->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY::JOYKEY_A))
	{
		//反射のパワーを設定
		m_fKickPowerWidth = MAX_KICKPOWER_WIDTH;
		m_fKickPowerHeight = MAX_KICKPOWER_HEIGHT;

		//壁キック状態に設定
		wallstate = WallState::KICK;

		//パーティクル生成
		for (int nCnt = 0; nCnt < 30; nCnt++)
		{
			//ランダムにカラーを設定
			float fR = static_cast<float>(rand() % 10 + 1) * 0.1f;
			float fG = static_cast<float>(rand() % 10 + 1) * 0.1f;
			float fB = static_cast<float>(rand() % 10 + 1) * 0.1f;

			CParticle::Create(CParticle::TYPE::NORMAL, aParam.pos, { 25.0f, 25.0f, 0.0f }, 20, { fR, fG, fB, 1.0f });
		}
	}
	else
	{
		//反射のパワーを1に設定
		m_fKickPowerWidth = 1.0f;
		m_fKickPowerHeight = SLIDE_POWER;

		//壁ずり状態に設定
		wallstate = WallState::SLIDE;
	}

	//触れた線上がXYの場合
	if (Line == WallLine::XY)
	{
		//反射ベクトルのX成分に対して、角度を変更
		if (Reflect.x < 0.0f)
		{
			fReflectAngle = 1.78f;
		}
		else
		{
			fReflectAngle = -1.78f;
		}

		//角度に合わせて移動量を変更
		aParam.move = { sinf(fReflectAngle + D3DX_PI) * m_fKickPowerWidth, cosf(fReflectAngle + D3DX_PI) * m_fKickPowerHeight, 0.0f };
	}
	//触れた線上がYZの場合
	else if (Line == WallLine::YZ)
	{
		//反射ベクトルのX成分に対して、角度を変更
		if (Reflect.z < 0.0f)
		{
			fReflectAngle = 1.78f;
		}
		else
		{
			fReflectAngle = -1.78f;
		}

		//角度に合わせて移動量を変更
		aParam.move = { 0.0f, cosf(fReflectAngle + D3DX_PI) * m_fKickPowerHeight, sinf(fReflectAngle + D3DX_PI) * m_fKickPowerWidth };
	}
}

//===========================================================================================================
// XY間の垂直ベクトル計算処理
//===========================================================================================================
D3DXVECTOR3 CBlock::SEGMENT_XY(float StartX, float StartY, float EndX, float EndY)
{
	//垂直ベクトルを求める
	D3DXVECTOR3 Start(StartX, StartY, 0.0f);
	D3DXVECTOR3 End(EndX, EndY, 0.0f);

	D3DXVECTOR3 r = End - Start;

	m_Normal.x = -r.y;
	m_Normal.y = r.x;

	//ベクトルを正規化
	D3DXVec3Normalize(&m_Normal, &m_Normal);

	return m_Normal;
}

//===========================================================================================================
// XZ間の垂直ベクトル計算処理
//===========================================================================================================
D3DXVECTOR3 CBlock::SEGMENT_XZ(float StartX, float StartZ, float EndX, float EndZ)
{
	//垂直ベクトルを求める
	D3DXVECTOR3 Start(StartX, 0.0f, StartZ);
	D3DXVECTOR3 End(EndX, 0.0f, EndZ);

	D3DXVECTOR3 r = End - Start;

	m_Normal.x = -r.z;
	m_Normal.z = r.x;

	//ベクトルを正規化
	D3DXVec3Normalize(&m_Normal, &m_Normal);

	return m_Normal;
}

//===========================================================================================================
// YZ間の垂直ベクトル計算処理
//===========================================================================================================
D3DXVECTOR3 CBlock::SEGMENT_YZ(float StartY, float StartZ, float EndY, float EndZ)
{
	//垂直ベクトルを求める
	D3DXVECTOR3 Start(0.0f, StartY, StartZ);
	D3DXVECTOR3 End(0.0f, EndY, EndZ);

	D3DXVECTOR3 r = End - Start;

	m_Normal.z = -r.y;
	m_Normal.y = r.z;

	//ベクトルを正規化
	D3DXVec3Normalize(&m_Normal, &m_Normal);

	return m_Normal;
}

//===========================================================================================================
// 生成処理
//===========================================================================================================
#include "slone.h"
#include "bossblock.h"
#include "blockmanager.h"
CBlock* CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, TYPE type)
{
	//タイプに応じてメモリを動的確保
	CBlock* pBlock = nullptr;

	switch (type)
	{
		//ノーマル
	case TYPE::NORMAL:
		pBlock = NEW CBlock(static_cast<int>(Category::BLOCK));
		break;

		//坂道
	case TYPE::SLONE:
		pBlock = NEW CSlone();
		break;

		//ボスブロック
	case TYPE::BOSS:
		pBlock = NEW CBossBlock();

	default:
		break;
	}

	//ブロック情報が存在する場合
	if (pBlock != nullptr)
	{
		//パラメータ設定
		pBlock->SetPos(pos);//座標
		pBlock->SetRot(rot);//角度
		pBlock->SetScale(scale);//拡大率
		pBlock->SetBlockType(type);//ブロックタイプ設定

		//初期化処理
		pBlock->Init();

		//マネージャー登録処理
		CManager::GetInstance()->GetScene()->GetBlockManager()->Regist(pBlock);
	}

	return pBlock;
}
