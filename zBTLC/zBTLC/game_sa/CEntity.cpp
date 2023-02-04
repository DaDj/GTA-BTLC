#include "CEntity.h"
#include "CShadows.h"
#include "CVector.h"
#include "CCamera.h"
#include "CPointLights.h"
#include "common.h"
#include "RenderWare.h"
#include "CCoronas.h"
#include "CPickups.h"
#include "CModelIndices.h"
#include "CVector.h"
#include "CWaterlevel.h"
#include "CGeneral.h"
#include "CMotionBlurStreaks.h"




// vtable functions

void CEntity::My_Init()
{
	//MemoryVP::InjectHook(0x536977,0x536A67,PATCH_JUMP);
//	MemoryVP::InjectHook(0x536A68, &MyPreRender_Shadow, PATCH_CALL);
	MemoryVP::InjectHook(0x535FA0, &CEntity::PreRender, PATCH_JUMP);
	MemoryVP::Patch(0x858614, &SetupLighting);
	MemoryVP::Nop(0x553A3A, 5); //deactivate
}

void CEntity::PreRender()
{
	//((void(__thiscall *)(CEntity *))(*(void ***)this)[17])(this);
	
	auto mi = CModelInfo::GetModelInfo(m_wModelIndex);
	CBaseModelInfo* ami = mi->AsAtomicModelInfoPtr();

	if (mi->m_n2dfxCount)
		ProcessLightsForEntity();

	if (!mi->bHasBeenPreRendered) {
		mi->bHasBeenPreRendered = true;

		if (ami && ami->m_pRwObject) {
			if (RpMatFXAtomicQueryEffects(ami->m_pRwAtomic) &&   RpAtomicGetGeometry(ami->m_pRwAtomic)) {
				RpGeometryForAllMaterials(RpAtomicGetGeometry(ami->m_pRwAtomic), MaterialUpdateUVAnimCB, nullptr);
			}
		}

		mi->IncreaseAlpha();
		// PC Only
		//if (ami) {
		//	CCustomBuildingDNPipeline::PreRenderUpdate(ami->m_pRwAtomic, false);
		//}
		//else if (mi->GetModelType() == MODEL_INFO_CLUMP) {
		//	RpClumpForAllAtomics(mi->m_pRwClump, CCustomBuildingDNPipeline::PreRenderUpdateRpAtomicCB, reinterpret_cast<void*>(false));
		//}
		 // PC Only
	}

	if (!m_bHasPreRenderEffects)
		return;

	if (ami
		&& ami->SwaysInWind()
		&& (!IsObject() || !AsObject()->objectFlags.bIsExploded)
		) {
		auto fDist = DistanceBetweenPoints2D(GetPosition(), TheCamera.GetPosition());
		CObject::fDistToNearestTree = std::min<float>(CObject::fDistToNearestTree, fDist);
		ModifyMatrixForTreeInWind();
	}

	if (m_bIsBIGBuilding) {
		if (ami && ami->IsCrane())
			ModifyMatrixForCrane();

		return;
	}

	if (!IsObject() && !IsDummy())
		return;

	if (IsObject()) {
		auto obj = AsObject();
		if (m_wModelIndex == ModelIndices::MI_COLLECTABLE1) {
			CPickups::DoCollectableEffects(this->AsObject());
			UpdateRW();
			UpdateRwFrame();
		}
		else if (m_wModelIndex == ModelIndices::MI_MONEY) {
			CPickups::DoMoneyEffects(this->AsObject());
			UpdateRW();
			UpdateRwFrame();
		}
		else if (m_wModelIndex == ModelIndices::MI_CARMINE
			|| m_wModelIndex == ModelIndices::MI_NAUTICALMINE
			|| m_wModelIndex == ModelIndices::MI_BRIEFCASE) {

			if (obj->objectFlags.bIsPickup) {
				CPickups::DoMineEffects(this->AsObject());
				UpdateRW();
				UpdateRwFrame();
			}
		}
		else if (m_wModelIndex == MODEL_MISSILE) {
			if (true) { //CReplay::Mode != MODE_PLAYBACK . we wont allow playpack anyway.
				CVector vecPos = GetPosition();
				auto fRand = static_cast<float>(CGeneral::GetRandomNumber() % 16) / 16.0F;
				CShadows::StoreShadowToBeRendered(
					eShadowTextureType::SHADOWTEX_PED,
					gpShadowExplosionTex,
					&vecPos,
					8.0F,
					0.0F,
					0.0F,
					-8.0F,
					255,
					static_cast<uint8>(fRand * 200.0F),
					static_cast<uint8>(fRand * 160.0F),
					static_cast<uint8>(fRand * 120.0F),
					20.0F,
					false,
					1.0F,
					nullptr,
					false
				);

				CPointLights::AddLight(
					ePointLightType::PLTYPE_POINTLIGHT,
					vecPos,
					CVector(0.0F, 0.0F, 0.0F),
					8.0F,
					fRand,
					fRand * 0.8F,
					fRand * 0.6F,
					RwFogType::rwFOGTYPENAFOGTYPE,
					true,
					nullptr
				);

				CCoronas::RegisterCorona(
					reinterpret_cast<uint32>(this),
					nullptr,
					static_cast<uint8>(fRand * 255.0F),
					static_cast<uint8>(fRand * 220.0F),
					static_cast<uint8>(fRand * 190.0F),
					255,
					vecPos,
					fRand * 6.0F,
					300.0F,
					gpCoronaTexture[0],
					eCoronaFlareType::FLARETYPE_NONE,
					true,
					false,
					0,
					0.0F,
					false,
					1.5F,
					0,
					15.0F,
					false,
					false
				);
			}
		}
		else if (m_wModelIndex == ModelIndices::MI_FLARE) {
			CVector vecPos = GetPosition();
			auto fRand = static_cast<float>(CGeneral::GetRandomNumber() % 16) / 16.0F;
			fRand = std::max<float>(fRand, 0.5F);
			CShadows::StoreShadowToBeRendered(
				eShadowTextureType::SHADOWTEX_PED,
				gpShadowExplosionTex,
				&vecPos,
				8.0F,
				0.0F,
				0.0F,
				-8.0F,
				255,
				static_cast<uint8>(fRand * 200.0F),
				static_cast<uint8>(fRand * 200.0F),
				static_cast<uint8>(fRand * 200.0F),
				20.0F,
				false,
				1.0F,
				nullptr,
				false
			);

			CPointLights::AddLight(
				ePointLightType::PLTYPE_POINTLIGHT,
				vecPos,
				CVector(0.0F, 0.0F, 0.0F),
				32.0F,
				fRand,
				fRand,
				fRand,
				RwFogType::rwFOGTYPENAFOGTYPE,
				true,
				nullptr
			);

			CCoronas::RegisterCorona(
				reinterpret_cast<unsigned int>(this),
				nullptr,
				static_cast<unsigned char>(fRand * 255.0F),
				static_cast<unsigned char>(fRand * 255.0F),
				static_cast<unsigned char>(fRand * 255.0F),
				255,
				vecPos,
				fRand * 6.0F,
				300.0F,
				gpCoronaTexture[0],
				eCoronaFlareType::FLARETYPE_NONE,
				true,
				false,
				0,
				0.0F,
				false,
				1.5F,
				0,
				15.0F,
				false,
				false
			);
		}
		else if (IsGlassModel()) {
			PreRenderForGlassWindow();
		}
		else if (obj->objectFlags.bIsPickup) {
			CPickups::DoPickUpEffects((CObject*)this);
			UpdateRW();
			UpdateRwFrame();
		}
		else if (m_wModelIndex == MODEL_GRENADE) {
			auto const& vecPos = GetPosition();
			
			CVector vecScaledCam = TheCamera.m_mCameraMatrix.GetRight() * 0.07F;
			CVector vecStreakStart = vecPos - vecScaledCam;
			auto vecStreakEnd = vecPos + vecScaledCam;
			if (CVector2D(obj->m_vecMoveSpeed).Magnitude() > 0.03F) {
				CMotionBlurStreaks::RegisterStreak(reinterpret_cast<uint32>(this), 100, 100, 100, 255, vecStreakStart, vecStreakEnd);
			}
		}
		else if (m_wModelIndex == MODEL_MOLOTOV) {
			auto const& vecPos = GetPosition();
			CVector vecScaledCam = (TheCamera.m_mCameraMatrix.GetRight()) * 0.07F;
			CVector vecStreakStart = vecPos - vecScaledCam;
			CVector vecStreakEnd = vecPos + vecScaledCam;
			if (CVector2D(obj->m_vecMoveSpeed).Magnitude() > 0.03F) {
				float fWaterLevel;
				if (!CWaterlevel::GetWaterLevelNoWaves(vecPos, &fWaterLevel, nullptr, nullptr) || vecPos.z > fWaterLevel) {
					CMotionBlurStreaks::RegisterStreak(reinterpret_cast<uint32>(this), 255, 160, 100, 255, vecStreakStart, vecStreakEnd);
				}
			}
		}
		else if (m_wModelIndex == ModelIndices::MI_BEACHBALL) {
			if (DistanceBetweenPoints(GetPosition(), TheCamera.GetPosition()) < 50.0F) {
				auto ucShadowStrength = 0.8; //static_cast<uint8>(CTimeCycle::m_CurrentColours.m_nShadowStrength);
				CShadows::StoreShadowToBeRendered(
					eShadowType::SHADOW_DEFAULT,
					gpShadowPedTex,
					&GetPosition(),
					0.4F,
					0.0F,
					0.0F,
					-0.4F,
					ucShadowStrength,
					ucShadowStrength,
					ucShadowStrength,
					ucShadowStrength,
					20.0F,
					false,
					1.0F,
					nullptr,
					false
				);
			}
		}
		else if (m_wModelIndex == ModelIndices::MI_MAGNOCRANE_HOOK
			|| m_wModelIndex == ModelIndices::MI_WRECKING_BALL
			|| m_wModelIndex == ModelIndices::MI_CRANE_MAGNET
			|| m_wModelIndex == ModelIndices::MI_MINI_MAGNET
			|| m_wModelIndex == ModelIndices::MI_CRANE_HARNESS) {

			if (DistanceBetweenPoints(GetPosition(), TheCamera.GetPosition()) < 100.0F) {
				CShadows::StoreShadowToBeRendered(
					eShadowType::SHADOW_DEFAULT,
					gpShadowPedTex,
					&GetPosition(),
					2.0F,
					0.0F,
					0.0F,
					-2.0F,
					128,
					128,
					128,
					128,
					50.0F,
					false,
					1.0F,
					nullptr,
					false
				);
			}
		}
		else if (m_wModelIndex == ModelIndices::MI_WINDSOCK) {
			ModifyMatrixForPoleInWind();
		}
	}
	/*
	if (m_wModelIndex == ModelIndices::MI_TRAFFICLIGHTS) {
		CTrafficLights::DisplayActualLight(this);
		CShadows::StoreShadowForPole(this, 2.957F, 0.147F, 0.0F, 16.0F, 0.4F, 0);
	}
	else if (m_wModelIndex == ModelIndices::MI_TRAFFICLIGHTS_VERTICAL)
		CTrafficLights::DisplayActualLight(this);
	else if (m_wModelIndex == ModelIndices::MI_TRAFFICLIGHTS_MIAMI) {
		CTrafficLights::DisplayActualLight(this);
		CShadows::StoreShadowForPole(this, 4.81F, 0.0F, 0.0F, 16.0F, 0.4F, 0);
	}
	else if (m_wModelIndex == ModelIndices::MI_TRAFFICLIGHTS_TWOVERTICAL) {
		CTrafficLights::DisplayActualLight(this);
		CShadows::StoreShadowForPole(this, 7.503F, 0.0F, 0.0F, 16.0F, 0.4F, 0);
	}
	else if (m_wModelIndex == ModelIndices::MI_TRAFFICLIGHTS_3
		|| m_wModelIndex == ModelIndices::MI_TRAFFICLIGHTS_4
		|| m_wModelIndex == ModelIndices::MI_TRAFFICLIGHTS_5
		|| m_wModelIndex == ModelIndices::MI_TRAFFICLIGHTS_GAY
		) {
		CTrafficLights::DisplayActualLight(this);
	}
	else if (m_wModelIndex == ModelIndices::MI_SINGLESTREETLIGHTS1)
		CShadows::StoreShadowForPole(this, 7.744F, 0.0F, 0.0F, 16.0F, 0.4F, 0);
	else if (m_wModelIndex == ModelIndices::MI_SINGLESTREETLIGHTS2)
		CShadows::StoreShadowForPole(this, 0.043F, 0.0F, 0.0F, 16.0F, 0.4F, 0);
	else if (m_wModelIndex == ModelIndices::MI_SINGLESTREETLIGHTS3)
		CShadows::StoreShadowForPole(this, 1.143F, 0.145F, 0.0F, 16.0F, 0.4F, 0);
	else if (m_wModelIndex == ModelIndices::MI_DOUBLESTREETLIGHTS)
		CShadows::StoreShadowForPole(this, 0.0F, -0.048F, 0.0F, 16.0F, 0.4F, 0);
	else if (m_wModelIndex == ModelIndices::MI_TRAFFICLIGHTS_VEGAS) {
		CTrafficLights::DisplayActualLight(this);
		CShadows::StoreShadowForPole(this, 7.5F, 0.2F, 0.0F, 16.0F, 0.4F, 0);
	} */

	return;
}


