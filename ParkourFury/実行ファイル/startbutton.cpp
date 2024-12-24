//==============================================================================================================================================
//
// スタートボタンに関する処理
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "startbutton.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CStartButton::CStartButton() : 
	CUI{},
	m_state{ STATE::STAND_BY} ,
	m_bLightUp{ false }
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CStartButton::~CStartButton()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CStartButton::Init()
{
	//基底クラス初期化処理
	if (FAILED(CUI::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CStartButton::Uninit()
{
	//基底クラス終了処理
	CUI::Uninit();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CStartButton::Update()
{
	//基底クラス更新処理
	CUI::Update();

	//エディタ中
	if (CManager::GetInstance()->GetScene()->GetSceneState() != CScene::SCENE::GAME)
	{
		//処理を抜ける
		return;
	}

	//ローカル変数宣言
	D3DXCOLOR color = GetColor();//カラー情報

	//状態別処理
	switch (m_state)
	{
		//待機中
	case STAND_BY:
		//明るくなっている場合
		if (m_bLightUp)
		{
			color.a += STAND_SPEED;
		}
		//暗くなっている場合
		else
		{
			color.a -= STAND_SPEED;
		}
		break;

		//点滅中
	case BLINKING:
		//明るくなっている場合
		if (m_bLightUp)
		{
			color.a = 1.0f;
		}
		//暗くなっている場合
		else
		{
			color.a = 0.0f;
		}
		break;

	default:
		break;
	}

	//カラーのα値が最大・最小値に達した場合
	if (color.a <= 0.0f || color.a >= 1.0f)
	{
		//ライトアップフラグを切り替える
		m_bLightUp = m_bLightUp ? false : true;
	}

	//マネージャーのインスタンスを取得
	CManager* pManager = CManager::GetInstance();

	//Enterキーが押された場合
	//Aボタンが押された場合
	if (pManager->GetKeyboard()->GetTrigger(DIK_RETURN) || 
		pManager->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY::JOYKEY_A))
	{
		//点滅状態にする
		m_state = BLINKING;
	}

	//更新情報設定
	SetColor(color);//カラー情報
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CStartButton::Draw()
{
	//基底クラス描画処理
	CUI::Draw();
}
