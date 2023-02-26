#include "stdafx.h"
#include "DataBasic.h"
#include "DataMgr.h"
#include <fstream>
//��ͼ���ݶ�ȡ
CMapDtMgr::CMapDtMgr()
{

}
CMapDtMgr::~CMapDtMgr()
{
}
void CMapDtMgr::loadData(const string& strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		getline(inFile, string());
		int nCount = 0;
		inFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			SMapDt* pData = new SMapDt();
			inFile >> pData->nID >> pData->strName;
			inFile >> pData->nRowCount >> pData->nColCount;
			inFile >> pData->nPlayerRow >> pData->nPlayerCol;

			for (int m = 0; m < pData->nRowCount; m++)
			{
				for (int n = 0; n < pData->nColCount; n++)
				{
					inFile >> pData->arrMap[m][n];
				}
			}
			m_vecDatas.push_back(pData);
		}
	}
	inFile.close();
}
//��ͼ���ݶ�ȡ����
//������ݶ�ȡ
CRoleDtMgr::CRoleDtMgr()
{

}
CRoleDtMgr::~CRoleDtMgr()
{
}
void CRoleDtMgr::loadData(const string& strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		getline(inFile, string());
		int nCount = 0;
		inFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			SRoleDt* pData = new SRoleDt();
			inFile >> pData->nID >> pData->strName;
			inFile >> pData->nHP >> pData->nMP;
			inFile >> pData->nAtk >> pData->nDef;
			inFile >> pData->strPic;
			m_vecDatas.push_back(pData);
		}
	}
	inFile.close();
}
//������ݶ�ȡ����
//NPC���ݶ�ȡ
CNpcDtMgr::CNpcDtMgr()
{

}
CNpcDtMgr::~CNpcDtMgr()
{
}
void CNpcDtMgr::loadData(const string& strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		getline(inFile, string());
		int nCount = 0;
		inFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			SNpcDt* pData = new SNpcDt();
			inFile >> pData->nID >> pData->strName >> pData->strPic >> pData->nRow >> pData->nCol >> pData->nMapID >> pData->nDeal;
			m_vecDatas.push_back(pData);
		}
	}
	inFile.close();
}
//���ݶ�ȡ����
//�������ݶ�ȡ
CEnemyDtMgr::CEnemyDtMgr()
{

}
CEnemyDtMgr::~CEnemyDtMgr()
{
}
void CEnemyDtMgr::loadData(const string& Path)
{
	fstream inFile(Path);
	if (inFile)
	{
		getline(inFile, string());
		int nCount = 0;
		inFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			SEnemyDt* pData = new SEnemyDt();
			inFile >> pData->nID >> pData->strName;
			inFile >> pData->nHP >> pData->nAtk;
			inFile >> pData->nDef >> pData->strPic;
			inFile >> pData->nRow >> pData->nCol;
			inFile >> pData->nMapID >> pData->nBattleMapID >> pData->nMoney;
			m_vecDatas.push_back(pData);
		}
	}
	inFile.close();
}
//�������ݶ�ȡ����
//װ��������ݶ�ȡ
void CItemDtMgr::loadData(const string& strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		getline(inFile,string());
		int nCount = 0;
		inFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			SItemDt* pData = new SItemDt();
			inFile >> pData->nID >> pData->strName;
			inFile >> pData->nAtk >> pData->nMoney>>pData->nDef;
			inFile >> pData->nHP >> pData->nMP >> pData->nNpcID >> pData->nType >> pData->strPic;
			m_vecDatas.push_back(pData);
		}
	}
	inFile.close();
}
CItemDtMgr::CItemDtMgr()
{

}
CItemDtMgr::~CItemDtMgr()
{

}
//װ��������ݶ�ȡ����
//ս����ͼ���ݶ�ȡ
void CBattleMapDtMgr::loadData(const string& strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		getline(inFile,string());
		int nCount = 0;
		inFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			SBattleMapDt* pData = new SBattleMapDt();
			inFile >> pData->nID >> pData->strName >> pData->nRowCount;
			inFile >> pData->nColCount >> pData->nPlayerRow >> pData->nPlayerCol;
			inFile >> pData->nEnemyRow >> pData->nEnemyCol;
			
			for (int m = 0; m < pData->nRowCount; m++)
			{
				for (int n = 0; n < pData->nColCount; n++)
				{
					inFile >> pData->arrMap[m][n];
				}
			}
			m_vecDatas.push_back(pData);
		}
	}
	inFile.close();
}
CBattleMapDtMgr::CBattleMapDtMgr()
{

}
CBattleMapDtMgr::~CBattleMapDtMgr()
{

}
//ս����ͼ���ݶ�ȡ����
//��Ҽ������ݶ�ȡ��ʼ
void CSkillDtMgr::loadData(const string& strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		getline(inFile, string());
		int nCount = 0;
		inFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			SSkillDt* pData = new SSkillDt();
			inFile >> pData->nID >> pData->strName;
			inFile >> pData->nMP >> pData->nAtk >> pData->nPlayerID;
			m_vecDatas.push_back(pData);
		}
	}
	inFile.close();
}
CSkillDtMgr::CSkillDtMgr()
{

}
CSkillDtMgr::~CSkillDtMgr()
{

}
//��Ҽ������ݶ�ȡ����
//�������ݶ�ȡ��ʼ
CMissionDtMgr::CMissionDtMgr()
{
}
CMissionDtMgr::~CMissionDtMgr()
{
}
void CMissionDtMgr::loadData(const string& strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		getline(inFile,string());
		int nCount = 0;
		inFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			SMissionDt* pData = new SMissionDt();
			inFile >> pData->nID >> pData->nNpcID >> pData->strName;
			inFile >> pData->strDescribe >> pData->nTalkLines;
			inFile >> pData->nFinishTalkLines >> pData->nNeedCount;
			inFile >> pData->nEnemyID >> pData->nReward >> pData->strType >>pData->nLink;
			for (int i = 0; i < pData->nTalkLines; i++)
			{
				string strTemp;
				//getline(inFile, strTemp);
				inFile >> strTemp;
				pData->m_vec_strGetMission.push_back(strTemp);
			}
			for (int i = 0; i < pData->nFinishTalkLines; i++)
			{
				string strTemp = "";
				//getline(inFile, strTemp);
				inFile >> strTemp;
				pData->m_vec_strFinishMission.push_back(strTemp);
			}
			m_vecDatas.push_back(pData);
		}
	}
}