void CEntity::MyPreRender_Shadow(CEntity *Entity)
{
	if (Entity == NULL)
		return;
	int Model_ID = Entity->m_wModelIndex;
	
	if(Model_ID == 0)
		return;


	static int TrafficL_Models[60] = { 4986,4987,6377,4989,4990,4991,4992,4993,5104,4995,5103,4997,4998,4999 };
	static int Lamp_Models[60] = { 1326,1347,1371,1573,1699,6401,5101, 5102,5105, 5380,5083,5351,5084,5350,5086,6389,6400,6402,6403,6404,6405,6406,6407,6408 };
	static int Bin_Models[60] = { 793, 794, 795, 796,797,798,799, 699,999, 5088,5089,5090,5091, 5092,5093,5094,5095,5096 };
	
	for (int  i = 0; i < 60; i++)
	{	
		if (Model_ID == TrafficL_Models[i])
		{
			CShadows::StoreShadowForPole(Entity, 0, 0.0, 0.2f, 16.0f, 0.5f, 0);
			((void(_cdecl*)(CEntity *))0x49DAB0)(Entity);
			return;
		}

		if (Model_ID == Lamp_Models[i])
		{
			CShadows::StoreShadowForPole(Entity, 0, 0.0, 0.2f, 16.0f, 0.5f, 0);
			return;
		}

	/*	if (Model_ID == Bin_Models[i])
		{
			CVector Pos = Entity->GetMatrix()->pos;
			CShadows::StoreShadowToBeRendered(1, gpShadowPedTex, &Pos, 2.0, 2.0, -2.0, -2.0, 255, 200, 200, 200, 10.2, 0, 2.0,0,0);
			CShadows::StoreShadowForPole(Entity, 0, 0.0, 0.2, 16.0, 0.5, 0);
			break;
		}*/
	} 


}
 
