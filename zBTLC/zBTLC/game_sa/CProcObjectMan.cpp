#include "CProcObjectMan.h"
#include "List_c.h"



static List_c g_procobj_current;


char CProcObjectMan::init()
{
	ListItem_c *v3 = (ListItem_c *)((char *)this + 0x2408); // esi@1
	signed int v4; // ebx@1
	v4 = 512;
	do
	{
		g_procobj_current.AddItem(v3);
		v3 = (ListItem_c *)((char *)v3 + 20);
		--v4;
	} while (v4);
	CProcObjectMan::LoadDataFile();
	return 1;
}

int CProcObjectMan::LoadDataFile()
{
	return ((bool(__thiscall *)(CProcObjectMan*))0x5A3140)(this);
}