//�������ݶ�ȡ����
void CLoad::load()
{
	CMapDtMgr* pMapDtMgr = new CMapDtMgr();
	pMapDtMgr->loadData("./Data/mapData.txt");
	CDataMgr::getInstance()->addMgr("MapDtMgr",pMapDtMgr);

	CRoleDtMgr* pRoleDtMgr = new CRoleDtMgr();
	pRoleDtMgr->loadData("./Data/playerData.txt");
	CDataMgr::getInstance()->addMgr("RoleDtMgr", pRoleDtMgr);

	CNpcDtMgr* pNpcDtMgr = new CNpcDtMgr();
	pNpcDtMgr->loadData("./Data/npcData.txt");
	CDataMgr::getInstance()->addMgr("NpcDtMgr", pNpcDtMgr);

	CEnemyDtMgr* pEnemyDtMgr = new CEnemyDtMgr();
	pEnemyDtMgr->loadData("./Data/enemyData.txt");
	CDataMgr::getInstance()->addMgr("EnemyDtMgr", pEnemyDtMgr);

	CItemDtMgr* pItemDtMgr = new CItemDtMgr();
	pItemDtMgr->loadData("./Data/weaponData.txt");
	CDataMgr::getInstance()->addMgr("ItemDtMgr",pItemDtMgr);

	CBattleMapDtMgr* pBattleMapDtMgr = new CBattleMapDtMgr();
	pBattleMapDtMgr->loadData("./Data/battleMapData.txt");
	CDataMgr::getInstance()->addMgr("BattleMapDtMgr", pBattleMapDtMgr);

	CSkillDtMgr* pSkillDtMgr = new CSkillDtMgr();
	pSkillDtMgr->loadData("./Data/skillData.txt");
	CDataMgr::getInstance()->addMgr("SkillDtMgr", pSkillDtMgr);

	CMissionDtMgr* pMissionDtMgr = new CMissionDtMgr();
	pMissionDtMgr->loadData("./Data/talkData.txt");
	CDataMgr::getInstance()->addMgr("MissionDtMgr",pMissionDtMgr);
}