void CEntity::Add(CRect &rect)
{
	((void (__thiscall *)(CEntity *, CRect &))(unsigned int)(*(void ***)this)[1])(this, rect);
}

void CEntity::Add()
{
	((void (__thiscall *)(CEntity *))(*(void ***)this)[2])(this);
}

void CEntity::Remove()
{
	((void (__thiscall *)(CEntity *))(*(void ***)this)[3])(this);
}

void CEntity::SetIsStatic(bool isStatic)
{
	((void (__thiscall *)(CEntity *, bool))(*(void ***)this)[4])(this, isStatic);
}

void CEntity::SetModelIndex(unsigned int index)
{
	((void (__thiscall *)(CEntity *, unsigned int))(*(void ***)this)[5])(this, index);
}

void CEntity::SetModelIndexNoCreate(unsigned int index)
{
	((void (__thiscall *)(CEntity *, unsigned int))(*(void ***)this)[6])(this, index);
}

void CEntity::CreateRwObject()
{
	((void (__thiscall *)(CEntity *))(*(void ***)this)[7])(this);
}

void CEntity::DeleteRwObject()
{
	((void (__thiscall *)(CEntity *))(*(void ***)this)[8])(this);
}

CRect CEntity::GetBoundRect()
{
	return ((CRect (__thiscall *)(CEntity *))(*(void ***)this)[9])(this);
}

