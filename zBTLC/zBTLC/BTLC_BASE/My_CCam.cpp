#include "My_CCam.h"
//Credits: based on dk22pac's aiming mod. 
//TODO: Implement this for every weapon with the new weapon loader. I.e. every weapon will have an own offset section in weapon.json
namespace My_CCam
{

	void _fastcall Process_FollowPedWithMouse(CCam *cam, int, CVector const &vec, float arg3, float arg4, float arg5)
	{
		CPed *Player = FindPlayerPed();
		offset.x = 0.0f;
		offset.y = 0.2f;
		offset.z = 0.0f;
		plugin::CallMethod<0x50F970, CCam *, CVector const&>(cam, Player->TransformFromObjectSpace(offset), arg3, arg4, arg5);
	}


	void _fastcall Process_FollowPed(CCam *cam, int, CVector const &vec, float arg3, float arg4, float arg5, char arg6)
	{
		CPed *Player = FindPlayerPed();
		offset.x = 0.0f;
		offset.y = 0.2f;
		offset.z = 0.0f;
		plugin::CallMethod<0x522D40, CCam *, CVector const&>(cam, Player->TransformFromObjectSpace(offset), arg3, arg4, arg5, arg6);
	}

	static void _fastcall Process_AimWeapon(CCam *cam, int, CVector const &vec, float arg3, float arg4, float arg5)
	{
		CPed *Player = FindPlayerPed();
		if (Player && !Player->m_bInVehicle)
		{
			switch (Player->m_aWeapons[Player->m_nActiveWeaponSlot].m_Type) {
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
					offset.x = 0.38f;
					offset.y = 0.2f;
					offset.z = 0.0f;
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
	//MemoryVP::InjectHook(0x527A09, Process_FollowPed, PATCH_CALL);

	float AIMWEAPON_RIFLE1_ZOOM = 50.0f;
	float AIMWEAPON_RIFLE2_ZOOM = 50.0f;
	float AIMWEAPON_DEFAULT_ZOOM = 50.0f;
	float AIMWEAPON_DRIVE_CLOSE_ENOUGH = 0.17453f;
	float AIMWEAPON_DRIVE_SENS_MULT = 0.25f;
	float AIMWEAPON_FREETARGET_SENS = 0.1f;
	float AIMWEAPON_STICK_SENS = 0.007f;
	MemoryVP::Patch<float>(0x8CC4B4, AIMWEAPON_RIFLE1_ZOOM);
	MemoryVP::Patch<float>(0x8CC4B8, AIMWEAPON_RIFLE2_ZOOM);
	MemoryVP::Patch<float>(0x521632, AIMWEAPON_DEFAULT_ZOOM);
	MemoryVP::Patch<float>(0x8CC4B0, AIMWEAPON_DRIVE_CLOSE_ENOUGH);
	MemoryVP::Patch<float>(0x8CC4AC, AIMWEAPON_DRIVE_SENS_MULT);
	MemoryVP::Patch<float>(0x8CC4A8, AIMWEAPON_FREETARGET_SENS);
	MemoryVP::Patch<float>(0x8CC4A0, AIMWEAPON_STICK_SENS);

	}
}