#pragma once
//==============================================================================================================================================
//
// �J�����Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _CAMERA_H_ //���̃}�N����`������Ȃ�������
#define _CAMERA_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "main.h"

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CCamera
{
public:
	//======================================
	// �񋓌^��`
	//======================================

	//���
	enum class STATE
	{
		NONE = 0,//��~
		LEFTTURN,//����]
		RIGHTTURN,//�E��]
		LOOP_TURN,//���[�v�^�[��
		MAX
	};

	//======================================
	// �֐�
	//======================================
	CCamera();//�R���X�g���N�^
	~CCamera();//�f�X�g���N�^
	HRESULT Init();//����������
	void Uninit();//�I������
	void Update();//�X�V����
	void RotationStage();//�X�e�[�W�J������]����
	void SetCamera();//�J�����̐ݒ�

	//���̐ݒ�
	void SetPosV(D3DXVECTOR3 pos) { m_posV = pos; }//���_
	void SetPosR(D3DXVECTOR3 pos) { m_posR = pos; }//�����_
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }//�p�x
	void SetState(STATE state);//���

	//�h��̏��
	void SetShake(int nFrame, int nShake)
	{
		m_nShakeFrame = nFrame;//�h���t���[����
		m_nMaxNumShake = nShake;//�U��̗�
	}

	//���_�ƒ����_�̃��Z�b�g
	void Reset()
	{
		m_posV = FirstPosV;//���_
		m_posR = { 0.0f, 0.0f, 0.0f };//�����_
		m_rot = { 0.0f, 0.0f, 0.0f };//�p�x
	}

	//���̎擾
	D3DXVECTOR3 GetRot() { return m_rot; }//�p�x
	D3DXVECTOR3 GetPosR() { return m_posR; }//�����_�̍��W
	float GetAddHeight() { return m_fAddHeight; }//���_�̍������Z��

	//======================================
	// �萔
	//======================================
	static inline const D3DXVECTOR3 FirstPosV = { 0.0f, 50.0f, -500.0f };

private:
	//======================================
	// �֐�
	//======================================
	void Turn();//��]����
	void Move();//�ړ�����
	void SetPosRArea();//�G���A�̒����ɒ����_��ݒ肷�鏈��
	void SetPosRPlayer();//�v���C���[�ɒ����_��ݒ肷�鏈��

	//======================================
	// �萔
	//======================================
	static inline const D3DXVECTOR3 VecU = { 0.0f, 1.0f, 0.0f };
	const float ADJUST_POS_SPEED = 10.0f;//�J�������W�������x
	const float MAX_ROLL = 0.05f;//��]���x
	const float MAX_SPEED = 10.0f;//�ړ����x
	const float MAX_STAGEROTATION = 0.1f;//�X�e�[�W�J������]���x
	const float TITLE_POSV_Y = 1000.0f;//�^�C�g�����̍���
	const float TITLE_DISTANCE = 3000.0f;//�^�C�g�����̎��_���璍���_�܂ł̋���
	const float TITLE_TURN_SPEED = 0.005f;//�^�C�g����ʉ�]���x
 
	//======================================
	// �ϐ�
	//======================================
	STATE m_State;//���
	D3DXVECTOR3 m_posV;//���_
	D3DXVECTOR3 m_TargetPosV;//�ړI�̎��_
	D3DXVECTOR3 m_posR;//�����_
	D3DXVECTOR3 m_TargetPosR;//�ړI�̒����_
	D3DXVECTOR3 m_rot;//�p�x
	D3DXVECTOR3 m_TargetRot;//�ڕW�̊p�x
	D3DXMATRIX m_mtxProjection;//�v���W�F�N�V�����s��
	D3DXMATRIX m_mtxView;//�r���[�s��
	int m_nShakeFrame;//�h���t���[����
	int m_nMaxNumShake;//�h��̗ʂ̍ő�l
	float m_fLength;//����
	float m_fDistanceMag;//���_�ƒ����_�̋����{��
	float m_fAddHeight;//���_�̍������Z��
	float m_fMoveRotY;//��]��
};

#endif
