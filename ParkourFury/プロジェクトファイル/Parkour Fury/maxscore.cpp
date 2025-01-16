//==============================================================================================================================================
//
// 最大スコアの表示に関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "maxscore.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CMaxScore::CMaxScore() : CUI()
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CMaxScore::~CMaxScore()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CMaxScore::Init()
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
void CMaxScore::Uninit()
{
	//基底クラス終了処理
	CUI::Uninit();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CMaxScore::Update()
{
	//基底クラス更新処理
	CUI::Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CMaxScore::Draw()
{
	//基底クラス描画処理
	CUI::Draw();
}
