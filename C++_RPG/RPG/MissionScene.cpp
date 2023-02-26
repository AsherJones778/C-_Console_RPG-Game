#include "stdafx.h"
#include "MissionScene.h"
#include "Player.h"
#include "GameMgr.h"
#include "DataMgr.h"
CMissionScene::CMissionScene()
{
	m_nIndex = 0;//��ʾ��ǰ����������
	m_pCurNpc = nullptr;
	m_bShowConfirm = false;//�Ƿ���ʾȷ�Ͻ�������˵�
	m_bConTaskMove = false;//ȷ�Ͻ��ܲ˵�����Ƿ���ƶ�
	m_nConfirmIndex = 0;//ȷ���������ʼ��
	m_bAlreadyTake = false;//�Ƿ��Ѿ��ӹ�������
	m_bAvoid = false; 
	m_nTime = 0;
	m_bTalk = false;
	m_bFinishTalk = false;
}
CMissionScene::~CMissionScene()
{
	CC_SAFE_DELETE(m_pCurNpc);
	CC_SAFE_DELETE(m_pPlayer);
	for (SMissionDt* pData : m_vecMissions)
	{
		delete pData;
		pData = nullptr;
	}
	m_vecMissions.clear();
}
void CMissionScene::update()
{
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();
	if (!m_bShowConfirm)
	{
		if (KEY_DOWN(VK_UP))
		{
			m_nIndex--;
			if (m_nIndex < 0)
			{
				m_nIndex = m_vecMissions.size() - 1;
			}
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			m_nIndex++;
			if (m_nIndex > m_vecMissions.size() - 1)
			{
				m_nIndex = 0;
			}
		}
		if (KEY_DOWN(VK_RETURN))
		{
			//��������������ҵ������б�����  
			if (!m_pPlayer->judgeMissionIsExist(m_vecMissions[m_nIndex]) && m_vecMissions[m_nIndex]->bIsFinish == false)
			{
				m_bShowConfirm = true;//��ʾ�Ƿ��������˵�
				m_bAlreadyTake = false;//û�ӹ��������  
				m_bConTaskMove = true;//ѡ���Ƿ��������˵� �����ƶ���
				m_bAvoid = false;
				m_bTalk = true;
			}
			else
			{
				m_bAlreadyTake = true;
				m_bShowConfirm = false;//����ʾ�Ƿ��������˵�
				m_bConTaskMove = false;//ѡ���Ƿ��������˵� �������ƶ�
			}
		}
		if (KEY_DOWN(VK_ESCAPE))
		{
			//���³�ʼ��һ�� �����ٴν���ͬһ��NPC���ϴν���ı�������ν�������̵�Ӱ��
			m_nIndex = 0;//��ʾ��ǰ����������
			m_bShowConfirm = false;//�Ƿ���ʾȷ�Ͻ�������˵�
			m_bConTaskMove = false;//ȷ�Ͻ��ܲ˵�����Ƿ���ƶ�
			m_nConfirmIndex = 0;//ȷ���������ʼ��
			m_bAlreadyTake = false;//�Ƿ��Ѿ��ӹ�������
			CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
		}
	}
	if (m_bConTaskMove && m_bShowConfirm && m_bAvoid)
	{
		if (KEY_DOWN(VK_UP))
		{
			m_nConfirmIndex--;
			if (m_nConfirmIndex < 0)
			{
				m_nConfirmIndex = 1;
			}
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			m_nConfirmIndex++;
			if (m_nConfirmIndex > 1)
			{
				m_nConfirmIndex = 0;
			}
		}
		if (KEY_DOWN(VK_RETURN))
		{
			if (0 == m_nConfirmIndex)
			{
				m_pPlayer->addMissionToVecMission(m_vecMissions[m_nIndex]);//�Ѵ�����ӽ���������б�
				m_bShowConfirm = false;
				m_bTalk = false;
			}
			if (1 == m_nConfirmIndex)
			{
				m_bShowConfirm = false;
				m_bTalk = false; 
			}

		}
		if (KEY_DOWN(VK_ESCAPE))
		{
			m_bConTaskMove = false;
			m_bShowConfirm = false;
		}
	}
	m_bAvoid = true;
}

void CMissionScene::render()
{
	cout << "             ��ǰNPC:" << m_pCurNpc->getName() << endl;
	cout << "----------------��ǰ�ɽ�������-----------------" << endl << endl;
	cout << "    " << "��������" << "\t" << "������" << "\t" << "��������" << endl;
	for (int i = 0; i < m_vecMissions.size(); i++)
	{
		if (i == m_nIndex)
		{
			cout << "->  ";
		}
		else
		{
			cout << "    ";
		}
		cout << m_vecMissions[i]->strName << "\t" << m_vecMissions[i]->strDescribe << "\t" << m_vecMissions[i]->strType << "��" << endl;
	}
	if (m_bAlreadyTake)
	{
		m_nTime++;
		cout << "�������Ѿ����ܹ��ˣ������ظ����ܣ�"<<endl;
		if (m_nTime > 10)
		{
			m_nTime = 0;
			m_bAlreadyTake = false;
		}
	}
	if (m_bShowConfirm)
	{
		cout << "---------------ȷ�����մ�����----------------" << endl;
		if (0 == m_nConfirmIndex)
		{
			cout << "  ��ȷ�Ͻ���      " << endl;
			cout << "    �����ٿ��ǿ���" << endl;
			m_bAlreadyTake = false;
		}
		else if (1 == m_nConfirmIndex)
		{
			cout << "    ȷ�Ͻ���      " << endl;
			cout << "  �������ٿ��ǿ���" << endl;
			m_bAlreadyTake = false;
		}
	}
	if (m_bTalk)
	{
		cout << "---------------�Ի�����---------------" << endl;
		for (string pData : m_vecMissions[m_nIndex]->m_vec_strGetMission)
		{
			cout << pData << endl;
		}
	}
}
void CMissionScene::initMissionWithNpcID(int nNpcID)
{
	m_vecMissions.clear();
	vector<SBaseDt*> vecDatas = CDataMgr::getInstance()->getMgr("MissionDtMgr")->getAllDatas();
	for (SBaseDt* pData : vecDatas)
	{
		SMissionDt* pMissionDt = static_cast<SMissionDt*>(pData);
		if (pMissionDt->nNpcID == nNpcID)
		{
			m_vecMissions.push_back(pMissionDt);
		}
	}
}