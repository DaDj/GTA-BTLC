#include "CObject.h"
#include "CModelInfo.h"
#include "CFileMgr.h"
#include <iostream>
#include <string>
#include <fstream>
#include "../stdafx.h"
#include "../Patch/paths/Paths.h"
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

uint16& CObject::nNoTempObjects = *(uint16*)(0xBB4A70);
float& CObject::fDistToNearestTree = *(float*)0x8D0A20;
bool& CObject::bAircraftCarrierSamSiteDisabled = *(bool*)0x8D0A24;
bool& CObject::bArea51SamSiteDisabled = *(bool*)0xBB4A72;


// Converted from thiscall void CObject::ProcessGarageDoorBehaviour(void) 0x44A4D0
void CObject::ProcessGarageDoorBehaviour() {
    ((void(__thiscall *)(CObject*))0x44A4D0)(this);
}

// Converted from thiscall bool CObject::CanBeDeleted(void) 0x59F120
bool CObject::CanBeDeleted() {
    return ((bool(__thiscall *)(CObject*))0x59F120)(this);
}

// Converted from thiscall void CObject::SetRelatedDummy(CDummyObject *relatedDummy) 0x59F160
void CObject::SetRelatedDummy(CDummyObject* relatedDummy) {
    ((void(__thiscall *)(CObject*, CDummyObject*))0x59F160)(this, relatedDummy);
}

// Converted from cdecl void CObject::SetMatrixForTrainCrossing(CMatrix *matrix,float) 0x59F200
void CObject::SetMatrixForTrainCrossing(CMatrix* matrix, float arg1) {
    ((void(__cdecl *)(CMatrix*, float))0x59F200)(matrix, arg1);
}

// Converted from thiscall bool CObject::TryToExplode(void) 0x59F2D0
bool CObject::TryToExplode() {
    return ((bool(__thiscall *)(CObject*))0x59F2D0)(this);
}

// Converted from thiscall void CObject::SetObjectTargettable(uchar targetable) 0x59F300
void CObject::SetObjectTargettable(unsigned char targetable) {
    ((void(__thiscall *)(CObject*, unsigned char))0x59F300)(this, targetable);
}

// Converted from thiscall bool CObject::CanBeTargetted(void) 0x59F320
bool CObject::CanBeTargetted() {
    return ((bool(__thiscall *)(CObject*))0x59F320)(this);
}

// Converted from thiscall void CObject::RefModelInfo(int modelIndex) 0x59F330
void CObject::RefModelInfo(int modelIndex) {
    ((void(__thiscall *)(CObject*, int))0x59F330)(this, modelIndex);
}

// Converted from thiscall void CObject::SetRemapTexture(RwTexture *remapTexture, short txdIndex) 0x59F350
void CObject::SetRemapTexture(RwTexture* remapTexture, short txdIndex) {
    ((void(__thiscall *)(CObject*, RwTexture*, short))0x59F350)(this, remapTexture, txdIndex);
}

// Converted from thiscall float CObject::GetRopeHeight(void) 0x59F380
float CObject::GetRopeHeight() {
    return ((float(__thiscall *)(CObject*))0x59F380)(this);
}

// Converted from thiscall void CObject::SetRopeHeight(float height) 0x59F3A0
void CObject::SetRopeHeight(float height) {
    ((void(__thiscall *)(CObject*, float))0x59F3A0)(this, height);
}

// Converted from thiscall CEntity* CObject::GetObjectCarriedWithRope(void) 0x59F3C0
CEntity* CObject::GetObjectCarriedWithRope() {
    return ((CEntity* (__thiscall *)(CObject*))0x59F3C0)(this);
}

// Converted from thiscall void CObject::ReleaseObjectCarriedWithRope(void) 0x59F3E0
void CObject::ReleaseObjectCarriedWithRope() {
    ((void(__thiscall *)(CObject*))0x59F3E0)(this);
}

// Converted from thiscall void CObject::AddToControlCodeList(void) 0x59F400
void CObject::AddToControlCodeList() {
    ((void(__thiscall *)(CObject*))0x59F400)(this);
}

// Converted from thiscall void CObject::RemoveFromControlCodeList(void) 0x59F450
void CObject::RemoveFromControlCodeList() {
    ((void(__thiscall *)(CObject*))0x59F450)(this);
}

// Converted from thiscall void CObject::ResetDoorAngle(void) 0x59F4B0
void CObject::ResetDoorAngle() {
    ((void(__thiscall *)(CObject*))0x59F4B0)(this);
}

