/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "CTrain.h"
#include "common.h"
#include "CTimer.h"
#include "CWeather.h"
#include "CStreaming.h"
#include "CCamera.h"

const int NumTracks = 5;
unsigned int& CTrain::GenTrain_Track = *(unsigned int *)0xC37FFC;
unsigned int& CTrain::GenTrain_TrainConfig = *(unsigned int *)0xC38000;
unsigned char& CTrain::GenTrain_Direction = *(unsigned char *)0xC38004;
unsigned int& CTrain::GenTrain_GenerationNode = *(unsigned int *)0xC38008;
unsigned int& CTrain::GenTrain_Status = *(unsigned int *)0xC3800C;
bool& CTrain::bDisableRandomTrains = *(bool *)0xC38010;
CVector *CTrain::aStationCoors = (CVector *)0x8D48F8;    //CVector CTrain::aStationCoors[6]
unsigned int *NumTrackNodes = *(unsigned int **)(0x6F8720 +3);         //0xC38014
CTrainNode **pTrackNodes = *(CTrainNode ***)(0x6F871A + 2);             //0xC38024
float *CTrain::arrTotalTrackLength = *(float **)(0x6F8710 +2);
float *CTrain::StationDist = (float *) 0xC38034;

void CTrain::MyInit()
{
	MemoryVP::Patch<BYTE>(0x6F7FE1, 0x04); //CTrain::DoTrainGenerationAndRemoval() patch to not spawn Tram
	MemoryVP::InjectHook(0x43426D, &CTrain::DoTrainGenerationAndRemoval, PATCH_CALL);
	/*MemoryVP::Patch<BYTE>(0x6F7480 + 1, 0x00);
	MemoryVP::Patch<BYTE>(0x6F74A6 + 1, 0x00);
	MemoryVP::Patch<BYTE>(0x6F74CC + 1, 0x00);*/

	MemoryVP::Patch<BYTE>(0x6F6CA7 + 2, NumTracks); //CTrain::FindClosestTrackNode more track support
	
}

// Converted from thiscall void CTrain::CTrain(int modelIndex,uchar createdBy) 0x6F6030
CTrain::CTrain(int modelIndex, unsigned char createdBy) : CVehicle(plugin::dummy) {
    ((void(__thiscall *)(CTrain*, int, unsigned char))0x6F6030)(this, modelIndex, createdBy);
}

// Converted from cdecl void CTrain::ReadAndInterpretTrackFile(char *filename,CTrainNode **nodes,int *lineCount,float *totalDist,int skipStations) 0x6F55D0
void CTrain::ReadAndInterpretTrackFile(char* filename, CTrainNode** nodes, int* lineCount, float* totalDist, int skipStations) {
    ((void(__cdecl *)(char*, CTrainNode**, int*, float*, int))0x6F55D0)(filename, nodes, lineCount, totalDist, skipStations);
}

// Converted from cdecl void CTrain::Shutdown(void) 0x6F58D0
void CTrain::Shutdown() {
    ((void(__cdecl *)())0x6F58D0)();
}

// Converted from cdecl void CTrain::UpdateTrains(void) 0x6F5900
void CTrain::UpdateTrains() {
    ((void(__cdecl *)())0x6F5900)();
}

// Converted from cdecl void ProcessTrainAnnouncements(void) 0x6F5910
void ProcessTrainAnnouncements() {
    ((void(__cdecl *)())0x6F5910)();
}

// Converted from cdecl void PlayAnnouncement(uchar,uchar) 0x6F5920
void PlayAnnouncement(unsigned char arg0, unsigned char arg1) {
    ((void(__cdecl *)(unsigned char, unsigned char))0x6F5920)(arg0, arg1);
}

// Converted from cdecl void CTrain::FindCoorsFromPositionOnTrack(float railDistance,int trackId,CVector *outCoors) 0x6F59E0
void CTrain::FindCoorsFromPositionOnTrack(float railDistance, int trackId, CVector* outCoors) {
    ((void(__cdecl *)(float, int, CVector*))0x6F59E0)(railDistance, trackId, outCoors);
}

// Converted from thiscall bool CTrain::FindMaximumSpeedToStopAtStations(float *speed) 0x6F5BA0
bool CTrain::FindMaximumSpeedToStopAtStations(float* speed) {
    return ((bool(__thiscall *)(CTrain*, float*))0x6F5BA0)(this, speed);

	if (m_nTrackId > 0)
		return false;



}

// Converted from thiscall uint CTrain::FindNumCarriagesPulled(void) 0x6F5CD0
unsigned int CTrain::FindNumCarriagesPulled() {
    return ((unsigned int(__thiscall *)(CTrain*))0x6F5CD0)(this);
}

