//////////////////////////////////////////////////////////////////
////              SAN ANDREAS - Limit adjusting               ////
//////////////////////////////////////////////////////////////////
//// Author: D4DJ         VERSION: 1.0    DATE: 07.08.2016    ////
//////////////////////////////////////////////////////////////////
//// Description:                                             ////
//// increase limits of various GTA things                    ////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include "../game_sa/CStreaming.h"
#include "../Patch/MemoryMgr.h"
#include <iostream>



namespace limits
{
	int AddImageToList(LPCSTR lpFileName, char notPlayerFile)
	{
		//((void(__cdecl *)())0x4083C0)();
		//((void(__cdecl *)(LPCSTR, char))0x407610)(lpFileName,notPlayerFile);

		int v2; // edi@1
		CDirectories *v3; // eax@1
		int v5; // esi@5

		v2 = 0;
		v3 = CStreaming::IMG_FILES;
		while (v3->name[0])
		{
			++v3;
			++v2;
			if ((signed int)v3 >= (signed int)((int)(&CStreaming::IMG_FILES) + sizeof(CStreaming::IMG_FILES)))
				return 0;
		}
		v5 = v2;
		strcpy(CStreaming::IMG_FILES[v2].name, lpFileName);
		CStreaming::IMG_FILES[v5].streamHandle = ((int(__cdecl *)(LPCSTR, unsigned __int8))0x4067B0)(lpFileName, 0); //CDStreamOpen
		CStreaming::IMG_FILES[v5].isNotPlayerImg = notPlayerFile;
		std::cout << "IMG loaded ->" << CStreaming::IMG_FILES[v2].name  << std::endl;
		return v2;
	}

	//increase possible IMG FILES
	void IMG_LIMIT()
	{
	MemoryVP::InjectHook(0x407610, &AddImageToList, PATCH_JUMP);

		//MemoryVP::Patch<void*>(0x407614, &CStreaming::IMG_FILES);	//->mov     eax, offset _ZN10CStreaming8ms_filesE; CStreaming::ms_files
		MemoryVP::Patch<void*>(0x40763A, &CStreaming::IMG_FILES);	//->lea     edx, _ZN10CStreaming8ms_filesE.name[esi]; CStreaming::ms_files
		MemoryVP::Patch<void*>(0x4083E9, &CStreaming::IMG_FILES);	//->mov     eax, offset _ZN10CStreaming8ms_filesE; CStreaming::ms_files
		MemoryVP::Patch<void*>(0x40840B, &CStreaming::IMG_FILES);	//->mov     eax, offset _ZN10CStreaming8ms_filesE; CStreaming::ms_files
		MemoryVP::Patch<void*>(0x40843B, &CStreaming::IMG_FILES);	//->lea     edx, _ZN10CStreaming8ms_filesE.name[ecx]; CStreaming::ms_files
		MemoryVP::Patch<void*>(0x408479, &CStreaming::IMG_FILES);	//->lea     edx, _ZN10CStreaming8ms_filesE.name[edx]; CStreaming::ms_files
		MemoryVP::Patch<void*>(0x5B82F1, &CStreaming::IMG_FILES);	//->mov     al, _ZN10CStreaming8ms_filesE.name; CStreaming::ms_files
		MemoryVP::Patch<void*>(0x5B82FD, &CStreaming::IMG_FILES);	//->mov     esi, offset _ZN10CStreaming8ms_filesE; CStreaming::ms_files
		MemoryVP::Patch<void*>(0x407663, &CStreaming::IMG_FILES->isNotPlayerImg);	//0x28	//->mov     _ZN10CStreaming8ms_filesE.isNotPlayerImg[esi], al
		MemoryVP::Patch<void*>(0x408461, &CStreaming::IMG_FILES->isNotPlayerImg);	//0x28	//->mov     _ZN10CStreaming8ms_filesE.isNotPlayerImg[esi], 1
		MemoryVP::Patch<void*>(0x4084A8, &CStreaming::IMG_FILES->isNotPlayerImg );	//0x28	//->mov     _ZN10CStreaming8ms_filesE.isNotPlayerImg[esi], 1
		MemoryVP::Patch<void*>(0x40757F, &CStreaming::IMG_FILES->streamHandle);	//0x2C	//->mov     eax, _ZN10CStreaming8ms_filesE.streamHandle[eax]
		MemoryVP::Patch<void*>(0x4075B8, &CStreaming::IMG_FILES->streamHandle);	//0x2C	//->mov     edx, _ZN10CStreaming8ms_filesE.streamHandle[eax]
		MemoryVP::Patch<void*>(0x407656, &CStreaming::IMG_FILES->streamHandle);	//0x2C	//->mov     _ZN10CStreaming8ms_filesE.streamHandle[esi], eax
		MemoryVP::Patch<void*>(0x4083C1, &CStreaming::IMG_FILES->streamHandle) ;	//0x2C	//->mov     eax, offset _ZN10CStreaming8ms_filesE.streamHandle
		MemoryVP::Patch<void*>(0x40845B, &CStreaming::IMG_FILES->streamHandle);	//0x2C	//->mov     _ZN10CStreaming8ms_filesE.streamHandle[esi], eax
		MemoryVP::Patch<void*>(0x4084A2, &CStreaming::IMG_FILES->streamHandle);	//0x2C	//->mov     _ZN10CStreaming8ms_filesE.streamHandle[esi], eax
		MemoryVP::Patch<void*>(0x408FDC, &CStreaming::IMG_FILES->streamHandle);	//0x2C	//->mov     eax, _ZN10CStreaming8ms_filesE.streamHandle[edx]
		MemoryVP::Patch<void*>(0x409D5A, &CStreaming::IMG_FILES->streamHandle);	//0x2C	//->mov     ecx, _ZN10CStreaming8ms_filesE.streamHandle[ecx]
		MemoryVP::Patch<void*>(0x40A0B7, &CStreaming::IMG_FILES->streamHandle);	//0x2C	//->mov     eax, _ZN10CStreaming8ms_filesE.streamHandle[edx]
		MemoryVP::Patch<void*>(0x40CC54, &CStreaming::IMG_FILES->streamHandle);	//0x2C	//->mov     eax, _ZN10CStreaming8ms_filesE.streamHandle[edx]
		MemoryVP::Patch<void*>(0x40CCC7, &CStreaming::IMG_FILES->streamHandle);	//0x2C	//->mov     ecx, _ZN10CStreaming8ms_filesE.streamHandle[ecx]																	
		MemoryVP::Patch<int>(0x407621 + 1, ((int)(&CStreaming::IMG_FILES) + sizeof(CStreaming::IMG_FILES)));
		MemoryVP::Patch<int>(0x4083F9 + 1, ((int)(&CStreaming::IMG_FILES) + sizeof(CStreaming::IMG_FILES)));
		MemoryVP::Patch<int>(0x408419 + 1, ((int)(&CStreaming::IMG_FILES) + sizeof(CStreaming::IMG_FILES)));
		MemoryVP::Patch<int>(0x5B8301 + 2, ((int)(&CStreaming::IMG_FILES) + sizeof(CStreaming::IMG_FILES)));
		MemoryVP::Patch<int>(0x4083DD + 1, ((int)(&CStreaming::IMG_FILES) + 0x2c + sizeof(CStreaming::IMG_FILES)));
	}
}