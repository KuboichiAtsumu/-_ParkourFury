//==============================================================================================================================================
//
// 空に関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "back_3D.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CBack3D::CBack3D(int nPriority) : CObjectX(nPriority)
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CBack3D::~CBack3D()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CBack3D::Init()
{
	//テクスチャ生成
	CTexture* pTex = CTexture::GetInstance();
	BindTexture(pTex->GetAddress(CTag::TAG::BACK_3D, static_cast<int>(m_Type)));//設定

	//モデル生成
	CXfile* pModel = CXfile::GetInstance();
	BindModel(pModel->GetAddress(CTag::TAG::BACK_3D, static_cast<int>(m_Type)));//設定
	SetSize();//サイズ設定

	//基底クラス初期化処理
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CBack3D::Uninit()
{
	//基底クラス終了処理
	CObjectX::Uninit();
}

//===========================================================================================================
// 解放処理
//===========================================================================================================
void CBack3D::Release()
{
	//基底クラス解放処理
	CObjectX::Release();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CBack3D::Update()
{
	//基底クラス更新処理
	CObjectX::Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CBack3D::Draw()
{
	//Xファイルのオブジェクト描画処理
	CObjectX::Draw();
}

//===========================================================================================================
// 生成処理
//===========================================================================================================
#include "sky.h"
#include "bossback.h"
#include "minigameback.h"
CBack3D* CBack3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, TYPE type)
{
	//タイプに応じてメモリを動的確保
	CBack3D* pBack3D = nullptr;

	switch (type)
	{
		//ステージ背景
	case CBack3D::TYPE::SKY:
		pBack3D = NEW CSky(static_cast<int>(Category::BACK_3D));
		break;

		//ボスエリア背景
	case CBack3D::TYPE::BOSS_STAGE:
		pBack3D = NEW CBossBack();
		break;

		//ミニゲーム背景
	case CBack3D::TYPE::MINIGAME:
		pBack3D = NEW CMiniGameBack();
		break;

	default:
		break;
	}

	//3D背景の情報が存在する場合
	if (pBack3D != nullptr)
	{
		//パラメータ設定
		pBack3D->SetPos(pos);//座標
		pBack3D->SetRot(rot);//角度
		pBack3D->SetScale(scale);//拡大率
		pBack3D->m_Type = type;//タイプ

		//初期化処理
		pBack3D->Init();
	}

	return pBack3D;
}

//===========================================================================================================
// 読込処理
//===========================================================================================================
void CBack3D::Load()
{
	//ローカル変数宣言
	D3DXVECTOR3 pos = { 0.0f, 0.0f, 0.0f };//座標情報保存用
	D3DXVECTOR3 rot = { 0.0f, 0.0f, 0.0f };//角度情報保存用
	D3DXVECTOR3 scale = { 0.0f, 0.0f, 0.0f };//拡大率情報保存用
	int nTag = 1;//タグ情報保存用
	int nType = 0;//タイプ情報保存用
	int nNumAll = 0;//総数

	//ファイルを開く
	FILE* pFile = fopen(CManager::GetInstance()->StageFile[static_cast<int>(CManager::GetInstance()->GetScene()->GetMode())], "rb");

	//オブジェクトデータの読み込み
	if (pFile != nullptr)
	{
		//ファイルの読み込み
		fread(&nNumAll, sizeof(int), 1, pFile);

		for (int nCnt = 0; nCnt < nNumAll; nCnt++)
		{
			//データの取得
			fread(&pos, sizeof(D3DXVECTOR3), 1, pFile);//座標
			fread(&rot, sizeof(D3DXVECTOR3), 1, pFile);//角度
			fread(&scale, sizeof(D3DXVECTOR3), 1, pFile);//拡大率
			fread(&nTag, sizeof(int), 1, pFile);//タグ
			fread(&nType, sizeof(int), 1, pFile);//種類

			//タグがブロックではない場合
			if (static_cast<CTag::TAG>(nTag) == CTag::TAG::BACK_3D)
			{
				//生成処理
				Create(pos, rot, scale, static_cast<TYPE>(nType));
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}
