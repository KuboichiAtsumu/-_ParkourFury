//==============================================================================================================================================
//
// UI管理に関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _UIMANAGER_H_ //このマクロ定義がされなかったら
#define _UIMANAGER_H_ //2重インクルード防止のマクロ定義

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "objectmanager.h"
#include "UI.h"

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CUIManager : public CObjectManager
{
public:
	//======================================
	// 関数
	//======================================
	CUIManager();//コンストラクタ
	~CUIManager() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	void Regist(CUI* pUI);//登録処理
	void Load() override;//読込処理
	CUI* FindUI(CUI::TYPE type);//検索処理

	//先頭オブジェクト
	CUI* GetTop() { return m_pTop; }//取得

private:
	//======================================
	// 関数
	//======================================
	void FillIdx();//インデックス調整

	//======================================
	// 変数
	//======================================
	CUI* m_pTop;//先頭オブジェクトのポインタ
	CUI* m_pCur;//終端オブジェクトのポインタ
};

#endif
