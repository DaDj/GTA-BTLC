#include "CVideomodemanager.h"



int CVideomodemanager::SubsystemIndex = 0;

CVideomodemanager::CVideomodemanager()
{
}


CVideomodemanager::~CVideomodemanager()
{
}


 int CVideomodemanager::GetNumSubSystems()
{
	int name = ((int(__cdecl*) ())0x7F2C00)();
	//if (name > 1)
	return 1;
	//return name;
//return ((int(__cdecl*) ())0x7F2C00)();
}

int CVideomodemanager::GetCurrentSubSystem()
{
	return ((int(__thiscall *)(void*))0x7F2C60)(this);
}

char* CVideomodemanager::GetSubSystemInfo(char *subsystemInfo, int subsystemIndex)
{
	return ((char*(__cdecl*)(char*, int))0x7F2C30)(subsystemInfo, subsystemIndex);
}

bool CVideomodemanager::SetSubSystem(int SubsystemIndex)
{
	return ((bool(__cdecl*) (int))0x7F2C90)(SubsystemIndex);
}


int CVideomodemanager::FreeVideoModeList()
{
	return ((int(__cdecl*) ())0x745A80)();
}

int CVideomodemanager::GetNumVideoModes()
{
	return ((int(__cdecl*) ())0x7F2CC0)();
}

void CVideomodemanager::GetVideoModeInfo(RwVideoMode *modeinfo, int modeindex)
{
	return ((void(__cdecl*) (RwVideoMode*,int))0x7F2CF0)( modeinfo, modeindex);
}
void CVideomodemanager::SetCurrentVideomode(int modeindex)
{
	((void(__cdecl*) (int))0x745C70)(modeindex);
}

bool CVideomodemanager::SetVideomode(int modeindex)
{
	return ((bool(__cdecl*) (int))0x7F2D50)(modeindex);
}

unsigned int CVideomodemanager::setMultisamplevels(int a1)
{
	return ((unsigned int(__cdecl*) (int))0x7F84F0)(a1);
}

int CVideomodemanager::setrefreshrate(int a1)
{
	return ((int(__cdecl*) (int))0x7F8580)(a1);
}
 int CVideomodemanager::sub_7460A0(int a1, int a2, int a3)
{
	return ((int(__cdecl*) (int, int, int))0x7460A0)(a1, a2, a3);
}

signed int  CVideomodemanager::DialogFunc(HWND hDlg, int a2, unsigned int a3, int a4)
{
	return ((signed int(__stdcall*) (HWND, int, unsigned int, int))0x745E50)(hDlg,a2, a3,  a4);
}