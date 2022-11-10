#pragma once

#include "plbase/PluginBase_SA.h"
#include "CPlaceable.h"
#include "CCam.h"
#include "CQueuedMode.h"
#include "CEntity.h"
#include "CCamPathSplines.h"
#include "CMatrix.h"

#pragma pack(push, 1)
class  CCamera : public CPlaceable
{
public:
	bool              m_bAboveGroundTrainNodesLoaded;
	bool              m_bBelowGroundTrainNodesLoaded;
	bool              m_bCamDirectlyBehind;
	bool              m_bCamDirectlyInFront;
	bool              m_bCameraJustRestored;
	bool              m_bcutsceneFinished;
	bool              m_bCullZoneChecksOn;
	bool              m_bFirstPersonBeingUsed;
	bool              m_bJustJumpedOutOf1stPersonBecauseOfTarget;
	bool              m_bIdleOn;
	bool              m_bInATunnelAndABigVehicle;
	bool              m_bInitialNodeFound;
	bool              m_bInitialNoNodeStaticsSet;
	bool              m_bIgnoreFadingStuffForMusic;
	bool              m_bPlayerIsInGarage;
	bool              m_bPlayerWasOnBike;
	bool              m_bJustCameOutOfGarage;
	bool              m_bJustInitalised;
	bool              m_bJust_Switched;
	bool              m_bLookingAtPlayer;
	bool              m_bLookingAtVector;
	bool              m_bMoveCamToAvoidGeom;
	bool              m_bObbeCinematicPedCamOn;
	bool              m_bObbeCinematicCarCamOn;
	bool              m_bRestoreByJumpCut;
	bool              m_bUseNearClipScript;
	bool              m_bStartInterScript;
	bool              m_bStartingSpline;
	bool              m_bTargetJustBeenOnTrain;
	bool              m_bTargetJustCameOffTrain;
	bool              m_bUseSpecialFovTrain;
	bool              m_bUseTransitionBeta;
	bool              m_bUseScriptZoomValuePed;
	bool              m_bUseScriptZoomValueCar;
	bool              m_bWaitForInterpolToFinish;
	bool              m_bItsOkToLookJustAtThePlayer;
	bool              m_bWantsToSwitchWidescreenOff;
	bool              m_bWideScreenOn;
	bool              m_b1rstPersonRunCloseToAWall;
	bool              m_bHeadBob;
	bool              m_bVehicleSuspenHigh;
	bool              m_bEnable1rstPersonCamCntrlsScript;
	bool              m_bAllow1rstPersonWeaponsCamera;
	bool              m_bCooperativeCamMode;
	bool              m_bAllowShootingWith2PlayersInCar;
	bool              m_bDisableFirstPersonInCar;
	unsigned short  m_wModeForTwoPlayersSeparateCars;
	unsigned short  m_wModeForTwoPlayersSameCarShootingAllowed;
	unsigned short  m_wModeForTwoPlayersSameCarShootingNotAllowed;
	unsigned short  m_wModeForTwoPlayersNotBothInCar;
	bool              m_bGarageFixedCamPositionSet;
	bool              m_bDoingSpecialInterPolation;
	bool              m_bScriptParametersSetForInterPol;
	bool              m_bFading;
	bool              m_bMusicFading;
	bool              m_bMusicFadedOut;
	bool              m_bFailedCullZoneTestPreviously;
	bool              m_bFadeTargetIsSplashScreen;
	bool              m_bWorldViewerBeingUsed;
	bool              m_bTransitionJUSTStarted;
	bool              m_bTransitionState;
	bool              m_nActiveCam;
	char pad0[2];  
	unsigned int  m_dwCamShakeStart;
	unsigned int  m_dwFirstPersonCamLastInputTime;
	unsigned int  m_dwLongestTimeInMill;
	unsigned int  m_dwNumberOfTrainCamNodes;
	unsigned int  m_dwTimeLastChange;
	unsigned int  m_dwTimeWeLeftIdle_StillNoInput;
	unsigned int  m_dwTimeWeEnteredIdle;
	unsigned int  m_dwTimeTransitionStart;
	unsigned int  m_dwTransitionDuration;
	unsigned int  m_dwTransitionDurationTargetCoors;
	unsigned int  m_dwBlurBlue;
	unsigned int  m_dwBlurGreen;
	unsigned int  m_dwBlurRed;
	unsigned int  m_dwBlurType;
	unsigned int  m_dwWorkOutSpeedThisNumFrames;
	unsigned int  m_dwNumFramesSoFar;
	unsigned int  m_dwCurrentTrainCamNode;
	unsigned int  m_dwMotionBlur;
	unsigned int  m_dwMotionBlurAddAlpha;
	unsigned int  m_dwCheckCullZoneThisNumFrames;
	unsigned int  m_dwZoneCullFrameNumWereAt;
	unsigned int  m_dwWhoIsInControlOfTheCamera;
	unsigned int  m_dwCarZoom;
	float             m_fCarZoomBase;
	float             m_fCarZoomTotal;
	float             m_fCarZoomSmoothed;
	float             m_fCarZoomValueScript;
	float             m_fPedZoom;
	float             m_fPedZoomBase;
	float             m_fPedZoomTotal;
	float             m_fPedZoomSmoothed;
	float             m_fPedZoomValueScript;
	float             m_fCamFrontXNorm;
	float             m_fCamFrontYNorm;
	float             m_fDistanceToWater;
	float             m_fHeightOfNearestWater;
	float             m_fFOVDuringInter;
	float             m_fLODDistMultiplier;
	float             m_fGenerationDistMultiplier;
	float             m_fAlphaSpeedAtStartInter;
	float             m_fAlphaWhenInterPol;
	float             m_fAlphaDuringInterPol;
	float             m_fBetaDuringInterPol;
	float             m_fBetaSpeedAtStartInter;
	float             m_fBetaWhenInterPol;
	float             m_fFOVWhenInterPol;
	float             m_fFOVSpeedAtStartInter;
	float             m_fStartingBetaForInterPol;
	float             m_fStartingAlphaForInterPol;
	float             m_fPedOrientForBehindOrInFront;
	float             m_fCameraAverageSpeed;
	float             m_fCameraSpeedSoFar;
	float             m_fCamShakeForce;
	float             m_fFovForTrain;
	float             m_fFOV_Wide_Screen;
	float             m_fNearClipScript;
	float             m_fOldBetaDiff;
	float             m_fPositionAlongSpline;
	float             m_fScreenReductionPercentage;
	float             m_fScreenReductionSpeed;
	float             m_fAlphaForPlayerAnim1rstPerson;
	float             m_fOrientation;
	float             m_fPlayerExhaustion;
	float             m_fSoundDistUp;
	float             m_fSoundDistUpAsRead;
	float             m_fSoundDistUpAsReadOld;
	float             m_fAvoidTheGeometryProbsTimer;
	unsigned short  m_wAvoidTheGeometryProbsDirn;
	char pad1[2];  
	float             m_fWideScreenReductionAmount;
	float             m_fStartingFOVForInterPol;
	CCam              m_aCams[3];
	class CGarage    *m_pToGarageWeAreIn;
	class CGarage    *m_pToGarageWeAreInForHackAvoidFirstPerson;
	CQueuedMode       m_PlayerMode;
	CQueuedMode       m_PlayerWeaponMode;
	CVector           m_vPreviousCameraPosition;
	CVector           m_vRealPreviousCameraPosition;
	CVector           m_vAimingTargetCoors;
	CVector           m_vFixedModeVector;
	CVector           m_vFixedModeSource;
	CVector           m_vFixedModeUpOffSet;
	CVector           m_vCutSceneOffset;
	CVector           m_vStartingSourceForInterPol;
	CVector           m_vStartingTargetForInterPol;
	CVector           m_vStartingUpForInterPol;
	CVector           m_vSourceSpeedAtStartInter;
	CVector           m_vTargetSpeedAtStartInter;
	CVector           m_vUpSpeedAtStartInter;
	CVector           m_vSourceWhenInterPol;
	CVector           m_vTargetWhenInterPol;
	CVector           m_vUpWhenInterPol;
	CVector           m_vClearGeometryVec;
	CVector           m_vGameCamPos;
	CVector           m_vSourceDuringInter;
	CVector           m_vTargetDuringInter;
	CVector           m_vUpDuringInter;
	CVector           m_vAttachedCamOffset;
	CVector           m_vAttachedCamLookAt;
	float             m_fAttachedCamAngle;
	struct RwCamera   *m_pRwCamera;
	class CEntity    *m_pTargetEntity;
	class CEntity    *m_pAttachedEntity;
	CCamPathSplines   m_aPathArray[4];
	bool              m_bMirrorActive;
	bool              m_bResetOldMatrix;
	char pad2[2];
	CMatrix           m_mCameraMatrix;
	CMatrix           m_mCameraMatrixOld;
	CMatrix           m_mViewMatrix;
	CMatrix           m_mMatInverse;
	CMatrix           m_mMatMirrorInverse;
	CMatrix           m_mMatMirror;
	CVector           m_avFrustumNormals[4];
	CVector m_avecFrustumWorldNormals[4];
	CVector m_avecFrustumWorldNormals_Mirror[4];
	float m_fFrustumPlaneOffsets[4];
	float m_fFrustumPlaneOffsets_Mirror[4];
	CVector field_BD4;
	int field_BE0;
	int field_BE4;
	int field_BE8;
	int field_BEC;
	int field_BF0;
	int field_BF4;
	int field_BF8;
	float             m_fFadeAlpha;
	float m_fEffectsFaderScalingFactor;
	float             m_fFadeDuration;
	float m_fTimeToFadeMusic;
	float m_fTimeToWaitToFadeMusic;
	float m_fFractionInterToStopMoving;
	float m_fFractionInterToStopCatchUp;
	float m_fFractionInterToStopMovingTarget;
	float m_fFractionInterToStopCatchUpTarget;
	float m_fGaitSwayBuffer;
	float m_fScriptPercentageInterToStopMoving;
	float m_fScriptPercentageInterToCatchUp;
	unsigned int m_nScriptTimeForInterPolation;
	unsigned short  m_wFadeInOutFlag;
	short field_C32;
	int field_C34;
	short field_C38;
	short field_C3A;
	short field_C3C;
	short field_C3E;
	unsigned int  m_dwFadeStartTime;
	int field_C44;
	int field_C48;
	int field_C4C;
	int field_C50;
	int field_C54;
	int field_C58;
	unsigned int  m_dwTransverseStartTime;
	unsigned int  m_dwTransverseEndTime;
	CVector           m_vTransverseEndPoint;
	CVector           m_vTransverseStartPoint;
	unsigned char   m_nTransverseMode;
	char field_C7D;
	char field_C7E;
	char field_C7F;
	CVector field_C80;
	char field_C8C;
	char field_C8D;
	char field_C8E;
	char field_C8F;
	int field_C90;
	unsigned int  m_dwStartJiggleTime;
	unsigned int  m_dwEndJiggleTime;
	int field_C9C;
	int field_CA0;
	unsigned int  m_dwStartZoomTime;
	unsigned int  m_dwEndZoomTime;
	float             m_fZoomInFactor;
	float             m_fZoomOutFactor;
	unsigned char   m_nZoomMode;
	char field_CB5;
	char field_CB6;
	char field_CB7;
	int field_CB8;
	int field_CBC;
	int field_CC0;
	CVector field_CC4;
	CVector field_CD0;
	char field_CDC;
	char field_CDD;
	char field_CDE;
	char field_CDF;
	CVector field_CE0;
	char field_CEC;
	bool              m_bBlockZoom;
	char field_CEE;
	char field_CEF;
	char field_CF0;
	char field_CF1;
	char field_CF2;
	char field_CF3;
	char field_CF4[80];
	int field_D44;
	int field_D48;
	int field_D4C;
	int field_D50;
	int field_D54;
	int field_D58;
	int field_D5C;
	int field_D60;
	int field_D64;
	int field_D68;
	int field_D6C;
	int field_D70;
	int field_D74;

	static float& m_f3rdPersonCHairMultY;
	static float& m_f3rdPersonCHairMultX;
	static float& m_fMouseAccelVertical;
	static float& m_fMouseAccelHorzntl;


	char GetFading();
	int GetFadeStage();
};
#pragma pack(pop)

extern  CCamera &TheCamera;