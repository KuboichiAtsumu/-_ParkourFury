//==============================================================================================================================================
//
// ボス移動ポイントに関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _BOSSMOVEPOINT_H_ //このマクロ定義がされなかったら
#define _BOSSMOVEPOINT_H_ //2重インクルード防止のマクロ定義

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "gimmick.h"

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CBossMovePoint : public CGimmick
{
public:
	//======================================
	// 列挙型定義
	//======================================

	//ワープポイント
	enum class Point
	{
		LEFT_DOWN = 0,//左下
		LEFT_UP,//左上
		RIGHT_UP,//右上
		RIGHT_DOWN,//右下
		MAX
	};

	//======================================
	// 関数
	//======================================
	CBossMovePoint();//コンストラクタ
	~CBossMovePoint() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Release() override;//解放処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CBossMovePoint* Find(int nIdx);//検索処理
	int GetIdx() { return m_nIdx; }//インデックスを取得

private:
	//======================================
	// 変数
	//======================================
	static std::vector<CBossMovePoint*> m_BossMovePoint;//全ポイントの情報
	static int m_nAll;//合計数
	int m_nIdx;//インデックス
};

#endif
