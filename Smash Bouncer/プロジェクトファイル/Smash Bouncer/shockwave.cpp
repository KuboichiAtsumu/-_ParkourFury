//==============================================================================================================================================
//
// 衝撃波に関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "shockwave.h"//衝撃波

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CShockWave::CShockWave(int nPriority) : CEffect3D(nPriority)
{
	//メンバ変数初期化
	m_bFlucUP = true;//カラーα値上昇フラグ
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CShockWave::~CShockWave()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CShockWave::Init()
{
	//パラメータ設定
	SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });

	//3Dエフェクト初期化処理
	if (FAILED(CEffect3D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CShockWave::Uninit()
{
	//3Dエフェクト終了処理
	CEffect3D::Uninit();
}

//===========================================================================================================
// 解放処理
//===========================================================================================================
void CShockWave::Release()
{
	//3Dエフェクト解放処理
	CEffect3D::Release();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CShockWave::Update()
{
	//拡大処理
	Scaling();

	//カラー変動処理
	FlucColor();

	//3Dエフェクト更新処理
	CEffect3D::Update();
}

//===========================================================================================================
// 拡大処理
//===========================================================================================================
void CShockWave::Scaling()
{
	//ローカル変数宣言
	D3DXVECTOR3 size = GetSize();//サイズ情報

	//サイズを拡大する
	size.x += SCALE_SPEED;
	size.z += SCALE_SPEED;

	//更新されたサイズ情報を設定
	SetSize(size);
}

//===========================================================================================================
// カラー変動処理
//===========================================================================================================
void CShockWave::FlucColor()
{
	//ローカル変数宣言
	D3DXCOLOR col = GetColor();//カラー情報

	//カラーα値上昇フラグがtrueの場合
	if (m_bFlucUP)
	{
		//α値を上昇
		col.a += FLUC_COLOR;

		//α値が最大になった場合
		if (col.a >= 1.00f)
		{
			//カラーα値上昇フラグをfalseにする
			m_bFlucUP = false;
		}
	}
	//カラーα値上昇フラグがfalseの場合
	else
	{
		//α値を減少
		col.a -= FLUC_COLOR;

		//α値が最小になった場合
		if (col.a <= 0.00f)
		{
			//終了処理
			Uninit();
		}
	}

	//更新されたカラー情報設定
	SetColor(col);
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CShockWave::Draw()
{
	//3Dエフェクト描画処理
	CEffect3D::Draw();
}
