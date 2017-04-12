#pragma once
#include "plbase/PluginBase_SA.h"
#include "CVector.h"
#include "CEntity.h"
#include "CPed.h"
#include "CVehicle.h"
#include "CWeaponInfo.h"
#include "CAnimBlendClumpData.h"

// returns player coors
CVector FindPlayerCoors(int playerId);
// returns player speed
CVector const& FindPlayerSpeed(int playerId);
// returns player ped or player vehicle if he's driving
CEntity * FindPlayerEntity(int playerId);
// gets player coords
CVector const& FindPlayerCentreOfWorld(int playerId);
// gets player coords with skipping sniper shift
CVector const& FindPlayerCentreOfWorld_NoSniperShift(int playerId);
// returns player coords with skipping interior shift
CVector FindPlayerCentreOfWorld_NoInteriorShift(int playerId);
// returns player angle in radians
float FindPlayerHeading(int playerId);
// returns Z coord for active player
float FindPlayerHeight();
// returns player ped
CPed * FindPlayerPed(int playerId = -1);
// returns player vehicle
CVehicle * FindPlayerVehicle(int playerId, bool bIncludeRemote);
// 2 players are playing
bool InTwoPlayersMode();
// vectorsub
CVector VectorSub(CVector const& from, CVector const& what);
// matrix mul
CVector Multiply3x3(CMatrix  const& matrix, CVector  const& vec);
RpHAnimHierarchy *GetAnimHierarchyFromSkinClump(RpClump *clump);

extern uint32_t &ClumpOffset;

#define RpClumpGetAnimBlendClumpData(clump) (*(CAnimBlendClumpData **)(((unsigned int)(clump) + ClumpOffset)))

AnimBlendFrameData *RpAnimBlendClumpFindFrame(RpClump *clump, char *name);

char *MakeUpperCase(char *dest, char *src);


 float x_fac(float x);
 float y_fac(float y);