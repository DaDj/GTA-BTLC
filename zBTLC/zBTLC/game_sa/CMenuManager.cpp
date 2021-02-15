#include "CMenuManager.h"
#include "CPad.h"
#include "CText.h"
#include "CFont.h"
#include "CTimer.h"
#include "RenderWare.h"
#include "../game_sa/CHud.h"

//#include "CAudioEngine.h"

MyDisplayoptions  CMenuManager::CustomOptions = { 0,800,600,0 };
CMenuManager &FrontEndMenuManager = *(CMenuManager *)0xBA6748;
CMenuPage	*MenuPages = (CMenuPage *)0x8CE008;

int CMenuManager::LikeALastSelectedMenuItem = 157;

bool& CMenuManager::bInvertMouseX = *(bool *)0xBA6744;
bool& CMenuManager::bInvertMouseY = *(bool *)0xBA6745;

int& CMenuManager::nLastMenuPage = *(int *)0x8CDFF0;

int& CMenuManager::ScanUserTracksProgressPos =  *(int *)0x8CE000;
int& CMenuManager::ScanUserTracksProgressPosChange = *(int *)0x8CDFFC;
bool& CMenuManager::byte_8CDFFA = *(bool *)0x8CDFFA;
int& CMenuManager::dword_B6B988 = *(int *)0xB6B988;

float CMenuManager::StretchX(float x)
{
	float width_fac = RsGlobal.maximumHeight / 448.0f;
	return x * width_fac;
}

float CMenuManager::StretchY(float y)
{
	float height_fac = RsGlobal.maximumHeight / 448.0f;
	return y * height_fac;
}

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

void CMenuManager::ProcessUserInput(int a2, char bDown, char bUp, char bEnter, char bExit, char wheel)
{
	((void(__thiscall *)(CMenuManager*,int, char, char, char, char, char))0x57B480)(this, a2, bDown, bUp, bEnter, bExit, wheel);
}

