//==============================================================================================================================================
//
// �J�����̏���
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "camera.h"
#include "manager.h"

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CCamera::CCamera() :  
	m_State(STATE::NONE),
	m_rot(0.0f,0.0f,0.0f),
	m_TargetRot(0.0f,0.0f,0.0f),
	m_posV(FirstPosV),
	m_posR(0.0f,70.0f,0.0f),
	m_nShakeFrame(0),
	m_nMaxNumShake(0),
	m_fLength(sqrtf(powf(m_posV.y, 2.0f) + powf(m_posV.z, 2.0f))),
	m_fDistanceMag(1.0f),
	m_fAddHeight(0.0f),
	m_fMoveRotY(0.0f)
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CCamera::~CCamera()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CCamera::Init()
{
	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CCamera::Uninit()
{
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
#include "game.h"
void CCamera::Update()
{
	//�V�[���̏����擾
	CScene* pScene = CManager::GetInstance()->GetScene();

	//�G�f�B�^��
	if (pScene->GetSceneState() == CScene::SCENE::EDIT_3D)
	{
		//�ړ�����
		Move();

		//�����𔲂���
		return;
	}

	//�^�C�g���V�[���̏ꍇ
	if (pScene->GetMode() == CScene::MODE::MODE_TITLE && 
		pScene->GetSceneState() == CScene::SCENE::GAME)
	{
		//���[�v�^�[����Ԃɂ���
		m_State = STATE::LOOP_TURN;

		//��]����
		Turn();

		return;
	}
	
	//�Q�[���V�[���̃C���X�^���X�擾
	CGame* pGame = CGame::GetInstance();

	//�v���C���[������̃G���A���ɂ���ꍇ
	if (pGame != nullptr &&
		pGame->GetArea() != CGame::GAME_AREA::NORMAL)
	{
		//�G���A�̒����ɒ����_��ݒ�
		SetPosRArea();
	}
	//�v���C���[���ʏ�X�e�[�W�ɂ���ꍇ
	else
	{
		//�v���C���[�̈ʒu�ɒ����_��ݒ�
		SetPosRPlayer();
	}
}

//===========================================================================================================
// �G���A�̒����ɒ����_��ݒ肷�鏈��
//===========================================================================================================
void CCamera::SetPosRArea()
{
	//���݂̃J�����̈ʒu����ړI�n�܂ł̋��������߂�
}

//===========================================================================================================
// �v���C���[�ɒ����_��ݒ肷�鏈��
//===========================================================================================================
#include "player.h"
void CCamera::SetPosRPlayer()
{
	//�v���C���[�J�e�S���[�̃I�u�W�F�N�g�����擾
	CObject* pFindObj = CObject::FindObject(CObject::Category::PLAYER);

	//�I�u�W�F�N�g��񂪑��݂���ꍇ
	if (pFindObj != nullptr)
	{
		//�v���C���[�N���X�Ƀ_�E���L���X�g
		CPlayer* pPlayer = CObject::DownCast<CPlayer, CObject>(pFindObj);

		//�_�E���L���X�g����
		if (pPlayer != nullptr)
		{
			//�����_�̍��W�̍X�V
			m_posR = pPlayer->GetPos();
			m_posR.y = pPlayer->GetPos().y + pPlayer->GetVtxMax().y;
		}
	}

	//��]���A�ڕW�̊p�x�ɓ��B���Ă��Ȃ��ꍇ
	if (m_State != STATE::NONE)
	{
		//�X�e�[�W�J������]����
		RotationStage();
	}

	//���_�̈ʒu�̍X�V
	m_posV.x = sinf(m_rot.y + D3DX_PI) * m_fLength + m_posR.x;
	m_posV.y = m_posR.y + FirstPosV.y;
	m_posV.z = cosf(m_rot.y + D3DX_PI) * m_fLength + m_posR.z;
}

//===========================================================================================================
// ��]����
//===========================================================================================================
void CCamera::Turn()
{
	//��]
	m_rot.y += TITLE_TURN_SPEED;

	//�p�x�␳
	CObject::CorrectionRot(m_rot.y);

	//���_�̈ʒu�̍X�V
	m_posV.x = sinf(m_rot.y + D3DX_PI) * TITLE_DISTANCE;
	m_posV.y = TITLE_POSV_Y;
	m_posV.z = cosf(m_rot.y + D3DX_PI) * TITLE_DISTANCE;
}

//===========================================================================================================
// �ړ�����
//===========================================================================================================
void CCamera::Move()
{
	//�G�f�B�^�p��Y���̊p�x���
	static float fRot_Y = 0.0f;

	//�}�E�X�̏����擾
	DIMOUSESTATE pMouse = CManager::GetInstance()->GetMouse()->Get();

	//���N���b�N�������Ă���ꍇ
	if (CManager::GetInstance()->GetMouse()->GetPress(static_cast<int>(CInputMouse::MOUSE::MOUSE_LEFT)))
	{
		//�}�E�X�̓����ɍ��킹�Ď��_����]����
		fRot_Y += pMouse.lX * 0.01f;

		//�p�x�␳
		CObject::CorrectionRot(fRot_Y);
	}
	//�z�C�[���������Ă���ꍇ
	else if (CManager::GetInstance()->GetMouse()->GetPress(static_cast<int>(CInputMouse::MOUSE::MOUSE_WHEEL)))
	{
		//���_�̍��������Z
		m_fAddHeight += pMouse.lY * 1.5f;
	}

	//�z�C�[���̓����ɍ��킹�ċ�����b��
	m_fDistanceMag += pMouse.lZ * 0.001f;

	//���_�̈ʒu�̍X�V
	m_posV.x = sinf(fRot_Y + D3DX_PI) * (m_fLength * m_fDistanceMag) + m_posR.x;
	m_posV.y = FirstPosV.y + m_fAddHeight;
	m_posV.z = cosf(fRot_Y + D3DX_PI) * (m_fLength * m_fDistanceMag) + m_posR.z;
}

//===========================================================================================================
// �X�e�[�W�J������]����
//===========================================================================================================
void CCamera::RotationStage()
{
	//��]������
	m_rot.y += m_fMoveRotY;

	//���݂̊p�x�ƖڕW�̊p�x�̐������قȂ�ꍇ
	if ((m_rot.y < 0.00f && m_TargetRot.y > 0.00f) || 
		(m_rot.y > 0.00f && m_TargetRot.y < 0.00f))
	{
		//�p�x�␳
		CObject::CorrectionRot(m_rot.y);
	}

	//�ڕW�̊p�x�𒴂��Ȃ��悤�ɒ���
	if ((m_rot.y < m_TargetRot.y && m_State == STATE::LEFTTURN) || 
		(m_rot.y > m_TargetRot.y && m_State == STATE::RIGHTTURN))
	{
		m_rot.y = m_TargetRot.y;

		//��Ԃ�߂�
		m_State = STATE::NONE;
	}
}

//===========================================================================================================
// �J�����̐ݒ�
//===========================================================================================================
void CCamera::SetCamera()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 adjust = { 0.0f, 0.0f, 0.0f };//�h��̗�

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, 
		D3DXToRadian(45.0f), 
		SCREEN_WIDTH / SCREEN_HEIGHT, 
		1.0f, 
		8000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�t���[������0�ȏ�̏ꍇ
	if (m_nShakeFrame > 0)
	{
		//�t���[����������
		m_nShakeFrame--;

		//�h��̗ʂ̍ő�l��1�ȏ�̏ꍇ
		if (m_nMaxNumShake >= 1)
		{
			//�h��̗ʂ�ݒ�
			adjust.x = static_cast<float>(rand() % (m_nMaxNumShake * 2) - m_nMaxNumShake);
			adjust.y = static_cast<float>(rand() % (m_nMaxNumShake * 2) - m_nMaxNumShake);
			adjust.z = static_cast<float>(rand() % (m_nMaxNumShake * 2) - m_nMaxNumShake);
		}
	}

	//�h��̗ʂ����Z�������_�ƒ����_�̒l��ۑ�
	D3DXVECTOR3 posV = m_posV + adjust;
	D3DXVECTOR3 posR = m_posR + adjust;

	//�r���[�}�g���b�N�X�̐���
	D3DXMatrixLookAtLH(&m_mtxView, &posV, &posR, &VecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//===========================================================================================================
// ��Ԃ̐ݒ�
//===========================================================================================================
void CCamera::SetState(STATE state)
{
	//��Ԑݒ�
	m_State = state;

	//��Ԃɍ��킹�ĖڕW�̊p�x�Ɖ�]�ʂ�ݒ�
	switch (m_State)
	{
		//�E��]
	case STATE::RIGHTTURN:
		//�ڕW�̊p�x��ݒ�
		m_TargetRot.y = m_rot.y + D3DX_PI * 0.5f;

		//��]�ʂ�ݒ�
		m_fMoveRotY = MAX_STAGEROTATION;
		break;

		//����]
	case STATE::LEFTTURN:
		//�ڕW�̊p�x��ݒ�
		m_TargetRot.y = m_rot.y - D3DX_PI * 0.5f;

		//��]�ʂ�ݒ�
		m_fMoveRotY = -MAX_STAGEROTATION;
		break;

	default:
		break;
	}

	//�p�x�␳
	CObject::CorrectionRot(m_TargetRot.y);
}