//===========================================================================================================================================================================================
//
// キーボード入力処理に関するヘッダーファイル
// Author;久保市篤武
//
//===========================================================================================================================================================================================
#ifndef _KEYBOARD_H_  //このマクロ定義がされなかったら
#define _KEYBOARD_H_  //2重インクルード防止のマクロ定義

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "input.h"//インプット

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CInputKeyboard : public CInput
{
public:
	//======================================
	// 関数
	//======================================
	CInputKeyboard();//コンストラクタ
	~CInputKeyboard();//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);//初期化処理
	void Uninit();//終了処理
	void Update();//更新処理
	bool GetPress(int nKey);//プレス情報取得
	bool GetTrigger(int nKey);//トリガー情報取得
	bool GetRepeat(int nKey, int nSpeed);//リピート情報取得

private:
	//======================================
	// 変数
	//======================================
	static int m_nCntKey;//長押し時間
	static const int MAX_KEY = 256;//キーの最大数
	BYTE m_aKeyState[MAX_KEY];//プレス情報
	BYTE m_aKeyStateTrigger[MAX_KEY];//トリガー情報
};

#endif
