//==============================================================================================================================================
//
// タイトルフレームに関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "titleframe.h"//タイトルフレーム

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CTitleFrame::CTitleFrame() : CObject2D()
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CTitleFrame::~CTitleFrame()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CTitleFrame::Init()
{
	//パラメータ設定
	SetSize(FRAME_SIZE);//サイズ
	SetColor(COLOR[rand() % COLOR_MAX]);//カラー

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
void CTitleFrame::Uninit()
{
	//2Dオブジェクト終了処理
	CObject2D::Uninit();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CTitleFrame::Update()
{
	//2Dオブジェクト更新処理
	CObject2D::Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CTitleFrame::Draw()
{
	//2Dオブジェクト描画処理
	CObject2D::Draw();
}

//===========================================================================================================
// 生成処理
//===========================================================================================================
CTitleFrame* CTitleFrame::Create(D3DXVECTOR2 pos)
{
	CTitleFrame* pTitleFrame = NEW CTitleFrame();

	//パラメータ設定
	pTitleFrame->SetType(CObject::UI);//オブジェクトタイプ
	pTitleFrame->SetPos(pos);//位置

	//初期化処理
	pTitleFrame->Init();

	return pTitleFrame;
}
