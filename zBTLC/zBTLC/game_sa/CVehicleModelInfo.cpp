#include "CVehicleModelInfo.h"
#include "rw/rpworld.h"
#include <iterator>
#include "CCarFxRender.h"
#include <list>
#include <vector>
#include "CVisibilityPlugins.h"



RwTexture *CVehicleModelInfo::ms_pRemapTexture = (RwTexture *)0xB4E47C;
RwTexture *CVehicleModelInfo::ms_pLightsTexture = (RwTexture *)0xB4E68C;
RwTexture *CVehicleModelInfo::ms_pLightsOnTexture = (RwTexture *)0xB4E690;
unsigned char *CVehicleModelInfo::ms_currentCol = (unsigned char *)0xB4E3F0;
//CRGBA *CVehicleModelInfo::ms_vehicleColourTable = (CRGBA *)0xB4E480;
CRGBA CVehicleModelInfo::ms_vehicleColourTable[256] = {};
char *CVehicleModelInfo::ms_compsUsed = (char *)0xB4E478;
char *CVehicleModelInfo::ms_compsToUse = (char *)0x8A6458;

char *CVehicleModelInfo::ms_lightsOn = (char*)0xB4E3E8;

VehicleLightFlags CVehicleModelInfo::LightStatus;

//RwTexture **CVehicleModelInfo::ms_aDirtTextures =(RwTexture **)0xC02BD0;
//RwTexture *CVehicleModelInfo::DirtTexture2[16] = {};

//Custom vehiclelights128 texture
RwTexture *CVehicleModelInfo::ms_pCustomLightsTexture;
// Custom vehiclelightson128 texture
RwTexture *CVehicleModelInfo::ms_pCustomLightsOnTexture;



void CVehicleModelInfo::ShutdownLightTexture()
{
	((void(__cdecl *)())0x4C7470)();
}

RwTexture * CVehicleModelInfo::FindTextureCB(char const * name)
{
	return ((RwTexture* (__cdecl *)(char const*))0x4C7510)(name);
}

void CVehicleModelInfo::UseCommonVehicleTexDicationary()
{
	((void(__cdecl *)())0x4C75A0)();
}

void CVehicleModelInfo::StopUsingCommonVehicleTexDicationary()
{
	((void(__cdecl *)())0x4C75C0)();
}

RpAtomic * CVehicleModelInfo::MoveObjectsCB(RwObject * object, void * data)
{
	return ((RpAtomic* (__cdecl *)(RwObject*, void*))0x4C7700)(object, data);
}

RpAtomic * CVehicleModelInfo::HideDamagedAtomicCB(RpAtomic * atomic, void * data)
{
	return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x4C7720)(atomic, data);
}

RpAtomic * CVehicleModelInfo::HideAllComponentsAtomicCB(RpAtomic * atomic, void * data)
{
	return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x4C7790)(atomic, data);
}

RpMaterial * CVehicleModelInfo::HasAlphaMaterialCB(RpMaterial * material, void * data)
{
	return ((RpMaterial* (__cdecl *)(RpMaterial*, void*))0x4C77C0)(material, data);
}

RpAtomic * CVehicleModelInfo::SetAtomicRendererCB(RpAtomic * atomic, void * data)
{
	return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x4C77E0)(atomic, data);
}

RpAtomic * CVehicleModelInfo::SetAtomicRendererCB_RealHeli(RpAtomic * atomic, void * data)
{
	return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x4C7870)(atomic, data);
}

RpAtomic * CVehicleModelInfo::SetAtomicRendererCB_Plane(RpAtomic * atomic, void * data)
{
	return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x4C7930)(atomic, data);
}

RpAtomic * CVehicleModelInfo::SetAtomicRendererCB_Boat(RpAtomic * atomic, void * data)
{
	return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x4C79A0)(atomic, data);
}

RpAtomic * CVehicleModelInfo::SetAtomicRendererCB_Heli(RpAtomic * atomic, void * data)
{
	return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x4C7A30)(atomic, data);
}

