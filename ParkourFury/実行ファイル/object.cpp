//==============================================================================================================================================
//
// オブジェクトに関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "object.h"

//===========================================================================================================
// 静的メンバ変数初期化
//===========================================================================================================
CObject* CObject::m_pTop[static_cast<int>(Category::MAX_CATEGORY)] = {};//先頭アドレス
CObject* CObject::m_pCur[static_cast<int>(Category::MAX_CATEGORY)] = {};//終端アドレス

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CObject::CObject(int nPriority)
{
	//メンバ変数初期化
	m_pVtxBuff = nullptr;//頂点バッファへのポインタ
	m_pTexture = nullptr;//テクスチャへのポインタ
	m_pPrev = nullptr;//前のオブジェクト情報
	m_pNext = nullptr;//次のオブジェクト情報
	m_nPriority = nPriority;//描画優先度
	m_bDelete = false;//削除フラグ
	m_category = static_cast<Category>(nPriority);//オブジェクトタイプ
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CObject::~CObject()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CObject::Init()
{
	//先頭アドレスが存在しない場合
	if (m_pTop[m_nPriority] == nullptr)
	{
		//自分自身を先頭アドレスに代入
		m_pTop[m_nPriority] = this;

		//前のオブジェクト情報にnullptrを代入
		m_pPrev = nullptr;
	}
	//先頭アドレスが存在する場合
	else
	{
		//先頭アドレスを取得
		CObject* pObj = m_pTop[m_nPriority];

		//オブジェクト情報がnullptrになるまで繰り返す
		while (pObj != nullptr)
		{
			//次のオブジェクト情報が存在しない場合
			if (pObj->m_pNext == nullptr)
			{
				//次のオブジェクト情報に自身の情報を保存
				pObj->m_pNext = this;

				//自身の前のオブジェクト情報を保存
				m_pPrev = pObj;

				break;
			}

			//オブジェクト情報を次の情報に変更する
			pObj = pObj->m_pNext;
		}
	}

	//自身の次のオブジェクト情報にnullptrを代入
	m_pNext = nullptr;

	//終端アドレスを代入
	m_pCur[m_nPriority] = this;

	return S_OK;
}

//===========================================================================================================
// 全オブジェクト終了処理
//===========================================================================================================
void CObject::UninitAll()
{
	//指定した順番に更新する
	for (int nCnt = 0; nCnt < static_cast<int>(Category::MAX_CATEGORY); nCnt++)
	{
		//先頭
		CObject* pObj = m_pTop[nCnt];

		//オブジェクト情報がnullptrになるまで繰り返す
		while (pObj != nullptr)
		{
			//次のオブジェクト情報を取得
			CObject* pNext = pObj->m_pNext;

			//終了処理
			pObj->Uninit();

			//オブジェクト情報を次の情報に変更する
			pObj = pNext;
		}
	}

	//全オブジェクト解放処理
	ReleaseAll();
}

//===========================================================================================================
// 全オブジェクト更新処理
//===========================================================================================================
void CObject::UpdateAll()
{
	//指定した順番に更新する
	for (int nCnt = 0; nCnt < static_cast<int>(Category::MAX_CATEGORY); nCnt++)
	{
		//先頭アドレスを取得する
		CObject* pObj = m_pTop[nCnt];

		//オブジェクト情報がnullptrになるまで繰り返す
		while (pObj != nullptr)
		{
			//次のオブジェクト情報を取得
			CObject* pNext = pObj->m_pNext;

			//オブジェクト情報が存在する場合
			if (pObj != nullptr)
			{
				//更新処理
				pObj->Update();
			}

			//オブジェクト情報を次の情報に変更する
			pObj = pNext;
		}
	}

	//全オブジェクト解放処理
	ReleaseAll();
}

//===========================================================================================================
// 全オブジェクト解放処理
//===========================================================================================================
void CObject::ReleaseAll()
{
	//指定した順番に解放する
	for (int nCnt = 0; nCnt < static_cast<int>(Category::MAX_CATEGORY); nCnt++)
	{
		//先頭
		CObject* pObj = m_pTop[nCnt];

		//オブジェクト情報がnullptrになるまで繰り返す
		while (pObj != nullptr)
		{
			//次のオブジェクト情報を取得
			CObject* pNext = pObj->m_pNext;

			//削除フラグがtrueの場合
			if (pObj->GetDeleteFlag())
			{
				//前のオブジェクト情報を取得
				CObject* pPrev = pObj->m_pPrev;

				//前のオブジェクト情報が存在する場合
				if (pPrev != nullptr)
				{
					//次のオブジェクト情報を繋ぐ
					pPrev->m_pNext = pNext;
				}
				//前のオブジェクト情報が存在しない場合
				else
				{
					//次のオブジェクト情報が存在する場合
					if (pNext != nullptr)
					{
						//次ののオブジェクト情報の前のオブジェクト情報をnullptrに設定
						pNext->m_pPrev = nullptr;
					}

					//先頭アドレスを変更
					m_pTop[nCnt] = pNext;
				}

				//次のオブジェクト情報が存在する場合
				if (pNext != nullptr)
				{
					//前のオブジェクト情報を繋ぐ
					pNext->m_pPrev = pPrev;
				}
				//次のオブジェクト情報が存在しない場合
				else
				{
					//前のオブジェクト情報が存在する場合
					if (pPrev != nullptr)
					{
						//前のオブジェクト情報の次のオブジェクト情報をnullptrに設定
						pPrev->m_pNext = nullptr;

						//終端アドレスを変更
						m_pCur[nCnt] = pPrev;
					}
				}

				//解放処理
				pObj->Release();
				delete pObj;
				pObj = nullptr;
			}

			//オブジェクト情報を次の情報に変更する
			pObj = pNext;
		}
	}
}

//===========================================================================================================
// 自分自身の解放処理
//===========================================================================================================
void CObject::Release()
{
	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//===========================================================================================================
// 全オブジェクト描画処理
//===========================================================================================================
void CObject::DrawAll()
{
	//指定した順番に描画する
	for (int nCnt = 0; nCnt < static_cast<int>(Category::MAX_CATEGORY); nCnt++)
	{
		//先頭
		CObject* pObj = m_pTop[nCnt];

		//オブジェクト情報がnullptrになるまで繰り返す
		while (pObj != nullptr)
		{
			//次のオブジェクト情報を取得
			CObject* pNext = pObj->m_pNext;

			//描画処理
			pObj->Draw();

			//オブジェクト情報を次の情報に変更する
			pObj = pNext;
		}
	}
}

//===========================================================================================================
// オブジェクト検索処理
//===========================================================================================================
CObject* CObject::FindObject(Category category)
{
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(Category::MAX_CATEGORY); nCntPriority++)
	{
		//先頭オブジェクトのポインタをコピー
		CObject* pObj = m_pTop[nCntPriority];

		//次のオブジェクトがnullptrになるまで繰り返す
		while (pObj != nullptr)
		{
			if (pObj->GetCategory() == category)
			{
				//カテゴリーが一致した場合ポインタを返す
				return pObj;
			}

			//次のオブジェクトのポインタをコピー
			pObj = pObj->m_pNext;
		}
	}

	return nullptr;
}

//===========================================================================================================
// 角度補正処理
//===========================================================================================================
void CObject::CorrectionRot(float& fRot)
{
	//3.14以上
	if (fRot > D3DX_PI)
	{
		fRot = -D3DX_PI + (fRot - D3DX_PI);
	}
	//-3.14以下
	else if (fRot < -D3DX_PI)
	{
		fRot = D3DX_PI + (fRot + D3DX_PI);
	}
}

//===========================================================================================================
// 動いている判定処理
//===========================================================================================================
bool CObject::MovingJudgeXZ(D3DXVECTOR3 move)
{
	//ローカル変数宣言
	bool bMove = false;//判定
	float fJudge = 0.01f;//動いている判定の範囲

	//動いている場合
	if ((move.x > fJudge || move.x < -fJudge) || (move.z > fJudge || move.z < -fJudge))
	{
		//フラグをtrueにする
		bMove = true;
	}

	return bMove;
}
