//==============================================================================================================================================
//
// UI�Ɋւ��鏈��
// Author : Atsumu Kuboichi
//
//==============================================================================================================================================

//===========================================================================================================
// �w�b�_�[�C���N���[�h
//===========================================================================================================
#include "UI.h"

//===========================================================================================================
// �ÓI�����o�ϐ�������
//===========================================================================================================
int CUI::m_nAll = 0;

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CUI::CUI(int nPriority) : 
	CObject2D{ nPriority },
	m_pPrev{ nullptr },
	m_pNext{ nullptr },
	m_Type{ TYPE::NONE },
	m_bEdit{ true }

{
	//�C���f�b�N�X�ݒ�
	m_nIdx = m_nAll;

	//�������Z
	m_nAll++;
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CUI::~CUI()
{
	//�������Z
	m_nAll--;
}

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT CUI::Init()
{
	//���g�̃^�C�v��int�^�ŕۑ�
	int nType = static_cast<int>(m_Type);

	//�e�N�X�`������
	CTexture* pTex = CTexture::GetInstance();//�擾
	int nTexIdx = pTex->Regist(CTag::TAG::UI, nType, CUI::TEXTURE_FILE[nType]);//�o�^
	BindTexture(pTex->GetAddress(nTexIdx));//�ݒ�

	//���N���X����������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CUI::Uninit()
{
	//���N���X�I������
	CObject2D::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CUI::Update()
{
	//���N���X�X�V����
	CObject2D::Update();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CUI::Draw()
{
	//���N���X�`�揈��
	CObject2D::Draw();
}

//===========================================================================================================
// ��������
//===========================================================================================================
#include "UImanager.h"
#include "heatgageframe.h"
#include "heatgage.h"
#include "timenumber.h"
#include "timerheading.h"
#include "mg_timerback.h"
#include "mg_timergage.h"
#include "mg_timerframe.h"
#include "titlelogo.h"
#include "startbutton.h"
#include "resulthead.h"
#include "resulttimehead.h"
#include "resultkillhead.h"
#include "resultheathead.h"
#include "seconds.h"
#include "percent.h"
#include "maxscore.h"
#include "resulttime.h"
#include "resultkill.h"
#include "resultheat.h"
#include "totalscore.h"
#include "tutorialhead.h"
#include "descriptheat.h"
#include "mg_head.h"
#include "escape.h"
#include "bosshp.h"
#include "bosshpframe.h"
CUI* CUI::Create(TYPE type, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR3 rot)
{
	//�^�C�v�ɉ����ă������𓮓I�m��
	CUI* pUI = nullptr;
	switch (type)
	{
		//�q�[�g�Q�[�W�t���[��
	case CUI::TYPE::HEAT_GAGE_FRAME:
		pUI = NEW CHeatGageFrame();
		break;

		//�q�[�g�Q�[�W
	case CUI::TYPE::HEAT_GAGE:
		pUI = NEW CHeatGage();
		break;

		//�^�C�}�[
	case CUI::TYPE::TIME_NUMBER:
		pUI = NEW CTimeNumber();
		break;

		//�^�C�}�[���o��
	case CUI::TYPE::TIMER_HEADING:
		pUI = NEW CTimeHeading();
		break;

		//�~�j�Q�[���^�C�}�[�w�i
	case CUI::TYPE::MINIGAME_BACK:
		pUI = NEW CMG_TimerBack();
		break;

		//�~�j�Q�[���^�C�}�[�Q�[�W
	case CUI::TYPE::MINIGAME_GAGE:
		pUI = NEW CMG_TimerGage();
		break;

		//�~�j�Q�[���^�C�}�[�t���[��
	case CUI::TYPE::MINIGAME_FRAME:
		pUI = NEW CMG_TimerFrame();
		break;

		//�^�C�g�����S
	case CUI::TYPE::TITLE_LOGO:
		pUI = NEW CTitleLogo();
		break;

		//�X�^�[�g�{�^��
	case CUI::TYPE::START_BUTTON:
		pUI = NEW CStartButton();
		break;

		//���U���g���o��
	case CUI::TYPE::RESULT_HEAD:
		pUI = NEW CResultHead();
		break;

		//���U���g�^�C�����o��
	case CUI::TYPE::RESULT_TIME_HEAD:
		pUI = NEW CResultTimeHead();
		break;

		//���U���g�L�������o��
	case CUI::TYPE::RESULT_KILL_HEAD:
		pUI = NEW CResultKillHead();
		break;

		//���U���g�q�[�g�ʌ��o��
	case CUI::TYPE::RESULT_HEAT_HEAD:
		pUI = NEW CResultHeatHead();
		break;

		//�b���P��
	case CUI::TYPE::SECONDS:
		pUI = NEW CSeconds();
		break;

		//�p�[�Z���g�}�[�N
	case CUI::TYPE::PERCENT:
		pUI = NEW CPercent();
		break;

		//�X�R�A�ő�l
	case CUI::TYPE::MAXSCORE:
		pUI = NEW CMaxScore();
		break;

		//���U���g�^�C��
	case CUI::TYPE::RESULT_TIME:
		pUI = NEW CResultTime();
		break;

		//���U���g�L����
	case CUI::TYPE::RESULT_KILL:
		pUI = NEW CResultKill();
		break;

		//���U���g���σq�[�g��
	case CUI::TYPE::RESULT_HEAT:
		pUI = NEW CResultHeat();
		break;

		//�g�[�^���X�R�A
	case CUI::TYPE::TOTAL_SCORE:
		pUI = NEW CTotalScore();
		break;

		//�`���[�g���A�����o��
	case CUI::TYPE::TUTORIAL_HEAD:
		pUI = NEW CTutorialHead();
		break;

		//�q�[�g�Q�[�W����
	case CUI::TYPE::DESCRIPT_HEAT:
		pUI = NEW CDescriptHeat();
		break;

		//�~�j�Q�[�����o��
	case CUI::TYPE::MINIGAME_HEAD:
		pUI = NEW CMG_Head();
		break;

		//�`�F�C�X�G���A�x��
	case CUI::TYPE::ESCAPE:
		pUI = NEW CEscape();
		break;

		//�{�XHP
	case CUI::TYPE::BOSS_HP:
		pUI = NEW CBossHP();
		break;

		//�{�XHP�t���[��
	case CUI::TYPE::BOSS_HP_FRAME:
		pUI = NEW CBossHPFrame();
		break;

	default:
		break;
	}

	//�|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (pUI != nullptr)
	{
		//�p�����[�^�ݒ�
		pUI->m_Type = type;//�^�C�v
		pUI->SetPos(pos);//���W
		pUI->SetSize(size);//�T�C�Y
		pUI->SetRot(rot);//�p�x

		//����������
		pUI->Init();

		//�}�l�[�W���[�o�^
		CManager::GetInstance()->GetScene()->GetUIManager()->Regist(pUI);
	}

	return pUI;
}
