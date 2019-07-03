#include "CMenuManager.h"
#include "CPad.h"
#include "CText.h"
#include "CFont.h"
#include "CTimer.h"
#include "RenderWare.h"
#include "../game_sa/CHud.h"

//#include "CAudioEngine.h"


CMenuManager &FrontEndMenuManager = *(CMenuManager *)0xBA6748;
CMenuPage	*MenuPages = (CMenuPage *)0x8CE008;

int CMenuManager::LikeALastSelectedMenuItem = 157;

bool& CMenuManager::bInvertMouseX = *(bool *)0xBA6744;
bool& CMenuManager::bInvertMouseY = *(bool *)0xBA6745;

int& CMenuManager::nLastMenuPage = *(int *)0x8CDFF0;

void CMenuManager::ProcessStreaming(char bImmediately)
{
	((void(__thiscall *)(CMenuManager*, char))0x573CF0)(this, bImmediately);
}

void CMenuManager::UserInput()
{
//	CMenuManager ThisMenuManager; // esi
//	//char DrawMouse; // al
//	//int v4; // ecx
//	//int v5; // eax
//	char selectedItem; // bl
//	//int v7; // ecx
//	//int v8; // edi
//	int v9; // eax
//	//char v10; // cl
//	char *v11; // eax
//	int v12; // eax
//	float v13; // ST08_4
//	//float v14; // ST18_4
//	//float v15; // ST08_4
//	//int v16; // eax
//	//int v17; // ecx
//	//int v18; // ecx
//	//int v19; // edx
//	//int v20; // eax
//	//int v21; // edx
//	//int v22; // ecx
//	//int v23; // eax
//	//Pad *v24; // eax
//	//CPad *v25; // eax
//	char v26; // bl
//	CPad *v27; // eax
//	CPad *v28; // eax
//	//CPad *v29; // eax
//	char v30; // al
//	//CPad *v31; // eax
//	//CPad *v32; // eax
//	char v33; // al
//	int v34; // [esp-8h] [ebp-30h]
//	char v35; // [esp+0h] [ebp-28h]
//	char wheel; // [esp+10h] [ebp-18h]
//	int bEnter = 0; // [esp+14h] [ebp-14h]
//	int bExit = 0; // [esp+18h] [ebp-10h]
//	int bUp = 0; // [esp+1Ch] [ebp-Ch]
//	int bDown = 0; // [esp+20h] [ebp-8h]
//	float v41; // [esp+24h] [ebp-4h]
//	CPad *CPad0 = CPad::GetPad(0);
//
//	//ThisMenuManager = *this;
//	if (m_bScanningUserTracks || field_1AEA)
//		return;
//
//	if (!m_bDrawMouse && m_dwOldMousePosLeft && m_dwOldMousePosTop)
//	{
//		if (m_dwOldMousePosLeft != m_dwMousePosLeft || m_dwOldMousePosTop != m_dwMousePosTop)
//			m_bDrawMouse = 1;
//	}
//
//	LikeALastSelectedMenuItem = m_dwSelectedMenuItem;
//	selectedItem = 0;
//	while (1)
//	{
//		if (MenuPages[m_nCurrentMenuPage].m_aButtons[selectedItem].m_nActionType &&
//			MenuPages[m_nCurrentMenuPage].m_aButtons[selectedItem].m_nActionType != MENU_ACTION_TEXT)
//		{
//			break;
//		}
//	LABEL_16:
//		if (++selectedItem >= 12)
//			goto MENU_ITEM_CHANGED;
//	}
//	//CFont::GetStringWidth(TheText.Get(MenuPages[m_nCurrentMenuPage].m_aButtons[selectedItem].m_szName), 1, 0);
//
//	// If current menu NOT active!!
//	if (CHud::y_fac(MenuPages[m_nCurrentMenuPage].m_aButtons[selectedItem].m_wPosnY) >= m_dwMousePosTop
//		|| CHud::y_fac(MenuPages[m_nCurrentMenuPage].m_aButtons[selectedItem].m_wPosnY + 26) <= m_dwMousePosTop)
//	{
//		if (m_bDrawMouse)
//		{
//			field_1B04 = LikeALastSelectedMenuItem;
//			m_dwSelectedMenuItem = LikeALastSelectedMenuItem;
//		}
//		goto LABEL_16;
//	}
//	if (!(field_1B74 & 1))
//	{
//		field_1B74 |= 1u;
//		field_1B70 = m_nCurrentMenuPage;
//	}
//	//byte_8CE004 = v2->field_1B04;
//	field_1B04 = selectedItem;
//	if (m_dwOldMousePosLeft && m_dwOldMousePosTop)
//	{
//		if (m_dwOldMousePosLeft != m_dwMousePosLeft || m_dwOldMousePosTop != m_dwMousePosTop)
//		{
//			m_dwSelectedMenuItem = selectedItem;
//			m_bDrawMouse = 1;
//		}
//	}
//	switch (MenuPages[m_nCurrentMenuPage].m_aButtons[selectedItem].m_nActionType)
//	{
//	case MENU_ACTION_SLIDER_BRIGHTNESS:
//	case MENU_ACTION_SLIDER_MUSIC:
//	case MENU_ACTION_SLIDER_SFX:
//	case MENU_ACTION_SLIDER_LOD:
//	case MENU_ACTION_SLIDER_MOUSESENSITIVITY:
//		break;
//	default:
//		bSlidingType = 2;
//		break;
//	}
//MENU_ITEM_CHANGED:
//
//	if (m_bDrawMouse && LikeALastSelectedMenuItem != m_dwSelectedMenuItem)
//	{
//		if (MenuPages[m_nCurrentMenuPage].m_aButtons[m_dwSelectedMenuItem].m_nActionType == MENU_ACTION_TEXT)
//		{
//			m_dwSelectedMenuItem++;
//			++field_1B04;
//		}
//		AudioEngine.ReportFrontendAudioEvent(3, 0.0, 1.0);
//	}
//	// update mouse posn
//
//	m_dwOldMousePosTop = m_dwMousePosTop;
//	m_dwOldMousePosLeft = m_dwMousePosLeft;
//	m_dwMousePosLeft = mousePosLeft_NotClipped;
//	m_dwMousePosTop = mousePosTop_NotClipped;
//	if (m_dwMousePosLeft < 0)
//		m_dwMousePosLeft = 0;
//	if (m_dwMousePosLeft > RsGlobal.maximumWidth)
//		m_dwMousePosLeft = RsGlobal.maximumWidth;
//	if (m_dwMousePosTop < 0)
//		m_dwMousePosTop = 0;
//	if (m_dwMousePosTop > RsGlobal.maximumHeight)
//		m_dwMousePosTop = RsGlobal.maximumHeight;
//	wheel = 0;
//
//	if (m_nCurrentMenuPage == MENUPAGE_CONTROLS_VEHICLE_ONFOOT)
//	{
//		if (!field_1AEA)
//			RedefineScreenUserInput(bEnter,bExit);
//		goto LABEL_113;
//	}
//	if (GetNumberOfMenuOptions() > 1)
//	{
//		AdditionalOptionInput(bUp, bDown);
//		if (CheckFrontEndDownInput())
//			bDown = 1;
//		else if (CheckFrontEndUpInput())
//			bUp = 1;
//		m_bDrawMouse = 0;
//	}
//	if (m_dwSelectedMenuItem || m_nCurrentMenuPage != MENUPAGE_PAUSE_MENU)
//	{
//		if ((CPad::NewKeyState.enter && !CPad::OldKeyState.enter
//			|| CPad::NewKeyState.extenter && !CPad::OldKeyState.extenter)
//			&& field_30 < 0
//			|| CPad0->NewState.ButtonCross && !CPad0->OldState.ButtonCross)
//		{
//			m_bDrawMouse = 0;
//			bEnter = 1;
//		}
//	}
//	else if ((!CPad::NewKeyState.enter && CPad::OldKeyState.enter
//		|| !CPad::NewKeyState.extenter && CPad::OldKeyState.extenter)
//		&& field_30 < 0
//		|| !CPad0->NewState.ButtonCross && CPad0->OldState.ButtonCross)
//	{
//		m_bDrawMouse = 0;
//		bEnter = 1;
//	}
//
//
//	CPad::GetPad(0);
//	if (!CPad::NewMouseControllerState.lmb && CPad::OldMouseControllerState.lmb && bSlidingType == 2)
//	{
//		if (m_nCurrentMenuPage == MENUPAGE_MAP
//			&& CHud::y_fac(388.0) < m_dwMousePosTop
//			|| m_bDrawMouse)
//		{
//			//v41 = m_dwMousePosTop;
//			bEnter = 1;
//		}
//	}
//	v26 = CPad::NewMouseControllerState.lmb;
//	CPad::GetPad(0);
//	if (v26)
//	{
//		switch (bSlidingType)
//		{
//		case 6:
//		case 8:
//		case 10:
//		case 12:
//		case 14:
//			v35 = 1;
//			goto LABEL_79;
//		case 7:
//		case 9:
//		case 11:
//		case 13:
//		case 15:
//			v35 = -1;
//		LABEL_79:
//			CheckSliderMovement(v35);
//			break;
//		default:
//			break;
//		}
//	}
//	CPad::GetPad(0);                              // left right sets?
//	if (CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb)
//		goto LABEL_151;
//	CPad::GetPad(0);
//	if (CPad::NewKeyState.left)
//	{
//		if (!CPad::OldKeyState.left)
//			goto LABEL_151;
//	}
//	if ((CPad::GetPad(0), CPad::NewKeyState.right) && !CPad::OldKeyState.right
//		|| (v27 = CPad::GetPad(0), v27->NewState.DPadLeft) && !v27->OldState.DPadLeft
//		|| (v28 = CPad::GetPad(0), (unsigned __int8)sub_4410E0((int)v28))
//		|| (CPad::GetPad(0), sub_5409B0())
//		|| (CPad::GetPad(0), sub_5409E0())
//		|| (CPad::GetPad(0), sub_57C400())
//		|| (CPad::GetPad(0), sub_57C420()))
//	{
//	LABEL_151:
//		switch (MenuPages[m_nCurrentMenuPage].m_aButtons[m_dwSelectedMenuItem].m_nActionType)
//		{
//		case 27:
//		case 28:
//		case 61:
//		case 62:
//			v34 = 1;
//			goto LABEL_96;
//		case 29:
//			v34 = 5;
//		LABEL_96:
//			AudioEngine.ReportFrontendAudioEvent(v34, 0.0, 1.0);
//			break;
//		default:
//			break;
//		}
//	}
//	v29 = CPad::GetPad(0);
//	if (v29->NewState.ButtonTriangle && !v29->OldState.ButtonTriangle
//		|| (CPad::GetPad(0), CPad::NewKeyState.esc) && !CPad::OldKeyState.esc)
//	{
//		v30 = m_nCurrentMenuPage;
//		if (v30 != MENUPAGE_MAIN_MENU
//			&& v30 != MENUPAGE_PAUSE_MENU
//			&& v30 != MENUPAGE_GAME_SAVE
//			&& v30 != MENUPAGE_GAME_WARNING_DONT_SAVE
//			&& v30 != MENUPAGE_SAVE_DONE_1
//			&& v30 != MENUPAGE_DELETE_FINISHED
//			&& v30 != MENUPAGE_EMPTY)
//		{
//			m_bDrawMouse = 0;
//			bExit = 1;
//		}
//	}
//	if (bDown || bUp || bEnter)
//		bExit = 0;
//LABEL_113:
//	if (CPad::NewKeyState.left
//		|| CPad::GetPad(0)->GetPedWalkLeftRight() < 0
//		|| CPad::GetPad(0)->NewState.DPadLeft)
//	{
//		if ((unsigned int)(CTimer::m_snTimeInMillisecondsPauseMode - m_dwTimeSlideLeftMove) > 200)
//		{
//			switch (MenuPages[m_nCurrentMenuPage].m_aButtons[m_dwSelectedMenuItem].m_nActionType)
//			{
//			case MENU_ACTION_STATS:
//			case MENU_ACTION_SLIDER_BRIGHTNESS:
//			case MENU_ACTION_SLIDER_MUSIC:
//			case MENU_ACTION_SLIDER_SFX:
//			case MENU_ACTION_SLIDER_LOD:
//			case MENU_ACTION_SLIDER_MOUSESENSITIVITY:
//				wheel = -1;
//				break;
//			default:
//				break;
//			}
//			ThisMenuManager.m_dwTimeSlideLeftMove = CTimer::m_snTimeInMillisecondsPauseMode;
//		}
//	}
//	else
//	{
//		CPad::GetPad(0);
//		if (CPad::NewKeyState.right
//			|| CPad::GetPad(0)->GetPedWalkLeftRight() > 0
//			|| CPad::GetPad(0)->NewState.DPadRight)
//		{
//			if ((unsigned int)(CTimer::m_snTimeInMillisecondsPauseMode - ThisMenuManager.m_dwTimeSlideRightMove) > 200)
//			{
//				switch (eMenuActions(MenuPages[m_nCurrentMenuPage].m_aButtons[m_dwSelectedMenuItem].m_nActionType))
//				{
//				case MENU_ACTION_STATS:
//				case MENU_ACTION_SLIDER_BRIGHTNESS:
//				case MENU_ACTION_SLIDER_MUSIC:
//				case MENU_ACTION_SLIDER_SFX:
//				case MENU_ACTION_SLIDER_LOD:
//				case MENU_ACTION_SLIDER_MOUSESENSITIVITY:
//					wheel = 1;
//					break;
//				default:
//					break;
//				}
//				ThisMenuManager.m_dwTimeSlideRightMove = CTimer::m_snTimeInMillisecondsPauseMode;
//			}
//		}
//	}
//	CPad::GetPad(0);
//	if (!CPad::NewMouseControllerState.wheelUp || CPad::OldMouseControllerState.wheelUp)
//	{
//		CPad::GetPad(0);
//		if (CPad::NewMouseControllerState.wheelDown
//			&& !CPad::OldMouseControllerState.wheelDown
//			&& m_nCurrentMenuPage != MENUPAGE_MAP)
//		{
//			wheel = -1;
//		}
//	}
//	else if (m_nCurrentMenuPage != MENUPAGE_MAP)
//	{
//		wheel = 1;
//	}
//	if (CheckFrontEndRightInput())
//	{
//		m_bDrawMouse = 0;
//		wheel = 1;
//		goto LABEL_140;
//	}
//	if (CheckFrontEndLeftInput())
//	{
//		m_bDrawMouse = 0;
//		wheel = -1;
//		goto LABEL_140;
//	}
//	if (wheel)
//	{
//	LABEL_140:
//		if (m_nCurrentMenuPage == MENUPAGE_AUDIO_SETTINGS
//			|| m_nCurrentMenuPage == MENUPAGE_USER_TRACKS_OPTIONS
//			|| m_nCurrentMenuPage == MENUPAGE_DISPLAY_SETTINGS
//			|| m_nCurrentMenuPage == MENUPAGE_DISPLAY_ADVANCED
//			|| m_nCurrentMenuPage == MENUPAGE_CONTROLLER_SETUP
//			|| m_nCurrentMenuPage == MENUPAGE_MOUSE_SETTINGS)
//		{
//			switch (MenuPages[v33].m_aButtons[m_dwSelectedMenuItem].m_nActionType)
//			{
//			case MENU_ACTION_BACK:
//			case MENU_ACTION_SWITCH:
//			case MENU_ACTION_CONFIGURATIONINPUT:
//			case MENU_ACTION_FOOTCONTROLs:
//			case MENU_ACTION_VEHICLECONTROLS:
//			case MENU_ACTION_SLIDER_BRIGHTNESS:
//			case MENU_ACTION_SLIDER_MUSIC:
//			case MENU_ACTION_SLIDER_SFX:
//			case MENU_ACTION_RADIOSTATION:
//			case MENU_ACTION_RESETSETTINGS:
//			case MENU_ACTION_SLIDER_LOD:
//			case MENU_ACTION_SLIDER_MOUSESENSITIVITY:
//				break;
//			default:
//				AudioEngine.ReportFrontendAudioEvent(1, 0.0, 1.0);
//				break;
//			}
//		}
//	}
//	ProcessUserInput(bDown, bUp, bEnter, bExit, wheel);
}


