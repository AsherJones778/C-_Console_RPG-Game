#pragma once
#include "DataBasic.h"
#include "Pet.h"
#include "Enemy.h"
#include "Npc.h"
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void update();
	bool isExist(int nRow, int nCol);
	//�ṩһ�����װ���Ľ��
	void addItemToBag(SItemDt* pItem);
	vector<SItemDt*> getBag();
	void addEquip(SItemDt* pEquip);
	SItemDt* getEquipByIndex(int nIndex);
	void removeItemFromBag(int nIndex);
	void transformData(SRoleDt* pData);
	int getMoney();
	void setMoney(int nMoney);
	bool isNearANpc();
	void restorePosition();
	void petMove();
	void takeOffItemByIndex(int nIndex);
	void addValue(SItemDt* pData);
	void delValue(SItemDt* pData);
	void AddMoney(int nMoney);
	//ս����ͼ��غ���
	void setRow(int nRow);//������ս����ͼ�и�ս����ͼ�е���ҵ���λ�ø�ֵ
	void setCol(int nCol);//������ս����ͼ�и�ս����ͼ�е���ҵ���λ�ø�ֵ
	void setPosition(int nRow,int nCol);
	void addMissionToVecMission(SMissionDt* pData);
	bool judgeMissionIsExist(SMissionDt* pData);
	void reduceMissionMonsterNumber(int nMonsterNumber);
	void delMission(SMissionDt* pData);
	CC_SYNTHESIZE(vector<SSkillDt*>, m_vecSkill,SkillBag);
	CC_SYNTHESIZE(vector<SMissionDt*>, m_vecMission, Mission);
	CC_SYNTHESIZE(SItemDt*, m_arrWeapons[4], Weapons);//����һ�����飬������ҵ�װ����
	CC_SYNTHESIZE(string,m_strPic,Pic);
	CC_SYNTHESIZE(CPet*, m_pPet, Pet);
	CC_SYNTHESIZE(int, m_nRowBk,RowBk);
	CC_SYNTHESIZE(int, m_nColBk, ColBk);
	CC_SYNTHESIZE(int, m_nHp,Hp);
	CC_SYNTHESIZE(int, m_nMp,Mp);
	CC_SYNTHESIZE(int, m_nAtk,Atk);
	CC_SYNTHESIZE(int, m_nDef,Def);
	CC_SYNTHESIZE(CEnemy*, m_pCurEnemyDt, Enemy);
	CC_SYNTHESIZE_READONLY(int, m_nRow, Row);
	CC_SYNTHESIZE_READONLY(int, m_nCol, Col);
	CC_SYNTHESIZE(int, m_nID, ID);
private:
	string m_strName;
	int m_nMoney;
	int m_nIndex;
	vector<SItemDt*> m_vecBag;
};