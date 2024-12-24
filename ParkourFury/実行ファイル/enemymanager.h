//==============================================================================================================================================
//
// エネミーマネージャーに関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _ENEMYMANAGER_H_ //このマクロ定義がされなかったら
#define _ENEMYMANAGER_H_ //2重インクルード防止のマクロ定義

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "objectmanager.h"
#include "enemy.h"

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CEnemyManager : public CObjectManager
{
public:
	//======================================
	// 関数
	//======================================
	CEnemyManager();//コンストラクタ
	~CEnemyManager() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	void Regist(CEnemy* pEnemy);//登録処理
	void Load() override;//読込処理
	bool Collision(CEnemy::CollisionParam& aParam);//当たり判定
	CEnemy* FindEnemy(CEnemy::TYPE type);//検索処理

	//生成時の総数
	int GetFirstAll() { return m_nFirstAll; }//取得

	//現在の総数
	int GetNowAll() { return m_nNowAll; }//取得

	//先頭オブジェクト
	CEnemy* GetTop() { return m_pTop; }//取得

private:
	//======================================
	// 変数
	//======================================
	static int m_nFirstAll;//生成時の総数
	static int m_nNowAll;//現在の総数
	CEnemy* m_pTop;//先頭オブジェクトのポインタ
	CEnemy* m_pCur;//終端オブジェクトのポインタ
};

#endif