void CMenuManager::RedefineScreenUserInput(int enter, int exit)
{
	((void(__thiscall *)(CMenuManager*, int, int))0x57EF50)(this, enter, exit);
}

int CMenuManager::GetNumberOfMenuOptions()
{
	return ((int(__thiscall *)(CMenuManager*))0x573E70)(this);
}

int CMenuManager::AdditionalOptionInput(int bUp, int bDown)
{
	return ((int(__thiscall *)(CMenuManager*, int, int))0x5773D0)(this, bUp, bDown);
}

bool CMenuManager::CheckFrontEndDownInput()
{
	return	((bool(__thiscall *)(CMenuManager*))0x5738B0)(this);
}

bool CMenuManager::CheckFrontEndUpInput()
{
	return	((bool(__thiscall *)(CMenuManager*))0x573840)(this);
}

bool CMenuManager::CheckFrontEndRightInput()
{
	return	((bool(__thiscall *)(CMenuManager*))0x573990)(this);
}

bool CMenuManager::CheckFrontEndLeftInput()
{
	return	((bool(__thiscall *)(CMenuManager*))0x573920)(this);
}

void CMenuManager::CheckSliderMovement(char count)
{
	((void(__thiscall *)(CMenuManager*, char))0x573440)(this, count);
}

void CMenuManager::ProcessUserInput(char bDown, char bUp, char bEnter, char bExit, char wheel)
{
	((void(__thiscall *)(CMenuManager*, char, char, char, char,char ))0x57B480)(this, bDown,bUp,bEnter,bExit,wheel);
}


void CMenuManager::MyInit()
{
}