RpAtomic * CVehicleModelInfo::SetAtomicRendererCB_Train(RpAtomic * atomic, void * data)
{
	return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x4C7AA0)(atomic, data);
}

void CVehicleModelInfo::SetAtomicRenderCallbacks()
{
	((void(__thiscall *)(CVehicleModelInfo*))0x4C7B10)(this);
}

RwObject * CVehicleModelInfo::SetAtomicFlagCB(RwObject * object, void * data)
{
	return ((RwObject* (__cdecl *)(RwObject*, void*))0x4C7B90)(object, data);
}

// Converted from stdcall RwObject* CVehicleModelInfo::ClearAtomicFlagCB(RwObject *object, void *data) 0x4C7BB0
RwObject* CVehicleModelInfo::ClearAtomicFlagCB(RwObject* object, void* data)
{
	return ((RwObject* (__cdecl *)(RwObject*, void*))0x4C7BB0)(object, data);
}

// Converted from thiscall void CVehicleModelInfo::SetVehicleComponentFlags(RwFrame *component, unsigned int flags) 0x4C7C10
void CVehicleModelInfo::SetVehicleComponentFlags(RwFrame* component, unsigned int flags)
{
	((void(__thiscall *)(CVehicleModelInfo*, RwFrame*, unsigned int))0x4C7C10)(this, component, flags);
}

// Converted from thiscall void CVehicleModelInfo::GetWheelPosn(int wheel, CVector &outVec, bool local) 0x4C7D20
void CVehicleModelInfo::GetWheelPosn(int wheel, CVector& outVec, bool local)
{
	((void(__thiscall *)(CVehicleModelInfo*, int, CVector&, bool))0x4C7D20)(this, wheel, outVec, local);
}

// Converted from thiscall bool CVehicleModelInfo::GetOriginalCompPosition(CVector &outVec, int component) 0x4C7DD0
bool CVehicleModelInfo::GetOriginalCompPosition(CVector& outVec, int component)
{
	return ((bool(__thiscall *)(CVehicleModelInfo*, CVector&, int))0x4C7DD0)(this, outVec, component);
}

// Converted from thiscall int CVehicleModelInfo::ChooseComponent(void) 0x4C8040
int CVehicleModelInfo::ChooseComponent()
{
	return ((int(__thiscall *)(CVehicleModelInfo*))0x4C8040)(this);
}

// Converted from thiscall int CVehicleModelInfo::ChooseSecondComponent(void) 0x4C8120
int CVehicleModelInfo::ChooseSecondComponent()
{
	return ((int(__thiscall *)(CVehicleModelInfo*))0x4C8120)(this);
}

// Converted from thiscall bool CVehicleModelInfo::IsUpgradeAvailable(VehicleUpgradePosn upgrade) 0x4C8200
bool CVehicleModelInfo::IsUpgradeAvailable(VehicleUpgradePosn upgrade)
{
	return ((bool(__thiscall *)(CVehicleModelInfo*, VehicleUpgradePosn))0x4C8200)(this, upgrade);
}