void CEntity::ProcessControl()
{
	((void (__thiscall *)(CEntity *))(*(void ***)this)[10])(this);
}

void CEntity::ProcessCollision()
{
	((void (__thiscall *)(CEntity *))(*(void ***)this)[11])(this);
}

void CEntity::ProcessShift()
{
	((void (__thiscall *)(CEntity *))(*(void ***)this)[12])(this);
}

bool CEntity::TestCollision()
{
	return ((bool (__thiscall *)(CEntity *))(*(void ***)this)[13])(this);
}

void CEntity::Teleport(CVector destination, bool resetRotation)
{
	((void (__thiscall *)(CEntity *, CVector, bool))(*(void ***)this)[14])(this, destination, resetRotation);
}

void CEntity::SpecialEntityPreCollisionStuff(CEntity *colEntity, bool unk1, unsigned char *unk2, unsigned char *unk3, unsigned char *unk4, unsigned char *unk5)
{
	((void (__thiscall *)(CEntity *, CEntity *, bool, unsigned char *, unsigned char *, unsigned char *, unsigned char *))(*(void ***)this)[15])(this, colEntity, unk1, unk2, unk3, unk4, unk5);
}

void CEntity::SpecialEntityCalcCollisionSteps(unsigned char *unk1, unsigned char *unk2)
{
	((void (__thiscall *)(CEntity *, unsigned char *, unsigned char *))(*(void ***)this)[16])(this, unk1, unk2);
}