// Converted from cdecl void TrainHitStuff(CPtrList &ptrList,CEntity *entity) 0x6F5CF0
void TrainHitStuff(CPtrList& ptrList, CEntity* entity) {
    ((void(__cdecl *)(CPtrList&, CEntity*))0x6F5CF0)(ptrList, entity);
}

// Converted from thiscall void CTrain::OpenTrainDoor(float state) 0x6F5D80
void CTrain::OpenTrainDoor(float state) {
    ((void(__thiscall *)(CTrain*, float))0x6F5D80)(this, state);
}

// Converted from thiscall void CTrain::AddPassenger(CPed *ped) 0x6F5D90
void CTrain::AddPassenger(CPed* ped) {
    ((void(__thiscall *)(CTrain*, CPed*))0x6F5D90)(this, ped);
}

// Converted from thiscall void CTrain::RemovePassenger(CPed *ped) 0x6F5DA0
void CTrain::RemovePassenger(CPed* ped) {
    ((void(__thiscall *)(CTrain*, CPed*))0x6F5DA0)(this, ped);
}

// Converted from cdecl void CTrain::DisableRandomTrains(bool disable) 0x6F5DB0
void CTrain::DisableRandomTrains(bool disable) {
    ((void(__cdecl *)(bool))0x6F5DB0)(disable);
}

// Converted from cdecl void CTrain::RemoveOneMissionTrain(CTrain* train) 0x6F5DC0
void CTrain::RemoveOneMissionTrain(CTrain* train) {
    ((void(__cdecl *)(CTrain*))0x6F5DC0)(train);
}

// Converted from cdecl void CTrain::ReleaseOneMissionTrain(CTrain* train) 0x6F5DF0
void CTrain::ReleaseOneMissionTrain(CTrain* train) {
    ((void(__cdecl *)(CTrain*))0x6F5DF0)(train);
}

// Converted from cdecl void CTrain::SetTrainSpeed(CTrain* train,float speed) 0x6F5E20
void CTrain::SetTrainSpeed(CTrain* train, float speed) {
    ((void(__cdecl *)(CTrain*, float))0x6F5E20)(train, speed);
}

// Converted from cdecl void CTrain::SetTrainCruiseSpeed(CTrain*,float cruiseSpeed) 0x6F5E50
void CTrain::SetTrainCruiseSpeed(CTrain* arg0, float cruiseSpeed) {
    ((void(__cdecl *)(CTrain*, float))0x6F5E50)(arg0, cruiseSpeed);
}

// Converted from cdecl CTrain* CTrain::FindCaboose(CTrain* train) 0x6F5E70
CTrain* CTrain::FindCaboose(CTrain* train) {
    return ((CTrain* (__cdecl *)(CTrain*))0x6F5E70)(train);
}

// Converted from cdecl CTrain* CTrain::FindEngine(CTrain* train) 0x6F5E90
CTrain* CTrain::FindEngine(CTrain* train) {
    return ((CTrain* (__cdecl *)(CTrain*))0x6F5E90)(train);
}

// Converted from cdecl CTrain* CTrain::FindCarriage(CTrain* train,uchar carriage) 0x6F5EB0
CTrain* CTrain::FindCarriage(CTrain* train, unsigned char carriage) {
    return ((CTrain* (__cdecl *)(CTrain*, unsigned char))0x6F5EB0)(train, carriage);
}

// Converted from thiscall bool CTrain::FindSideStationIsOn(void) 0x6F5EF0
bool CTrain::FindSideStationIsOn() {
    return ((bool(__thiscall *)(CTrain*))0x6F5EF0)(this);
}

// Converted from cdecl void CTrain::FindNextStationPositionInDirection(bool clockwiseDirection,float distance,float *distanceToStation,int *numStations) 0x6F5F00
void CTrain::FindNextStationPositionInDirection(bool clockwiseDirection, float distance, float* distanceToStation, int* numStations) {
    ((void(__cdecl *)(bool, float, float*, int*))0x6F5F00)(clockwiseDirection, distance, distanceToStation, numStations);
}

// Converted from thiscall bool CTrain::IsInTunnel(void) 0x6F6320
bool CTrain::IsInTunnel() {
    return ((bool(__thiscall *)(CTrain*))0x6F6320)(this);
}

// Converted from cdecl void MarkSurroundingEntitiesForCollisionWithTrain(CVector,float,CEntity *,bool) 0x6F6640
void MarkSurroundingEntitiesForCollisionWithTrain(CVector arg0, float arg1, CEntity* arg2, bool arg3) {
    ((void(__cdecl *)(CVector, float, CEntity*, bool))0x6F6640)(arg0, arg1, arg2, arg3);
}