void CMenuManager::DrawBackground()
{
	int SpriteID;
	if (!m_bTexturesLoaded)
		return;
	switch (m_nCurrentMenuPage)
	{
	case MENUPAGE_STATS:
	case MENUPAGE_LANGUAGE:
	case MENUPAGE_QUIT_GAME_ASK:
	case MENUPAGE_MAIN_MENU:
	case MENUPAGE_PAUSE_MENU:
		SpriteID = 15;
		break;
	case MENUPAGE_START_GAME:
	case MENUPAGE_USER_TRACKS_OPTIONS:
	case MENUPAGE_OPTIONS:
		SpriteID = 14;
		break;
	case MENUPAGE_BRIEF:
	case MENUPAGE_LOAD_GAME:
	case MENUPAGE_DELETE_GAME:
	case MENUPAGE_GAME_SAVE:
		SpriteID = 13;
		break;
	case MENUPAGE_AUDIO_SETTINGS:
		SpriteID = 13;
		break;
	case MENUPAGE_DISPLAY_SETTINGS:
	case MENUPAGE_DISPLAY_ADVANCED:
		SpriteID = 18;
		break;
	case MENUPAGE_MAP:
	case MENUPAGE_CONTROLS_VEHICLE_ONFOOT:
		SpriteID = 0;
		break;
	case MENUPAGE_CONTROLLER_SETUP:
	case MENUPAGE_MOUSE_SETTINGS:
		SpriteID = 17;
		break;
	default:
		SpriteID = 0;
		break;
	}


	CRect BackgrndRect;
	BackgrndRect.m_fLeft = 0;
	BackgrndRect.m_fRight = RsGlobal.maximumWidth;
	BackgrndRect.m_fTop = 0;
	BackgrndRect.m_fBottom = RsGlobal.maximumHeight;
	CSprite2d::DrawRect(BackgrndRect, CRGBA::CRGBA(0, 0, 0, 255));

	FrontEndMenuManager.m_nBackgroundSprite = SpriteID;
	if (m_nBackgroundSprite)
	{
		//Letterbox crop for background
		float Ratio = RsGlobal.maximumWidth / RsGlobal.maximumHeight;
		float goalwidth = 1.77 * RsGlobal.maximumHeight;
		float goalheight = RsGlobal.maximumWidth / 1.77;
		
		if (RsGlobal.maximumWidth > goalwidth)
		{
			float heightdiff = RsGlobal.maximumHeight - goalheight;
			BackgrndRect.m_fTop =  heightdiff;
			BackgrndRect.m_fLeft = 2.0f;
		}
		else if (RsGlobal.maximumHeight > goalheight)
		{
			float widthdiff = RsGlobal.maximumWidth - goalwidth;
			BackgrndRect.m_fTop = 2.0f;
			BackgrndRect.m_fLeft = widthdiff;
		}
		else
		{
			BackgrndRect.m_fLeft = 0.0f;
			BackgrndRect.m_fTop = 1.0f;
		}
		

		BackgrndRect.m_fRight = RsGlobal.maximumWidth ;
		BackgrndRect.m_fBottom = RsGlobal.maximumHeight;
		FrontEndMenuManager.m_apBackgroundTextures[SpriteID - 13].Draw(BackgrndRect, CRGBA::CRGBA(255, 255, 255, 255));
	}

	if (m_nCurrentMenuPage == MENUPAGE_MAP)
	{
		float tmpMapBaseX = m_fMapBaseX;
		float tmpMapZoom = m_fMapZoom;
		float tmpMapBaseY = m_fMapBaseY;
		PrintMap();
		m_fMapBaseX = tmpMapBaseX;
		m_fMapZoom = tmpMapZoom;
		m_fMapBaseY = tmpMapBaseY;
	}
	if (m_nCurrentMenuPage == MENUPAGE_CONTROLS_VEHICLE_ONFOOT)
		DrawControllerSetupScreen();
	else if (m_nCurrentMenuPage == MENUPAGE_EMPTY)
		DrawQuitGameScreen();
	else
		DrawStandardMenus(1);

	if (IsKeyUnbound)
	{
		char* Text;

		if (!(field_1B4C & 1))
		{
			field_1B4C |= 1u;
			m_dwMAYBEKeyDelay = CTimer::m_snTimeInMillisecondsPauseMode;
		}
		if (FrontEndMenuManager.m_bExitMenu)
		{
			m_dwMAYBEKeyDelay = CTimer::m_snTimeInMillisecondsPauseMode;
			m_bExitMenu = 0;
		}
		
		if (RwCameraBeginUpdate(Scene.m_pRwCamera))
		{
			if (IsKeyUnbound == 1 )
				Text = "FEC_ER3"; //vehicle unbounded onf foot control
			else if (IsKeyUnbound == 2 )
				Text = "FEC_ER2"; //foot unbounded vehicle control
			else 
				Text = "FEC_ERI"; //some key not bound

			CSprite2d::SetRecipNearClip();
			CSprite2d::InitPerFrame();
			CFont::InitPerFrame();
			DefinedState2d();
			CMenuManager::SmallMessageScreen(Text);
			CFont::DrawFonts();
		}

		CFont::DrawFonts();
		if ((unsigned int)(CTimer::m_snTimeInMillisecondsPauseMode - FrontEndMenuManager.m_dwMAYBEKeyDelay) > 7000
			|| CPad::NewKeyState.esc && !CPad::OldKeyState.esc
			&& (unsigned int)(CTimer::m_snTimeInMillisecondsPauseMode - FrontEndMenuManager.m_dwMAYBEKeyDelay) > 1000)
		{
			IsKeyUnbound = 0;
			FrontEndMenuManager.m_bExitMenu = 1;
		}
		return;
	}

	//User Tracks Scanning Message
	if (m_bScanningUserTracks)
	{
		if (!(FrontEndMenuManager.field_1B4C & 2))
		{
			FrontEndMenuManager.field_1B4C |= 2u;
			FrontEndMenuManager.field_1B40 = CTimer::m_snTimeInMillisecondsPauseMode;
		}
		if (RwCameraBeginUpdate(Scene.m_pRwCamera))
		{
			CSprite2d::SetRecipNearClip();
			CSprite2d::InitPerFrame();
			CFont::InitPerFrame();
			DefinedState2d();
			CMenuManager::SmallMessageScreen("FEA_SMP");// SCANNING USER TRACKS - PLEASE WAIT~n~~n~Press ESC to cancel
			CFont::DrawFonts();
		}
		if (CTimer::m_FrameCounter & 4)
		{
			ScanUserTracksProgressPos -= ScanUserTracksProgressPosChange; //Usertracksearchbar

			if (ScanUserTracksProgressPos >= RsGlobal.maximumWidth / 2 + StretchX(50))
				ScanUserTracksProgressPosChange = StretchX(1);

			if (ScanUserTracksProgressPos <= RsGlobal.maximumWidth / 2 - StretchX(50))
			{
				ScanUserTracksProgressPos = RsGlobal.maximumWidth / 2 - StretchX(50);
				ScanUserTracksProgressPosChange = StretchX(-1);
			}
				
		}
		CRect LoadbarBgrndRect;
		LoadbarBgrndRect.m_fLeft = RsGlobal.maximumWidth/2 - StretchX(50);
		LoadbarBgrndRect.m_fTop = RsGlobal.maximumHeight/2 + StretchY(26) ;
		LoadbarBgrndRect.m_fRight = RsGlobal.maximumWidth / 2 + StretchX(50);
		LoadbarBgrndRect.m_fBottom= RsGlobal.maximumHeight / 2 + StretchY(32);
		CSprite2d::DrawRect(LoadbarBgrndRect, CRGBA::CRGBA(50,50,50,255));

	
		CRect RectLoadBar;
		RectLoadBar.m_fLeft = ScanUserTracksProgressPos;
		RectLoadBar.m_fTop = RsGlobal.maximumHeight / 2 + StretchY(26);
		RectLoadBar.m_fRight = ScanUserTracksProgressPos + StretchX(5);
		RectLoadBar.m_fBottom = RsGlobal.maximumHeight / 2 + StretchY(32);
		CSprite2d::DrawRect(RectLoadBar, CRGBA::CRGBA(225,225,225,255));
		CFont::DrawFonts();
		int v56 = 0;
		ResetHelperText();
		if (byte_8CDFFA)
		{
			FrontEndMenuManager.field_1B40 = CTimer::m_snTimeInMillisecondsPauseMode;
			byte_8CDFFA = 0;
		}
		if ( UtraxThreadDesc.startUtraxThread(5)
			|| CPad::NewKeyState.esc && !CPad::OldKeyState.esc)
		{
			if ((unsigned int)(CTimer::m_snTimeInMillisecondsPauseMode - FrontEndMenuManager.field_1B40) > 3000
				|| CPad::NewKeyState.esc && !CPad::OldKeyState.esc)
			{
				if (dword_B6B988 >= 2)
				{
					if (dword_B6B988 == 2) //v28
					{
						if (!CPad::NewKeyState.esc && !CPad::OldKeyState.esc)
						{
							UtraxThreadDesc.loadUtrax();
							 v56 = 5;
							FrontEndMenuManager.m_bScanningUserTracks = 0;
							byte_8CDFFA = 1;
							SetHelperText(v56);
							CMenuManager::DisplayHelperText(0);
							return;
						}
					}
					if (dword_B6B988 <= 3)
						dword_B6B988 = 0;
				}

				if (dword_B6B988 == 3) //v29
				{
					v56 = 4;
				}
				else if (dword_B6B988 >= 2 && !dword_B6B988 > 3)
				{			
					dword_B6B988 = 0;
				}
				if (!CPad::NewKeyState.esc && !CPad::OldKeyState.esc)
				{
					CMenuManager::DisplayHelperText(0);
					return;
				}
				v56 = 4;
				FrontEndMenuManager.m_bScanningUserTracks = 0;
				byte_8CDFFA = 1;
				SetHelperText(v56);
				CMenuManager::DisplayHelperText(0);
				return;
			}
		}
	}

	// Draw Mouse
	if (m_bDrawMouse)
	{
		int MapTop = StretchY(60.0f);
		int MaptBottom = RsGlobal.maximumHeight - StretchY(60.0f);
		int Mapleft = StretchX(60.0f);
		int MapRight = RsGlobal.maximumWidth - StretchX(60.0f);

		CFont::RenderFontBuffer();
		if (m_nCurrentMenuPage == MENUPAGE_MAP
			&& CPad::GetPad(m_nPlayerNumber)->NewMouseControllerState.lmb
			&& m_dwMousePosLeft > Mapleft && m_dwMousePosLeft < MapRight 
			&& m_dwMousePosTop > MapTop && m_dwMousePosTop < MaptBottom)
		{
			CRect MouseRect;
			MouseRect.m_fLeft = m_dwMousePosLeft;
			MouseRect.m_fRight = MouseRect.m_fLeft + StretchX(15.0f);
			MouseRect.m_fTop = m_dwMousePosTop;
			MouseRect.m_fBottom = MouseRect.m_fTop + StretchY(15.0f);
			m_apMouseTextures[1].Draw(MouseRect, CRGBA::CRGBA(255, 255, 255, 255));
		}
		else
		{
			CRect MouseRect;
			MouseRect.m_fLeft = m_dwMousePosLeft;
			MouseRect.m_fRight = MouseRect.m_fLeft + StretchX(20.0f);
			MouseRect.m_fTop = m_dwMousePosTop;
			MouseRect.m_fBottom = MouseRect.m_fTop + StretchY(20.0f);
			m_apMouseTextures[0].Draw(MouseRect, CRGBA::CRGBA(255, 255, 255, 255));
		}
	}
}

