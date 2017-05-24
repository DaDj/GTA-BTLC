
#include "windowmode.h"
#include "../../Patch/MemoryMgr.h"
#define DEBUG_WND
#define HIDWORD(_qw)    ((DWORD)(((_qw) >> 32) & 0xffffffff))
static int* GcurSelVM = (int*)0x8D6220;
static char **Subsystems = (char**)0xC920D0;
LPCSTR *Appname = (LPCSTR*)0x8D6224;
//static char** Subsystems;

HWND INITINSTANCE(HINSTANCE hinstance)
{
	RECT rect = 
	{
		0, 
		0, 
		RsGlobal.maximumWidth,
		RsGlobal.maximumHeight
	};

	AdjustWindowRect(&rect, 0x10000000, 0);
	return CreateWindowExA(
		0,
		*Appname,
		RsGlobal.appName ,
		0x10000000,
		0,
		0,
		rect.right - rect.left,
		rect.bottom- rect.top,
		0,
		0,
		hinstance,
		0);
}

void changeresu()
{
	std::cout << "Enable window mode" << std::endl;
	//*GcurSelVM = 58;
	//CVideomodemanager::SetCurrentVideomode(*GcurSelVM);
	*GcurSelVM = 0;
	CVideomodemanager::SetCurrentVideomode(*GcurSelVM);
	FrontEndMenuManager.m_dwAppliedResolution = *GcurSelVM;
	FrontEndMenuManager.m_dwResolution = *GcurSelVM;

}

char** __cdecl FIND_VIDEOMODES()
{
	CVideomodemanager vidmgr;
	RwVideoMode modeinfo;
	int i_vidmodes = 0;
	int* currentsubsys = (int*)0x8D6248;
	int* unknown = (int*)0xC8CF80;

	if (GetAsyncKeyState(VK_TAB))
	{
		
		changeresu();
		SetFocus(RsGlobal.ps->window);
		SetForegroundWindow(RsGlobal.ps->window);
	}
		

	if (Subsystems)
	{
		if (*currentsubsys == vidmgr.GetCurrentSubSystem())
		{
			//std::cout << FrontEndMenuManager.m_dwAppliedResolution << std::endl;
			//std::cout << FrontEndMenuManager.m_dwResolution << std::endl;
			//std::cout << RsGlobal.maximumHeight << std::endl;
			//std::cout << RsGlobal.maximumWidth << std::endl;
			return Subsystems;
		}
		CVideomodemanager::FreeVideoModeList();
	}
	*currentsubsys = vidmgr.GetCurrentSubSystem();
	i_vidmodes = CVideomodemanager::GetNumVideoModes();
	int v3 = 0;

	for (Subsystems = (char**)calloc(i_vidmodes, 4); v3 < i_vidmodes; ++v3)
	{
		CVideomodemanager::GetVideoModeInfo(&modeinfo, v3);
		if (modeinfo.flags & 1)
		{
			float ratio = (float)modeinfo.height / (float)modeinfo.width;
			if (modeinfo.width < 1024 || modeinfo.height < 768 || modeinfo.depth < 32
				|| ratio != 0.81 && ratio != 0.75 && ratio != 0.60000002 && ratio != 0.625 && ratio != 0.5625
				|| (modeinfo.width != 640 || modeinfo.height != 480)
				&& (unsigned int)(unknown - modeinfo.height * modeinfo.width * modeinfo.depth / 8) <= 0x2D00000)
			{
				Subsystems[v3] = 0;
			}
			else
			{
				char* v4 = (char*)calloc(100, 1);
				Subsystems[v3] = v4;
				sprintf(v4, " _____%lu X %lu", modeinfo.width, modeinfo.height);
				//std::cout << v3 << " "<< modeinfo.width << " " << modeinfo.height << " " << modeinfo.depth << " " << modeinfo.flags << " " << std::endl;
			}
		}
		else
		{
			CVideomodemanager::GetVideoModeInfo(&modeinfo, FrontEndMenuManager.m_dwResolution);
			char* v4 = (char*)calloc(100, 1);
			Subsystems[v3] = v4;
			//sprintf(v4, " _____%lu X %lu", modeinfo.width, modeinfo.height, modeinfo.depth);
			//sprintf(v4, " windowed");
			//std::cout << v3 << " " << modeinfo.width << " " << modeinfo.height << " " << modeinfo.depth << " " << modeinfo.flags << " " << std::endl;
		}
	}
	return Subsystems;
}

