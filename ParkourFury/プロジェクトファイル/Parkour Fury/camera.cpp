//==============================================================================================================================================
//
// カメラの処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "camera.h"
#include "manager.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CCamera::CCamera() :  
	m_State(STATE::NONE),
	m_rot(0.0f,0.0f,0.0f),
	m_TargetRot(0.0f,0.0f,0.0f),
	m_posV(FirstPosV),
	m_posR(0.0f,70.0f,0.0f),
	m_nShakeFrame(0),
	m_nMaxNumShake(0),
	m_fLength(sqrtf(powf(m_posV.y, 2.0f) + powf(m_posV.z, 2.0f))),
	m_fDistanceMag(1.0f),
	m_fAddHeight(0.0f),
	m_fMoveRotY(0.0f)
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CCamera::~CCamera()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CCamera::Init()
{
	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CCamera::Uninit()
{
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
#include "game.h"
void CCamera::Update()
{
	//シーンの情報を取得
	CScene* pScene = CManager::GetInstance()->GetScene();

	//エディタ中
	if (pScene->GetSceneState() == CScene::SCENE::EDIT_3D)
	{
		//移動処理
		Move();

		//処理を抜ける
		return;
	}

	//タイトルシーンの場合
	if (pScene->GetMode() == CScene::MODE::MODE_TITLE && 
		pScene->GetSceneState() == CScene::SCENE::GAME)
	{
		//ループターン状態にする
		m_State = STATE::LOOP_TURN;

		//回転処理
		Turn();

		return;
	}
	
	//ゲームシーンのインスタンス取得
	CGame* pGame = CGame::GetInstance();

	//プレイヤーが特定のエリア内にいる場合
	if (pGame != nullptr &&
		pGame->GetArea() != CGame::GAME_AREA::NORMAL)
	{
		//エリアの中央に注視点を設定
		SetPosRArea();
	}
	//プレイヤーが通常ステージにいる場合
	else
	{
		//プレイヤーの位置に注視点を設定
		SetPosRPlayer();
	}
}

//===========================================================================================================
// エリアの中央に注視点を設定する処理
//===========================================================================================================
void CCamera::SetPosRArea()
{
	//現在のカメラの位置から目的地までの距離を求める
}

//===========================================================================================================
// プレイヤーに注視点を設定する処理
//===========================================================================================================
#include "player.h"
void CCamera::SetPosRPlayer()
{
	//プレイヤーカテゴリーのオブジェクト情報を取得
	CObject* pFindObj = CObject::FindObject(CObject::Category::PLAYER);

	//オブジェクト情報が存在する場合
	if (pFindObj != nullptr)
	{
		//プレイヤークラスにダウンキャスト
		CPlayer* pPlayer = CObject::DownCast<CPlayer, CObject>(pFindObj);

		//ダウンキャスト成功
		if (pPlayer != nullptr)
		{
			//注視点の座標の更新
			m_posR = pPlayer->GetPos();
			m_posR.y = pPlayer->GetPos().y + pPlayer->GetVtxMax().y;
		}
	}

	//回転中、目標の角度に到達していない場合
	if (m_State != STATE::NONE)
	{
		//ステージカメラ回転処理
		RotationStage();
	}

	//視点の位置の更新
	m_posV.x = sinf(m_rot.y + D3DX_PI) * m_fLength + m_posR.x;
	m_posV.y = m_posR.y + FirstPosV.y;
	m_posV.z = cosf(m_rot.y + D3DX_PI) * m_fLength + m_posR.z;
}

//===========================================================================================================
// 回転処理
//===========================================================================================================
void CCamera::Turn()
{
	//回転
	m_rot.y += TITLE_TURN_SPEED;

	//角度補正
	CObject::CorrectionRot(m_rot.y);

	//視点の位置の更新
	m_posV.x = sinf(m_rot.y + D3DX_PI) * TITLE_DISTANCE;
	m_posV.y = TITLE_POSV_Y;
	m_posV.z = cosf(m_rot.y + D3DX_PI) * TITLE_DISTANCE;
}

//===========================================================================================================
// 移動処理
//===========================================================================================================
void CCamera::Move()
{
	//エディタ用のY軸の角度情報
	static float fRot_Y = 0.0f;

	//マウスの情報を取得
	DIMOUSESTATE pMouse = CManager::GetInstance()->GetMouse()->Get();

	//左クリックを押している場合
	if (CManager::GetInstance()->GetMouse()->GetPress(static_cast<int>(CInputMouse::MOUSE::MOUSE_LEFT)))
	{
		//マウスの動きに合わせて視点を回転する
		fRot_Y += pMouse.lX * 0.01f;

		//角度補正
		CObject::CorrectionRot(fRot_Y);
	}
	//ホイールを押している場合
	else if (CManager::GetInstance()->GetMouse()->GetPress(static_cast<int>(CInputMouse::MOUSE::MOUSE_WHEEL)))
	{
		//視点の高さを加算
		m_fAddHeight += pMouse.lY * 1.5f;
	}

	//ホイールの動きに合わせて距離を話す
	m_fDistanceMag += pMouse.lZ * 0.001f;

	//視点の位置の更新
	m_posV.x = sinf(fRot_Y + D3DX_PI) * (m_fLength * m_fDistanceMag) + m_posR.x;
	m_posV.y = FirstPosV.y + m_fAddHeight;
	m_posV.z = cosf(fRot_Y + D3DX_PI) * (m_fLength * m_fDistanceMag) + m_posR.z;
}

//===========================================================================================================
// ステージカメラ回転処理
//===========================================================================================================
void CCamera::RotationStage()
{
	//回転させる
	m_rot.y += m_fMoveRotY;

	//現在の角度と目標の角度の正負が異なる場合
	if ((m_rot.y < 0.00f && m_TargetRot.y > 0.00f) || 
		(m_rot.y > 0.00f && m_TargetRot.y < 0.00f))
	{
		//角度補正
		CObject::CorrectionRot(m_rot.y);
	}

	//目標の角度を超えないように調整
	if ((m_rot.y < m_TargetRot.y && m_State == STATE::LEFTTURN) || 
		(m_rot.y > m_TargetRot.y && m_State == STATE::RIGHTTURN))
	{
		m_rot.y = m_TargetRot.y;

		//状態を戻す
		m_State = STATE::NONE;
	}
}

//===========================================================================================================
// カメラの設定
//===========================================================================================================
void CCamera::SetCamera()
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスのポインタ
	D3DXVECTOR3 adjust = { 0.0f, 0.0f, 0.0f };//揺れの量

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, 
		D3DXToRadian(45.0f), 
		SCREEN_WIDTH / SCREEN_HEIGHT, 
		1.0f, 
		8000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//フレーム数が0以上の場合
	if (m_nShakeFrame > 0)
	{
		//フレーム数を減少
		m_nShakeFrame--;

		//揺れの量の最大値が1以上の場合
		if (m_nMaxNumShake >= 1)
		{
			//揺れの量を設定
			adjust.x = static_cast<float>(rand() % (m_nMaxNumShake * 2) - m_nMaxNumShake);
			adjust.y = static_cast<float>(rand() % (m_nMaxNumShake * 2) - m_nMaxNumShake);
			adjust.z = static_cast<float>(rand() % (m_nMaxNumShake * 2) - m_nMaxNumShake);
		}
	}

	//揺れの量を加算した視点と注視点の値を保存
	D3DXVECTOR3 posV = m_posV + adjust;
	D3DXVECTOR3 posR = m_posR + adjust;

	//ビューマトリックスの生成
	D3DXMatrixLookAtLH(&m_mtxView, &posV, &posR, &VecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//===========================================================================================================
// 状態の設定
//===========================================================================================================
void CCamera::SetState(STATE state)
{
	//状態設定
	m_State = state;

	//状態に合わせて目標の角度と回転量を設定
	switch (m_State)
	{
		//右回転
	case STATE::RIGHTTURN:
		//目標の角度を設定
		m_TargetRot.y = m_rot.y + D3DX_PI * 0.5f;

		//回転量を設定
		m_fMoveRotY = MAX_STAGEROTATION;
		break;

		//左回転
	case STATE::LEFTTURN:
		//目標の角度を設定
		m_TargetRot.y = m_rot.y - D3DX_PI * 0.5f;

		//回転量を設定
		m_fMoveRotY = -MAX_STAGEROTATION;
		break;

	default:
		break;
	}

	//角度補正
	CObject::CorrectionRot(m_TargetRot.y);
}