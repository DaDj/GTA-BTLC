#pragma once
#include "plbase/PluginBase_SA.h"
#include "CMenuPanel.h"

class CMenuSystem
{
public:
	static char *MenuInUse[2];
	static bool *CurrentMenuInUse;
	static char &NumMenusInUse;

	static void ActivateItems(unsigned char panelId, bool item1, bool item2, bool item3, bool item4, bool item5, bool item6, bool item7, bool item8, bool item9, bool item10, bool item11, bool item12);
	static void ActivateOneItem(unsigned char panelId, unsigned char rowId, bool enable);
	
	// Returns panel Id
	static unsigned char CreateNewMenu(eMenuType type, char *pTitle, float posX, float posY, float width, char columns, bool interactive, bool background, eFontAlignment alignment);
	
	static char CheckForAccept(unsigned char panelId);
	static char CheckForSelected(unsigned char panelId);
	static void Initialise();
	static void Process(unsigned char panelId);
	static CMenuPanel* InputStandardMenu(unsigned char panelId);
	static CMenuPanel* InputGridMenu(unsigned char panelId);
	static void DisplayStandardMenu(unsigned char panelId, bool bBrightFont);
	static void DisplayGridMenu(unsigned char panelId, bool bBrightFont);
	static void HighlightOneItem(unsigned char panelId, unsigned char itemId, bool bHighlight = true);
	static CMenuPanel** InsertMenu(unsigned char panelId, unsigned char columnId, char *pTitle, char *str1, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7, char *str8, char *str9, char *str10, char *str11, char *str12);
	static CMenuPanel* InsertOneMenuItem(unsigned char panelId, unsigned char columnId, unsigned char rowId, char *str);
	static CMenuPanel* InsertOneMenuItemWithNumber(unsigned char panelId, unsigned char columnId, unsigned char rowId, char *str, int number1, int number2);
	static void SetActiveMenuItem(unsigned char panelId, char rowId);
	static void SetColumnHeader(unsigned char panelId, unsigned char columnId, char *str);
	static void SetColumnOrientation(unsigned char panelId, unsigned char columnId, eFontAlignment alignment);
	static void SetColumnWidth(unsigned char panelId, unsigned char columnId, unsigned short width);
	static void SetDPadInput(unsigned char panelId, bool bEnable);
	static void SetHeaderOrientation(unsigned char panelId, unsigned char columnId, eFontAlignment alignment);
	static void SwitchOffMenu(unsigned char panelId);
};
