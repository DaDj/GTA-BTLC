#pragma once

#include "plbase/PluginBase_SA.h"
#include "CPlayerInfo.h"
#include "CColPoint.h"
#include "CEntity.h"
#include "CStoredCollPoly.h"

class CWorld
{
public:
	// Player data array for 2 players.
	static CPlayerInfo *Players;
	// Current player we playing.
	static int8_t& PlayerInFocus;
	// entity to ignore
	static CEntity *&pIgnoreEntity;
	static bool ProcessLineOfSight(CVector  const& origin, CVector  const& target, CColPoint &colPoint, 
		CEntity *&colEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, 
		bool seeThrough, bool cameraObjects, bool shootThrough);

	static bool CWorld::GetIsLineOfSightClear(CVector  const& origin, CVector  const& target, bool solid,
		bool bSolid, bool bCar, bool bActor, bool bObject, bool bParticle, bool a8);

	static float FindGroundZForCoord(float x, float y);

    static bool ProcessVerticalLine(CVector const& origin, float distance, CColPoint &colPoint, CEntity *&colEntity,
        bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool seeThrough, CStoredCollPoly *poly);

    // add entity to game world
    static void Add(CEntity *entity);
    // remove entity from game world
    static void Remove(CEntity *entity);
};