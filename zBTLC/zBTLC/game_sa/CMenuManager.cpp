#include "CMenuManager.h"
#include "CPad.h"
#include "CText.h"
#include "CFont.h"
#include "CTimer.h"
#include "RenderWare.h"
//#include "CAudioEngine.h"


CMenuManager &FrontEndMenuManager = *(CMenuManager *)0xBA6748;
CMenuPage	*MenuPages = (CMenuPage *)0x8CE008;

int CMenuManager::LikeALastSelectedMenuItem = 157;

bool& CMenuManager::bInvertMouseX = *(bool *)0xBA6744;
bool& CMenuManager::bInvertMouseY = *(bool *)0xBA6745;

int& CMenuManager::nLastMenuPage = *(int *)0x8CDFF0;

void CMenuManager::ProcessStreaming(char bImmediately)
{
	m_bTexturesLoaded = 0;
}

void CMenuManager::UserInput()
{
	CMenuManager *v2; // esi
	//char DrawMouse; // al
	int v4; // ecx
	int v5; // eax
	char selectedItem; // bl
	int v7; // ecx
	int v8; // edi
	int v9; // eax
	char v10; // cl
	char *v11; // eax
	int v12; // eax
	float v13; // ST08_4
	float v14; // ST18_4
	float v15; // ST08_4
	int v16; // eax
	int v17; // ecx
	int v18; // ecx
	int v19; // edx
	int v20; // eax
	int v21; // edx
	int v22; // ecx
	int v23; // eax
	CPad *v24; // eax
	CPad *v25; // eax
	char v26; // bl
	CPad *v27; // eax
	CPad *v28; // eax
	CPad *v29; // eax
	char v30; // al
	CPad *v31; // eax
	CPad *v32; // eax
	char v33; // al
	int v34; // [esp-8h] [ebp-30h]
	char v35; // [esp+0h] [ebp-28h]
	char wheel; // [esp+10h] [ebp-18h]
	int bEnter = 0; // [esp+14h] [ebp-14h]
	int bExit = 0; // [esp+18h] [ebp-10h]
	int bUp = 0; // [esp+1Ch] [ebp-Ch]
	int bDown = 0; // [esp+20h] [ebp-8h]
	float v41; // [esp+24h] [ebp-4h]

	v2 = this;
	if (this->m_bScanningUserTracks || this->field_1AEA)
		return;
	                
	if (!m_bDrawMouse)
	{
		v4 = m_dwOldMousePosLeft;
		if (v4)
		{
			v5 = v2->m_dwOldMousePosTop;
			if (v5)
			{
				if (v4 != v2->m_dwMousePosLeft || v5 != v2->m_dwMousePosTop)
					v2->m_bDrawMouse = 1;
			}
		}
	}
	LikeALastSelectedMenuItem = v2->m_dwSelectedMenuItem;
	selectedItem = 0;
	while (1)
	{
		v7 = v2->m_nCurrentMenuPage;
		v8 = selectedItem;
		v9 = v7 * 226 + v8 * 18;
		v10 = MenuPages[v7].m_aButtons[v8].m_nActionType;
		if (v10)
		{
			if (v10 != 1)
				break;
		}
	LABEL_16:
		if (++selectedItem >= 12)
			goto MENU_ITEM_CHANGED;
	}
	v11 = TheText.Get(&MenuPages[0].m_aButtons[0].m_szName[v9]);
	CFont::GetStringWidth(v11, 1, 0);
	v12 = v2->m_nCurrentMenuPage;
	v41 = (double)v2->m_dwMousePosTop;
	v13 = (double)MenuPages[v12].m_aButtons[v8].m_wPosnY;
	if (CMenuManager::StretchY(v13) >= v41
		|| (v14 = (double)v2->m_dwMousePosTop,
			v41 = MenuPages[v2->m_nCurrentMenuPage].m_aButtons[v8].m_wPosnY + 26,
			v15 = v41,
			CMenuManager::StretchY(v15) <= v14))
	{
		if (v2->m_bDrawMouse)
		{
			v16 = LikeALastSelectedMenuItem;
			v2->field_1B04 = LikeALastSelectedMenuItem;
			v2->m_dwSelectedMenuItem = v16;
		}
		goto LABEL_16;
	}
	if (!(FrontEndMenuManager.field_1B74 & 1))
	{
		v17 = v2->m_nCurrentMenuPage;
		FrontEndMenuManager.field_1B74 |= 1u;
		FrontEndMenuManager.field_1B70 = v17;
	}
	v18 = v2->m_dwOldMousePosLeft;
	//byte_8CE004 = v2->field_1B04;
	v2->field_1B04 = selectedItem;
	if (v18)
	{
		v19 = v2->m_dwOldMousePosTop;
		if (v19)
		{
			if (v18 != v2->m_dwMousePosLeft || v19 != v2->m_dwMousePosTop)
			{
				v2->m_dwSelectedMenuItem = selectedItem;
				v2->m_bDrawMouse = 1;
			}
		}
	}
	switch (MenuPages[v2->m_nCurrentMenuPage].m_aButtons[selectedItem].m_nActionType)
	{
	case MENU_ACTION_SLIDER_BRIGHTNESS:
	case MENU_ACTION_SLIDER_MUSIC:
	case MENU_ACTION_SLIDER_SFX:
	case MENU_ACTION_SLIDER_LOD:
	case MENU_ACTION_SLIDER_MOUSESENSITIVITY:
		break;
	default:
		v2->bSlidingType = 2;
		break;
	}
	MENU_ITEM_CHANGED:
		if (v2->m_bDrawMouse)
		{
			v20 = v2->m_dwSelectedMenuItem;
			if (LikeALastSelectedMenuItem != v20)
			{
				if (MenuPages[v2->m_nCurrentMenuPage].m_aButtons[v20].m_nActionType == 1)
				{
					v2->m_dwSelectedMenuItem = v20 + 1;
					++v2->field_1B04;
				}
				AudioEngine.ReportFrontendAudioEvent(3, 0.0, 1.0);
			}
		}                                             // update mouse posn
	v21 = v2->m_dwMousePosLeft;
	v22 = v2->mousePosTop_NotClipped;
	v2->m_dwOldMousePosTop = v2->m_dwMousePosTop;
	v23 = v2->mousePosLeft_NotClipped;
	v2->m_dwOldMousePosLeft = v21;
	v2->m_dwMousePosLeft = v23;
	v2->m_dwMousePosTop = v22;
	if (v23 < 0)
		v2->m_dwMousePosLeft = 0;
	if (v2->m_dwMousePosLeft > RsGlobal.maximumWidth)
		v2->m_dwMousePosLeft = RsGlobal.maximumWidth;
	if (v22 < 0)
		v2->m_dwMousePosTop = 0;
	if (v2->m_dwMousePosTop > RsGlobal.maximumHeight)
		v2->m_dwMousePosTop = RsGlobal.maximumHeight;
	wheel = 0;
	if (v2->m_nCurrentMenuPage == MENUPAGE_CONTROLS_VEHICLE_ONFOOT)
	{
		if (!v2->field_1AEA)
			CMenuManager::RedefineScreenUserInput(v2, (int)&bEnter, (int)&bExit);
		goto LABEL_113;
	}
	if ((unsigned __int8)CMenuManager::GetNumberOfMenuOptions(v2) > 1u)
	{
		CMenuManager::AdditionalOptionInput(v2, (int)&bUp, (int)&bDown);
		if (CMenuManager::CheckFrontEndDownInput(v2))
		{
			bDown = 1;
			goto LABEL_48;
		}
		if (CMenuManager::CheckFrontEndUpInput(v2))
		{
			bUp = 1;
		LABEL_48:
			v2->m_bDrawMouse = 0;
		}
	}
	if (v2->m_dwSelectedMenuItem || v2->m_nCurrentMenuPage != MENUPAGE_PAUSE_MENU)
	{
		CPad::GetPad(0);
		if ((CPad::NewKeyState.enter && !CPad::OldKeyState.enter
			|| CPad::NewKeyState.extenter && !CPad::OldKeyState.extenter)
			&& v2->field_30 < 0
			|| (v25 = CPad::GetPad(0), v25->NewState.ButtonCross) && !v25->OldState.ButtonCross)
		{
		LABEL_66:
			v2->m_bDrawMouse = 0;
			bEnter = 1;
		}
	}
	else
	{
		CPad *Pad1 = CPad::GetPad(0);
		if ((!CPad::NewKeyState.enter && CPad::OldKeyState.enter
			|| !CPad::NewKeyState.extenter && CPad::OldKeyState.extenter)
			&& v2->field_30 < 0)
		{
			goto LABEL_66;
		}
		v24 = CPad::GetPad(0);
		if (!v24->NewState.ButtonCross)
		{
			if (v24->OldState.ButtonCross)
				goto LABEL_66;
		}
	}
	CPad::GetPad(0);
	if (!CPad::NewMouseControllerState.lmb && CPad::OldMouseControllerState.lmb && v2->bSlidingType == 2)
	{
		if (v2->m_nCurrentMenuPage == MENUPAGE_MAP 
			&& CMenuManager::StretchY(388.0) < (double)v2->m_dwMousePosTop
			|| v2->m_bDrawMouse)
		{
			v41 = (double)v2->m_dwMousePosTop;
			bEnter = 1;
		}
	}
	v26 = CPad::NewMouseControllerState.lmb;
	CPad::GetPad(0);
	if (v26)
	{
		switch (v2->bSlidingType)
		{
		case 6:
		case 8:
		case 10:
		case 12:
		case 14:
			v35 = 1;
			goto LABEL_79;
		case 7:
		case 9:
		case 11:
		case 13:
		case 15:
			v35 = -1;
		LABEL_79:
			CMenuManager::CheckSliderMovement(v2, v35);
			break;
		default:
			break;
		}
	}
	CPad::GetPad(0);                              // left right sets?
	if (CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb)
		goto LABEL_151;
	CPad::GetPad(0);
	if (CPad::NewKeyState.left)
	{
		if (!CPad::OldKeyState.left)
			goto LABEL_151;
	}
	if ((CPad::GetPad(0), CPad::NewKeyState.right) && !CPad::OldKeyState.right
		|| (v27 = CPad::GetPad(0), v27->NewState.DPadLeft) && !v27->OldState.DPadLeft
		|| (v28 = CPad::GetPad(0), (unsigned __int8)sub_4410E0((int)v28))
		|| (CPad::GetPad(0), sub_5409B0())
		|| (CPad::GetPad(0), sub_5409E0())
		|| (CPad::GetPad(0), sub_57C400())
		|| (CPad::GetPad(0), sub_57C420()))
	{
	LABEL_151:
		switch (MenuPages[v2->m_nCurrentMenuPage].m_aButtons[v2->m_dwSelectedMenuItem].m_nActionType)
		{
		case 27:
		case 28:
		case 61:
		case 62:
			v34 = 1;
			goto LABEL_96;
		case 29:
			v34 = 5;
		LABEL_96:
			AudioEngine.ReportFrontendAudioEvent(v34, 0.0, 1.0);
			break;
		default:
			break;
		}
	}
	v29 = CPad::GetPad(0);
	if (v29->NewState.ButtonTriangle && !v29->OldState.ButtonTriangle
		|| (CPad::GetPad(0), CPad::NewKeyState.esc) && !CPad::OldKeyState.esc)
	{
		v30 = v2->m_nCurrentMenuPage;
		if (v30 != MENUPAGE_MAIN_MENU
			&& v30 != MENUPAGE_PAUSE_MENU
			&& v30 != MENUPAGE_GAME_SAVE
			&& v30 != MENUPAGE_GAME_WARNING_DONT_SAVE
			&& v30 != MENUPAGE_SAVE_DONE_1
			&& v30 != MENUPAGE_DELETE_FINISHED
			&& v30 != MENUPAGE_EMPTY)
		{
			v2->m_bDrawMouse = 0;
			bExit = 1;
		}
	}
	if (bDown || bUp ||bEnter)
		bExit = 0;
LABEL_113:
	if (CPad::NewKeyState.left
		||  CPad::GetPad(0)->GetPedWalkLeftRight() < 0
		|| CPad::GetPad(0)->NewState.DPadLeft)
	{
		if ((unsigned int)(CTimer::m_snTimeInMillisecondsPauseMode - FrontEndMenuManager.m_dwTimeSlideLeftMove) > 200)
		{
			switch (MenuPages[v2->m_nCurrentMenuPage].m_aButtons[v2->m_dwSelectedMenuItem].m_nActionType)
			{
			case 21:
			case MENU_ACTION_SLIDER_BRIGHTNESS:
			case MENU_ACTION_SLIDER_MUSIC:
			case MENU_ACTION_SLIDER_SFX:
			case MENU_ACTION_SLIDER_LOD:
			case MENU_ACTION_SLIDER_MOUSESENSITIVITY:
				wheel = -1;
				break;
			default:
				break;
			}
			FrontEndMenuManager.m_dwTimeSlideLeftMove = CTimer::m_snTimeInMillisecondsPauseMode;
		}
	}
	else
	{
		CPad::GetPad(0);
		if (CPad::NewKeyState.right
			|| CPad::GetPad(0)->GetPedWalkLeftRight() > 0
			|| CPad::GetPad(0)->NewState.DPadRight)
		{
			if ((unsigned int)(CTimer::m_snTimeInMillisecondsPauseMode - FrontEndMenuManager.m_dwTimeSlideRightMove) > 200)
			{
				switch (MenuPages[v2->m_nCurrentMenuPage].m_aButtons[v2->m_dwSelectedMenuItem].m_nActionType)
				{
				case 21:
				case 27:
				case 28:
				case 29:
				case 61:
				case 62:
					wheel = 1;
					break;
				default:
					break;
				}
				FrontEndMenuManager.m_dwTimeSlideRightMove = CTimer::m_snTimeInMillisecondsPauseMode;
			}
		}
	}
	CPad::GetPad(0);
	if (!CPad::NewMouseControllerState.wheelUp || CPad::OldMouseControllerState.wheelUp)
	{
		CPad::GetPad(0);
		if (CPad::NewMouseControllerState.wheelDown
			&& !CPad::OldMouseControllerState.wheelDown
			&& v2->m_nCurrentMenuPage != MENUPAGE_MAP)
		{
			wheel = -1;
		}
	}
	else if (v2->m_nCurrentMenuPage != MENUPAGE_MAP)
	{
		wheel = 1;
	}
	if (CMenuManager::CheckFrontEndRightInput((int)v2))
	{
		v2->m_bDrawMouse = 0;
		wheel = 1;
		goto LABEL_140;
	}
	if (CMenuManager::CheckFrontEndLeftInput((int)v2))
	{
		v2->m_bDrawMouse = 0;
		wheel = -1;
		goto LABEL_140;
	}
	if (wheel)
	{
	LABEL_140:
		v33 = v2->m_nCurrentMenuPage;
		if (v33 == MENUPAGE_AUDIO_SETTINGS
			|| v33 == MENUPAGE_USER_TRACKS_OPTIONS
			|| v33 == MENUPAGE_DISPLAY_SETTINGS
			|| v33 == MENUPAGE_DISPLAY_ADVANCED
			|| v33 == MENUPAGE_CONTROLLER_SETUP
			|| v33 == MENUPAGE_MOUSE_SETTINGS)
		{
			switch (MenuPages[v33].m_aButtons[v2->m_dwSelectedMenuItem].m_nActionType)
			{
			case MENU_ACTION_BACK:
			case MENU_ACTION_SWITCH:
			case 7:
			case 8:
			case 9:
			case 27:
			case 28:
			case 29:
			case 32:
			case 57:
			case 61:
			case 62:
				break;
			default:
			AudioEngine.ReportFrontendAudioEvent(1, 0.0, 1.0);
				break;
			}
		}
	}
	CMenuManager::ProcessUserInput(v2, a2, bDown, bUp, bEnter, bExit, wheel);
}

void CMenuManager::MyInit()
{
}


