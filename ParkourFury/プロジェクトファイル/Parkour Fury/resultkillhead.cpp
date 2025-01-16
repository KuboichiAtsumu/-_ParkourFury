//==============================================================================================================================================
//
// リザルトの見出し(キル数)に関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "resultkillhead.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CResultKillHead::CResultKillHead() : CUI()
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CResultKillHead::~CResultKillHead()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CResultKillHead::Init()
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
void CResultKillHead::Uninit()
{
	//基底クラス終了処理
	CUI::Uninit();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CResultKillHead::Update()
{
	//基底クラス更新処理
	CUI::Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CResultKillHead::Draw()
{
	//基底クラス描画処理
	CUI::Draw();
}
