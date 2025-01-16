//==============================================================================================================================================
//
// スコアUIに関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "scoreUI.h"//スコアUI

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CScoreUI::CScoreUI(int nPriority) : CObject2D(nPriority)
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CScoreUI::~CScoreUI()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CScoreUI::Init()
{
	//パラメータ設定
	SetPos(POS);//位置
	SetSize(SIZE);//サイズ
	
	//テクスチャ生成
	CTexture* pTex = CManager::GetTexture();//取得
	int nTextureIdx = pTex->Regist(TEXTURE_FILE);//登録
	BindTexture(pTex->GetAddress(nTextureIdx));//設定
	SetTextureIdx(nTextureIdx);//ID設定

	//2Dオブジェクト初期化処理
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CScoreUI::Uninit()
{
	//2Dオブジェクト終了処理
	CObject2D::Uninit();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CScoreUI::Update()
{
	//ローカル変数宣言
	D3DXCOLOR col = GetColor();//カラー

	//α値が最大ではない場合
	if (col.a < 1.0f)
	{
		//α値を上げる
		col.a += COLOR_ASCENT;

		//更新されたカラー情報を設定
		SetColor(col);

		//2Dオブジェクト更新処理
		CObject2D::Update();
	}
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CScoreUI::Draw()
{
	//2Dオブジェクト描画処理
	CObject2D::Draw();
}

//===========================================================================================================
// 生成処理
//===========================================================================================================
CScoreUI* CScoreUI::Create()
{
	CScoreUI* pHeading = NEW CScoreUI();

	//パラメータ設定
	pHeading->SetType(CObject::UI);//オブジェクトタイプ
	pHeading->SetColor({ 1.0f,1.0f,1.0f,0.0f });//カラー

	//初期化処理
	pHeading->Init();

	return pHeading;
}