RpMaterial* CVehicleModelInfo::SetEditableMaterialsCBb(RpMaterial* material, void* data)
{
	RestoreEntry **pEntries = (RestoreEntry **)data;
	int CarColorID;
	int LightID = -1;
	int MaterialColor = *(int*)&material->color & 0xFFFFFF;
	int LighttextureType = 0;

	if (ms_pRemapTexture && material && RpMaterialGetTexture(material) && material->texture->name[0] == '#')
	{
		(*pEntries)->address = &material->texture;
		(*pEntries)->value = (int)material->texture;
		(*pEntries)++;
		material->texture = (RwTexture*)ms_pRemapTexture->raster;
	}

	if ((int)material->texture == (int)ms_pLightsTexture->raster)
		LighttextureType = 1;
	else if (ms_pCustomLightsTexture != nullptr && (int)material->texture == (int)ms_pCustomLightsTexture)
		LighttextureType = 2;
	else
		LighttextureType = 0;

	if (LighttextureType)
	{
		switch (MaterialColor)
		{
		case 0xAFFF: //Left Headlight 
			LightID = LightStatus.bHeadlight_Left;
			break;
		case 0xC8FF00: //Right Headlight
			LightID = LightStatus.bHeadlight_Right;
			break;
		case 0xFFB9: //Left taillight
			if (LighttextureType == 1)
				LightID = max(LightStatus.bTaillight_Left, LightStatus.bBrakelight_Left);
			else
				LightID = LightStatus.bTaillight_Left;
			break;
		case 0x3CFF: //Right Taillight
			if (LighttextureType == 1)
				LightID = max(LightStatus.bTaillight_Right, LightStatus.bBrakelight_Right);
			else
				LightID = LightStatus.bTaillight_Right;
			break;
		case 0xFFB8: //Left Brake Light
			LightID = LightStatus.bBrakelight_Left;
			break;
		case 0x3BFF: //Right Brake Light
			LightID = LightStatus.bBrakelight_Right;
			break;
		case 0xC6FF00: //Right Reverse Light
			LightID = LightStatus.bReverselight_Right;
			break;
		case 0xADFF: //Left Reverse Light
			LightID = LightStatus.bReverselight_Left;
			break;
		
		case 0xFFB7: //Front Left Indicator Light
			LightID = LightStatus.bIndicator_FrontLeft;
			break;
		case 0x3AFF: //Front Right Indicator Light
			LightID = LightStatus.bIndicator_FrontRight;
			break;
		case 0xFFB5: //Back Left Indicator Light
			LightID = LightStatus.bIndicator_RearLeft;
			break;
		case 0x38FF: //Back Right Indicator Light
			LightID = LightStatus.bIndicator_RearRight;
			break;
		default:
			LightID = -1;
		}
		(*pEntries)->address = &material->color;
		(*pEntries)->value = *(int*)&material->color;
		(*pEntries)++;
		material->color.red = 255;
		material->color.blue = 255;
		material->color.green = 255;

		if (LightID > 0)
		{
			(*pEntries)->address = &material->texture;
			(*pEntries)->value = (int)material->texture;
			(*pEntries)++;

			(*pEntries)->address = &material->surfaceProps.ambient;
			(*pEntries)->value = *(int*)&material->surfaceProps.ambient;
			(*pEntries)++;

			(*pEntries)->address = &material->surfaceProps.specular;
			(*pEntries)->value = *(int*)&material->surfaceProps.specular;
			(*pEntries)++;

			(*pEntries)->address = &material->surfaceProps.diffuse;
			(*pEntries)->value = *(int*)&material->surfaceProps.diffuse;
			(*pEntries)++;

			if (LighttextureType == 1)
				material->texture = (RwTexture*)ms_pLightsOnTexture->raster;
			else if (LighttextureType == 2)
				material->texture = ms_pCustomLightsOnTexture;

			material->surfaceProps.ambient = 16.0;
			material->surfaceProps.specular = 0;
			material->surfaceProps.diffuse = 0;
		}
	}
	else
	{
		switch (MaterialColor)
		{
		case 0xFF3C:	CarColorID = CVehicleModelInfo::ms_currentCol[0]; break;
		case 0xAF00FF:	CarColorID = CVehicleModelInfo::ms_currentCol[1]; break;
		case 0xFFFF00:	CarColorID = CVehicleModelInfo::ms_currentCol[2]; break;
		case 0xFF00FF:	CarColorID = CVehicleModelInfo::ms_currentCol[3]; break;
		default: return material;
		}
		(*pEntries)->address = &material->color;
		(*pEntries)->value = *(int*)&material->color; //get all colors somehow....
		(*pEntries)++;
		material->color.red		= CVehicleModelInfo::ms_vehicleColourTable[CarColorID].red;
		material->color.green	= CVehicleModelInfo::ms_vehicleColourTable[CarColorID].green;
		material->color.blue	= CVehicleModelInfo::ms_vehicleColourTable[CarColorID].blue;
	}
	return material;
	//return ((RpMaterial* (__cdecl *)(RpMaterial*, void*))0x4C8220)(material, data);
}

