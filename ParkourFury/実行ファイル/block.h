//==============================================================================================================================================
//
// ブロックに関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _BLOCK_H_ //このマクロ定義がされなかったら
#define _BLOCK_H_ //2重インクルード防止のマクロ定義

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "objectX.h"

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CBlock : public CObjectX
{
public:
	//======================================
	// 列挙型定義
	//======================================

	//タイプ
	enum class TYPE
	{
		NONE = 0,
		NORMAL,//ノーマル
		SLONE,//坂道
		BOSS,//ボス
		MAX
	};

	//壁の判定
	enum class WallState
	{
		NONE = 0,
		SLIDE,//壁ずり
		KICK,//壁キック
		CLIFF,//崖掴まり
		MAX
	};

	//======================================
	// 構造体定義
	//======================================

	//当たり判定用パラメータ
	struct CollisionParam
	{
		D3DXVECTOR3 pos;//座標
		D3DXVECTOR3 oldpos;//更新前の座標
		D3DXVECTOR3 move;//移動量
		D3DXVECTOR3 size;//サイズ
		D3DXVECTOR3 rot;//角度
		TYPE type;//当たったブロックのタイプ
	};

	//当たり判定フラグ
	struct CollisionFlag
	{
		bool X;//X軸
		bool Y_UP;//Y軸上
		bool Y_DOWN;//Y軸下
		bool Z;//Z軸
	};

	//======================================
	// 関数
	//======================================
	CBlock(int nPriority = static_cast<int>(Category::BLOCK));//コンストラクタ
	~CBlock() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Release() override;//解放処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CBlock* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, TYPE type);//生成処理
	virtual CBlock::CollisionFlag Collision(CollisionParam& aParam);//当たり判定
	WallState WallKick(CollisionParam& aParam);//壁キック処理

	//前のオブジェクト情報
	void SetPrevBlock(CBlock* pBlock) { m_pPrev = pBlock; }//設定
	CBlock* GetPrevBlock() { return m_pPrev; }//決定

	//次のオブジェクト情報
	void SetNextBlock(CBlock* pBlock) { m_pNext = pBlock; }//設定
	CBlock* GetNextBlock() { return m_pNext; }//取得

	//ブロックタイプ
	void SetBlockType(TYPE type) { m_Type = type; }//設定
	TYPE GetBlockType() { return m_Type; }//取得

	//垂直ベクトル
	D3DXVECTOR3 SEGMENT_XY(float StartX, float StartY, float EndX, float EndY);//XY間の垂直ベクトル計算処理
	D3DXVECTOR3 SEGMENT_XZ(float StartX, float StartZ, float EndX, float EndZ);//XZ間の垂直ベクトル計算処理
	D3DXVECTOR3 SEGMENT_YZ(float StartY, float StartZ, float EndY, float EndZ);//YZ間の垂直ベクトル計算処理
	D3DXVECTOR3 GetNormal() { return m_Normal; }

private:
	//======================================
	// 列挙型定義
	//======================================

	//触れた壁の線上
	enum class WallLine
	{
		NONE = 0,
		XY,//XY線上
		YZ,//YZ線上
	};

	//======================================
	// 関数
	//======================================
	void ReflectAngleCalculate(CollisionParam& aParam, WallLine Line, WallState& wallstate);
	
	//======================================
	// 変数
	//======================================
	const float MAX_KICKPOWER_WIDTH = 8.5f;//壁キックのX軸の強さ最大値
	const float MAX_KICKPOWER_HEIGHT = 75.0f;//壁キックのY軸の強さ最大値
	const float SLIDE_POWER = -8.0f;//壁ずりの重力の強さ
	static float m_fKickPowerWidth;//壁キックのX軸の強さ
	static float m_fKickPowerHeight;//壁キックのY軸の強さ
	CBlock* m_pPrev;//前のオブジェクト情報へのポインタ
	CBlock* m_pNext;//次のオブジェクト情報へのポインタ
	TYPE m_Type;//種類
	D3DXVECTOR3 m_Normal;//垂直ベクトル
};

#endif