// Converted from thiscall void CObject::LockDoor(void) 0x59F5C0
void CObject::LockDoor() {
    ((void(__thiscall *)(CObject*))0x59F5C0)(this);
}

// Converted from thiscall void CObject::Init(void) 0x59F840
void CObject::Init() {
    ((void(__thiscall *)(CObject*))0x59F840)(this);
}

// Converted from thiscall void CObject::DoBurnEffect(void) 0x59FB50
void CObject::DoBurnEffect() {
    ((void(__thiscall *)(CObject*))0x59FB50)(this);
}

// Converted from thiscall uchar CObject::GetLightingFromCollisionBelow(void) 0x59FD00
unsigned char CObject::GetLightingFromCollisionBelow() {
    return ((unsigned char(__thiscall *)(CObject*))0x59FD00)(this);
}

// Converted from thiscall void CObject::ProcessSamSiteBehaviour(void) 0x5A07D0
void CObject::ProcessSamSiteBehaviour() {
    ((void(__thiscall *)(CObject*))0x5A07D0)(this);
}

// Converted from thiscall void CObject::ProcessTrainCrossingBehaviour(void) 0x5A0B50
void CObject::ProcessTrainCrossingBehaviour() {
    ((void(__thiscall *)(CObject*))0x5A0B50)(this);
}

// Converted from thiscall void CObject::ObjectDamage(float damage,CVector *fxOrigin,CVector *fxDirection,CEntity *damager,eWeaponType weaponType) 0x5A0D90
void CObject::ObjectDamage(float damage, CVector* fxOrigin, CVector* fxDirection, CEntity* damager, eWeaponType weaponType) {
    ((void(__thiscall *)(CObject*, float, CVector*, CVector*, CEntity*, eWeaponType))0x5A0D90)(this, damage, fxOrigin, fxDirection, damager, weaponType);
}

// Converted from thiscall void CObject::Explode(void) 0x5A1340
void CObject::Explode() {
    ((void(__thiscall *)(CObject*))0x5A1340)(this);
}

// Converted from thiscall void CObject::ObjectFireDamage(float damage,CEntity *damager) 0x5A1580
void CObject::ObjectFireDamage(float damage, CEntity* damager) {
    ((void(__thiscall *)(CObject*, float, CEntity*))0x5A1580)(this, damage, damager);
}

// Converted from cdecl void CObject::TryToFreeUpTempObjects(int numObjects) 0x5A1840
void CObject::TryToFreeUpTempObjects(int numObjects) {
    ((void(__cdecl *)(int))0x5A1840)(numObjects);
}

// Converted from cdecl void CObject::DeleteAllTempObjects(void) 0x5A18B0
void CObject::DeleteAllTempObjects() {
    ((void(__cdecl *)())0x5A18B0)();
}

// Converted from cdecl void CObject::DeleteAllMissionObjects(void) 0x5A1910
void CObject::DeleteAllMissionObjects() {
    ((void(__cdecl *)())0x5A1910)();
}

// Converted from cdecl void CObject::DeleteAllTempObjectsInArea(CVector point,float radius) 0x5A1980
void CObject::DeleteAllTempObjectsInArea(CVector point, float radius) {
    ((void(__cdecl *)(CVector, float))0x5A1980)(point, radius);
}

// Converted from thiscall void CObject::GrabObjectToCarryWithRope(CPhysical *attachTo) 0x5A1AB0
void CObject::GrabObjectToCarryWithRope(CPhysical* attachTo) {
    ((void(__thiscall *)(CObject*, CPhysical*))0x5A1AB0)(this, attachTo);
}

// Converted from thiscall bool CObject::CanBeUsedToTakeCoverBehind(void) 0x5A1B60
bool CObject::CanBeUsedToTakeCoverBehind() {
    return ((bool(__thiscall *)(CObject*))0x5A1B60)(this);
}

CObject* CObject::Create(int modelIndex) {
    return ((CObject* (__cdecl *)(int))0x5A1F60)(modelIndex);
}

CObject* CObject::Create(CDummyObject* dummyObject) {
    return ((CObject* (__cdecl *)(CDummyObject*))0x5A2070)(dummyObject);
}

// Converted from thiscall void CObject::ProcessControlLogic(void) 0x5A29A0
void CObject::ProcessControlLogic() {
    ((void(__thiscall *)(CObject*))0x5A29A0)(this);
}

