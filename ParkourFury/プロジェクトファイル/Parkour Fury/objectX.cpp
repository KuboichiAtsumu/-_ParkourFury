//==============================================================================================================================================
//
// Xファイルオブジェクトに関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "objectX.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CObjectX::CObjectX(int nPriority) : CObject3D(nPriority)
{
	//メンバ変数初期化
	m_vtxMin = { 0.0f, 0.0f, 0.0f };//最小頂点座標
	m_vtxMax = { 0.0f, 0.0f, 0.0f };//最大頂点座標
	m_Size = { 0.0f, 0.0f, 0.0f };//サイズ
	m_Scale = { 1.0f, 1.0f, 1.0f };//拡大率
	m_fLength = 0.0f;//対角線の長さ
	m_fAngle = 0.0f;//対角線の角度
	m_StandLine = STAND_LINE::XY;//座標の線上

	//モデル情報初期化
	m_aModelInfo.pMesh = nullptr;
	m_aModelInfo.pBuffMat = nullptr;
	m_aModelInfo.dwNumMat = 0;
	m_aModelInfo.Diffuse.clear();
	m_aModelInfo.FirstDiffuse.clear();
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CObjectX::~CObjectX()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CObjectX::Init()
{
	//オブジェクト初期化処理
	if (FAILED(CObject::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CObjectX::Uninit()
{
	//3Dオブジェクト終了処理
	CObject3D::Uninit();
}

//===========================================================================================================
// 解放処理
//===========================================================================================================
void CObjectX::Release()
{
	//3Dオブジェクト解放処理
	CObject3D::Release();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CObjectX::Update()
{
	//角度に合わせて最大・最小の頂点座標を更新
	m_vtxMin.x = GetPos().x + sinf(GetRot().y - (D3DX_PI - m_fAngle)) * m_fLength;//X座標の最小値
	m_vtxMin.z = GetPos().z + cosf(GetRot().y + m_fAngle) * m_fLength;//Z座標の最小値
	m_vtxMax.x = GetPos().x + sinf(GetRot().y + m_fAngle) * m_fLength;//X座標の最大値
	m_vtxMax.z = GetPos().z + cosf(GetRot().y - (D3DX_PI - m_fAngle)) * m_fLength;//Z座標の最大値

	//更新された頂点座標に応じてサイズも更新
	m_Size =
	{
		abs(m_vtxMax.x - m_vtxMin.x),//x軸
		abs(m_vtxMax.y - m_vtxMin.y) * m_Scale.y,//y軸
		abs(m_vtxMax.z - m_vtxMin.z)//z軸
	};

	//座標の線上の設定
	SetStandLine();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CObjectX::Draw()
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルのデータへのポインタ
	D3DXMATRIX mtxWorld;//ワールドマトリックス情報
	LPDIRECT3DTEXTURE9 pTexture = GetTexture();//テクスチャ情報
	D3DXVECTOR3 Pos = GetPos();//座標情報
	D3DXVECTOR3 Rot = GetRot();//角度情報

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	//拡大率を反映
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	//角度を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Rot.y, Rot.x, Rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//座標を反映
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//法線の長さを1にする。
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	if (m_aModelInfo.pBuffMat != nullptr)
	{
		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_aModelInfo.pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_aModelInfo.dwNumMat; nCntMat++)
		{
			//色合い設定
			pMat->MatD3D.Diffuse = m_aModelInfo.Diffuse[nCntMat];

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, pTexture);

			//モデルの描画
			m_aModelInfo.pMesh->DrawSubset(nCntMat);
		}
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//===========================================================================================================
// 立っている線上の設定処理
//===========================================================================================================
void CObjectX::SetStandLine()
{
	//座標情報を取得
	D3DXVECTOR3 pos = GetPos();

	//Z軸の線上にいる場合
	if (pos.x > CManager::VTXMIN_FIELD.x && pos.x < CManager::VTXMAX_FIELD.x)
	{
		//立っている線上をXYに設定
		m_StandLine = STAND_LINE::XY;
	}
	//X軸の線上にいる場合
	else if (pos.z > CManager::VTXMIN_FIELD.z && pos.z < CManager::VTXMAX_FIELD.z)
	{
		//立っている線上をYZに設定
		m_StandLine = STAND_LINE::YZ;
	}
}

////===========================================================================================================
//// OBB当たり判定
////===========================================================================================================
//bool CObjectX::CollisionOBB(OBB a, OBB b)
//{
//	const float EPSILON = 0.0f;
//
//	float R[3][3], AbsR[3][3];
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			R[i][j] = D3DXVec3Dot(&a.DirectionVec[i], &b.DirectionVec[j]);
//			AbsR[i][j] = fabsf(R[i][j]) + EPSILON;
//		}
//	}
//
//	D3DXVECTOR3 t = b.center - a.center;
//	t = D3DXVECTOR3(D3DXVec3Dot(&t, &a.DirectionVec[0]), D3DXVec3Dot(&t, &a.DirectionVec[1]), D3DXVec3Dot(&t, &a.DirectionVec[2]));
//
//	//軸L=A0, L=A1, L=A2判定
//	float ra, rb;
//
//	for (int i = 0; i < 3; i++)
//	{
//		ra = a.Coordinate_Axes[i];
//		rb = b.Coordinate_Axes[0] * AbsR[i][0] + b.Coordinate_Axes[1] * AbsR[i][1] + b.Coordinate_Axes[2] * AbsR[i][2];
//		if (fabsf(t[i]) > ra + rb)
//		{
//			return true;
//		}
//	}
//	//軸L=B0, L=B1, L=B2判定
//	for (int i = 0; i < 3; i++)
//	{
//		ra = a.Coordinate_Axes[0] * AbsR[0][i] + a.Coordinate_Axes[1] * AbsR[1][i] + a.Coordinate_Axes[2] * AbsR[2][i];
//		rb = b.Coordinate_Axes[i];
//		if (fabsf(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb)
//		{
//			return true;
//		}
//	}
//
//	//軸L=A0 X B0判定
//	ra = a.Coordinate_Axes[1] * AbsR[2][0] + a.Coordinate_Axes[2] * AbsR[1][0];
//	rb = b.Coordinate_Axes[1] * AbsR[0][2] + b.Coordinate_Axes[2] * AbsR[0][1];
//	if (fabsf(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb)
//	{
//		return true;
//	}
//
//	//軸L=A0 X B1判定
//	ra = a.Coordinate_Axes[1] * AbsR[2][1] + a.Coordinate_Axes[2] * AbsR[1][1];
//	rb = b.Coordinate_Axes[0] * AbsR[0][2] + b.Coordinate_Axes[2] * AbsR[0][0];
//	if (fabsf(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb)
//	{
//		return true;
//	}
//
//	//軸L=A0 X B2判定
//	ra = a.Coordinate_Axes[1] * AbsR[2][2] + a.Coordinate_Axes[2] * AbsR[1][2];
//	rb = b.Coordinate_Axes[0] * AbsR[0][1] + b.Coordinate_Axes[1] * AbsR[0][0];
//	if (fabsf(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb)
//	{
//		return true;
//	}
//
//	//軸L=A1 X B0判定
//	ra = a.Coordinate_Axes[0] * AbsR[2][0] + a.Coordinate_Axes[2] * AbsR[0][0];
//	rb = b.Coordinate_Axes[1] * AbsR[1][2] + b.Coordinate_Axes[2] * AbsR[1][1];
//	if (fabsf(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb)
//	{
//		return true;
//	}
//
//	//軸L=A1 X B1判定
//	ra = a.Coordinate_Axes[0] * AbsR[2][1] + a.Coordinate_Axes[2] * AbsR[0][1];
//	rb = b.Coordinate_Axes[0] * AbsR[1][2] + b.Coordinate_Axes[2] * AbsR[1][0];
//	if (fabsf(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb)
//	{
//		return true;
//	}
//
//	//軸L=A1 X B2判定
//	ra = a.Coordinate_Axes[0] * AbsR[2][2] + a.Coordinate_Axes[2] * AbsR[0][2];
//	rb = b.Coordinate_Axes[0] * AbsR[1][1] + b.Coordinate_Axes[1] * AbsR[1][0];
//	if (fabsf(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb)
//	{
//		return true;
//	}
//
//	//軸L=A2 X B0判定
//	ra = a.Coordinate_Axes[0] * AbsR[1][0] + a.Coordinate_Axes[1] * AbsR[0][0];
//	rb = b.Coordinate_Axes[1] * AbsR[2][2] + b.Coordinate_Axes[2] * AbsR[2][1];
//	if (fabsf(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb)
//	{
//		return true;
//	}
//
//	//軸L=A2 X B1判定
//	ra = a.Coordinate_Axes[0] * AbsR[1][1] + a.Coordinate_Axes[1] * AbsR[0][1];
//	rb = b.Coordinate_Axes[0] * AbsR[2][2] + b.Coordinate_Axes[2] * AbsR[2][0];
//	if (fabsf(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb)
//	{
//		return true;
//	}
//
//	//軸L=A2 X B2判定
//	ra = a.Coordinate_Axes[0] * AbsR[1][2] + a.Coordinate_Axes[1] * AbsR[0][2];
//	rb = b.Coordinate_Axes[0] * AbsR[2][1] + b.Coordinate_Axes[1] * AbsR[2][0];
//	if (fabsf(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb)
//	{
//		return true;
//	}
//
//	return false;
//}

//===========================================================================================================
// モデル登録
//===========================================================================================================
void CObjectX::SetSize()
{
	//ローカル変数宣言
	BYTE* pVtxBuff;//頂点バッファへのポインタ

	//頂点数の取得
	int nNumVtx = m_aModelInfo.pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	DWORD sizeFVF = D3DXGetFVFVertexSize(m_aModelInfo.pMesh->GetFVF());

	//頂点バッファのロック
	m_aModelInfo.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nIdxVtx = 0; nIdxVtx < nNumVtx; nIdxVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//モデルの最小値と最大値を取得
		if (vtx.x < m_vtxMin.x)
		{//X座標の最小値
			m_vtxMin.x = vtx.x;
		}
		if (vtx.y < m_vtxMin.y)
		{//Y座標の最小値
			m_vtxMin.y = vtx.y;
		}
		if (vtx.z < m_vtxMin.z)
		{//Z座標の最小値
			m_vtxMin.z = vtx.z;
		}
		if (vtx.x > m_vtxMax.x)
		{//X座標の最大値
			m_vtxMax.x = vtx.x;
		}
		if (vtx.y > m_vtxMax.y)
		{//Y座標の最大値
			m_vtxMax.y = vtx.y;
		}
		if (vtx.z > m_vtxMax.z)
		{//Z座標の最大値
			m_vtxMax.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	//種類ごとのサイズを求める
	m_Size =
	{
		(m_vtxMax.x - m_vtxMin.x) * m_Scale.x,//x軸
		(m_vtxMax.y - m_vtxMin.y) * m_Scale.y,//y軸
		(m_vtxMax.z - m_vtxMin.z) * m_Scale.z//z軸
	};

	//対角線の長さを求める
	m_fLength = sqrtf(powf(m_Size.x, 2.0f) + powf(m_Size.z, 2.0f)) * 0.5f;

	//対角線の角度を求める
	m_fAngle = atan2f(m_Size.x, m_Size.z);

	//頂点バッファのアンロック
	m_aModelInfo.pMesh->UnlockVertexBuffer();
}