RpAtomic * CVehicleModelInfo::SetEditableMaterialsCB(RpAtomic * atomic, void * data)
{

	return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x4C83E0)(atomic, data);
}

// Converted from stdcall void CVehicleModelInfo::SetEditableMaterials(RpClump *clump) 0x4C8430
void CVehicleModelInfo::SetEditableMaterials(RpClump* clump)
{
	((void(__cdecl *)(RpClump*))0x4C8430)(clump);
}

// Converted from stdcall void CVehicleModelInfo::ResetEditableMaterials(RpClump *clump) 0x4C8460
void CVehicleModelInfo::ResetEditableMaterials(RpClump* clump)
{
	((void(__cdecl *)(RpClump*))0x4C8460)(clump);
}

// Converted from thiscall void CVehicleModelInfo::SetVehicleColour(unsigned char prim, unsigned char sec, unsigned char tert, unsigned char quat) 0x4C84B0
void CVehicleModelInfo::SetVehicleColour(unsigned char prim, unsigned char sec, unsigned char tert, unsigned char quat)
{
	((void(__thiscall *)(CVehicleModelInfo*, unsigned char, unsigned char, unsigned char, unsigned char))0x4C84B0)(this, prim, sec, tert, quat);
}

// Converted from thiscall void CVehicleModelInfo::ChooseVehicleColour(unsigned char &prim, unsigned char &sec, unsigned char &tert, unsigned char &quat, int variationShift) 0x4C8500
void CVehicleModelInfo::ChooseVehicleColour(unsigned char& prim, unsigned char& sec, unsigned char& tert, unsigned char& quat, int variationShift)
{
	((void(__thiscall *)(CVehicleModelInfo*, unsigned char&, unsigned char&, unsigned char&, unsigned char&, int))0x4C8500)(this, prim, sec, tert, quat, variationShift);
}

// Converted from thiscall int CVehicleModelInfo::GetNumRemaps(void) 0x4C86B0
int CVehicleModelInfo::GetNumRemaps()
{
	return ((int(__thiscall *)(CVehicleModelInfo*))0x4C86B0)(this);
}

// Converted from thiscall void CVehicleModelInfo::AddRemap(int txd) 0x4C86D0
void CVehicleModelInfo::AddRemap(int txd)
{
	((void(__thiscall *)(CVehicleModelInfo*, int))0x4C86D0)(this, txd);
}

// Converted from stdcall void CVehicleModelInfo::AddWheelUpgrade(int wheelSetNumber, int modelId) 0x4C8700
void CVehicleModelInfo::AddWheelUpgrade(int wheelSetNumber, int modelId)
{
	((void(__cdecl *)(int, int))0x4C8700)(wheelSetNumber, modelId);
}

int CVehicleModelInfo::GetNumWheelUpgrades(int wheelSetNumber)
{
	return ((int(__cdecl *)(int))0x4C8740)(wheelSetNumber);
}

void CVehicleModelInfo::GetWheelUpgrade(int wheelSetNumber, int wheelUpgradeNumber)
{
	((void(__cdecl *)(int, int))0x4C8750)(wheelSetNumber, wheelUpgradeNumber);
}

void CVehicleModelInfo::DeleteVehicleColourTextures()
{
	((void(__cdecl *)())0x4C8770)();
}

void CVehicleModelInfo::LoadEnvironmentMaps()
{
	((void(__cdecl *)())0x4C8780)();
}

void CVehicleModelInfo::ShutdownEnvironmentMaps()
{
	((void(__cdecl *)())0x4C87D0)();
}

RpMaterial* CVehicleModelInfo::GetMatFXEffectMaterialCB(RpMaterial* material, void* data)
{
	return ((RpMaterial* (__cdecl *)(RpMaterial*, void*))0x4C8810)(material, data);
}

RpMaterial* CVehicleModelInfo::SetEnvironmentMapCB(RpMaterial* material, void* data)
{
	return ((RpMaterial* (__cdecl *)(RpMaterial*, void*))0x4C8840)(material, data);
}