void CEntity::Render()
{
	((void (__thiscall *)(CEntity *))(*(void ***)this)[18])(this);
}

bool CEntity::SetupLighting()
{
	this->m_bIsBIGBuilding = false;
	this->m_bLightObject = true;
	if (!m_bLightObject)
		return false;
	((void(__cdecl *)())0x735C80)(); //	ActivateDirectional();

	const auto& vecPos = GetPosition();
	auto fLight = CPointLights::GenerateLightsAffectingObject(&vecPos, nullptr, this) * 0.5F;
	SetLightColoursForPedsCarsAndObjects(fLight);

	//return ((bool (__thiscall *)(CEntity *))(*(void ***)this)[19])(this);
	return true;
}

void CEntity::RemoveLighting()
{
	((void (__thiscall *)(CEntity *))(*(void ***)this)[20])(this);
}

void CEntity::FlagToDestroyWhenNextProcessed()
{
	((void (__thiscall *)(CEntity *))(*(void ***)this)[21])(this);
}

// Converted from thiscall void CEntity::UpdateRwFrame(void) 0x532B00
void CEntity::UpdateRwFrame()
{
	((void (__thiscall *)(CEntity*))0x532B00)(this);
}

// Converted from thiscall void CEntity::UpdateRpHAnim(void) 0x532B20
void CEntity::UpdateRpHAnim()
{
	((void (__thiscall *)(CEntity*))0x532B20)(this);
}

// Converted from thiscall bool CEntity::HasPreRenderEffects(void) 0x532B70
bool CEntity::HasPreRenderEffects()
{
	return ((bool (__thiscall *)(CEntity*))0x532B70)(this);
}

// Converted from thiscall bool CEntity::DoesNotCollideWithFlyers(void) 0x532D40
bool CEntity::DoesNotCollideWithFlyers()
{
	return ((bool (__thiscall *)(CEntity*))0x532D40)(this);
}

// Converted from stdcall RpMaterial* MaterialUpdateUVAnimCB(RpMaterial *material,void *data) 0x532D70
RpMaterial* MaterialUpdateUVAnimCB(RpMaterial* material, void* data)
{
	return ((RpMaterial* (__cdecl *)(RpMaterial*, void*))0x532D70)(material, data);
}

// Converted from thiscall void CEntity::ModifyMatrixForPoleInWind(void) 0x532DB0
void CEntity::ModifyMatrixForPoleInWind()
{
	((void (__thiscall *)(CEntity*))0x532DB0)(this);
}

// Converted from thiscall bool CEntity::LivesInThisNonOverlapSector(int sectorX,int sectorY) 0x533050
bool CEntity::LivesInThisNonOverlapSector(int sectorX, int sectorY)
{
	return ((bool (__thiscall *)(CEntity*, int, int))0x533050)(this, sectorX, sectorY);
}

// Converted from thiscall void CEntity::SetupBigBuilding(void) 0x533150
void CEntity::SetupBigBuilding()
{
	((void (__thiscall *)(CEntity*))0x533150)(this);
}

