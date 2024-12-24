//==============================================================================================================================================
//
// リザルトの見出しに関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "resulthead.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CResultHead::CResultHead() : CUI()
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CResultHead::~CResultHead()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CResultHead::Init()
{
	//基底クラス初期化処理
	if (FAILED(CUI::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CResultHead::Uninit()
{
	//基底クラス終了処理
	CUI::Uninit();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CResultHead::Update()
{
	//基底クラス更新処理
	CUI::Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CResultHead::Draw()
{
	//基底クラス描画処理
	CUI::Draw();
}
