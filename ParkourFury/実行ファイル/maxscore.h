//==============================================================================================================================================
//
// 最大スコアの表示に関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _MAXSCORE_H_ //このマクロ定義がされなかったら
#define _MAXSCORE_H_ //2重インクルード防止のマクロ定義

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "UI.h"

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CMaxScore : public CUI
{
public:
	//======================================
	// 関数
	//======================================
	CMaxScore();//コンストラクタ
	~CMaxScore() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
};

#endif