// Converted from thiscall void CEntity::ModifyMatrixForCrane(void) 0x533170
void CEntity::ModifyMatrixForCrane()
{
	((void (__thiscall *)(CEntity*))0x533170)(this);
}

// Converted from thiscall void CEntity::PreRenderForGlassWindow(void) 0x533240
void CEntity::PreRenderForGlassWindow()
{
	((void (__thiscall *)(CEntity*))0x533240)(this);
}

// Converted from thiscall void CEntity::SetRwObjectAlpha(int alpha) 0x5332C0
void CEntity::SetRwObjectAlpha(int alpha)
{
	((void (__thiscall *)(CEntity*, int))0x5332C0)(this, alpha);
}

// Converted from stdcall bool IsEntityPointerValid(CEntity *entity) 0x533310
bool IsEntityPointerValid(CEntity* entity)
{
	return ((bool (__cdecl *)(CEntity*))0x533310)(entity);
}

// Converted from thiscall CVector CEntity::FindTriggerPointCoors(int triggerIndex) 0x533380
CVector CEntity::FindTriggerPointCoors(int triggerIndex)
{
	CVector result;
	((void (__thiscall *)(CEntity*, CVector*, int))0x533380)(this, &result, triggerIndex);
	return result;
}

// Converted from thiscall C2dEffect* CEntity::GetRandom2dEffect(int effectType,uchar) 0x533410
C2dEffect* CEntity::GetRandom2dEffect(int effectType, unsigned char arg1)
{
	return ((C2dEffect* (__thiscall *)(CEntity*, int, unsigned char))0x533410)(this, effectType, arg1);
}

// Converted from thiscall CVector CEntity::TransformFromObjectSpace(CVector const &offset) 0x5334F0
CVector CEntity::TransformFromObjectSpace(CVector const& offset)
{
	CVector result;
	((void (__thiscall *)(CEntity*, CVector*, CVector const&))0x5334F0)(this, &result, offset);
	return result;
}

// Converted from thiscall void CEntity::TransformFromObjectSpace(CVector &outPosn,CVector const &offset) 0x533560
void CEntity::TransformFromObjectSpace(CVector& outPosn, CVector const& offset)
{
	((void (__thiscall *)(CEntity*, CVector&, CVector const&))0x533560)(this, outPosn, offset);
}

// Converted from thiscall void CEntity::CreateEffects(void) 0x533790
void CEntity::CreateEffects()
{
	((void (__thiscall *)(CEntity*))0x533790)(this);
}

// Converted from thiscall void CEntity::DestroyEffects(void) 0x533BF0
void CEntity::DestroyEffects()
{
	((void (__thiscall *)(CEntity*))0x533BF0)(this);
}

// Converted from thiscall void CEntity::AttachToRwObject(RwObject *object, bool updateEntityMatrix) 0x533ED0
void CEntity::AttachToRwObject(RwObject* object, bool updateEntityMatrix)
{
	((void (__thiscall *)(CEntity*, RwObject*, bool))0x533ED0)(this, object, updateEntityMatrix);
}

// Converted from thiscall void CEntity::DetachFromRwObject(void) 0x533FB0
void CEntity::DetachFromRwObject()
{
	((void (__thiscall *)(CEntity*))0x533FB0)(this);
}

// Converted from thiscall CVector CEntity::GetBoundCentre(void) 0x534250
CVector CEntity::GetBoundCentre()
{
	CVector result;
	((void (__thiscall *)(CEntity*, CVector*))0x534250)(this, &result);
	return result;
}

// Converted from thiscall void CEntity::GetBoundCentre(CVector &outCentre) 0x534290
void CEntity::GetBoundCentre(CVector& outCentre)
{
	((void (__thiscall *)(CEntity*, CVector&))0x534290)(this, outCentre);
}

// Converted from thiscall void CEntity::RenderEffects(void) 0x5342B0
void CEntity::RenderEffects()
{
	((void (__thiscall *)(CEntity*))0x5342B0)(this);
}

// Converted from thiscall bool CEntity::GetIsTouching(CEntity *entity) 0x5343F0
bool CEntity::GetIsTouching(CEntity* entity)
{
	return ((bool (__thiscall *)(CEntity*, CEntity*))0x5343F0)(this, entity);
}