// Converted from thiscall void CTrain::RemoveRandomPassenger(void) 0x6F6850
void CTrain::RemoveRandomPassenger() {
    ((void(__thiscall *)(CTrain*))0x6F6850)(this);
}

// Converted from cdecl void CTrain::RemoveMissionTrains(void) 0x6F6A20
void CTrain::RemoveMissionTrains() {
    ((void(__cdecl *)())0x6F6A20)();
}

// Converted from cdecl void CTrain::RemoveAllTrains(void) 0x6F6AA0
void CTrain::RemoveAllTrains() {
    ((void(__cdecl *)())0x6F6AA0)();
}

// Converted from cdecl void CTrain::ReleaseMissionTrains(void) 0x6F6B60
void CTrain::ReleaseMissionTrains() {
    ((void(__cdecl *)())0x6F6B60)();
}

// Converted from cdecl int CTrain::FindClosestTrackNode(CVector posn,int *outTrackId) 0x6F6BD0
int CTrain::FindClosestTrackNode(CVector posn, int* outTrackId) {
    return ((int(__cdecl *)(CVector, int*))0x6F6BD0)(posn, outTrackId);
}

// Converted from thiscall void CTrain::FindPositionOnTrackFromCoors(void) 0x6F6CC0
void CTrain::FindPositionOnTrackFromCoors() {
    ((void(__thiscall *)(CTrain*))0x6F6CC0)(this);
}

// Converted from cdecl CTrain* CTrain::FindNearestTrain(CVector posn,bool mustBeMainTrain) 0x6F7090
CTrain* CTrain::FindNearestTrain(CVector posn, bool mustBeMainTrain) {
    return ((CTrain* (__cdecl *)(CVector, bool))0x6F7090)(posn, mustBeMainTrain);
}

// Converted from cdecl void CTrain::SetNewTrainPosition(CTrain* train,CVector posn) 0x6F7140
void CTrain::SetNewTrainPosition(CTrain* train, CVector posn) {
    ((void(__cdecl *)(CTrain*, CVector))0x6F7140)(train, posn);
}

// Converted from cdecl bool CTrain::IsNextStationAllowed(CTrain* train) 0x6F7260
bool CTrain::IsNextStationAllowed(CTrain* train) {
    return ((bool(__cdecl *)(CTrain*))0x6F7260)(train);
}

// Converted from cdecl void CTrain::SkipToNextAllowedStation(CTrain* train) 0x6F72F0
void CTrain::SkipToNextAllowedStation(CTrain* train) {
    ((void(__cdecl *)(CTrain*))0x6F72F0)(train);
}

// Converted from cdecl void CTrain::InitTrains(void) 0x6F7440
void CTrain::InitTrains() {
    ((void(__cdecl *)())0x6F7440)();
}

// Converted from cdecl void CTrain::CreateMissionTrain(CVector posn,bool clockwiseDirection,uint trainType,CTrain**outFirstCarriage,CTrain**outLastCarriage,int nodeIndex,int trackId,bool isMissionTrain) 0x6F7550
void CTrain::CreateMissionTrain(CVector posn, bool clockwiseDirection, unsigned int trainType, CTrain**outFirstCarriage, CTrain**outLastCarriage, int nodeIndex, int trackId, bool isMissionTrain) {
    ((void(__cdecl *)(CVector, bool, unsigned int, CTrain**, CTrain**, int, int, bool))0x6F7550)(posn, clockwiseDirection, trainType, outFirstCarriage, outLastCarriage, nodeIndex, trackId, isMissionTrain);
}

