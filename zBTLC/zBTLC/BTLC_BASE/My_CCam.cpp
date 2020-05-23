#include "My_CCam.h"
#include "../game_sa/CCamera.h"
//Credits: based on dk22pac's aiming mod. 
//TODO: Implement this for every weapon with the new weapon loader. I.e. every weapon will have an own offset section in weapon.json
namespace My_CCam
{

	void _fastcall Process_FollowPedWithMouse(CCam *cam, int, CVector const &vec, float arg3, float arg4, float arg5)
	{
		CPed *Player = FindPlayerPed();
	/*	if (Switch_side())
			offset.x =0.0f;
		else*/
		offset.x = 0.20f;
		offset.y = -0.2f;
		offset.z = -0.11f;
		plugin::CallMethod<0x50F970, CCam *, CVector const&>(cam, Player->TransformFromObjectSpace(offset), arg3, arg4, arg5);
	}


	void _fastcall Process_FollowPed(CCam *cam, int, CVector const &vec, float arg3, float arg4, float arg5, char arg6)
	{
		CPed *Player = FindPlayerPed();
		/*if (Switch_side())
			offset.x = -0.0f;
		else*/
		offset.x = 0.10f;
		offset.y = 0.1f;
		offset.z = -0.00f;
		plugin::CallMethod<0x522D40, CCam *, CVector const&>(cam, Player->TransformFromObjectSpace(offset), arg3, arg4, arg5, arg6);
	}


	 void _fastcall Process_Rocket(CCam *_camthis, int, CVector const &a2, float a3, float a4, float a5, char HeatSeekingflag)
	{
		FindPlayerPed(-1)->m_bIsVisible = 1;
		CPed *Player = FindPlayerPed();


	/*	if (TheCamera.m_fPedZoomBase < -0.5)
			offset.y = 1.0;
		if (TheCamera.m_fPedZoomBase > 3.0)
			offset.y = -0.5;
		else if (TheCamera.m_fPedZoomBase > 1.0)
			offset.y = 0.0;*/

		offset.y = 0.0;


		if (Switch_side())
			offset.x = -0.24f;
		else
			offset.x = 0.34f;
		offset.z = -0.00f;


		plugin::CallMethod<0x521500, CCam *, CVector const&>(_camthis, Player->TransformFromObjectSpace(offset), a3, a4, a5);
	//	plugin::CallMethod<0x511B50, CCam *, CVector const&>(_camthis, Player->TransformFromObjectSpace(offset), a3, a4, a5, HeatSeekingflag);
	}


	static void _fastcall Process_AimWeapon(CCam *cam, int, CVector const &vec, float arg3, float arg4, float arg5)
	{
		CPed *Player = FindPlayerPed();
		if (Player && !Player->m_bInVehicle)
		{
			switch (Player->m_aWeapons[Player->m_nActiveWeaponSlot].m_nType) {
				case WEAPON_PISTOL:
				case WEAPON_PISTOL_SILENCED:
				case WEAPON_DESERT_EAGLE:
				case WEAPON_SHOTGUN:
				case WEAPON_SAWNOFF:
				case WEAPON_SPAS12:
				case WEAPON_MICRO_UZI:
				case WEAPON_MP5:
				case WEAPON_TEC9:
				case WEAPON_AK47:
				case WEAPON_M4:
				case WEAPON_COUNTRYRIFLE:
				case WEAPON_ROCKET:
				case WEAPON_ROCKET_HS:
				case WEAPON_FTHROWER:

				
			
				/*	if (TheCamera.m_fPedZoomBase < -0.5)
						offset.y = 1.0;
					if (TheCamera.m_fPedZoomBase > 3.0)
						offset.y = -0.5;
					else if (TheCamera.m_fPedZoomBase > 1.0)*/
						offset.y = 0.0;
						
				
					if (Switch_side())
						offset.x = -0.24f;
					else
						offset.x = 0.34f;
					offset.z = -0.00f;


					plugin::CallMethod<0x521500, CCam *, CVector const&>(cam, Player->TransformFromObjectSpace(offset), arg3, arg4, arg5);
					break;
				default:
					plugin::CallMethod<0x521500, CCam *, CVector const&>(cam, vec, arg3, arg4, arg5);
					break;
				}
		}
		else
			plugin::CallMethod<0x521500, CCam *, CVector const&>(cam, vec, arg3, arg4, arg5);
	}