// Converted from thiscall bool CEntity::GetIsTouching(CVector const &centre,float radius) 0x5344B0
bool CEntity::GetIsTouching(CVector const& centre, float radius)
{
	return ((bool (__thiscall *)(CEntity*, CVector const&, float))0x5344B0)(this, centre, radius);
}

// Converted from thiscall bool CEntity::GetIsOnScreen(void) 0x534540
bool CEntity::GetIsOnScreen()
{
	return ((bool (__thiscall *)(CEntity*))0x534540)(this);
}

// Converted from thiscall bool CEntity::GetIsBoundingBoxOnScreen(void) 0x5345D0
bool CEntity::GetIsBoundingBoxOnScreen()
{
	return ((bool (__thiscall *)(CEntity*))0x5345D0)(this);
}

// Converted from thiscall void CEntity::ModifyMatrixForTreeInWind(void) 0x534E90
void CEntity::ModifyMatrixForTreeInWind()
{
	((void (__thiscall *)(CEntity*))0x534E90)(this);
}

// Converted from thiscall void CEntity::ModifyMatrixForBannerInWind(void) 0x535040
void CEntity::ModifyMatrixForBannerInWind()
{
	((void (__thiscall *)(CEntity*))0x535040)(this);
}

// Converted from thiscall CColModel* CEntity::GetColModel(void) 0x535300
CColModel* CEntity::GetColModel()
{
	return ((CColModel* (__thiscall *)(CEntity*))0x535300)(this);
}

// Converted from thiscall void CEntity::CalculateBBProjection(CVector *,CVector *,CVector *,CVector *) 0x535340
void CEntity::CalculateBBProjection(CVector* arg0, CVector* arg1, CVector* arg2, CVector* arg3)
{
	((void (__thiscall *)(CEntity*, CVector*, CVector*, CVector*, CVector*))0x535340)(this, arg0, arg1, arg2, arg3);
}

// Converted from thiscall void CEntity::UpdateAnim(void) 0x535F00
void CEntity::UpdateAnim()
{
	((void (__thiscall *)(CEntity*))0x535F00)(this);
}

// Converted from thiscall bool CEntity::IsVisible(void) 0x536BC0
bool CEntity::IsVisible()
{
	return ((bool (__thiscall *)(CEntity*))0x536BC0)(this);
}

// Converted from thiscall float CEntity::GetDistanceFromCentreOfMassToBaseOfModel(void) 0x536BE0
float CEntity::GetDistanceFromCentreOfMassToBaseOfModel()
{
	return ((float (__thiscall *)(CEntity*))0x536BE0)(this);
}

// Converted from thiscall void CEntity::CleanUpOldReference(CEntity** entity) 0x571A00
void CEntity::CleanUpOldReference(CEntity** entity)
{
	((void (__thiscall *)(CEntity*, CEntity**))0x571A00)(this, entity);
}

// Converted from thiscall void CEntity::ResolveReferences(void) 0x571A40
void CEntity::ResolveReferences()
{
	((void (__thiscall *)(CEntity*))0x571A40)(this);
}

// Converted from thiscall void CEntity::PruneReferences(void) 0x571A90
void CEntity::PruneReferences()
{
	((void (__thiscall *)(CEntity*))0x571A90)(this);
}

// Converted from thiscall void CEntity::RegisterReference(CEntity** entity) 0x571B70
void CEntity::RegisterReference(CEntity** entity)
{
	((void (__thiscall *)(CEntity*, CEntity**))0x571B70)(this, entity);
}

// Converted from thiscall void CEntity::ProcessLightsForEntity(void) 0x6FC7A0
void CEntity::ProcessLightsForEntity()
{
	((void (__thiscall *)(CEntity*))0x6FC7A0)(this);
}

// Converted from thiscall void CEntity::RemoveEscalatorsForEntity(void) 0x717900
void CEntity::RemoveEscalatorsForEntity()
{
	((void (__thiscall *)(CEntity*))0x717900)(this);
}

// Converted from thiscall bool CEntity::IsEntityOccluded(void) 0x71FAE0
bool CEntity::IsEntityOccluded()
{
	return ((bool (__thiscall *)(CEntity*))0x71FAE0)(this);
}

void CEntity::UpdateRW() {
	((void(__thiscall *)(CEntity*))0x446F90)(this);
}

bool CEntity::IsGlassModel()
{
	return ((bool(__thiscall *)(CEntity*))0x46A760)(this);
}
