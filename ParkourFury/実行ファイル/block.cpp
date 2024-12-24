//==============================================================================================================================================
//
// �u���b�N�Ɋւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "block.h"

//===========================================================================================================
// �ÓI�����o�ϐ�������
//===========================================================================================================
float CBlock::m_fKickPowerWidth = 30.0f;
float CBlock::m_fKickPowerHeight = 7.0f;

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	//�����o�ϐ�������
	m_pPrev = nullptr;//�O�̃u���b�N���
	m_pNext = nullptr;//���̃u���b�N���
	m_Type = CBlock::TYPE::NONE;//�u���b�N�^�C�v
	m_Normal = { 0.0f, 0.0f, 0.0f };//�����x�N�g��
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CBlock::~CBlock()
{
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CBlock::Init()
{
	//���f������
	CXfile* pModel = CXfile::GetInstance();//�C���X�^���X���擾
	BindModel(pModel->GetAddress(CTag::TAG::BLOCK, static_cast<int>(m_Type)));//�ݒ�
	SetSize();//�T�C�Y�ݒ�

	//���N���X����������
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CBlock::Uninit()
{
	//���N���X�I������
	CObjectX::Uninit();
}

//===========================================================================================================
// �������
//===========================================================================================================
void CBlock::Release()
{
	//���N���X�������
	CObjectX::Release();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CBlock::Update()
{
	//���N���X�X�V����
	CObjectX::Update();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CBlock::Draw()
{
	//�G�f�B�^���[�h�̏ꍇ
	if (CManager::GetInstance()->GetScene()->GetSceneState() == CScene::SCENE::EDIT_3D)
	{//�`�悹���ɏ����𔲂���
		return;
	}

	//���N���X�`�揈��
	CObjectX::Draw();
}

//===========================================================================================================
// �����蔻��
//===========================================================================================================
CBlock::CollisionFlag CBlock::Collision(CollisionParam& aParam)
{
	//�����擾
	CollisionFlag aFlag = {};//�����蔻��t���O�\����
	D3DXVECTOR3 Pos = GetPos();//���W
	D3DXVECTOR3 Size = GetSize();//�T�C�Y

	//=======================================================================
	// Y��
	//=======================================================================

	//�㑤�̔���
	if (aParam.pos.y < Pos.y + Size.y * 0.5f
		&& aParam.oldpos.y >= Pos.y + Size.y * 0.5f)
	{
		//XZ�Ԃ͈͓̔��ɂ���ꍇ
		if ((aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
			&& aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f)
			&& (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
				&& aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f))
		{
			//���W���C��
			aParam.pos.y = Pos.y + Size.y * 0.5f;

			//Y���̈ړ��ʂ����Z�b�g
			aParam.move.y = 0.0f;

			//Y���̏㑤�̓����蔻���true�ɂ���
			aFlag.Y_UP = true;

			//�������g�̃^�C�v��ۑ�
			aParam.type = m_Type;
		}
	}

	//�����̔���
	if (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
		&& aParam.oldpos.y + aParam.size.y <= Pos.y - Size.y * 0.5f)
	{
		//XZ�Ԃ͈͓̔��ɂ���ꍇ
		if ((aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
			&& aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f)
			&& (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
				&& aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f))
		{
			//���W���C��
			aParam.pos.y = Pos.y - Size.y * 0.5f - aParam.size.y;

			//Y���̈ړ��ʂ����Z�b�g
			aParam.move.y = 0.0f;

			//Y���̉����̓����蔻���true�ɂ���
			aFlag.Y_DOWN = true;

			//�������g�̃^�C�v��ۑ�
			aParam.type = m_Type;
		}
	}

	//=======================================================================
	// X��
	//=======================================================================

	//�����̔���
	if (aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
		&& aParam.oldpos.x + aParam.size.x * 0.5f <= Pos.x - Size.x * 0.5f)
	{
		//YZ�Ԃ͈͓̔��ɂ���ꍇ
		if ((aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
			&& aParam.pos.y < Pos.y + Size.y * 0.5f)
			&& (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
			&& aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f))
		{
			//���W���C��
			aParam.pos.x = Pos.x - Size.x * 0.5f - aParam.size.x * 0.5f;

			//X���̓����蔻��
			aFlag.X = true;

			//�������g�̃^�C�v��ۑ�
			aParam.type = m_Type;
		}
	}

	//�E���̔���
	if (aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f
		&& aParam.oldpos.x - aParam.size.x * 0.5f >= Pos.x + Size.x * 0.5f)
	{
		//YZ�Ԃ͈͓̔��ɂ���ꍇ
		if ((aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
			&& aParam.pos.y < Pos.y + Size.y * 0.5f)
			&& (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
			&& aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f))
		{
			//���W���C��
			aParam.pos.x = Pos.x + Size.x * 0.5f + aParam.size.x * 0.5f;

			//X���̓����蔻���true�ɂ���
			aFlag.X = true;

			//�������g�̃^�C�v��ۑ�
			aParam.type = m_Type;
		}
	}

	//=======================================================================
	// Z��
	//=======================================================================

	//��O���̔���
	if (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
		&& aParam.oldpos.z + aParam.size.z * 0.5f <= Pos.z - Size.z * 0.5f)
	{
		//XY�Ԃ͈͓̔��ɂ���ꍇ
		if ((aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
			&& aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f)
			&& (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
			&& aParam.pos.y < Pos.y + Size.y * 0.5f))
		{
			//���W���C��
			aParam.pos.z = Pos.z - Size.z * 0.5f - aParam.size.z * 0.5f;

			//Z���̓����蔻���true�ɂ���
			aFlag.Z = true;

			//�������g�̃^�C�v��ۑ�
			aParam.type = m_Type;
		}
	}

	//�����̔���
	if (aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f
		&& aParam.oldpos.z - aParam.size.z * 0.5f >= Pos.z + Size.z * 0.5f)
	{
		//XY�Ԃ͈͓̔��ɂ���ꍇ
		if ((aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
			&& aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f)
			&& (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f))
		{
			//���W���C��
			aParam.pos.z = Pos.z + Size.z * 0.5f + aParam.size.z * 0.5f;

			//Z���̓����蔻���true�ɂ���
			aFlag.Z = true;

			//�������g�̃^�C�v��ۑ�
			aParam.type = m_Type;
		}
	}

	return aFlag;
}

//===========================================================================================================
// �ǃL�b�N����
//===========================================================================================================
CBlock::WallState CBlock::WallKick(CBlock::CollisionParam& aParam)
{
	//�⓹�̏ꍇ
	if (m_Type == TYPE::SLONE)
	{
		//�������I��
		return WallState::NONE;
	}

	//���[�J���ϐ��錾
	CManager* pManager = CManager::GetInstance();//�}�l�[�W���[�ւ̃|�C���^
	WallState wallstate = WallState::NONE;//�ǂ̐ڐG���
	D3DXVECTOR3 Pos = GetPos();//�ʒu���
	D3DXVECTOR3 Size = GetSize();//�T�C�Y���
	bool bCollision = false;//�ǂƂ̐ڐG����t���O
	bool bCliff = false;//�R�͂܂蔻��
	WallLine Line = WallLine::NONE;

	//�ړ��L�[��������Ă���ꍇ
	if (pManager->GetKeyboard()->GetPress(DIK_D)
		|| pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY::JOYKEY_RIGHT)
		|| pManager->GetKeyboard()->GetPress(DIK_A)
		|| pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY::JOYKEY_LEFT))
	{
		//�����̔���
		if ((aParam.pos.x + aParam.size.x * 0.5f >= Pos.x - Size.x * 0.5f
			&& aParam.oldpos.x + aParam.size.x * 0.5f <= Pos.x - Size.x * 0.5f)
			&& (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f)
			&& (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
				&& aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f))
		{
			//�u���b�N�̐����x�N�g�������߂�
			SEGMENT_XY(Pos.x, Pos.y - Size.y * 0.5f, Pos.x, Pos.y + Size.y * 0.5f);

			//�ڐG�����true�ɂ���
			bCollision = true;

			//�G�ꂽ�����XY�ɐݒ�
			Line = WallLine::XY;

			//�v���C���[�̒��_���u���b�N���������ꍇ
			if (aParam.pos.y + aParam.size.y >= Pos.y + Size.y * 0.5f - 10.0f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f - 10.0f)
			{
				//�R�͂܂蔻���true�ɂ���
				bCliff = true;

				//�J�����̊p�x���擾
				float fCamera_Rot_Y = pManager->GetCamera()->GetRot().y;

				//�p�x�̉��Z��
				float fAddRot_Y = 0.0f;

				//�J�����̊p�x�̒l�����̒l�̏ꍇ
				if (fCamera_Rot_Y >= 0.0f)
				{
					//���Z�ʂ�ݒ�
					fAddRot_Y =  -D3DX_PI * 0.5f;
				}
				//�J�����̊p�x�̒l�����̒l�̏ꍇ
				else
				{
					//���Z�ʂ�ݒ�
					fAddRot_Y = D3DX_PI * 0.5f;
				}

				//�p�x���E�����ɒ���
				aParam.rot.y = pManager->GetCamera()->GetRot().y + fAddRot_Y;
			}
		}

		//�E���̔���
		else if ((aParam.pos.x - aParam.size.x * 0.5f <= Pos.x + Size.x * 0.5f
			&& aParam.oldpos.x - aParam.size.x * 0.5f >= Pos.x + Size.x * 0.5f)
			&& (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f)
			&& (aParam.pos.z + aParam.size.z * 0.5f > Pos.z - Size.z * 0.5f
				&& aParam.pos.z - aParam.size.z * 0.5f < Pos.z + Size.z * 0.5f))
		{
			//�u���b�N�̐����x�N�g�������߂�
			SEGMENT_XY(Pos.x, Pos.y + Size.y * 0.5f, Pos.x, Pos.y - Size.y * 0.5f);

			//�ڐG�����true�ɂ���
			bCollision = true;

			//�G�ꂽ�����XY�ɐݒ�
			Line = WallLine::XY;

			//�v���C���[�̒��_���u���b�N���������ꍇ
			if (aParam.pos.y + aParam.size.y >= Pos.y + Size.y * 0.5f - 10.0f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f - 10.0f)
			{
				//�R�͂܂蔻���true�ɂ���
				bCliff = true;

				//�J�����̊p�x���擾
				float fCamera_Rot_Y = pManager->GetCamera()->GetRot().y;

				//�p�x�̉��Z��
				float fAddRot_Y = 0.0f;

				//�J�����̊p�x�̒l�����̒l�̏ꍇ
				if (fCamera_Rot_Y >= 0.0f)
				{
					//���Z�ʂ�ݒ�
					fAddRot_Y =  D3DX_PI * 0.5f;
				}
				//�J�����̊p�x�̒l�����̒l�̏ꍇ
				else
				{
					//���Z�ʂ�ݒ�
					fAddRot_Y = -D3DX_PI * 0.5f;
				}

				//�p�x���E�����ɒ���
				aParam.rot.y = pManager->GetCamera()->GetRot().y + fAddRot_Y;
			}
		}

		//��O���̔���
		else if ((aParam.pos.z + aParam.size.z * 0.5f >= Pos.z - Size.z * 0.5f
			&& aParam.oldpos.z + aParam.size.z * 0.5f <= Pos.z - Size.z * 0.5f)
			&& (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f)
			&& (aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
				&& aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f))
		{
			//�u���b�N�̐����x�N�g�������߂�
			SEGMENT_YZ(Pos.y - Size.y * 0.5f, Pos.z, Pos.y + Size.y * 0.5f, Pos.z);

			//�ڐG�����true�ɂ���
			bCollision = true;

			//�G�ꂽ�����YZ�ɐݒ�
			Line = WallLine::YZ;

			//�v���C���[�̒��_���u���b�N���������ꍇ
			if (aParam.pos.y + aParam.size.y >= Pos.y + Size.y * 0.5f - 10.0f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f - 10.0f)
			{
				//�R�͂܂蔻���true�ɂ���
				bCliff = true;

				//�J�����̊p�x���擾
				float fCamera_Rot_Y = pManager->GetCamera()->GetRot().y;

				//�p�x�̉��Z��
				float fAddRot_Y = 0.0f;

				//�J�����̊p�x�̒l�����̒l�̏ꍇ
				if (fCamera_Rot_Y >= 0.0f)
				{
					//���Z�ʂ�ݒ�
					fAddRot_Y = D3DX_PI * 0.5f;
				}
				//�J�����̊p�x�̒l�����̒l�̏ꍇ
				else
				{
					//���Z�ʂ�ݒ�
					fAddRot_Y = -D3DX_PI * 0.5f;
				}

				//�p�x���E�����ɒ���
				aParam.rot.y = pManager->GetCamera()->GetRot().y + fAddRot_Y;
			}
		}

		//�����̔���
		else if ((aParam.pos.z - aParam.size.z * 0.5f <= Pos.z + Size.z * 0.5f
			&& aParam.oldpos.z - aParam.size.z * 0.5f >= Pos.z + Size.z * 0.5f)
			&& (aParam.pos.y + aParam.size.y > Pos.y - Size.y * 0.5f
				&& aParam.pos.y < Pos.y + Size.y * 0.5f)
			&& (aParam.pos.x + aParam.size.x * 0.5f > Pos.x - Size.x * 0.5f
				&& aParam.pos.x - aParam.size.x * 0.5f < Pos.x + Size.x * 0.5f))
		{
			//�u���b�N�̐����x�N�g�������߂�
			SEGMENT_YZ(Pos.y + Size.y * 0.5f, Pos.z, Pos.y - Size.y * 0.5f, Pos.z);

			//�ڐG�����true�ɂ���
			bCollision = true;

			//�G�ꂽ�����YZ�ɐݒ�
			Line = WallLine::YZ;

			//�v���C���[�̒��_���u���b�N���������ꍇ
			if (abs((aParam.pos.y + aParam.size.y) - (Pos.y + Size.y * 0.5f)) <= 10.0f)
			{
				//�R�͂܂蔻���true�ɂ���
				bCliff = true;

				//�J�����̊p�x���擾
				float fCamera_Rot_Y = pManager->GetCamera()->GetRot().y;

				//�p�x�̉��Z��
				float fAddRot_Y = 0.0f;

				//�J�����̊p�x�̒l�����̒l�̏ꍇ
				if (fCamera_Rot_Y >= 0.0f)
				{
					//���Z�ʂ�ݒ�
					fAddRot_Y = -D3DX_PI * 0.5f;
				}
				//�J�����̊p�x�̒l�����̒l�̏ꍇ
				else
				{
					//���Z�ʂ�ݒ�
					fAddRot_Y = D3DX_PI * 0.5f;
				}

				//�p�x���E�����ɒ���
				aParam.rot.y = pManager->GetCamera()->GetRot().y + fAddRot_Y;
			}
		}
	}

	//�ڐG���肪true�̏ꍇ
	if (bCollision)
	{
		//���˃x�N�g���v�Z����
		ReflectAngleCalculate(aParam, Line, wallstate);
	}

	////�R�͂܂蔻�肪true�̏ꍇ
	//if (bCliff)
	//{
	//	//�R�͂܂��Ԃɐݒ�
	//	wallstate = WallState::NONE;

	//	//�ړ��ʂ�0�ɂ���
	//	aParam.move = { 0.0f, 0.0f, 0.0f };

	//	//�ʒu�𒲐�����
	//	aParam.pos.y = Pos.y + Size.y * 0.5f - aParam.size.y - 10.0f;
	//}

	return wallstate;
}

//===========================================================================================================
// ���˃x�N�g���v�Z����
//===========================================================================================================
#include "particle.h"
void CBlock::ReflectAngleCalculate(CollisionParam& aParam, WallLine Line, WallState& wallstate)
{
	//���[�J���ϐ��錾
	CManager* pManager = CManager::GetInstance();//�}�l�[�W���[�ւ̃|�C���^
	float fReflectAngle = 0.0f;//���˃x�N�g���̊p�x

	//�����x�N�g�������߂�
	D3DXVECTOR3 Direction = aParam.pos - aParam.oldpos;

	//�i�s�x�N�g���𐳋K��
	D3DXVec3Normalize(&Direction, &Direction);

	//�W�������߂�
	D3DXVECTOR3 Factor(-Direction.x * m_Normal.x, -Direction.y * m_Normal.y, -Direction.z * m_Normal.z);

	//�W���𐳋K��
	D3DXVec3Normalize(&Factor, &Factor);

	//���s�x�N�g�������߂�
	D3DXVECTOR3 Parallel(Direction.x + Factor.x * m_Normal.x, Direction.y + Factor.y * m_Normal.y, Direction.z + Factor.z * m_Normal.z);

	//���s�x�N�g���𐳋K��
	D3DXVec3Normalize(&Parallel, &Parallel);

	//���˃x�N�g�������߂�
	D3DXVECTOR3 Reflect(Direction.x + 2.0f * Factor.x * m_Normal.x, Direction.y + 2.0f * Factor.y * m_Normal.y, Direction.z + 2.0f * Factor.z * m_Normal.z);

	//���˃x�N�g���𐳋K��
	D3DXVec3Normalize(&Reflect, &Reflect);

	//�W�����v�{�^���������ꂽ�ꍇ
	if (pManager->GetKeyboard()->GetTrigger(DIK_SPACE)
		|| pManager->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY::JOYKEY_A))
	{
		//���˂̃p���[��ݒ�
		m_fKickPowerWidth = MAX_KICKPOWER_WIDTH;
		m_fKickPowerHeight = MAX_KICKPOWER_HEIGHT;

		//�ǃL�b�N��Ԃɐݒ�
		wallstate = WallState::KICK;

		//�p�[�e�B�N������
		for (int nCnt = 0; nCnt < 30; nCnt++)
		{
			//�����_���ɃJ���[��ݒ�
			float fR = static_cast<float>(rand() % 10 + 1) * 0.1f;
			float fG = static_cast<float>(rand() % 10 + 1) * 0.1f;
			float fB = static_cast<float>(rand() % 10 + 1) * 0.1f;

			CParticle::Create(CParticle::TYPE::NORMAL, aParam.pos, { 25.0f, 25.0f, 0.0f }, 20, { fR, fG, fB, 1.0f });
		}
	}
	else
	{
		//���˂̃p���[��1�ɐݒ�
		m_fKickPowerWidth = 1.0f;
		m_fKickPowerHeight = SLIDE_POWER;

		//�ǂ����Ԃɐݒ�
		wallstate = WallState::SLIDE;
	}

	//�G�ꂽ���オXY�̏ꍇ
	if (Line == WallLine::XY)
	{
		//���˃x�N�g����X�����ɑ΂��āA�p�x��ύX
		if (Reflect.x < 0.0f)
		{
			fReflectAngle = 1.78f;
		}
		else
		{
			fReflectAngle = -1.78f;
		}

		//�p�x�ɍ��킹�Ĉړ��ʂ�ύX
		aParam.move = { sinf(fReflectAngle + D3DX_PI) * m_fKickPowerWidth, cosf(fReflectAngle + D3DX_PI) * m_fKickPowerHeight, 0.0f };
	}
	//�G�ꂽ���オYZ�̏ꍇ
	else if (Line == WallLine::YZ)
	{
		//���˃x�N�g����X�����ɑ΂��āA�p�x��ύX
		if (Reflect.z < 0.0f)
		{
			fReflectAngle = 1.78f;
		}
		else
		{
			fReflectAngle = -1.78f;
		}

		//�p�x�ɍ��킹�Ĉړ��ʂ�ύX
		aParam.move = { 0.0f, cosf(fReflectAngle + D3DX_PI) * m_fKickPowerHeight, sinf(fReflectAngle + D3DX_PI) * m_fKickPowerWidth };
	}
}

//===========================================================================================================
// XY�Ԃ̐����x�N�g���v�Z����
//===========================================================================================================
D3DXVECTOR3 CBlock::SEGMENT_XY(float StartX, float StartY, float EndX, float EndY)
{
	//�����x�N�g�������߂�
	D3DXVECTOR3 Start(StartX, StartY, 0.0f);
	D3DXVECTOR3 End(EndX, EndY, 0.0f);

	D3DXVECTOR3 r = End - Start;

	m_Normal.x = -r.y;
	m_Normal.y = r.x;

	//�x�N�g���𐳋K��
	D3DXVec3Normalize(&m_Normal, &m_Normal);

	return m_Normal;
}

//===========================================================================================================
// XZ�Ԃ̐����x�N�g���v�Z����
//===========================================================================================================
D3DXVECTOR3 CBlock::SEGMENT_XZ(float StartX, float StartZ, float EndX, float EndZ)
{
	//�����x�N�g�������߂�
	D3DXVECTOR3 Start(StartX, 0.0f, StartZ);
	D3DXVECTOR3 End(EndX, 0.0f, EndZ);

	D3DXVECTOR3 r = End - Start;

	m_Normal.x = -r.z;
	m_Normal.z = r.x;

	//�x�N�g���𐳋K��
	D3DXVec3Normalize(&m_Normal, &m_Normal);

	return m_Normal;
}

//===========================================================================================================
// YZ�Ԃ̐����x�N�g���v�Z����
//===========================================================================================================
D3DXVECTOR3 CBlock::SEGMENT_YZ(float StartY, float StartZ, float EndY, float EndZ)
{
	//�����x�N�g�������߂�
	D3DXVECTOR3 Start(0.0f, StartY, StartZ);
	D3DXVECTOR3 End(0.0f, EndY, EndZ);

	D3DXVECTOR3 r = End - Start;

	m_Normal.z = -r.y;
	m_Normal.y = r.z;

	//�x�N�g���𐳋K��
	D3DXVec3Normalize(&m_Normal, &m_Normal);

	return m_Normal;
}

//===========================================================================================================
// ��������
//===========================================================================================================
#include "slone.h"
#include "bossblock.h"
#include "blockmanager.h"
CBlock* CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, TYPE type)
{
	//�^�C�v�ɉ����ă������𓮓I�m��
	CBlock* pBlock = nullptr;

	switch (type)
	{
		//�m�[�}��
	case TYPE::NORMAL:
		pBlock = NEW CBlock(static_cast<int>(Category::BLOCK));
		break;

		//�⓹
	case TYPE::SLONE:
		pBlock = NEW CSlone();
		break;

		//�{�X�u���b�N
	case TYPE::BOSS:
		pBlock = NEW CBossBlock();

	default:
		break;
	}

	//�u���b�N��񂪑��݂���ꍇ
	if (pBlock != nullptr)
	{
		//�p�����[�^�ݒ�
		pBlock->SetPos(pos);//���W
		pBlock->SetRot(rot);//�p�x
		pBlock->SetScale(scale);//�g�嗦
		pBlock->SetBlockType(type);//�u���b�N�^�C�v�ݒ�

		//����������
		pBlock->Init();

		//�}�l�[�W���[�o�^����
		CManager::GetInstance()->GetScene()->GetBlockManager()->Regist(pBlock);
	}

	return pBlock;
}
