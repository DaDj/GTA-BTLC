#pragma once
#include "plbase/PluginBase_SA.h"
#include "CFont.h"

enum eMenuType : char
{
	MENU_TYPE_DEFAULT,
	MENU_TYPE_GRID,
};

#pragma pack(push, 1)
class CMenuPanel
{
public:
	char			m_anUsedCarColors[64];
	eMenuType		m_nType;
	char			m_aaacRowTitles[4][12][10];
	char			_pad1[3];
	int			m_aadwNumberInRowTitle[4][12];
	int			m_aadw2ndNumberInRowTitle[4][12];
	char			m_aacColumnHeaders[4][10];
	char			m_acTitle[10];
	bool			m_abRowSelectable[12];
	bool			m_abRowAlreadyBought[12];
	eFontAlignment	m_anColumnAlignment[4];
	eFontAlignment	m_anColumnHeaderAlignment[4];
	char			m_nNumRows;
	char			m_nNumColumns;
	bool			m_abColumnInteractive[4];
	float			m_afColumnWidth[4];
	CVector2D		m_vPosn;
	bool			m_bColumnBackground;
	char			m_nSelectedRow;
	char			m_nAcceptedRow;
	char			_pad2;

	//static CMenuPanel *MenuNumber[2];
};
#pragma pack(pop)

VALIDATE_SIZE(CMenuPanel, 0x418);

extern CMenuPanel *MenuNumber;
