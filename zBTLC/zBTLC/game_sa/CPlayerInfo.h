#pragma once

#include "plbase/PluginBase_SA.h"
#include "CPlayerData.h"
#include "CVector.h"

enum ePlayerState
{
	PLAYERSTATE_PLAYING,
	PLAYERSTATE_HASDIED,
	PLAYERSTATE_HASBEENARRESTED,
	PLAYERSTATE_FAILEDMISSION,
	PLAYERSTATE_LEFTGAME
};

#pragma pack(push, 1)
class CPlayerInfo
{
public:
	class CPed *m_pPed;                     // Pointer to the player ped (should always be set)
	CPlayerData m_PlayerData;              // instance of player variables
	void *m_pRemoteVehicle;           // Pointer to vehicle player is driving remotely at the moment.(NULL if on foot)
	void *m_pSpecCar;                 // which car is using the special collision model
	int m_dwMoney;                  // Points for this player
	int m_dwDisplayMoney;           // Points as they would be displayed
	unsigned int m_dwCollectablesPickedUp;   // How many bags of sugar do we have
	unsigned int m_dwTotalNumCollectables;   // How many bags of sugar are there to be had in the game
	unsigned int m_dwLastBumpPlayerCarTimer; // Keeps track of when the last ped bumped into the player car
	unsigned int m_dwTaxiTimer;              // Keeps track of how long the player has been in a taxi with a passenger (in msecs)
	unsigned int m_dwVehicleTimeCounter;     // keeps track of how long player has been in car for driving skill
	unsigned char m_bTaxiTimerScore;          // If TRUE then add 1 to score for each second that the player is driving a taxi
	unsigned char m_bTryingToExitCar;         // if player holds exit car button, want to trigger getout once car slowed enough with a passenger
	char _pad0[2];
	void *m_pLastTargetVehicle;       // Last vehicle player tried to enter.
	unsigned char m_bPlayerState;             // What's going on.
	unsigned char m_bAfterRemoteVehicleExplosion;
	unsigned char m_bCreateRemoteVehicleExplosion;
	unsigned char m_bFadeAfterRemoteVehicleExplosion;
	unsigned int m_dwTimeOfRemoteVehicleExplosion;
	unsigned int m_dwLastTimeEnergyLost;     // To make numbers flash on the HUD;
	unsigned int m_dwLastTimeArmourLost;
	unsigned int m_dwLastTimeBigGunFired;    // Tank guns etc
	unsigned int m_dwTimesUpsideDownInARow;  // Make car blow up if car upside down
	unsigned int m_dwTimesStuckInARow;       // Make car blow up if player cannot get out.
	unsigned int m_dwCarTwoWheelCounter;     // how long has player's car been on two wheels
	float m_fCarTwoWheelDist;         // Make car blow up if player cannot get out.
	unsigned int m_dwCarLess3WheelCounter;   // how long has player's car been on less than 3 wheels
	unsigned int m_dwBikeRearWheelCounter;   // how long has player's bike been on rear wheel only
	float m_fBikeRearWheelDist;
	unsigned int m_dwBikeFrontWheelCounter;  // how long has player's bike been on front wheel only
	float m_fBikeFrontWheelDist;
	unsigned int m_dwTempBufferCounter;      // so wheels can leave the ground for a few frames without stopping above counters
	unsigned int m_dwBestCarTwoWheelsTimeMs;
	float m_fBestCarTwoWheelsDistM;
	unsigned int m_dwBestBikeWheelieTimeMs;
	float m_fBestBikeWheelieDistM;
	unsigned int m_dwBestBikeStoppieTimeMs;
	float m_fBestBikeStoppieDistM;
	unsigned short m_wCarDensityForCurrentZone;
	char _pad1[2];
	float m_fRoadDensityAroundPlayer; // 1.0f for an average city.
	unsigned int m_dwTimeOfLastCarExplosionCaused;
	unsigned int m_dwExplosionMultiplier;
	unsigned int m_dwHavocCaused;            // A counter going up when the player does bad stuff.
	unsigned short m_wTimeLastEaten;           // A counter that starts at 5000, increases by 1 every minute
	char _pad2[2];
	float m_fCurrentChaseValue;       // How 'ill' is the chase at the moment
	unsigned char m_bDoesNotGetTired;
	unsigned char m_bFastReload;
	unsigned char m_bFireProof;
	unsigned char m_bMaxHealth;
	unsigned char m_bMaxArmour;
	unsigned char m_bGetOutOfJailFree;        // Player doesn't lose money/weapons next time arrested
	unsigned char m_bFreeHealthCare;          // Player doesn't lose money nexed time patched up at hospital
	unsigned char m_bCanDoDriveBy;
	unsigned char m_bBustedAudioStatus;
	char _pad3;
	unsigned short m_wLastBustMessageNumber;
	unsigned int m_dwCrosshairActivated;
	CVector2D m_vCrosshairTarget;         // -1 ... 1 on screen
	char m_acSkinName[32];
	struct RwTexture *m_pSkinTexture;
	unsigned char m_bParachuteReferenced;
	char _pad4[3];
	unsigned int m_dwRequireParachuteTimer;
};
#pragma pack(pop)

//VALIDATE_SIZE(CPlayerInfo, 0x190);