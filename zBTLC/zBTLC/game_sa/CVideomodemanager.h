#pragma once

#include "RenderWare.h"
class CVideomodemanager
{
public:
	CVideomodemanager();
	~CVideomodemanager();

	

	static int GetNumSubSystems(); //Numbers of Subsystems -added trick to skip the Dialogfunc //RWENGINE
	int GetCurrentSubSystem();//RWENGINE
	static char* GetSubSystemInfo(char *subsystemInfo, int subsystemIndex);
	static bool SetSubSystem(int subsystemIndex);
	static int FreeVideoModeList();//RWENGINE
	static int GetNumVideoModes();//RWENGINE
	static void GetVideoModeInfo(RwVideoMode *modeinfo, int modeindex); //RWENGINE
	static void SetCurrentVideomode(int modeIndex);
	static bool SetVideomode(int modeindex);
	static int setrefreshrate(int a1);
	static unsigned int setMultisamplevels(int a1);
	static  int sub_7460A0(int a1, int a2, int a3);
	static signed int  DialogFunc(HWND hDlg, int a2, unsigned int a3, int a4);

	static int CVideomodemanager::SubsystemIndex;

};

