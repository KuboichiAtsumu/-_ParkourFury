//==============================================================================================================================================
//
// スコア表示に関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "scorenumber.h"//スコア表示
#include "score.h"//スコアデータ

//===========================================================================================================
// 静的メンバ変数初期化
//===========================================================================================================
CScoreNumber* CScoreNumber::m_apNumber[MAX_NUMBER] = {};//オブジェクト情報
int CScoreNumber::m_nSaveScore = 0;//スコア
int CScoreNumber::m_nDigit = 0;//桁数

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CScoreNumber::CScoreNumber(int nPriority) : CScore(nPriority)
{
	//メンバ変数初期化
	m_nIdx = 0;//各桁のID
	m_bUse = true;//使用フラグ
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CScoreNumber::~CScoreNumber()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CScoreNumber::Init()
{
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
void CScoreNumber::Uninit()
{
	//2Dオブジェクト終了処理
	CObject2D::Uninit();
}

//===========================================================================================================
// 解放処理
//===========================================================================================================
void CScoreNumber::Release()
{
	//2Dオブジェクト解放処理
	CObject2D::Release();

	//IDを保存
	int nID = m_nIdx;

	//データが存在する場合
	if (m_apNumber[nID] != nullptr)
	{
		m_apNumber[nID] = nullptr;
	}
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CScoreNumber::Update()
{
	//ローカル変数宣言
	VERTEX_2D* pVtx;//頂点情報へのポインタ
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//頂点バッファへのポインタ
	D3DXCOLOR col = GetColor();//カラー
	int aPosTexU[MAX_NUMBER];//各桁の数字を格納用
	int nMulti = 10;//各桁の倍数
	int nScore = m_nSaveScore;//現在のスコア

	//桁数をリセット
	m_nDigit = 0;

	//桁数を求める
	while (nScore != 0)
	{
		nScore /= 10;//スコアを10で割る
		m_nDigit++;//桁数を加算
	}

	//スコアが0の場合
	if (m_nDigit == 0)
	{
		//桁数を1に調整
		m_nDigit = 1;
	}

	//桁数分だけ使用する
	if (m_nIdx < m_nDigit)
	{
		m_bUse = true;
	}
	else
	{
		m_bUse = false;
	}

	//各桁の数字を求める
	for (int nCnt = 0; nCnt < m_nIdx; nCnt++)
	{
		//何桁目かを求める
		nMulti *= 10;
	}

	//数字に合わせてテクスチャ座標を変更
	aPosTexU[m_nIdx] = (m_nSaveScore % nMulti) / (nMulti / 10);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(aPosTexU[m_nIdx] / 10.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((aPosTexU[m_nIdx] + 1) / 10.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(aPosTexU[m_nIdx] / 10.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((aPosTexU[m_nIdx] + 1) / 10.0f, 1.0f);

	//頂点バッファをアンロックする
	pVtxBuff->Unlock();

	//α値が最大ではない場合
	if (col.a < 1.0f)
	{
		//α値を上げる
		col.a += COLOR_ASCENT;

		//更新されたカラー情報を設定
		SetColor(col);
	}

	//2Dオブジェクト更新処理
	CObject2D::Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CScoreNumber::Draw()
{
	//使用フラグがfalseの場合
	if (!m_bUse)
	{
		return;
	}

	//2Dオブジェクト描画処理
	CObject2D::Draw();
}

//===========================================================================================================
// 生成処理
//===========================================================================================================
CScoreNumber* CScoreNumber::Create(int nIdx, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	//データが存在しない場合
	if (m_apNumber[nIdx] == nullptr)
	{
		//メモリを動的確保
		m_apNumber[nIdx] = NEW CScoreNumber();

		//パラメータ設定
		m_apNumber[nIdx]->SetType(TYPE::UI);//オブジェクトタイプ
		m_apNumber[nIdx]->SetIndex(nIdx);//番号
		m_apNumber[nIdx]->SetSize(size);//サイズ
		m_apNumber[nIdx]->SetPos(pos);//生成位置
		m_apNumber[nIdx]->SetColor(col);//カラー

		//初期化処理
		m_apNumber[nIdx]->Init();
	}

	return m_apNumber[nIdx];
}

//===========================================================================================================
// 生成位置設定処理
//===========================================================================================================
void CScoreNumber::SetPos(D3DXVECTOR2 pos)
{
	//ローカル変数宣言
	D3DXVECTOR2 size = GetSize();//サイズ情報

	//右から順番に生成していく
	CObject2D::SetPos({ pos.x - size.x * m_nIdx, pos.y });
}
