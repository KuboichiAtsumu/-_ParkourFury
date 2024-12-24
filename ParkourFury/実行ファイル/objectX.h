//==============================================================================================================================================
//
// 3D�I�u�W�F�N�g�Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _OBJECTX_H_ //���̃}�N����`������Ȃ�������
#define _OBJECTX_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "object3D.h"
#include "xfile.h"

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CObjectX : public CObject3D
{
public:
	//=============================================================
	// �񋓌^��`
	//=============================================================

	//���W�̐���
	enum class STAND_LINE
	{
		XY,
		YZ,
	};

	//======================================
	// �֐�
	//======================================
	CObjectX(int nPriority = 3);//�R���X�g���N�^
	~CObjectX() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Release() override;//�������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��

	//���f�����
	void BindModel(CXfile::ModelInfo* aModelInfo) { m_aModelInfo = *aModelInfo; }//�ݒ�
	CXfile::ModelInfo GetModelInfo() { return m_aModelInfo; }//�擾

	//�ŏ����_���
	void SetVtxMin(D3DXVECTOR3 vtxMin) { m_vtxMin = vtxMin; }//�ݒ�
	D3DXVECTOR3 GetVtxMin() { return m_vtxMin; }//�擾

	//�ő咸�_���
	void SetVtxMax(D3DXVECTOR3 vtxMax) { m_vtxMax = vtxMax; }//�ݒ�
	D3DXVECTOR3 GetVtxMax() { return m_vtxMax; }//�擾

	//�T�C�Y���
	void SetSize();//�ݒ�
	void SetUpdateSize(D3DXVECTOR3 size) { m_Size = size; }//�X�V���ꂽ�T�C�Y����ݒ�
	D3DXVECTOR3 GetSize() { return m_Size; }//�擾

	//�Ίp���̒���
	void SetLength(float fLength) { m_fLength = fLength; }//�ݒ�

	//�Ίp���̊p�x
	void SetAngle(float fAngle) { m_fAngle = fAngle; }//�ݒ�

	//�g�嗦���
	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; }//�ݒ�
	D3DXVECTOR3 GetScale() { return m_Scale; }//�擾

	//���W�̐���
	STAND_LINE GetStandLine() { return m_StandLine; }//�擾

private:
	//======================================
	// �֐�
	//======================================
	void SetStandLine();//���W�̐���̐ݒ�

	//======================================
	// �ϐ�
	//======================================
	CXfile::ModelInfo m_aModelInfo;//�e���f�����
	D3DXVECTOR3 m_vtxMin;//�ŏ����_���W
	D3DXVECTOR3 m_vtxMax;//�ő咸�_���W
	D3DXVECTOR3 m_Size;//�T�C�Y
	D3DXVECTOR3 m_Scale;//�g�嗦
	STAND_LINE m_StandLine;//���W�̐���
	float m_fLength;//�Ίp���̒���
	float m_fAngle;//�Ίp���̊p�x
};

#endif