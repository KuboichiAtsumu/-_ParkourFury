//==============================================================================================================================================
//
// パーティクルに関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "particle.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CParticle::CParticle(int nPriority) : 
	CBillboard{ nPriority },
	m_type{ TYPE::NONE },
	m_nLife{ 10 }
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CParticle::~CParticle()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CParticle::Init()
{
	//テクスチャ生成
	CTexture* pTex = CTexture::GetInstance();//取得
	int nTexIdx = pTex->Regist(CTag::TAG::EFFECT, 1, "data/TEXTURE/EFFECT/Particle.jpg");//登録
	BindTexture(pTex->GetAddress(nTexIdx));//設定

	//基底クラス初期化処理
	if (FAILED(CBillboard::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CParticle::Uninit()
{
	//基底クラス終了処理
	CBillboard::Uninit();
}

//===========================================================================================================
// 解放処理
//===========================================================================================================
void CParticle::Release()
{
	//基底クラス解放処理
	CBillboard::Release();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CParticle::Update()
{
	//座標更新
	SetPos(GetPos() + GetMove());

	//寿命減少
	m_nLife--;

	//寿命が0
	if (m_nLife <= 0)
	{
		//終了処理
		Uninit();
	}

	//寿命に合わせて薄くする
	D3DXVECTOR3 size = GetSize();
	size.x = m_MaxSize.x * (static_cast<float>(m_nLife) / static_cast<float>(m_nMaxLife));
	size.y = m_MaxSize.y * (static_cast<float>(m_nLife) / static_cast<float>(m_nMaxLife));
	SetSize(size);

	//基底クラス更新処理
	CBillboard::Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CParticle::Draw()
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスのポインタ
	D3DXMATRIX mtxTrans;//計算用マトリックス
	D3DXMATRIX mtxView;//ビューマトリックス取得用
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 pTexture = GetTexture();//テクスチャ情報へのポインタ
	D3DXMATRIX mtxWorld;//ワールドマトリックス情報
	D3DXVECTOR3 Pos = GetPos();//座標情報

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&mtxWorld, nullptr, &mtxView);//逆行列を求める
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;

	//座標を反映
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//ライトを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zバッファ書き込み無効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテスト有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//aブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//aブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//ライトを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Zバッファ書き込み有効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテスト無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//===========================================================================================================
// 生成処理
//===========================================================================================================
CParticle* CParticle::Create(TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife, D3DXCOLOR col)
{
	//メモリを動的確保
	CParticle* pParticle = NEW CParticle(static_cast<int>(Category::EFFECT));

	//ターゲット情報が存在する場合
	if (pParticle != nullptr)
	{
		//パラメータ設定
		pParticle->m_type = type;//タイプ
		pParticle->SetPos(pos);//座標
		pParticle->SetSize(size);//サイズ
		pParticle->m_MaxSize = size;//最大サイズ
		pParticle->m_nLife = nLife;//ライフ
		pParticle->m_nMaxLife = pParticle->m_nLife;//最大ライフ
		pParticle->SetColor(col);//カラー

		//移動量設定
		pParticle->RandMoveValue();

		//初期化処理
		pParticle->Init();
	}

	return pParticle;
}

//===========================================================================================================
// 移動量設定
//===========================================================================================================
void CParticle::RandMoveValue()
{
	//各座標の移動方向ベクトルを設定
	float fX = static_cast<float>(rand() % 21 - 10) * 0.1f * SPEED;
	float fY = static_cast<float>(rand() % 21 - 10) * 0.1f * SPEED;
	float fZ = static_cast<float>(rand() % 21 - 10) * 0.1f * SPEED;

	//移動量設定
	SetMove({ fX, fY, fZ });
}