// Converted from cdecl void CTrain::DoTrainGenerationAndRemoval(void) 0x6F7900
void CTrain::DoTrainGenerationAndRemoval() {


	//((void(__cdecl *)())0x6F7900)();

	int MaxSpawnDistance = 120 * TheCamera.m_fLODDistMultiplier ;
	int MinSpawnDistance = 80 * TheCamera.m_fLODDistMultiplier;
	int DespawnDist = 130 * TheCamera.m_fLODDistMultiplier;
	int NewGenDelay = 5000; //how often a new train will be generated
	float speed = 30.0f;


	int(&_trainCarriageModels)[16][16] = *(int(*)[16][16])0x8D44F8;
	int CurrentTrack = 2;
	float Dist = 0;
	bool GenATrain = 1;
	int TrainType = 0; 
	int iModel = 0;
	CTrainNode *MyNodes = pTrackNodes[CurrentTrack];
	int MyModelID = 0;;
	CTrain *TheTrain[NumTracks] = {};
	static int lasTcreate[NumTracks] = {};
	int Direction = 0;
	int NearestNodeId = 0;
	bool GenFinal = 0;

	//Find any trains on the tracks 
	for (size_t i = 0; i < CPools::ms_pVehiclePool->m_nSize; i++)
	{
		if (CPools::ms_pVehiclePool->GetAt(i) != nullptr && CPools::ms_pVehiclePool->GetAt(i)->m_dwVehicleSubClass == VEHICLE_TRAIN)
			TheTrain[((CTrain*)CPools::ms_pVehiclePool->GetAt(i))->m_nTrackId] = (CTrain*)CPools::ms_pVehiclePool->GetAt(i);	
	}

	for (CurrentTrack = 0; CurrentTrack < NumTracks; CurrentTrack++)
	{
		MyNodes = pTrackNodes[CurrentTrack];
		TrainType = rand() % 2 + 8;
		iModel = 0;
		NearestNodeId = 0;
		GenATrain = 1;
		GenFinal = 0;
		int NodeId = 0;

		do
		{
			MyModelID = _trainCarriageModels[TrainType][iModel];
			if (CStreaming::ms_aInfoForModel[MyModelID].m_loadState != 1)
			{
				CStreaming::RequestModel(MyModelID, 8);
				GenATrain = 0;
			}
			iModel++;
		} while (_trainCarriageModels[TrainType][iModel]);


		//Lets delete Trains which are too far away.
		if (TheTrain[CurrentTrack] != nullptr && !TheTrain[CurrentTrack]->GetIsOnScreen() && DistanceBetweenPoints(TheTrain[CurrentTrack]->GetPosition(), FindPlayerCoors(-1)) > DespawnDist)
		{
			RemoveOneMissionTrain(TheTrain[CurrentTrack]);
			TheTrain[CurrentTrack]->CanBeDeleted();
			lasTcreate[CurrentTrack] = CTimer::m_snTimeInMilliseconds + rand() % 1200;
			return;
		}

		if (GenATrain != 1)
			return;

		if (CTimer::m_snTimeInMilliseconds - lasTcreate[CurrentTrack] < NewGenDelay || TheTrain[CurrentTrack] != nullptr)
			return;

		for (int i = 0; i < NumTrackNodes[CurrentTrack]; i++)
		{
			Dist = DistanceBetweenPoints(MyNodes[i].GetPosn(), FindPlayerCoors(-1));
			float DistOld = DistanceBetweenPoints(MyNodes[NearestNodeId].GetPosn(), FindPlayerCoors(-1));
			if (DistOld > Dist)
				NearestNodeId = i;
		}

		for (NodeId = 0; NodeId < NumTrackNodes[CurrentTrack]; NodeId++)
		{
			Dist = DistanceBetweenPoints(MyNodes[NodeId].GetPosn(), FindPlayerCoors(-1));

			//This sets that the train will drive towards the player. It provides a better experience.
			//Cause if a train spawns in direction away from player and drives away the player most likely won't see the train.
			//may introduce a little rand fucntion to give a very small chance of spawning away driving trains? Idk maybe some day...
			if (Direction && !(NodeId < NearestNodeId) || (!Direction && (NodeId > NearestNodeId)))
				GenFinal = true;

			if (Dist < MaxSpawnDistance && Dist > MinSpawnDistance && GenFinal)
			{
				CVector TrainPos;
				TrainPos.x = 0;
				TrainPos.y = 0;
				TrainPos.z = 0;

				CreateMissionTrain(TrainPos, false, TrainType, &TheTrain[CurrentTrack], 0, NodeId, CurrentTrack, 0);

				//SetTrainSpeed(TheTrain, speed);
				TheTrain[CurrentTrack]->FindMaximumSpeedToStopAtStations(&speed);
				//SetTrainCruiseSpeed(TheTrain, 35.0f);
				TheTrain[CurrentTrack]->m_nTrainFlags.bStopsAtStations = 1;
				TheTrain[CurrentTrack]->m_nTrainFlags.bPassengersCanEnterAndLeave = 1;
				TheTrain[CurrentTrack]->m_nTrainFlags.bForceSlowDown = 1;
				TheTrain[CurrentTrack]->m_autoPilot.m_nCruiseSpeed = speed;
				TheTrain[CurrentTrack]->m_bStreamingDontDelete = true;
				lasTcreate[CurrentTrack] = CTimer::m_snTimeInMilliseconds + rand() % 1200;
				break;
			}
		}
		
	}
}
		
	



// Converted from thiscall void CTrain::AddNearbyPedAsRandomPassenger(void) 0x6F8170
void CTrain::AddNearbyPedAsRandomPassenger() {
    ((void(__thiscall *)(CTrain*))0x6F8170)(this);
}