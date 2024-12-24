//==============================================================================================================================================
//
// X�t�@�C���I�u�W�F�N�g�Ɋւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "objectX.h"

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CObjectX::CObjectX(int nPriority) : CObject3D(nPriority)
{
	//�����o�ϐ�������
	m_vtxMin = { 0.0f, 0.0f, 0.0f };//�ŏ����_���W
	m_vtxMax = { 0.0f, 0.0f, 0.0f };//�ő咸�_���W
	m_Size = { 0.0f, 0.0f, 0.0f };//�T�C�Y
	m_Scale = { 1.0f, 1.0f, 1.0f };//�g�嗦
	m_fLength = 0.0f;//�Ίp���̒���
	m_fAngle = 0.0f;//�Ίp���̊p�x
	m_StandLine = STAND_LINE::XY;//���W�̐���

	//���f����񏉊���
	m_aModelInfo.pMesh = nullptr;
	m_aModelInfo.pBuffMat = nullptr;
	m_aModelInfo.dwNumMat = 0;
	m_aModelInfo.Diffuse.clear();
	m_aModelInfo.FirstDiffuse.clear();
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CObjectX::~CObjectX()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CObjectX::Init()
{
	//�I�u�W�F�N�g����������
	if (FAILED(CObject::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CObjectX::Uninit()
{
	//3D�I�u�W�F�N�g�I������
	CObject3D::Uninit();
}

//===========================================================================================================
// �������
//===========================================================================================================
void CObjectX::Release()
{
	//3D�I�u�W�F�N�g�������
	CObject3D::Release();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CObjectX::Update()
{
	//�p�x�ɍ��킹�čő�E�ŏ��̒��_���W���X�V
	m_vtxMin.x = GetPos().x + sinf(GetRot().y - (D3DX_PI - m_fAngle)) * m_fLength;//X���W�̍ŏ��l
	m_vtxMin.z = GetPos().z + cosf(GetRot().y + m_fAngle) * m_fLength;//Z���W�̍ŏ��l
	m_vtxMax.x = GetPos().x + sinf(GetRot().y + m_fAngle) * m_fLength;//X���W�̍ő�l
	m_vtxMax.z = GetPos().z + cosf(GetRot().y - (D3DX_PI - m_fAngle)) * m_fLength;//Z���W�̍ő�l

	//�X�V���ꂽ���_���W�ɉ����ăT�C�Y���X�V
	m_Size =
	{
		abs(m_vtxMax.x - m_vtxMin.x),//x��
		abs(m_vtxMax.y - m_vtxMin.y) * m_Scale.y,//y��
		abs(m_vtxMax.z - m_vtxMin.z)//z��
	};

	//���W�̐���̐ݒ�
	SetStandLine();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CObjectX::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���̃f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X���
	LPDIRECT3DTEXTURE9 pTexture = GetTexture();//�e�N�X�`�����
	D3DXVECTOR3 Pos = GetPos();//���W���
	D3DXVECTOR3 Rot = GetRot();//�p�x���

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	//�p�x�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Rot.y, Rot.x, Rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//���W�𔽉f
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//�@���̒�����1�ɂ���B
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	if (m_aModelInfo.pBuffMat != nullptr)
	{
		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_aModelInfo.pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_aModelInfo.dwNumMat; nCntMat++)
		{
			//�F�����ݒ�
			pMat->MatD3D.Diffuse = m_aModelInfo.Diffuse[nCntMat];

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture);

			//���f���̕`��
			m_aModelInfo.pMesh->DrawSubset(nCntMat);
		}
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===========================================================================================================
// �����Ă������̐ݒ菈��
//===========================================================================================================
void CObjectX::SetStandLine()
{
	//���W�����擾
	D3DXVECTOR3 pos = GetPos();

	//Z���̐���ɂ���ꍇ
	if (pos.x > CManager::VTXMIN_FIELD.x && pos.x < CManager::VTXMAX_FIELD.x)
	{
		//�����Ă�������XY�ɐݒ�
		m_StandLine = STAND_LINE::XY;
	}
	//X���̐���ɂ���ꍇ
	else if (pos.z > CManager::VTXMIN_FIELD.z && pos.z < CManager::VTXMAX_FIELD.z)
	{
		//�����Ă�������YZ�ɐݒ�
		m_StandLine = STAND_LINE::YZ;
	}
}

////===========================================================================================================
//// OBB�����蔻��
////===========================================================================================================
//bool CObjectX::CollisionOBB(OBB a, OBB b)
//{
//	const float EPSILON = 0.0f;
//
//	float R[3][3], AbsR[3][3];
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			R[i][j] = D3DXVec3Dot(&a.DirectionVec[i], &b.DirectionVec[j]);
//			AbsR[i][j] = fabsf(R[i][j]) + EPSILON;
//		}
//	}
//
//	D3DXVECTOR3 t = b.center - a.center;
//	t = D3DXVECTOR3(D3DXVec3Dot(&t, &a.DirectionVec[0]), D3DXVec3Dot(&t, &a.DirectionVec[1]), D3DXVec3Dot(&t, &a.DirectionVec[2]));
//
//	//��L=A0, L=A1, L=A2����
//	float ra, rb;
//
//	for (int i = 0; i < 3; i++)
//	{
//		ra = a.Coordinate_Axes[i];
//		rb = b.Coordinate_Axes[0] * AbsR[i][0] + b.Coordinate_Axes[1] * AbsR[i][1] + b.Coordinate_Axes[2] * AbsR[i][2];
//		if (fabsf(t[i]) > ra + rb)
//		{
//			return true;
//		}
//	}
//	//��L=B0, L=B1, L=B2����
//	for (int i = 0; i < 3; i++)
//	{
//		ra = a.Coordinate_Axes[0] * AbsR[0][i] + a.Coordinate_Axes[1] * AbsR[1][i] + a.Coordinate_Axes[2] * AbsR[2][i];
//		rb = b.Coordinate_Axes[i];
//		if (fabsf(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb)
//		{
//			return true;
//		}
//	}
//
//	//��L=A0 X B0����
//	ra = a.Coordinate_Axes[1] * AbsR[2][0] + a.Coordinate_Axes[2] * AbsR[1][0];
//	rb = b.Coordinate_Axes[1] * AbsR[0][2] + b.Coordinate_Axes[2] * AbsR[0][1];
//	if (fabsf(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb)
//	{
//		return true;
//	}
//
//	//��L=A0 X B1����
//	ra = a.Coordinate_Axes[1] * AbsR[2][1] + a.Coordinate_Axes[2] * AbsR[1][1];
//	rb = b.Coordinate_Axes[0] * AbsR[0][2] + b.Coordinate_Axes[2] * AbsR[0][0];
//	if (fabsf(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb)
//	{
//		return true;
//	}
//
//	//��L=A0 X B2����
//	ra = a.Coordinate_Axes[1] * AbsR[2][2] + a.Coordinate_Axes[2] * AbsR[1][2];
//	rb = b.Coordinate_Axes[0] * AbsR[0][1] + b.Coordinate_Axes[1] * AbsR[0][0];
//	if (fabsf(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb)
//	{
//		return true;
//	}
//
//	//��L=A1 X B0����
//	ra = a.Coordinate_Axes[0] * AbsR[2][0] + a.Coordinate_Axes[2] * AbsR[0][0];
//	rb = b.Coordinate_Axes[1] * AbsR[1][2] + b.Coordinate_Axes[2] * AbsR[1][1];
//	if (fabsf(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb)
//	{
//		return true;
//	}
//
//	//��L=A1 X B1����
//	ra = a.Coordinate_Axes[0] * AbsR[2][1] + a.Coordinate_Axes[2] * AbsR[0][1];
//	rb = b.Coordinate_Axes[0] * AbsR[1][2] + b.Coordinate_Axes[2] * AbsR[1][0];
//	if (fabsf(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb)
//	{
//		return true;
//	}
//
//	//��L=A1 X B2����
//	ra = a.Coordinate_Axes[0] * AbsR[2][2] + a.Coordinate_Axes[2] * AbsR[0][2];
//	rb = b.Coordinate_Axes[0] * AbsR[1][1] + b.Coordinate_Axes[1] * AbsR[1][0];
//	if (fabsf(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb)
//	{
//		return true;
//	}
//
//	//��L=A2 X B0����
//	ra = a.Coordinate_Axes[0] * AbsR[1][0] + a.Coordinate_Axes[1] * AbsR[0][0];
//	rb = b.Coordinate_Axes[1] * AbsR[2][2] + b.Coordinate_Axes[2] * AbsR[2][1];
//	if (fabsf(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb)
//	{
//		return true;
//	}
//
//	//��L=A2 X B1����
//	ra = a.Coordinate_Axes[0] * AbsR[1][1] + a.Coordinate_Axes[1] * AbsR[0][1];
//	rb = b.Coordinate_Axes[0] * AbsR[2][2] + b.Coordinate_Axes[2] * AbsR[2][0];
//	if (fabsf(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb)
//	{
//		return true;
//	}
//
//	//��L=A2 X B2����
//	ra = a.Coordinate_Axes[0] * AbsR[1][2] + a.Coordinate_Axes[1] * AbsR[0][2];
//	rb = b.Coordinate_Axes[0] * AbsR[2][1] + b.Coordinate_Axes[1] * AbsR[2][0];
//	if (fabsf(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb)
//	{
//		return true;
//	}
//
//	return false;
//}

//===========================================================================================================
// ���f���o�^
//===========================================================================================================
void CObjectX::SetSize()
{
	//���[�J���ϐ��錾
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	int nNumVtx = m_aModelInfo.pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	DWORD sizeFVF = D3DXGetFVFVertexSize(m_aModelInfo.pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_aModelInfo.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nIdxVtx = 0; nIdxVtx < nNumVtx; nIdxVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//���f���̍ŏ��l�ƍő�l���擾
		if (vtx.x < m_vtxMin.x)
		{//X���W�̍ŏ��l
			m_vtxMin.x = vtx.x;
		}
		if (vtx.y < m_vtxMin.y)
		{//Y���W�̍ŏ��l
			m_vtxMin.y = vtx.y;
		}
		if (vtx.z < m_vtxMin.z)
		{//Z���W�̍ŏ��l
			m_vtxMin.z = vtx.z;
		}
		if (vtx.x > m_vtxMax.x)
		{//X���W�̍ő�l
			m_vtxMax.x = vtx.x;
		}
		if (vtx.y > m_vtxMax.y)
		{//Y���W�̍ő�l
			m_vtxMax.y = vtx.y;
		}
		if (vtx.z > m_vtxMax.z)
		{//Z���W�̍ő�l
			m_vtxMax.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	//��ނ��Ƃ̃T�C�Y�����߂�
	m_Size =
	{
		(m_vtxMax.x - m_vtxMin.x) * m_Scale.x,//x��
		(m_vtxMax.y - m_vtxMin.y) * m_Scale.y,//y��
		(m_vtxMax.z - m_vtxMin.z) * m_Scale.z//z��
	};

	//�Ίp���̒��������߂�
	m_fLength = sqrtf(powf(m_Size.x, 2.0f) + powf(m_Size.z, 2.0f)) * 0.5f;

	//�Ίp���̊p�x�����߂�
	m_fAngle = atan2f(m_Size.x, m_Size.z);

	//���_�o�b�t�@�̃A�����b�N
	m_aModelInfo.pMesh->UnlockVertexBuffer();
}
