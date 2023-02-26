#include "stdafx.h"
#include "GameWin.h"
#include "GameMgr.h"
#include "Player.h"
enum 
{
	E_WIN_RESTART,
	E_WIN_SHOWVALUE,
	E_WIN_EXIT,
};

CGameWin::CGameWin()
{
	m_nIndex = E_WIN_RESTART;
	m_bShowPlayerValue = false;
}


CGameWin::~CGameWin()
{
}

void CGameWin::update()
{
	if (KEY_DOWN(VK_UP))
	{
		m_nIndex--;
		if (m_nIndex < E_WIN_RESTART)
		{
			m_nIndex = E_WIN_EXIT;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nIndex++;
		if (m_nIndex > E_WIN_EXIT)
		{
			m_nIndex = E_WIN_RESTART;
		}
	}
	
	if (KEY_DOWN(VK_RETURN))
	{
		if (E_WIN_RESTART == m_nIndex)
		{
			CGameMgr::getInstance()->setGameScene(E_GAME_MENU);
		}
		else if (E_WIN_SHOWVALUE == m_nIndex)
		{
			m_bShowPlayerValue = true;
		}
		else if (E_WIN_EXIT == m_nIndex)
		{
			exit(0);
		}
	}

	if (m_bShowPlayerValue && KEY_DOWN(VK_ESCAPE))
	{
		m_bShowPlayerValue = false;
	}
}

void CGameWin::render()
{
	
	if (!m_bShowPlayerValue)
	{
		cout << "恭喜您完成最终任务:杀死兽群领主-黑色狄瑞吉（野猪）" << endl;
		cout << "解救了萨拉德村庄的村民们" << endl <<endl;
		cout << "您已经成功通关" << endl;
		if (E_WIN_RESTART == m_nIndex)
		{
			cout << "■■■■■■■■■■■■■■■" << endl;
			cout << "■    →换个角色重新开始    ■" << endl;
			cout << "■      显示玩家属性        ■" << endl;
			cout << "■      退出游戏            ■" << endl;
			cout << "■■■■■■■■■■■■■■■" << endl;
		}
		else if (E_WIN_SHOWVALUE == m_nIndex)
		{
			cout << "■■■■■■■■■■■■■■■" << endl;
			cout << "■      换个角色重新开始    ■" << endl;
			cout << "■    →显示玩家属性        ■" << endl;
			cout << "■      退出游戏            ■" << endl;
			cout << "■■■■■■■■■■■■■■■" << endl;
		}
		else if (E_WIN_EXIT == m_nIndex)
		{
			cout << "■■■■■■■■■■■■■■■" << endl;
			cout << "■      换个角色重新开始    ■" << endl;
			cout << "■      显示玩家属性        ■" << endl;
			cout << "■    →退出游戏            ■" << endl;
			cout << "■■■■■■■■■■■■■■■" << endl;
		}

	}
	else
	{
		cout << "---------------玩家属性---------------" <<endl;
		CPlayer* curPlayer = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();
		cout << "--------------------状态栏-------------------" << endl << endl;
		cout << "    " << "玩家名称" << "\t" << "血量" << "\t" << "蓝量" << "\t" << "攻击" << "\t" << "防御" << endl;
		CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();
		cout << "    " << pPlayer->getPic() << "\t\t" << pPlayer->getHp() << "\t" << pPlayer->getMp() << "\t" << pPlayer->getAtk() << "\t" << pPlayer->getDef() << endl;
		cout << "-------------------- 背  包 -------------------" << endl << endl;
		cout << "    " << "名称" << "\t" << "血量" << "\t" << "蓝量" << "\t" << "攻击" << "\t" << "数量" << endl;
		vector<SItemDt*> vecBag = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getBag();
		for (int i = 0; i < vecBag.size(); i++)
		{
			cout << vecBag[i]->strName << "\t" << vecBag[i]->nHP << "\t";
			cout << vecBag[i]->nMP << "\t" << vecBag[i]->nAtk << "\t" << vecBag[i]->nCount << endl;
		}
		cout << "--------------------装备栏-------------------" << endl << endl;
		cout << "    " << "名称" << "\t" << "血量" << "\t" << "蓝量" << "\t" << "攻击" << "\t" << "防御" << endl;
		for (int i = 0; i < 4; i++)
		{
			SItemDt* pEquip = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getEquipByIndex(i);
			if (!pEquip)
			{
				cout << "空" << "\t" << "\t" << "0" << "\t" << "0" << "\t" << "0" << "\t" << "0" << endl;
			}
			else
			{
				cout << pEquip->strName << "\t" << pEquip->nHP << "\t" << pEquip->nMP << "\t" << pEquip->nAtk << "\t" << pEquip->nDef << endl;
			}
		}
		cout << "    您当前的金币：";
		cout << CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getMoney() << endl;
		cout << endl;
	}

}
