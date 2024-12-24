//==============================================================================================================================================
//
// メイン処理に関するヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _MAIN_H_ //このマクロ定義がされなかったら
#define _MAIN_H_ //2重インクルード防止のマクロ定義

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CProcess final
{
public:
	//======================================
	// 関数
	//======================================
	CProcess();//コンストラクタ
	~CProcess();//デストラクタ
	static void ToggleFullscreen(HWND hWnd);//フルスクリーン処理

private:
	//======================================
	// 変数
	//======================================
	static RECT m_windowRect;//ウィンドウ切り替え用変数
	static bool m_isFullscreen;//ウィンドウ切り替え用フラグ
};

#endif
