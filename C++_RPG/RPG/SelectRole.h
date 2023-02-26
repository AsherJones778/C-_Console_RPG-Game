#pragma once
#include "DataBasic.h"
class CSelectRole
{
public:
	CSelectRole();
	~CSelectRole();
	void update();
	void render();
	CC_SYNTHESIZE(SRoleDt*, m_defRole,DefiniteRole);
private:
	vector<SBaseDt*> m_vecAllRole;
	int m_nSelectIndex;
};

