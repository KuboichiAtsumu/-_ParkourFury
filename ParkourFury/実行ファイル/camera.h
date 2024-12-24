#pragma once
//==============================================================================================================================================
//
// カメラに関する処理のヘッダーファイル
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _CAMERA_H_ //このマクロ定義がされなかったら
#define _CAMERA_H_ //2重インクルード防止のマクロ定義

//===========================================================================================================
// ヘッダーインクルード
//===========================================================================================================
#include "main.h"

//===========================================================================================================
// クラス定義
//===========================================================================================================
class CCamera
{
public:
	//======================================
	// 列挙型定義
	//======================================

	//状態
	enum class STATE
	{
		NONE = 0,//停止
		LEFTTURN,//左回転
		RIGHTTURN,//右回転
		LOOP_TURN,//ループターン
		MAX
	};

	//======================================
	// 関数
	//======================================
	CCamera();//コンストラクタ
	~CCamera();//デストラクタ
	HRESULT Init();//初期化処理
	void Uninit();//終了処理
	void Update();//更新処理
	void RotationStage();//ステージカメラ回転処理
	void SetCamera();//カメラの設定

	//情報の設定
	void SetPosV(D3DXVECTOR3 pos) { m_posV = pos; }//視点
	void SetPosR(D3DXVECTOR3 pos) { m_posR = pos; }//注視点
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }//角度
	void SetState(STATE state);//状態

	//揺れの情報
	void SetShake(int nFrame, int nShake)
	{
		m_nShakeFrame = nFrame;//揺れるフレーム数
		m_nMaxNumShake = nShake;//振れの量
	}

	//視点と注視点のリセット
	void Reset()
	{
		m_posV = FirstPosV;//視点
		m_posR = { 0.0f, 0.0f, 0.0f };//注視点
		m_rot = { 0.0f, 0.0f, 0.0f };//角度
	}

	//情報の取得
	D3DXVECTOR3 GetRot() { return m_rot; }//角度
	D3DXVECTOR3 GetPosR() { return m_posR; }//注視点の座標
	float GetAddHeight() { return m_fAddHeight; }//視点の高さ加算量

	//======================================
	// 定数
	//======================================
	static inline const D3DXVECTOR3 FirstPosV = { 0.0f, 50.0f, -500.0f };

private:
	//======================================
	// 関数
	//======================================
	void Turn();//回転処理
	void Move();//移動処理
	void SetPosRArea();//エリアの中央に注視点を設定する処理
	void SetPosRPlayer();//プレイヤーに注視点を設定する処理

	//======================================
	// 定数
	//======================================
	static inline const D3DXVECTOR3 VecU = { 0.0f, 1.0f, 0.0f };
	const float ADJUST_POS_SPEED = 10.0f;//カメラ座標調整速度
	const float MAX_ROLL = 0.05f;//回転速度
	const float MAX_SPEED = 10.0f;//移動速度
	const float MAX_STAGEROTATION = 0.1f;//ステージカメラ回転速度
	const float TITLE_POSV_Y = 1000.0f;//タイトル時の高さ
	const float TITLE_DISTANCE = 3000.0f;//タイトル時の視点から注視点までの距離
	const float TITLE_TURN_SPEED = 0.005f;//タイトル画面回転速度
 
	//======================================
	// 変数
	//======================================
	STATE m_State;//状態
	D3DXVECTOR3 m_posV;//視点
	D3DXVECTOR3 m_TargetPosV;//目的の視点
	D3DXVECTOR3 m_posR;//注視点
	D3DXVECTOR3 m_TargetPosR;//目的の注視点
	D3DXVECTOR3 m_rot;//角度
	D3DXVECTOR3 m_TargetRot;//目標の角度
	D3DXMATRIX m_mtxProjection;//プロジェクション行列
	D3DXMATRIX m_mtxView;//ビュー行列
	int m_nShakeFrame;//揺れるフレーム数
	int m_nMaxNumShake;//揺れの量の最大値
	float m_fLength;//距離
	float m_fDistanceMag;//視点と注視点の距離倍率
	float m_fAddHeight;//視点の高さ加算量
	float m_fMoveRotY;//回転量
};

#endif
