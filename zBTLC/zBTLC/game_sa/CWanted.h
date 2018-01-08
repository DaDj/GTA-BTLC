#pragma once

#include "plbase/PluginBase_SA.h"
#include "CCrimeBeingQd.h"
#include "CWantedAudio.h"

#pragma pack(push, 1)
class CWanted
{
public:
	unsigned int  m_dwChaosLevel;
	unsigned int  m_dwChaosLevelBeforeParole;
	unsigned int  m_dwLastTimeWantedDecreased;
	unsigned int  m_dwLastTimeWantedLevelChanged;
	unsigned int  m_dwTimeOfParole;
	float             m_fMultiplier;
	unsigned char   m_bCopsInPursuit;
	unsigned char   m_bMaxCopsInPursuit;
	unsigned char   m_bMaxCopCarsInPursuit;
	unsigned char   m_bCopsBeatingSuspect;
	unsigned short  m_wChanceOnRoadBlock;
	unsigned char   m_bPoliceBackOff : 1;       // If this is set the police will leave player alone (for cut-scenes)
    unsigned char   m_bPoliceBackOffGarage : 1; // If this is set the police will leave player alone (for garages)
    unsigned char   m_bEverybodyBackOff : 1;    // If this is set then everybody (including police) will leave the player alone (for cut-scenes)
    unsigned char   m_bSwatRequired : 1;        // These three booleans are needed so that the
    unsigned char   m_bFbiRequired : 1;         // streaming required vehicle stuff can be overrided
    unsigned char   m_bArmyRequired : 1;
	char _pad0;	    
	unsigned int  m_dwCurrentChaseTime;
	unsigned int  m_dwCurrentChaseTimeCounter;
	unsigned int  m_dwTimeCounting;
	unsigned int  m_dwWantedLevel;
	unsigned int  m_dwWantedLevelBeforeParole;
	CCrimeBeingQd     m_asCrimesBeingQd[16];
	class CCopPed    *m_apCopsInPursuit[10];
	CWantedAudio      m_WantedAudio;

	static CWanted* FindPlayerWanted(int number);
};
#pragma pack(pop)

VALIDATE_SIZE(CWanted, 0x29C);