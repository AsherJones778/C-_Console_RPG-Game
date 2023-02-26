#pragma once
#include "DataBase.h"
//地图数据结构体
struct SMapDt : public SBaseDt
{
	SMapDt()
	{
		nRowCount = 0;
		nColCount = 0;
		nPlayerRow = 0;
		nPlayerCol = 0;
		memset(arrMap, 0, sizeof(arrMap));
	}
	int nRowCount;
	int nColCount;
	int nPlayerRow;
	int nPlayerCol;

	int arrMap[100][100];
};
//地图数据管理者
class CMapDtMgr : public CBaseDtMgr
{
public:
	CMapDtMgr();
	~CMapDtMgr();
	void loadData(const string& strPath);
};
//角色数据结构体
struct SRoleDt : public SBaseDt
{
	SRoleDt()
	{
		nHP = 0;
		nMP = 0;
		nAtk = 0;
		nDef = 0;
		strPic = "";
	}
	int nHP;
	int nMP;
	int nAtk;
	int nDef;
	string strPic;
};
//角色数据管理者
class CRoleDtMgr : public CBaseDtMgr
{
public:
	CRoleDtMgr();
	~CRoleDtMgr();
	void loadData(const string& strPath);
};
//NPC数据结构体
struct SNpcDt : public SBaseDt
{
	SNpcDt()
	{
		strPic = "";
		nRow = 0;
		nCol = 0;
		nMapID = 0; 
		nDeal = 0;
	}
	string strPic;
	int nRow;
	int nCol;
	int nMapID;
	int nDeal;
};
//NPC数据管理者
class CNpcDtMgr : public CBaseDtMgr
{
public:
	CNpcDtMgr();
	~CNpcDtMgr();
	void loadData(const string& strPath);
};
//怪物数据结构体
struct SEnemyDt : public SBaseDt
{
	SEnemyDt()
	{
		nHP = 0;
		nAtk = 0;
		nDef = 0;
		strPic = "";
		nRow = 0;
		nCol = 0;
		nMapID = 0;
		nBattleMapID = 0;
		nMoney = 0;
	}
	int nHP;
	int nAtk;
	int nDef;
	int nRow;
	int nCol;
	int nMapID;
	string strPic;
	int nBattleMapID;
	int nMoney;
};
//怪物数据管理者
class CEnemyDtMgr : public CBaseDtMgr
{
public:
	CEnemyDtMgr();
	~CEnemyDtMgr();
	void loadData(const string& Path);

};
//武器数据结构体
struct SItemDt : public SBaseDt
{
	SItemDt()
	{
		nID = 0;
		strName = "";
		nAtk = 0;
		nMoney = 0;
		nDef = 0;
		nHP = 0;
		nMP = 0;
		nNpcID = 0;
		nCount = 0;
		nType = 0;
		strPic = "";
	}
	int nID;
	string strName;
	int nAtk;
	int nMoney;
	int nDef;
	int nHP;
	int nMP;
	int nNpcID;
	int nCount;
	int nType;
	string strPic;
};
//武器数据管理者
class CItemDtMgr : public CBaseDtMgr
{
public:
	CItemDtMgr();
	~CItemDtMgr();
	virtual void loadData(const string& strPath);
private:
};
//战斗地图结构体
struct SBattleMapDt : public SBaseDt
{
	SBattleMapDt()
	{
		nRowCount = 0;
		nColCount = 0;
		nPlayerRow = 0;
		nPlayerCol = 0;
		nEnemyRow = 0;
		nEnemyCol = 0;
		memset(arrMap, 0, sizeof(arrMap));
	}
	int nRowCount;
	int nColCount;
	int nPlayerRow;
	int nPlayerCol;
	int nEnemyRow;
	int nEnemyCol;
	int arrMap[100][100];
};
//战斗地图数据管理者
class CBattleMapDtMgr :public CBaseDtMgr
{
public:
	CBattleMapDtMgr();
	~CBattleMapDtMgr();
	virtual void loadData(const string& strPath);
private:

};
//技能数据结构体
struct SSkillDt : public SBaseDt
{
	SSkillDt()
	{
		nMP = 0;
		nAtk = 0;
		nPlayerID = 0;
	}
	int nMP;
	int nAtk;
	int nPlayerID;
};
//技能数据管理者
class CSkillDtMgr : public CBaseDtMgr
{
public:
	CSkillDtMgr();
	~CSkillDtMgr();
	virtual void loadData(const string& strPath);
};
//任务数据结构体
struct SMissionDt : public SBaseDt
{
	SMissionDt()
	{
		nNpcID = 0;
		strDescribe = "";
		nTalkLines = 0;
		nFinishTalkLines = 0;
		nNeedCount = 0;
		nEnemyID = 0;
		nReward = 0;
		bIsFinish = false;
		strType = "";
		nLink = 0;
	}
	int nNpcID;
	string strDescribe;
	int nTalkLines;
	int nFinishTalkLines;
	int nNeedCount;
	int nEnemyID;
	int nReward;
	bool bIsFinish;
	string strType;
	int nLink;
	vector<string> m_vec_strGetMission;
	vector<string> m_vec_strFinishMission;
};
//任务数据管理者
class CMissionDtMgr : public CBaseDtMgr
{
public:
	CMissionDtMgr();
	~CMissionDtMgr();
	virtual void loadData(const string& strPath);
private:
	
};


//代理类
class CLoad
{
public:
	CLoad::CLoad(){}
	CLoad::~CLoad(){}

	static void load();
};

