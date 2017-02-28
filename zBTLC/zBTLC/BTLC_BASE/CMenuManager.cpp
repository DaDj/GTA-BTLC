#include "CMenuManager.h"
#include <string.h>

CMenuManager &FrontEndMenuManager = *(CMenuManager *)0xBA6748;


void CMenuManager::set_new_menu()
{
	//ENTRYS: action,name,type,targetmenu,posx,posy,align
	CMenuItem		ms_pMenus[] = {

		// ID: 0  Stats
			{ "FEP_STA", 42, 3,
			21, "FES_PLA", 12, 0, 57, 120, 1,
			21, "FES_MON", 12, 0, 0, 0, 1,
			21, "FES_WEA", 12, 0, 0, 0, 1,
			21, "FES_CRI", 12, 0, 0, 0, 1,
			21, "FES_GAN", 12, 0, 0, 0, 1,
			21, "FES_ACH", 12, 0, 0, 0, 1,
			21, "FES_MIS", 12, 0, 0, 0, 1,
			21, "FES_MSC", 12, 0, 0, 0, 1,
			2, "FEDS_TB", 11, 42, 320, 380, 3
			},
			// ID: 1  Game(New game,load game,delete game) 
			{ "FEH_LOA", 42, 1,
			10, "FES_NGA", 11, 6, 80, 150, 1,
			5, "FES_LOA", 11, 9, 0, 0, 1,
			5, "FES_DEL", 11, 10, 0, 0, 1,
			2, "FEDS_TB", 11, 0, 490, 380, 1
			},
			// ID: 2  Brief
			{ "FEH_BRI", 42, 4,
			2, "FEDS_TB", 11, 42, 57, 410, 1
			},
			// ID: 3  Audio
			{ "FEH_AUD", 33, 1,
			28, "FEA_MUS", 12, 3, 57, 100, 1,
			29, "FEA_SFX", 12, 3, 0, 0, 1,
			30, "FEA_BAS", 12, 3, 0, 0, 1,
			31, "FEA_ART", 12, 3, 0, 0, 1,
			5, "FEA_TIT", 11, 26, 320, 225, 3,
			32, "FEA_RSS", 12, 3, 57, 260, 1,
			5, "FET_DEF", 11, 24, 320, 367, 3,
			2, "FEDS_TB", 11, 42, 0, 0, 3
			},
			// ID: 4  Display
			{ "FEH_DIS", 33, 2,
			27, "FED_BRI", 12, 4, 57, 127, 1,
			33, "MAP_LEG", 12, 4, 0, 0, 1,
			34, "FED_RDR", 12, 4, 0, 0, 1,
			35, "FED_HUD", 12, 4, 0, 0, 1,
			25, "FED_SUB", 12, 4, 0, 0, 1,
			65, "FED_GLS", 12, 4, 0, 0, 1,
			5, "FED_ADV", 11, 27, 320, 320, 3,
			5, "FET_DEF", 11, 23, 320, 365, 3,
			2, "FEDS_TB", 11, 33, 0, 0, 3
			},
			// ID: 5  Map
			{ "FEH_MAP", 42, 2,
			2, "FEDS_TB", 11, 42, 57, 410, 1
			},
			// ID: 6  New Game (if a game already loaded)
			{ "FES_NGA", 1, 0,
			1, "FESZ_QR", 0, 0, 0, 0, 0,
			4, "FEM_NO", 11, 1, 320, 215, 3,
			14, "FEM_YES", 11, 6, 320, 240, 3
			},
			// ID: 7  New Game (if mission pack available)
			{ "FES_NGA", 1, 0,
			1, "FEN_NGS", 0, 0, 0, 0, 1,
			5, "FEN_NGX", 11, 6, 320, 150, 3,
			11, "FEN_MPX", 9, 0, 0, 0, 3,
			11, "FEN_MPX", 9, 0, 0, 0, 3,
			11, "FEN_MPX", 9, 0, 0, 0, 3,
			11, "FEN_MPX", 9, 0, 0, 0, 3,
			11, "FEN_MPX", 9, 0, 0, 0, 3,
			11, "FEN_MPX", 9, 0, 0, 0, 3,
			11, "FEN_MPX", 9, 0, 0, 0, 3,
			11, "FEN_MPX", 9, 0, 0, 0, 3,
			11, "FEN_MPX", 9, 0, 0, 0, 3,
			11, "FEN_MPX", 9, 0, 0, 0, 3
			},
			// ID: 8 Load Mission
			{ "FES_LMI", 1, 0,
			1, "FESZ_QM", 0, 0, 0, 0, 0,
			4, "FEM_NO", 11, 1, 320, 215, 3,
			12, "FEM_YES", 11, 0, 320, 240, 3
			},
			// ID: 9  Load Game (load savegame/slot screen)
			{ "FET_LG", 1, 1,
			1, "FES_SEL", 0, 0, 0, 0, 1,
			13, "FEM_SL1", 1, 0, 80, 150, 1,
			13, "FEM_SL2", 2, 0, 80, 170, 1,
			13, "FEM_SL3", 3, 0, 80, 190, 1,
			13, "FEM_SL4", 4, 0, 80, 210, 1,
			13, "FEM_SL5", 5, 0, 80, 230, 1,
			13, "FEM_SL6", 6, 0, 80, 250, 1,
			13, "FEM_SL7", 7, 0, 80, 270, 1,
			13, "FEM_SL8", 8, 0, 80, 290, 1,
			2, "FEDS_TB", 11, 0, 490, 380, 3
			},
			// ID: 10  Delte Game(delete savegame)
			{ "FES_DEL", 1, 2,
			1, "FES_SED", 0, 0, 0, 0, 1,
			13, "FEM_SL1", 1, 0, 80, 150, 1,
			13, "FEM_SL2", 2, 0, 80, 170, 1,
			13, "FEM_SL3", 3, 0, 80, 190, 1,
			13, "FEM_SL4", 4, 0, 80, 210, 1,
			13, "FEM_SL5", 5, 0, 80, 230, 1,
			13, "FEM_SL6", 6, 0, 80, 250, 1,
			13, "FEM_SL7", 7, 0, 80, 270, 1,
			13, "FEM_SL8", 8, 0, 80, 290, 1,
			2, "FEDS_TB", 11, 0, 490, 380, 3
			},
			// ID: 11  Load game (All unsaved progress in your current game will be lost.)
			{ "FET_LG", 9, 0,
			1, "FESZ_QL", 0, 0, 0, 0, 0,
			4, "FEM_NO", 11, 9, 320, 215, 3,
			3, "FEM_YES", 11, 13, 320, 240, 3
			},
			// ID: 12  Delete Game(delete savegame question)
			{ "FES_DEL", 10, 0,
			1, "FESZ_QD", 0, 0, 0, 0, 0,
			4, "FEM_NO", 11, 10, 320, 215, 3,
			3, "FEM_YES", 11, 14, 320, 240, 3
			},
			// ID: 13  Load game
			{ "FET_LG", 9, 0
			},
			// ID: 14  Delete Game
			{ "FES_DEL", 10, 0
			},
			// ID: 15  Delete Game Delete Successful.
			{ "FES_DEL", 1, 0,
			1, "FES_DSC", 0, 0, 0, 0, 0,
			5, "FEM_OK", 11, 1, 320, 240, 3
			},
			// ID: 16 Save Game
			{ "FET_SG", 4294967295, 0,
			1, "FES_SES", 0, 0, 0, 0, 1,
			18, "FEM_SL1", 1, 17, 80, 150, 1,
			18, "FEM_SL2", 2, 17, 80, 170, 1,
			18, "FEM_SL3", 3, 17, 80, 190, 1,
			18, "FEM_SL4", 4, 17, 80, 210, 1,
			18, "FEM_SL5", 5, 17, 80, 230, 1,
			18, "FEM_SL6", 6, 17, 80, 250, 1,
			18, "FEM_SL7", 7, 17, 80, 270, 1,
			18, "FEM_SL8", 8, 17, 80, 290, 1,
			15, "FESZ_CA", 11, 0, 470, 380, 3
			},
			// ID: 17 Save Game (question)
			{ "FET_SG", 16, 0,
			1, "FESZ_QZ", 0, 0, 0, 0, 0,
			4, "FEM_NO", 11, 16, 320, 215, 3,
			3, "FEM_YES", 11, 18, 320, 240, 3
			},
			// ID: 18 Save Game
			{ "FET_SG", 16, 0
			},
			// ID: 19  Save Game (confirm done)
			{ "FET_SG", 16, 0,
			1, "FES_SSC", 0, 0, 0, 0, 0,
			54, "FEM_OK", 11, 0, 320, 240, 3
			},
			// ID: 20  Save Game
			{ "FET_SG", 42, 0
			},
			// ID: 21 Load Game
			{ "FET_LG", 42, 0
			},
			// ID: 22 Save Game(Warning! One or more cheats have been activated)
			{ "FET_SG", 1, 0,
			1, "FES_CHE", 0, 0, 0, 0, 0,
			5, "FEM_OK", 11, 16, 320, 240, 3
			},
			// ID: 23  Display (Are you sure you want to reset)
			{ "FEH_DIS", 4, 7,
			1, "FED_RDP", 0, 0, 0, 0, 0,
			5, "FEM_NO", 11, 4, 320, 215, 3,
			57, "FEM_YES", 11, 4, 320, 240, 3
			},
			// ID: 24  Audio(question reset)
			{ "FEH_AUD", 3, 6,
			1, "FED_RDP", 0, 0, 0, 0, 0,
			5, "FEM_NO", 11, 3, 320, 215, 3,
			57, "FEM_YES", 11, 3, 320, 240, 3
			},
			// ID: 25  Controller Setup
			{ "FET_CTL", 36, 3,
			1, "FED_RDP", 0, 0, 0, 0, 0,
			5, "FEM_NO", 11, 36, 320, 215, 3,
			57, "FEM_YES", 11, 36, 320, 240, 3
			},
			// ID: 26  User Tracks
			{ "FEA_TIT", 3, 4, 
			1, "FEA_SUB", 0, 0, 0, 0, 0,
			63, "FEA_MPM", 12, 26, 57, 190, 1,
			64, "FEA_AMS", 12, 26, 0, 0, 1,
			6, "FEA_SCN", 11, 26, 0, 0, 1,
			2, "FEDS_TB", 11, 3, 320, 360, 3
			},
			// ID: 27  Display (settings)
			{ "FEH_DIS", 4, 3,
			61, "FEM_LOD", 12, 27, 57, 127, 1, //DRAW DISTANCE
			24, "FEM_FRM", 12, 27, 0, 0, 1, //FRAME LIMITER
			26, "FED_WIS", 12, 27, 0, 0, 1, //Widescreen
			42, "FED_FXQ", 12, 27, 0, 0, 1, //VISUAL FX QUALITY
			43, "FED_MIP", 12, 27, 0, 0, 1, //MIP MAPPING
			44, "FED_AAS", 12, 27, 0, 0, 1, //ANTI ALIASING
			56, "FED_RES", 12, 27, 0, 0, 1, //RESOLUTION
			2, "FEDS_TB", 11, 4, 320, 360, 3 
			},
			// ID: 28 Language
			{ "FEH_LAN", 33, 3, 
			37, "FEL_ENG", 11, 28, 320, 132, 3,
			41, "FEL_SPA", 11, 28, 0, 0, 3,
			2, "FEDS_TB", 11, 4, 490, 380, 1
			},
			// ID: 29  Save Game
			{ "FET_SG", 1, 0,
			1, "FED_LWR", 0, 0, 0, 0, 0, //
			5, "FEC_OKK", 11, 16, 0, 0, 0 //O.K.
			},
			// ID: 30   Save Game
			{ "FET_SG", 16, 0,
			1, "FEC_SVU", 0, 0, 0, 0, 0, //Save Unsuccessful. 
			5, "FEC_OKK", 11, 16, 0, 0, 0 //O.K.
			},
			// ID: 31  Load Game
			{ "FET_LG", 16, 0,
			1, "FEC_SVU", 0, 0, 0, 0, 0 //Save Unsuccessful. 
			},
			// ID: 32  Load Game
			{ "FET_LG", 1, 0,
			1, "FEC_LUN", 0, 0, 0, 0, 0, //Load Unsuccessful. File Corrupted, Please delete.
			2, "FEDS_TB", 11, 1, 0, 0, 0
			},
			// ID: 33  Options
			{ "FET_OPT", 42, 5,
			5, "FEO_CON", 11, 36, 210, 152, 3, //Controller Setup
			5, "FEO_AUD", 11, 3, 0, 0, 3, //Audio Setup
			5, "FEO_DIS", 11, 4, 0, 0, 3, //Display Setup
			5, "FEH_LAN", 11, 28, 0, 0, 3, //Language
			2, "FEDS_TB", 11, 0, 490, 380, 1 
			},
			// ID: 34  Main Menu
			{ "FEM_MM", 255, 0,
			10, "FES_NGA", 11, 6, 80, 150, 1,
			5, "FES_LOA", 11, 9, 0, 0, 1,
			5, "FEP_STG", 11, 1, 0, 0, 1,
			5, "FEP_OPT", 11, 33, 0, 0, 1,
			5, "FEP_QUI", 11, 35, 0, 0, 1
			},
			// ID: 35 
			{ "FET_QG", 42, 6,
			1, "FEQ_SRE", 0, 0, 0, 0, 0,
			55, "FEM_NO", 11, 42, 320, 215, 3,
			53, "FEM_YES", 11, 42, 320, 240, 3
			},
			// ID: 36 
			{ "FET_CTL", 33, 0,
			58, "FEC_CFG", 12, 36, 57, 150, 1,
			5, "FEC_RED", 11, 37, 320, 195, 3,
			7, "FEC_CFG", 10, 36, 0, 0, 3,
			5, "FET_DEF", 11, 25, 320, 275, 3,
			2, "FEDS_TB", 11, 0, 0, 0, 3
			},
			// ID: 37 
			{ "FET_CTL", 36, 1,
			8, "FET_CFT", 11, 38, 320, 190, 3,
			9, "FET_CCR", 11, 38, 0, 0, 3,
			2, "FEDS_TB", 11, 36, 320, 270, 3
			},
			// ID: 38 
			{ "FET_CTL", 37, 0
			},
			// ID: 39 
			{ "FEC_MOU", 36, 2,
			62, "FEC_MSH", 12, 39, 40, 130, 1,
			46, "FEC_IVV", 12, 39, 0, 0, 1,
			59, "FET_MST", 12, 39, 0, 0, 1,
			60, "FET_MFL", 12, 39, 0, 0, 1,
			2, "FEDS_TB", 11, 0, 320, 290, 3
			},
			// ID: 40 
			{ "FEJ_TIT", 36, 2,
			47, "FEJ_INX", 12, 40, 40, 130, 1,
			48, "FEJ_INY", 12, 40, 0, 0, 1,
			51, "FEJ_INA", 12, 40, 0, 0, 1,
			49, "FEJ_RNX", 12, 40, 40, 245, 1,
			50, "FEJ_RNY", 12, 40, 0, 0, 1,
			52, "FEJ_RNA", 12, 40, 0, 0, 1,
			2, "FEDS_TB", 11, 0, 320, 370, 3
			},
			// ID: 41 
			{ "FET_PAU", 255, 0,
			54, "FEP_RES", 11, 0, 80, 140, 1,
			5, "FEH_MAP", 11, 5, 0, 0, 1,
			//5, "FEP_STA", 11, 0, 0, 0, 1,
			5, "FEH_BRI", 11, 2, 0, 0, 1,
			5, "FEH_SGA", 11, 1, 0, 0, 1,
			5, "FEP_OPT", 11, 33, 0, 0, 1,
			5, "FEP_QUI", 11, 35, 0, 0, 1
			}
	};
	
	memcpy((void*)0x8CE008, &ms_pMenus, sizeof(ms_pMenus));

} 	