RpMaterial* CVehicleModelInfo::SetEnvMapCoeffCB(RpMaterial* material, void* data)
{
	return ((RpMaterial* (__cdecl *)(RpMaterial*, void*))0x4C88B0)(material, data);
}

RpAtomic* CVehicleModelInfo::SetRenderPipelinesCB(RpAtomic* atomic, void* data)
{
	return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x4C88F4)(atomic, data);
}

void CVehicleModelInfo::SetRenderPipelines()
{
	((void(__thiscall *)(CVehicleModelInfo*))0x4C8900)(this);
}

char* CVehicleModelInfo::GetCustomCarPlateText()
{
	return ((char*(__thiscall *)(CVehicleModelInfo*))0x4C8970)(this);
}

void CVehicleModelInfo::SetCustomCarPlateText(char* text)
{
	((void(__thiscall *)(CVehicleModelInfo*, char*))0x4C8980)(this, text);
}

int CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(int modelId)
{
	return ((int(__cdecl *)(int))0x4C89B0)(modelId);
}

void CVehicleModelInfo::ReduceMaterialsInVehicle()
{
	((void(__thiscall *)(CVehicleModelInfo*))0x4C8BD0)(this);
}

void CVehicleModelInfo::SetupLightFlags(CVehicle* vehicle)
{
	((void(__thiscall *)(CVehicleModelInfo*, CVehicle*))0x4C8C90)(this, vehicle);
}

RwFrame* CVehicleModelInfo::CollapseFramesCB(RwFrame* frame, void* data)
{
	return ((RwFrame* (__cdecl *)(RwFrame*, void*))0x4C8E30)(frame, data);
}

void CVehicleModelInfo::PreprocessHierarchy()
{
	((void(__thiscall *)(CVehicleModelInfo*))0x4C8E60)(this);
}

RpAtomic* CVehicleModelInfo::SetEnvironmentMapAtomicCB(RpAtomic* atomic, void* data)
{
	return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x4C9410)(atomic, data);
}

RpAtomic * CVehicleModelInfo::SetEnvMapCoeffAtomicCB(RpAtomic * atomic, void * data)
{
	return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x4C9430)(atomic, data);
}

void CVehicleModelInfo::SetCarCustomPlate()
{
	((void(__thiscall *)(CVehicleModelInfo*))0x4C9450)(this);
}

void CVehicleModelInfo::DisableEnvMap()
{
	((void(__thiscall *)(CVehicleModelInfo*))0x4C97E0)(this);
}

void CVehicleModelInfo::SetEnvMapCoeff(float coeff)
{
	((void(__thiscall *)(CVehicleModelInfo*, float))0x4C9800)(this, coeff);
}

int CVehicleModelInfo::GetNumDoors()
{
	return ((int(__thiscall *)(CVehicleModelInfo*))0x4C73C0)(this);
}

RpAtomic* CVehicleModelInfo::FindDirtMaterials(RpAtomic* atomic, void * data)
{

	return atomic;
}

// Courtesy of Silent (from SilentPatch)

