//==============================================================================================================================================
//
// �u���b�N�Ɋւ��鏈���̃w�b�_�[�t�@�C��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================
#ifndef _BLOCK_H_ //���̃}�N����`������Ȃ�������
#define _BLOCK_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "objectX.h"

//===========================================================================================================
// �N���X��`
//===========================================================================================================
class CBlock : public CObjectX
{
public:
	//======================================
	// �񋓌^��`
	//======================================

	//�^�C�v
	enum class TYPE
	{
		NONE = 0,
		NORMAL,//�m�[�}��
		SLONE,//�⓹
		BOSS,//�{�X
		MAX
	};

	//�ǂ̔���
	enum class WallState
	{
		NONE = 0,
		SLIDE,//�ǂ���
		KICK,//�ǃL�b�N
		CLIFF,//�R�͂܂�
		MAX
	};

	//======================================
	// �\���̒�`
	//======================================

	//�����蔻��p�p�����[�^
	struct CollisionParam
	{
		D3DXVECTOR3 pos;//���W
		D3DXVECTOR3 oldpos;//�X�V�O�̍��W
		D3DXVECTOR3 move;//�ړ���
		D3DXVECTOR3 size;//�T�C�Y
		D3DXVECTOR3 rot;//�p�x
		TYPE type;//���������u���b�N�̃^�C�v
	};

	//�����蔻��t���O
	struct CollisionFlag
	{
		bool X;//X��
		bool Y_UP;//Y����
		bool Y_DOWN;//Y����
		bool Z;//Z��
	};

	//======================================
	// �֐�
	//======================================
	CBlock(int nPriority = static_cast<int>(Category::BLOCK));//�R���X�g���N�^
	~CBlock() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Release() override;//�������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBlock* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, TYPE type);//��������
	virtual CBlock::CollisionFlag Collision(CollisionParam& aParam);//�����蔻��
	WallState WallKick(CollisionParam& aParam);//�ǃL�b�N����

	//�O�̃I�u�W�F�N�g���
	void SetPrevBlock(CBlock* pBlock) { m_pPrev = pBlock; }//�ݒ�
	CBlock* GetPrevBlock() { return m_pPrev; }//����

	//���̃I�u�W�F�N�g���
	void SetNextBlock(CBlock* pBlock) { m_pNext = pBlock; }//�ݒ�
	CBlock* GetNextBlock() { return m_pNext; }//�擾

	//�u���b�N�^�C�v
	void SetBlockType(TYPE type) { m_Type = type; }//�ݒ�
	TYPE GetBlockType() { return m_Type; }//�擾

	//�����x�N�g��
	D3DXVECTOR3 SEGMENT_XY(float StartX, float StartY, float EndX, float EndY);//XY�Ԃ̐����x�N�g���v�Z����
	D3DXVECTOR3 SEGMENT_XZ(float StartX, float StartZ, float EndX, float EndZ);//XZ�Ԃ̐����x�N�g���v�Z����
	D3DXVECTOR3 SEGMENT_YZ(float StartY, float StartZ, float EndY, float EndZ);//YZ�Ԃ̐����x�N�g���v�Z����
	D3DXVECTOR3 GetNormal() { return m_Normal; }

private:
	//======================================
	// �񋓌^��`
	//======================================

	//�G�ꂽ�ǂ̐���
	enum class WallLine
	{
		NONE = 0,
		XY,//XY����
		YZ,//YZ����
	};

	//======================================
	// �֐�
	//======================================
	void ReflectAngleCalculate(CollisionParam& aParam, WallLine Line, WallState& wallstate);
	
	//======================================
	// �ϐ�
	//======================================
	const float MAX_KICKPOWER_WIDTH = 8.5f;//�ǃL�b�N��X���̋����ő�l
	const float MAX_KICKPOWER_HEIGHT = 75.0f;//�ǃL�b�N��Y���̋����ő�l
	const float SLIDE_POWER = -8.0f;//�ǂ���̏d�͂̋���
	static float m_fKickPowerWidth;//�ǃL�b�N��X���̋���
	static float m_fKickPowerHeight;//�ǃL�b�N��Y���̋���
	CBlock* m_pPrev;//�O�̃I�u�W�F�N�g���ւ̃|�C���^
	CBlock* m_pNext;//���̃I�u�W�F�N�g���ւ̃|�C���^
	TYPE m_Type;//���
	D3DXVECTOR3 m_Normal;//�����x�N�g��
};

#endif
