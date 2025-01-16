#ifdef _DEBUG
//==============================================================================================================================================
//
// エディタオブジェクトマネージャーに関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _EDITMANAGER_H_ //このマクロ定義がされなかったら
#define _EDITMANAGER_H_ //2重インクルード防止のマクロ定義

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "objectmanager.h"
#include "edit3D.h"

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CEdit3DManager : public CObjectManager
{
public:
	//======================================
	// 関数
	//======================================
	CEdit3DManager();//コンストラクタ
	~CEdit3DManager() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	void Regist(CEdit3D* pBlock);//登録処理
	void Load() override;//読込処理
	CEdit3D* Find(int nIdx);//インデックス検索処理

private:
	//======================================
	// 変数
	//======================================
	CEdit3D* m_pTop;//先頭オブジェクトのポインタ
	CEdit3D* m_pCur;//終端オブジェクトのポインタ
};

#endif
#endif // _DEBUG