// Converted from cdecl bool IsObjectPointerValid_NotInWorld(CObject *object) 0x5A2B90
bool IsObjectPointerValid_NotInWorld(CObject* object) {
    return ((bool(__cdecl *)(CObject*))0x5A2B90)(object);
}

// Converted from cdecl bool IsObjectPointerValid(CObject *object) 0x5A2C20
bool IsObjectPointerValid(CObject* object) {
    return ((bool(__cdecl *)(CObject*))0x5A2C20)(object);
}


//modified Setobjectdata - changes masspoint to the middle of the boundingbox
//TODO: load file for exception objects( modelindex, flag (2 = masspoitn from file, 1= set new middle masspoint,0 = keep original), x_offset, y_offset, z_offset )
void CObject::SetObjectdata(int modelindex, CObject* object)
{
	static  structObject_masspoint ChangedObjects[5000];

	//Call standard Object data function
	((void(__cdecl *)(int, CObject*))0x5A2D00)(modelindex, object);

	//Read custom masspoint
	static int once = 0;
	if (!once)
	{
		once = 1;
		CObject::ReadMasspoints(ChangedObjects);
	}

	//check if the object is in the new masspoint array
	int flag = 0;
	float x, y, z;
	if (ChangedObjects)
	{
		for (int i = 0; i < 5000; i++)
		{
			if (ChangedObjects[i].Modelindex == modelindex)
			{
				flag = ChangedObjects[i].Flag;
				x = ChangedObjects[i].x;
				y = ChangedObjects[i].y;
				z = ChangedObjects[i].z;
				//std::cout << modelindex << "  " << ChangedObjects[i].Modelname << std::endl;
				break;
			}
		}
	}

	if (flag != 0)
	{
		//Get boundingbox coords
		float bound_zmax = CModelInfo::ms_modelInfoPtrs[modelindex]->m_pColModel->m_boundBox.m_max.z;
		float bound_zmin = CModelInfo::ms_modelInfoPtrs[modelindex]->m_pColModel->m_boundBox.m_min.z;
		float massz = bound_zmax + bound_zmin / 2; //middle

		float bound_xmax = CModelInfo::ms_modelInfoPtrs[modelindex]->m_pColModel->m_boundBox.m_max.x;
		float bound_xmin = CModelInfo::ms_modelInfoPtrs[modelindex]->m_pColModel->m_boundBox.m_min.x;
		float massx = bound_xmax + bound_xmin / 2; //middle

		float bound_ymax = CModelInfo::ms_modelInfoPtrs[modelindex]->m_pColModel->m_boundBox.m_max.y;
		float bound_ymin = CModelInfo::ms_modelInfoPtrs[modelindex]->m_pColModel->m_boundBox.m_min.y;
		float massy = bound_ymax + bound_ymin / 2; //middle
		if (flag == 2)
		{
			massx = x;
			massy = y;
			massz = z;
		}
		//get the special response type of the object
		int response = object->m_pObjectInfo->m_nSpecialColResponseCase;
		switch (response)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			//If it is a dynamic object -> set masspoint to the middle
			object->m_vecCentreOfMass.x = massx;
			object->m_vecCentreOfMass.y = massy;
			object->m_vecCentreOfMass.z = massz;
			break;
		default:
			break;
		}
	}
}

void CObject::ReadMasspoints(structObject_masspoint Result[])
{
	using namespace std;
	string Line;
	ifstream myfile;
	int i = 0;
	char line2[500] = "";

	char* FILEPath = plugin::paths::GetPluginDirPathA();
	strcat(FILEPath, "..\\data\\masspoints.dat");
	//std::cout << FILEPath << std::endl;
	myfile.open(FILEPath);

	if (!myfile.is_open())
	{
			cout << " Opening Masspoints.dat FAILED!" << endl;
			return;
	}

	cout << "loaded  ...\\data\\masspoints.dat " << endl;
	while (getline(myfile, Line))
	{
		strcpy(line2, Line.c_str());
		if (line2[0] != ';')
		{
			sscanf(line2, "%d, %s %d, %f, %f, %f", &Result[i].Modelindex, &Result[i].Modelname, &Result[i].Flag, &Result[i].x, &Result[i].y, &Result[i].z);
			//std::cout << i << "  " << Result[i].Modelindex << " " << Result[i].Modelname << "  " << Result[i].Flag << Result[i].x << Result[i].y << Result[i].z << std::endl;
		}
		i++;
	}
	myfile.close();
	return;
}