void CVehicleModelInfo::FindEditableMaterialList()
{
	std::vector<RpMaterial*> editableMaterials;

	RpClump *clump = reinterpret_cast<RpClump*>(m_pRwObject);

	RpAtomic * atomic;
	RpGeometry *Geometry;

	for (RwLLLink* link = rwLinkListGetFirstLLLink(&clump->atomicList); link != rwLinkListGetTerminator(&clump->atomicList); link = rwLLLinkGetNext(link))
	{
		atomic = rwLLLinkGetData(link, RpAtomic, inClumpLink);
		if (atomic == nullptr)
			break;
		Geometry = atomic->geometry;
		int NumMaterials = Geometry->matList.numMaterials;
		for (int i = 0; i < NumMaterials; i++)
		{
			if (RwTexture* texture = RpMaterialGetTexture(Geometry->matList.materials[i]))
			{
				if (const char* texName = RwTextureGetName(texture))
				{
					if (strcmp(texName, "vehiclegrunge256") == 0)
						editableMaterials.push_back(Geometry->matList.materials[i]);

					if (strcmp(texName, "vehicle_genericmud_truck") == 0)
						editableMaterials.push_back(Geometry->matList.materials[i]);


					if (strcmp(texName, "vehiclegrunge_iv") == 0)
						editableMaterials.push_back(Geometry->matList.materials[i]);
				}
			}
		}
	}

	//
	//	FindDirtMaterials(m_pVehicleStruct->m_apExtras[i], &editableMaterials);

	for (uint32_t i = 0; i < m_pVehicleStruct->m_nNumExtras; i++)
	{
		Geometry = m_pVehicleStruct->m_apExtras[i]->geometry;
		int NumMaterials = Geometry->matList.numMaterials;
		for (int i = 0; i < NumMaterials; i++)
		{
			if (RwTexture* texture = RpMaterialGetTexture(Geometry->matList.materials[i]))
			{
				if (const char* texName = RwTextureGetName(texture))
				{
					if (strcmp(texName, "vehiclegrunge256") == 0)
						editableMaterials.push_back(Geometry->matList.materials[i]);

					if (strcmp(texName, "vehicle_genericmud_truck") == 0)
						editableMaterials.push_back(Geometry->matList.materials[i]);

					if (strcmp(texName, "vehiclegrunge_iv") == 0)
						editableMaterials.push_back(Geometry->matList.materials[i]);
				}
			}
		}
	}

	m_numDirtMaterials = editableMaterials.size();
	if (m_numDirtMaterials > IN_PLACE_BUFFER_DIRT_SIZE)
	{
		m_dirtMaterials = new RpMaterial*[m_numDirtMaterials];
		std::copy(editableMaterials.begin(), editableMaterials.end(), stdext::make_checked_array_iterator(m_dirtMaterials, m_numDirtMaterials));
	}
	else
	{
		m_dirtMaterials = nullptr;
		// Use existing space instead of allocating new space
		std::copy(editableMaterials.begin(), editableMaterials.end(), m_staticDirtMaterials);
	}
	m_nCurrentPrimaryColor = -1;
	m_nCurrentSecondaryColor = -1;
	m_nCurrentQuaternaryColor = -1;
	m_nCurrentTertiaryColor = -1;
}


void CVehicleModelInfo::RemapDirt(CVehicleModelInfo* modelInfo, uint32_t dirtID)
{
	RpMaterial** materials = modelInfo->m_numDirtMaterials > CVehicleModelInfo::IN_PLACE_BUFFER_DIRT_SIZE ? modelInfo->m_dirtMaterials : modelInfo->m_staticDirtMaterials;


	for (size_t i = 0; i < modelInfo->m_numDirtMaterials; i++)
	{
		// RpMaterialSetTexture(materials[i], materials[i]->texture);

		if (strcmp(materials[i]->texture->name, "vehicle_genericmud_truck") == 0)
			RpMaterialSetTexture(materials[i], CCarFxRender::ms_aDirtTextures_2[dirtID]);

		if (strcmp(materials[i]->texture->name, "vehiclegrunge_iv") == 0)
			RpMaterialSetTexture(materials[i], CCarFxRender::ms_aDirtTextures_3[dirtID]);

		if (strcmp(materials[i]->texture->name, "vehiclegrunge256") == 0)
			RpMaterialSetTexture(materials[i], CCarFxRender::ms_aDirtTextures[dirtID]);
	}

}

void CVehicleModelInfo::MyInit()
{
	//Patch New Dirt Materials (includes silents fix for Dirtlevels)
	MemoryVP::InjectHook(0x5D5DB0, &CVehicleModelInfo::RemapDirt, PATCH_JUMP);
	MemoryVP::InjectHook(0x4C9648, &CVehicleModelInfo::FindEditableMaterialList, PATCH_CALL);
	MemoryVP::Patch<DWORD>(0x4C964D, 0x0FEBCE8B);

	MemoryVP::InjectHook(0x4C8220, &CVehicleModelInfo::SetEditableMaterialsCBb, PATCH_JUMP);
}