	void INIT()
	{
	MemoryVP::InjectHook(0x527A95, Process_AimWeapon, PATCH_CALL);
	//MemoryVP::InjectHook(0x5279E5, Process_FollowPedWithMouse, PATCH_CALL);
	MemoryVP::InjectHook(0x527A09, Process_FollowPed, PATCH_CALL);
	MemoryVP::InjectHook(0x527A2D, Process_Rocket, PATCH_CALL);

	float AIMWEAPON_RIFLE1_ZOOM = 45.0f;
	float AIMWEAPON_RIFLE2_ZOOM = 30.0f;
	float AIMWEAPON_DEFAULT_ZOOM = 45.0f;
	float AIMWEAPON_DRIVE_CLOSE_ENOUGH = 0.04453f;
	float AIMWEAPON_DRIVE_SENS_MULT = 0.02f;
	float AIMWEAPON_FREETARGET_SENS = 0.05f;
	float AIMWEAPON_STICK_SENS = 0.007f;
	MemoryVP::Patch<float>(0x8CC4B4, AIMWEAPON_RIFLE1_ZOOM);
	MemoryVP::Patch<float>(0x8CC4B8, AIMWEAPON_RIFLE2_ZOOM);
	MemoryVP::Patch<float>(0x521632, AIMWEAPON_DEFAULT_ZOOM);
	MemoryVP::Patch<float>(0x8CC4B0, AIMWEAPON_DRIVE_CLOSE_ENOUGH);
	MemoryVP::Patch<float>(0x8CC4AC, AIMWEAPON_DRIVE_SENS_MULT);
	MemoryVP::Patch<float>(0x8CC4A8, AIMWEAPON_FREETARGET_SENS);
	MemoryVP::Patch<float>(0x8CC4A0, AIMWEAPON_STICK_SENS);

	struct tAimingCamData {
		float m_fMaxDist, m_fSomeAdditionalDist, _rel_to_vert_angle_mp, _someVertAngle, m_fZShift,  m_fVertAngleUpLimit, m_fVertAngleDownLimit;
	};
	
	tAimingCamData (&camdata)[4] = *(tAimingCamData(*)[4])0x8CC4C0;  //{ 1.3, 1.6, 1.0 -0.12, 0.0, 0.78539819, 1.5533431 };

	int index = 0;
	camdata[index].m_fMaxDist = 0.5f;
	camdata[index].m_fSomeAdditionalDist = 0.8f;
	camdata[index]._rel_to_vert_angle_mp = 1.0f;
	camdata[index]._someVertAngle = -0.10f;
	camdata[index].m_fZShift = 0.0f;
	camdata[index].m_fVertAngleUpLimit = 0.78539819f;
	camdata[index].m_fVertAngleDownLimit = 0.8533431f;



	}


	bool Switch_side()
	{
		static bool sw_side = false; //1 = right, 0 = left
		bool rightside_dis_clear = true; //false = way too near
		bool rightside_dis_clear_out = true; //false = way too near
		CVector Position_right = FindPlayerPed()->TransformFromObjectSpace(CVector(1.0f, 0.2f, 0.6f));
		CVector Position_right_out = FindPlayerPed()->TransformFromObjectSpace(CVector(1.5f, 0.2f, 0.6f));
		CVector Position_left = FindPlayerPed()->TransformFromObjectSpace(CVector(-1.0f, 0.2f, 0.6f));
		CVector PlayerPosition = FindPlayerCoors(-1);

		rightside_dis_clear_out = CWorld::GetIsLineOfSightClear(PlayerPosition, Position_right_out, 1, 1, 0, 0, 0, 0, 0);
		rightside_dis_clear = CWorld::GetIsLineOfSightClear(PlayerPosition, Position_right, 1, 1, 0, 0, 0, 0, 0);

		if (!rightside_dis_clear || (sw_side && !rightside_dis_clear_out))
			sw_side = true;
		else
			sw_side = false;
		return sw_side;
	}
}