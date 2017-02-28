//////////////////////////////////////////////////////////////////
////              SAN ANDREAS - BUGFIXES					  ////
//////////////////////////////////////////////////////////////////
//// Author: D4DJ         VERSION: 2.0    DATE: 02.08.2016    ////
//////////////////////////////////////////////////////////////////
//// Description:                                             ////
//// A shitload of bugfixes.                                  ////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include <Windows.h>
#include "../Patch/MemoryMgr.h"

namespace BUGFIX
{
	/// <summary>
	/// FIXES of various GTA:SA BUGS
	/// </summary>
	void various()
	{
		//Enables running on metal.
	//	*(DWORD *)0x55E870 = 0xC2C03366;
	//	*(WORD *)0x55E874 = 0x0004;

		// Fix vehicle back lights both using light state 3 (SA bug)
	//	*(BYTE *)0x6E1D4F = 2;

		//FIXES/disables automatic weapon reload
		MemoryVP::Patch<char>(0x60B4DA, 0x83);
		MemoryVP::Patch<char>(0x60B4DA + 1, 0xC4);
		MemoryVP::Patch<char>(0x60B4DA + 2, 0x08);
		MemoryVP::Patch<char>(0x60B4DA + 3, 0xEB);
		MemoryVP::Patch<char>(0x60B4DA + 4, 0x21);
	}
}