int __cdecl psSelectDevice()
{
	CVideomodemanager Vidmgr;
	HWND v2;//v2
	HWND v3;//v3
	int i_whilelooper = 0; //v4
	char *Info_SubSystem = (char*)0xC8CFC0; //v5
	int Refreshrate; //V7
	RwVideoMode modeinfo;
	int* i_Subsystems = (int*)0xC920F0;
	int* SubsystemIndex = (int*)0xC920F4;
	DWORD* unk_C92104 = (DWORD*)0xC92104;
	int* not_vidmodeselected = (int*)0x8D6218;
	int* unk_C92118 = (int*)0xC92118;
	bool success = false;
//	unsigned __int64 CurrentSubSystem; //v6
	__int32* unk_C92108 = (int*)0xC92108;

		v3 = RsGlobal.ps->window;
		v2 = RsGlobal.ps->instance;
		*i_Subsystems = CVideomodemanager::GetNumSubSystems();

		if (!*i_Subsystems)
			return 0;
		if (*i_Subsystems > 16)
			*i_Subsystems = 16;

		if (*i_Subsystems > 0)
		{
			do
			{
				CVideomodemanager::GetSubSystemInfo(Info_SubSystem, i_whilelooper++);
				Info_SubSystem += 80;
				std::cout << Info_SubSystem[80];
			} while (i_whilelooper < *i_Subsystems);
		}

		*SubsystemIndex = Vidmgr.GetCurrentSubSystem();
		//CurrentSubSystem = __rdtsc();
		//*unk_C92104 = HIDWORD(CurrentSubSystem);
		//*unk_C92108 = CurrentSubSystem;

	if (*i_Subsystems <= 1)
	{
		*unk_C92118 = 0;
		if (CVideomodemanager::SetSubSystem(*SubsystemIndex))
		{
				if (!FIND_VIDEOMODES()[FrontEndMenuManager.m_dwResolution] || !FrontEndMenuManager.m_dwResolution)
				{

					while ((signed int)*GcurSelVM < CVideomodemanager::GetNumVideoModes())
					{
						CVideomodemanager::GetVideoModeInfo(&modeinfo, *GcurSelVM);
						if (!*not_vidmodeselected || modeinfo.width == 1440 && modeinfo.height == 900 && modeinfo.depth == 32 && modeinfo.flags & 1)
						{
							success = true;
							break;
						}
						++*GcurSelVM;
					}
					if (!success)
					{
						MessageBoxA(0, "Cannot find 800x600x32 video mode", "GTA: San Andreas", 0);
						return 0;
					}
				}
				if (!success)
				{
					FrontEndMenuManager.m_dwAppliedResolution = FrontEndMenuManager.m_dwResolution;
					*GcurSelVM = FrontEndMenuManager.m_dwResolution;
				}
			
			success = true;
		}
		if (!success)
			return 0;
	}

	if (!success)
	{
		*unk_C92118 = 0;
		if (!DialogBoxParamA((HINSTANCE)v2, (LPCSTR)0x68, v3, (DLGPROC)CVideomodemanager::DialogFunc, 0) || !CVideomodemanager::SetSubSystem(*SubsystemIndex))
			return 0;
	}
	
	CVideomodemanager::GetVideoModeInfo(&modeinfo, *GcurSelVM);
	FrontEndMenuManager.m_dwSelectedMenuItem = 0;
	if (!CVideomodemanager::SetVideomode(*GcurSelVM))
	return 0;

	if (modeinfo.flags & 1)
	{
		Refreshrate = CVideomodemanager::sub_7460A0(modeinfo.width, modeinfo.height, modeinfo.depth);
		if (Refreshrate != -1)
			CVideomodemanager::setrefreshrate(Refreshrate);

			RsGlobal.maximumWidth = modeinfo.width;
			RsGlobal.maximumHeight = modeinfo.height;
			RsGlobal.ps->fullscreen = 1;
	}
	CVideomodemanager::setMultisamplevels(FrontEndMenuManager.m_dwAppliedAntiAliasingLevel);
	return 1;
}

