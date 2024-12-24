//==============================================================================================================================================
//
// ミニゲームの見出しに関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "mg_head.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CMG_Head::CMG_Head() : CUI()
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CMG_Head::~CMG_Head()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CMG_Head::Init()
{
	//エディット可能フラグ
	SetEditFlag(false);

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
void CMG_Head::Uninit()
{
	//基底クラス終了処理
	CUI::Uninit();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
#include "game.h"
void CMG_Head::Update()
{
	//ゲームシーンのインスタンス取得
	CGame* pGame = CGame::GetInstance();

	//ミニゲーム中ではない場合
	if (pGame != nullptr &&
		pGame->GetArea() != CGame::GAME_AREA::MINI_GAME)
	{
		//終了処理
		Uninit();

		//処理を抜ける
		return;
	}

	//基底クラス更新処理
	CUI::Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CMG_Head::Draw()
{
	//基底クラス描画処理
	CUI::Draw();
}
