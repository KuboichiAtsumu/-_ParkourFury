//==============================================================================================================================================
//
// トータルスコアに関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "totalscore.h"

//===========================================================================================================
// 静的メンバ変数初期化
//===========================================================================================================
int CTotalScore::m_nDigit = 0;//桁数

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CTotalScore::CTotalScore() : CUI()
{
	//メンバ変数初期化
	m_nIdx = m_nDigit;//インデックス
	m_nDigit++;//桁数を加算
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CTotalScore::~CTotalScore()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
#include "game.h"
#include "timer.h"
HRESULT CTotalScore::Init()
{
	//座標設定
	SetNumberPos(GetPos());

	//テクスチャ分割数
	SetDivisionTex_X(10);//横

	//エディット可能フラグ
	SetEditFlag(false);

	//トータルスコア計算
	int nTime = CGame::GetInstance()->GetResultScore().nGoalTime;//タイムを取得
	float fRatioTime = 1.0f - static_cast<float>(nTime) / static_cast<float>(CTimer::MAX_TIMER);
	nTime = static_cast<int>(100.0f * fRatioTime);

	float fKill = CGame::GetInstance()->GetResultScore().fNumKillenemy;//キル数を取得
	int nKill = static_cast<int>(fKill);//int型にキャスト

	float fHeat = CGame::GetInstance()->GetResultScore().fAverageHeat;//平均ヒート量を取得
	int nHeat = static_cast<int>(fHeat);//int型にキャスト

	int nTotalScore = nTime + nKill + nHeat;

	//ローカル変数宣言
	int nMulti = 1;//各桁の倍数

	//インデックスに合わせて倍数を求める
	for (int nCntTime = 0; nCntTime < m_nIdx + 1; nCntTime++)
	{
		nMulti *= 10;
	}

	// 該当する桁の数字を求める
	int nPosTex = (nTotalScore % nMulti) / (nMulti / 10);

	//横のアニメーションパターンを設定
	SetPatternAnim_X(nPosTex);

	//基底クラス初期化処理
	if (FAILED(CUI::Init())) return E_FAIL;

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CTotalScore::Uninit()
{
	//基底クラス終了処理
	CUI::Uninit();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CTotalScore::Update()
{
	//基底クラス更新処理
	CUI::Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CTotalScore::Draw()
{
	//基底クラス描画処理
	CUI::Draw();
}

//===========================================================================================================
// 座標設定
//===========================================================================================================
void CTotalScore::SetNumberPos(D3DXVECTOR2 pos)
{
	//桁数に応じて左にずらす
	SetPos({ pos.x - m_nIdx * (GetSize().x), pos.y });
}