char CMenuManager::PrintMap()
{
	return	((char(__thiscall *)(CMenuManager*))0x575130)(this);
}

char CMenuManager::DrawControllerSetupScreen()
{
	return	((char(__thiscall *)(CMenuManager*))0x57F300)(this);
}

void CMenuManager::DrawQuitGameScreen()
{
	((char(__thiscall *)(CMenuManager*))0x57D860)(this);
}

char CMenuManager::DrawStandardMenus(char a2)
{
	return ((char(__thiscall *)(CMenuManager*, char))0x5794A0)(this, a2);
}

char CMenuManager::SmallMessageScreen(char* Key)
{
	return ((char(__thiscall *)(CMenuManager*, char*))0x574010)(this, Key);
}

void CMenuManager::ResetHelperText()
{
	((void(__thiscall *)(CMenuManager*))0x57CD30)(this);
}

int CMenuManager::SetHelperText(int a2)
{
	return ((int(__thiscall *)(CMenuManager*, int))0x57CD10)(this, a2);
}

char CMenuManager::DisplayHelperText(char * text)
{
	return ((char(__thiscall *)(CMenuManager*, char*))0x57E240)(this, text);
}

int CMenuManager::DisplaySlider(float x, float y, float Height, float Height2, float Width, float progress, signed int rgbaColor)
{
	float PosLeft = x;
	float PosRight = x + Width;
	float PosRightProgress = x + Width * progress;
	float PosTop = y + Height2 / 2 - 2 * Height;
	float PosBottom = PosTop + 2 * Height;

	// Draw Black background (as border)
	CRect BackgroundRectBorder = CRect(PosLeft - StretchX(1.0f), PosTop - StretchY(1.0f), PosRight + StretchX(1.0f), PosBottom + StretchY(1.0f));
	CSprite2d::DrawRect(BackgroundRectBorder, CRGBA::CRGBA(10, 10, 10, 255));

	//Draw real gray background
	CRect BackgroundRect = CRect(PosLeft, PosTop, PosRight, PosBottom);
	CSprite2d::DrawRect(BackgroundRect, CRGBA::CRGBA(100, 100, 100, 255));

	//Draw current Progress/Slider
	CRect Rect = CRect(PosLeft, PosTop, PosRightProgress, PosBottom);
	CSprite2d::DrawRect(Rect, CRGBA::CRGBA(240, 240, 240, 240));

	// Draw an slider knob
	float SizeXKnob = StretchX(2.0f);
	float OverSizeYKnob = StretchY(0.0f);
	CRect CurrentPosRect = CRect(PosRightProgress - SizeXKnob, PosTop - OverSizeYKnob, PosRightProgress + SizeXKnob, PosBottom + OverSizeYKnob);
	CSprite2d::DrawRect(CurrentPosRect, CRGBA::CRGBA(20, 20, 20, 255));

	return x + Width * progress + StretchX(2.0f);
}

void CMenuManager::DefinedState2d()
{
	((char(__thiscall *)(CMenuManager*))0x734750)(this);
}


void CMenuManager::MyInit()
{
	MemoryVP::InjectHook(0x576860, &CMenuManager::DisplaySlider, PATCH_JUMP);
	MemoryVP::InjectHook(0x57B750, &CMenuManager::DrawBackground, PATCH_JUMP);
}



