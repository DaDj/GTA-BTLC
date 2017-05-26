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
#include "../game_sa/CWaterlevel.h"
#include "../Patch/MemoryMgr.h"
#include <iostream>
#include "limits.h"



namespace limits
{
	void Init()
	{
		limits::IMG_LIMIT();	//Limit adjusting
		Water_limit::init(); //waterlimit
	}

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

	namespace Water_limit
	{	
		void Vertices_limit()
		{
			MemoryVP::Patch<void*>(0x6E5B6E, &CWaterlevel::Vertices->posX); //= 0xC22910 + 0x0  -> mov     word ptr _ZN11CWaterLevel11m_aVerticesE.posX[eax], bx; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E5BC3, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E5BF7, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   ebp, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edi]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E5EA3, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E5ED7, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   ebp, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ebx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E5F84, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> mov     ax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E5F8B, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> cmp     ax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[esi]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E6487, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E64A7, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posX[eax*4]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E65E4, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E6608, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posX[eax*4]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E7B9B, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posX[eax*4]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E7BBC, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   edx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E7C51, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   ecx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[eax]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E7C73, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posX[edx*4]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E7E11, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> mov     dx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E7E18, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> cmp     dx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E7E3A, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> mov     cx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E7E41, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> cmp     cx, word ptr ss:_ZN11CWaterLevel11m_aVerticesE.posX[ebp]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E7E5A, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> mov     dx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E7E61, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> cmp     dx, word ptr ss:_ZN11CWaterLevel11m_aVerticesE.posX[ebp]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E811C, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> mov     dx, _ZN11CWaterLevel11m_aVerticesE.posX[ecx*4]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E8127, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> cmp     dx, _ZN11CWaterLevel11m_aVerticesE.posX[eax*4]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E8143, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> mov     bx, _ZN11CWaterLevel11m_aVerticesE.posX[ebx*4]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E814E, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> cmp     bx, _ZN11CWaterLevel11m_aVerticesE.posX[eax*4]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E9E2F, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ebx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E9E63, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   edx, _ZN11CWaterLevel11m_aVerticesE.posX[ecx*4]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6EA00A, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6EA04C, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6EA08E, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[esi]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6EFC1F, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[eax]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6EFC5E, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   ecx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6EFC95, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   edx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6EFDF9, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   edx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6EFE31, &CWaterlevel::Vertices->posX);//= 0xC22910 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[eax]; CWaterLevel::m_aVertices
			MemoryVP::Patch<void*>(0x6E5B36, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> mov     edx, offset _ZN11CWaterLevel11m_aVerticesE.posY
			MemoryVP::Patch<void*>(0x6E5B75, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> mov     _ZN11CWaterLevel11m_aVerticesE.posY[eax], di
			MemoryVP::Patch<void*>(0x6E5C15, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[edx]
			MemoryVP::Patch<void*>(0x6E5C45, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   ebx, _ZN11CWaterLevel11m_aVerticesE.posY[esi]
			MemoryVP::Patch<void*>(0x6E5EFC, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> mov     ax, _ZN11CWaterLevel11m_aVerticesE.posY[edx]
			MemoryVP::Patch<void*>(0x6E5F06, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> mov     di, _ZN11CWaterLevel11m_aVerticesE.posY[esi]
			MemoryVP::Patch<void*>(0x6E64BF, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]
			MemoryVP::Patch<void*>(0x6E64E0, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[edx*4]
			MemoryVP::Patch<void*>(0x6E6624, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]
			MemoryVP::Patch<void*>(0x6E6649, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[edx*4]
			MemoryVP::Patch<void*>(0x6E7BDC, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   edx, _ZN11CWaterLevel11m_aVerticesE.posY[eax*4]
			MemoryVP::Patch<void*>(0x6E7BF6, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]
			MemoryVP::Patch<void*>(0x6E7C58, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[eax]
			MemoryVP::Patch<void*>(0x6E7C8E, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> mov     cx, _ZN11CWaterLevel11m_aVerticesE.posY[edx*4]
			MemoryVP::Patch<void*>(0x6E7DF8, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> mov     bx, _ZN11CWaterLevel11m_aVerticesE.posY[edx]
			MemoryVP::Patch<void*>(0x6E7E08, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> cmp     bx, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]
			MemoryVP::Patch<void*>(0x6E7E31, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> cmp     bx, ss:_ZN11CWaterLevel11m_aVerticesE.posY[ebp]
			MemoryVP::Patch<void*>(0x6E801C, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> mov     ax, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]
			MemoryVP::Patch<void*>(0x6E8029, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> mov     bx, _ZN11CWaterLevel11m_aVerticesE.posY[edx]
			MemoryVP::Patch<void*>(0x6E804B, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> mov     bp, _ZN11CWaterLevel11m_aVerticesE.posY[eax*4]
			MemoryVP::Patch<void*>(0x6E8060, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[eax]
			MemoryVP::Patch<void*>(0x6E807B, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> mov     ax, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]
			MemoryVP::Patch<void*>(0x6E8088, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[eax]
			MemoryVP::Patch<void*>(0x6E809A, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> cmp     _ZN11CWaterLevel11m_aVerticesE.posY[ecx], bx
			MemoryVP::Patch<void*>(0x6E80BF, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> cmp     _ZN11CWaterLevel11m_aVerticesE.posY[edx], bx
			MemoryVP::Patch<void*>(0x6E80D8, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> cmp     _ZN11CWaterLevel11m_aVerticesE.posY[edx], bx
			MemoryVP::Patch<void*>(0x6E80FD, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> cmp     _ZN11CWaterLevel11m_aVerticesE.posY[edx*4], bx
			MemoryVP::Patch<void*>(0x6E9E8D, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[ebx]
			MemoryVP::Patch<void*>(0x6E9EC1, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   edx, _ZN11CWaterLevel11m_aVerticesE.posY[ecx*4]
			MemoryVP::Patch<void*>(0x6E9FFF, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   edx, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]
			MemoryVP::Patch<void*>(0x6EA03D, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[edx]
			MemoryVP::Patch<void*>(0x6EA07F, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[esi]
			MemoryVP::Patch<void*>(0x6EFC18, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   edi, _ZN11CWaterLevel11m_aVerticesE.posY[eax]
			MemoryVP::Patch<void*>(0x6EFC57, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]
			MemoryVP::Patch<void*>(0x6EFC8E, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posY[edx]
			MemoryVP::Patch<void*>(0x6EFDCB, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]
			MemoryVP::Patch<void*>(0x6EFE2A, &CWaterlevel::Vertices->posY);//= 0xC22910 + 0x2  -> movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posY[eax]
			MemoryVP::Patch<void*>(0x6E5863, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fld     _ZN11CWaterLevel11m_aVerticesE.posZ[eax*4]
			MemoryVP::Patch<void*>(0x6E58B7, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fld     _ZN11CWaterLevel11m_aVerticesE.posZ[eax*4]
			MemoryVP::Patch<void*>(0x6E5945, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fld     _ZN11CWaterLevel11m_aVerticesE.posZ[edx*4]
			MemoryVP::Patch<void*>(0x6E598F, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fld     _ZN11CWaterLevel11m_aVerticesE.posZ[eax*4]
			MemoryVP::Patch<void*>(0x6E5B7B, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> lea     edx, _ZN11CWaterLevel11m_aVerticesE.posZ[eax]
			MemoryVP::Patch<void*>(0x6E5CA9, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fld     _ZN11CWaterLevel11m_aVerticesE.posZ[esi]
			MemoryVP::Patch<void*>(0x6E5CB3, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[edx]
			MemoryVP::Patch<void*>(0x6E5CBB, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fld     _ZN11CWaterLevel11m_aVerticesE.posZ[edi]
			MemoryVP::Patch<void*>(0x6E5CC7, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[edx]
			MemoryVP::Patch<void*>(0x6E5CD3, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fadd    _ZN11CWaterLevel11m_aVerticesE.posZ[edx]
			MemoryVP::Patch<void*>(0x6E5D83, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fld     _ZN11CWaterLevel11m_aVerticesE.posZ[esi]
			MemoryVP::Patch<void*>(0x6E5D8E, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[eax*4]
			MemoryVP::Patch<void*>(0x6E5D96, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fld     _ZN11CWaterLevel11m_aVerticesE.posZ[edi]
			MemoryVP::Patch<void*>(0x6E5DA3, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[eax*4]
			MemoryVP::Patch<void*>(0x6E5DAE, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fadd    _ZN11CWaterLevel11m_aVerticesE.posZ[eax*4]
			MemoryVP::Patch<void*>(0x6E5FC4, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fld     _ZN11CWaterLevel11m_aVerticesE.posZ[esi]
			MemoryVP::Patch<void*>(0x6E5FD0, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[edx]
			MemoryVP::Patch<void*>(0x6E5FDE, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fld     _ZN11CWaterLevel11m_aVerticesE.posZ[ebx]
			MemoryVP::Patch<void*>(0x6E5FE4, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[edx]
			MemoryVP::Patch<void*>(0x6E5FF0, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fadd    _ZN11CWaterLevel11m_aVerticesE.posZ[edx]
			MemoryVP::Patch<void*>(0x6E60AE, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fld     _ZN11CWaterLevel11m_aVerticesE.posZ[esi]
			MemoryVP::Patch<void*>(0x6E60BA, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[ebx]
			MemoryVP::Patch<void*>(0x6E60C4, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fld     _ZN11CWaterLevel11m_aVerticesE.posZ[edx]
			MemoryVP::Patch<void*>(0x6E60CA, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[ebx]
			MemoryVP::Patch<void*>(0x6E60D4, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> fadd    _ZN11CWaterLevel11m_aVerticesE.posZ[ebx]
			MemoryVP::Patch<void*>(0x6E9FC7, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> mov     eax, _ZN11CWaterLevel11m_aVerticesE.posZ[ebx]
			MemoryVP::Patch<void*>(0x6EFBF6, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> lea     edi, _ZN11CWaterLevel11m_aVerticesE.posZ[eax]
			MemoryVP::Patch<void*>(0x6EFC35, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> lea     eax, _ZN11CWaterLevel11m_aVerticesE.posZ[ecx]
			MemoryVP::Patch<void*>(0x6EFC6C, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> lea     eax, _ZN11CWaterLevel11m_aVerticesE.posZ[edx]
			MemoryVP::Patch<void*>(0x6EFD90, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> lea     edi, _ZN11CWaterLevel11m_aVerticesE.posZ[edi*4]
			MemoryVP::Patch<void*>(0x6EFDC2, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> lea     edi, _ZN11CWaterLevel11m_aVerticesE.posZ[ecx]
			MemoryVP::Patch<void*>(0x6EFDF0, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> lea     edi, _ZN11CWaterLevel11m_aVerticesE.posZ[edx]
			MemoryVP::Patch<void*>(0x6EFE1E, &CWaterlevel::Vertices->posZ);//= 0xC22910 + 0x4  -> lea     edi, _ZN11CWaterLevel11m_aVerticesE.posZ[eax]
			MemoryVP::Patch<void*>(0x6E5CEF, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]
			MemoryVP::Patch<void*>(0x6E5CFD, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]
			MemoryVP::Patch<void*>(0x6E5D06, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]
			MemoryVP::Patch<void*>(0x6E5D0D, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]
			MemoryVP::Patch<void*>(0x6E5D1A, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fadd    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]
			MemoryVP::Patch<void*>(0x6E5DCB, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]
			MemoryVP::Patch<void*>(0x6E5DD9, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]
			MemoryVP::Patch<void*>(0x6E5DE2, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]
			MemoryVP::Patch<void*>(0x6E5DE9, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]
			MemoryVP::Patch<void*>(0x6E5DF4, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fadd    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]
			MemoryVP::Patch<void*>(0x6E600C, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]
			MemoryVP::Patch<void*>(0x6E601A, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]
			MemoryVP::Patch<void*>(0x6E6025, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]
			MemoryVP::Patch<void*>(0x6E602C, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]
			MemoryVP::Patch<void*>(0x6E6039, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fadd    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]
			MemoryVP::Patch<void*>(0x6E60F0, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]
			MemoryVP::Patch<void*>(0x6E60FE, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]
			MemoryVP::Patch<void*>(0x6E6107, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]
			MemoryVP::Patch<void*>(0x6E610E, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]
			MemoryVP::Patch<void*>(0x6E611B, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fadd    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]
			MemoryVP::Patch<void*>(0x6E9F09, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fld     _ZN11CWaterLevel11m_aVerticesE.tU[ebx]
			MemoryVP::Patch<void*>(0x6E9F41, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fld     _ZN11CWaterLevel11m_aVerticesE.tU[ecx]
			MemoryVP::Patch<void*>(0x6E9F71, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fld     _ZN11CWaterLevel11m_aVerticesE.tU[ecx]
			MemoryVP::Patch<void*>(0x6E9FA1, &CWaterlevel::Vertices->tU);//= 0xC22910 + 0x8  -> fld     _ZN11CWaterLevel11m_aVerticesE.tU[ecx]
			MemoryVP::Patch<void*>(0x6E5D30, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]
			MemoryVP::Patch<void*>(0x6E5D3E, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]
			MemoryVP::Patch<void*>(0x6E5D47, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]
			MemoryVP::Patch<void*>(0x6E5D4E, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]
			MemoryVP::Patch<void*>(0x6E5D5B, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fadd    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]
			MemoryVP::Patch<void*>(0x6E5E0B, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]
			MemoryVP::Patch<void*>(0x6E5E19, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]
			MemoryVP::Patch<void*>(0x6E5E22, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]
			MemoryVP::Patch<void*>(0x6E5E29, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]
			MemoryVP::Patch<void*>(0x6E5E34, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fadd    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]
			MemoryVP::Patch<void*>(0x6E604F, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]
			MemoryVP::Patch<void*>(0x6E605D, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]
			MemoryVP::Patch<void*>(0x6E6068, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]
			MemoryVP::Patch<void*>(0x6E606F, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]
			MemoryVP::Patch<void*>(0x6E607C, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fadd    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]
			MemoryVP::Patch<void*>(0x6E6131, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]
			MemoryVP::Patch<void*>(0x6E613F, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]
			MemoryVP::Patch<void*>(0x6E6148, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]
			MemoryVP::Patch<void*>(0x6E614F, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]
			MemoryVP::Patch<void*>(0x6E615C, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fadd    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]
			MemoryVP::Patch<void*>(0x6E9F20, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fld     _ZN11CWaterLevel11m_aVerticesE.tV[ebx]
			MemoryVP::Patch<void*>(0x6E9F54, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fld     _ZN11CWaterLevel11m_aVerticesE.tV[ecx]
			MemoryVP::Patch<void*>(0x6E9F84, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fld     _ZN11CWaterLevel11m_aVerticesE.tV[ecx]
			MemoryVP::Patch<void*>(0x6E9FB4, &CWaterlevel::Vertices->tV);//= 0xC22910 + 0xC  -> fld     _ZN11CWaterLevel11m_aVerticesE.tV[ecx]
			MemoryVP::Patch<void*>(0x6EA0EE, &CWaterlevel::Vertices->field_10);//= 0xC22910 + 0x10  -> movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.field_10[ebx]
			MemoryVP::Patch<void*>(0x6EA149, &CWaterlevel::Vertices->field_10);//= 0xC22910 + 0x10  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.field_10[ecx]
			MemoryVP::Patch<void*>(0x6EA193, &CWaterlevel::Vertices->field_10);//= 0xC22910 + 0x10  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.field_10[edx]
			MemoryVP::Patch<void*>(0x6EA1CB, &CWaterlevel::Vertices->field_10);//= 0xC22910 + 0x10  -> movsx   edx, _ZN11CWaterLevel11m_aVerticesE.field_10[esi]
			MemoryVP::Patch<void*>(0x6EA0F5, &CWaterlevel::Vertices->field_11);//= 0xC22910 + 0x11  -> movsx   edx, _ZN11CWaterLevel11m_aVerticesE.field_11[ebx]
			MemoryVP::Patch<void*>(0x6EA150, &CWaterlevel::Vertices->field_11);//= 0xC22910 + 0x11  -> movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.field_11[ecx]
			MemoryVP::Patch<void*>(0x6EA19A, &CWaterlevel::Vertices->field_11);//= 0xC22910 + 0x11  -> movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.field_11[edx]
			MemoryVP::Patch<void*>(0x6EA1D2, &CWaterlevel::Vertices->field_11);//= 0xC22910 + 0x11  -> movsx   eax, _ZN11CWaterLevel11m_aVerticesE.field_11[esi]
		}
		
		void Quads_Limit()
		{
			MemoryVP::Patch<void*>(0x6E5859, &CWaterlevel::Quads);  //= 0xC21C90 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel8m_aQuadsE.field_0[ecx]; CWaterLevel::m_aQuads
			MemoryVP::Patch<void*>(0x6E5985, &CWaterlevel::Quads);  //= 0xC21C90 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel8m_aQuadsE.field_0[ecx]; CWaterLevel::m_aQuads
			MemoryVP::Patch<void*>(0x6E7B88, &CWaterlevel::Quads);  //= 0xC21C90 + 0x0  -> mov     esi, offset _ZN11CWaterLevel8m_aQuadsE; CWaterLevel::m_aQuads
			MemoryVP::Patch<void*>(0x6E816A, &CWaterlevel::Quads);  //= 0xC21C90 + 0x0  -> mov     word ptr _ZN11CWaterLevel8m_aQuadsE.field_0[eax], si; CWaterLevel::m_aQuads
			MemoryVP::Patch<void*>(0x6E8635, &CWaterlevel::Quads);  //= 0xC21C90 + 0x0  -> lea     ecx, _ZN11CWaterLevel8m_aQuadsE.field_0[eax*2]; CWaterLevel::m_aQuads
			MemoryVP::Patch<void*>(0x6E8709, &CWaterlevel::Quads);  //= 0xC21C90 + 0x0  -> lea     ecx, _ZN11CWaterLevel8m_aQuadsE.field_0[eax*2]; CWaterLevel::m_aQuads
			MemoryVP::Patch<void*>(0x6E9E1D, &CWaterlevel::Quads);  //= 0xC21C90 + 0x0  -> mov     edi, offset _ZN11CWaterLevel8m_aQuadsE; CWaterLevel::m_aQuads
			MemoryVP::Patch<void*>(0x6E8171, &CWaterlevel::Quads->field_2);  //= 0xC21C90 + 0x2  -> mov     _ZN11CWaterLevel8m_aQuadsE.field_2[eax], di
			MemoryVP::Patch<void*>(0x6E8178, &CWaterlevel::Quads->field_4);  //= 0xC21C90 + 0x4  -> mov     _ZN11CWaterLevel8m_aQuadsE.field_4[eax], cx
			MemoryVP::Patch<void*>(0x6EFCCF, &CWaterlevel::Quads->field_4);  //= 0xC21C90 + 0x4  -> mov     esi, offset _ZN11CWaterLevel8m_aQuadsE.field_4
			MemoryVP::Patch<void*>(0x6E817F, &CWaterlevel::Quads->field_6);  //= 0xC21C90 + 0x6  -> mov     _ZN11CWaterLevel8m_aQuadsE.field_6[eax], dx
			MemoryVP::Patch<void*>(0x6E5849, &CWaterlevel::Quads->m_flags);  //= 0xC21C90 + 0x8  -> mov     dx, _ZN11CWaterLevel8m_aQuadsE.m_flags[ecx]
			MemoryVP::Patch<void*>(0x6E588A, &CWaterlevel::Quads->m_flags);  //= 0xC21C90 + 0x8  -> mov     _ZN11CWaterLevel8m_aQuadsE.m_flags[ecx], dx
			MemoryVP::Patch<void*>(0x6E5979, &CWaterlevel::Quads->m_flags);  //= 0xC21C90 + 0x8  -> mov     dx, _ZN11CWaterLevel8m_aQuadsE.m_flags[ecx]
			MemoryVP::Patch<void*>(0x6E59B0, &CWaterlevel::Quads->m_flags);  //= 0xC21C90 + 0x8  -> mov     _ZN11CWaterLevel8m_aQuadsE.m_flags[ecx], dx
			MemoryVP::Patch<void*>(0x6E8185, &CWaterlevel::Quads->m_flags);  //= 0xC21C90 + 0x8  -> and     byte ptr _ZN11CWaterLevel8m_aQuadsE.m_flags[eax], 0FEh
			MemoryVP::Patch<void*>(0x6E8199, &CWaterlevel::Quads->m_flags);  //= 0xC21C90 + 0x8  -> mov     cx, _ZN11CWaterLevel8m_aQuadsE.m_flags[eax]
			MemoryVP::Patch<void*>(0x6E81AD, &CWaterlevel::Quads->m_flags);  //= 0xC21C90 + 0x8  -> mov     _ZN11CWaterLevel8m_aQuadsE.m_flags[eax], cx
			MemoryVP::Patch<void*>(0x6E81B5, &CWaterlevel::Quads->m_flags);  //= 0xC21C90 + 0x8  -> or      byte ptr _ZN11CWaterLevel8m_aQuadsE.m_flags[eax], 4
			MemoryVP::Patch<void*>(0x6E81CB, &CWaterlevel::Quads->m_flags);  //= 0xC21C90 + 0x8  -> and     byte ptr _ZN11CWaterLevel8m_aQuadsE.m_flags[eax], 0FBh
		}

		void Triangles_Limit()
		{
			MemoryVP::Patch<void*>(0x6E58AD, &CWaterlevel::Triangles); // = 0xC22854 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel12m_aTrianglesE.field_0[edx]; CWaterLevel::m_aTriangles
			MemoryVP::Patch<void*>(0x6E593B, &CWaterlevel::Triangles); //= 0xC22854 + 0x0  -> movsx   eax, word ptr _ZN11CWaterLevel12m_aTrianglesE.field_0[esi]; CWaterLevel::m_aTriangles
			MemoryVP::Patch<void*>(0x6E7C44, &CWaterlevel::Triangles); //= 0xC22854 + 0x0  -> movsx   eax, _ZN11CWaterLevel12m_aTrianglesE.field_0[esi*8]; CWaterLevel::m_aTriangles
			MemoryVP::Patch<void*>(0x6E7E7F, &CWaterlevel::Triangles); //= 0xC22854 + 0x0  -> mov     _ZN11CWaterLevel12m_aTrianglesE.field_0[esi*8], cx; CWaterLevel::m_aTriangles
			MemoryVP::Patch<void*>(0x6E8673, &CWaterlevel::Triangles); //= 0xC22854 + 0x0  -> lea     edx, _ZN11CWaterLevel12m_aTrianglesE.field_0[eax*8]; CWaterLevel::m_aTriangles
			MemoryVP::Patch<void*>(0x6E86E4, &CWaterlevel::Triangles); //= 0xC22854 + 0x0  -> lea     eax, _ZN11CWaterLevel12m_aTrianglesE.field_0[eax*8]; CWaterLevel::m_aTriangles
			MemoryVP::Patch<void*>(0x6EFC27, &CWaterlevel::Triangles); //= 0xC22854 + 0x0  -> movsx   edx, _ZN11CWaterLevel12m_aTrianglesE.field_0[esi*8]; CWaterLevel::m_aTriangles
			MemoryVP::Patch<void*>(0x6E7C64, &CWaterlevel::Triangles->field_2); // = 0xC22854 + 0x2  -> movsx   ecx, _ZN11CWaterLevel12m_aTrianglesE.field_2[esi*8]
			MemoryVP::Patch<void*>(0x6E7E8B, &CWaterlevel::Triangles->field_2); // = 0xC22854 + 0x2  -> mov     _ZN11CWaterLevel12m_aTrianglesE.field_2[esi*8], dx
			MemoryVP::Patch<void*>(0x6EFBEA, &CWaterlevel::Triangles->field_2); // = 0xC22854 + 0x2  -> movsx   ecx, _ZN11CWaterLevel12m_aTrianglesE.field_2[esi*8]
			MemoryVP::Patch<void*>(0x6E7C7F, &CWaterlevel::Triangles->field_4); // = 0xC22854 + 0x4  -> movsx   ecx, _ZN11CWaterLevel12m_aTrianglesE.field_4[esi*8]
			MemoryVP::Patch<void*>(0x6E7E93, &CWaterlevel::Triangles->field_4); // = 0xC22854 + 0x4  -> mov     _ZN11CWaterLevel12m_aTrianglesE.field_4[esi*8], ax
			MemoryVP::Patch<void*>(0x6EFBE2, &CWaterlevel::Triangles->field_4); // = 0xC22854 + 0x4  -> movsx   eax, _ZN11CWaterLevel12m_aTrianglesE.field_4[esi*8]
			MemoryVP::Patch<void*>(0x6E589D, &CWaterlevel::Triangles->field_6); // = 0xC22854 + 0x6  -> mov     cx, _ZN11CWaterLevel12m_aTrianglesE.field_6[edx]
			MemoryVP::Patch<void*>(0x6E58DE, &CWaterlevel::Triangles->field_6); // = 0xC22854 + 0x6  -> mov     _ZN11CWaterLevel12m_aTrianglesE.field_6[edx], cx
			MemoryVP::Patch<void*>(0x6E592F, &CWaterlevel::Triangles->field_6); // = 0xC22854 + 0x6  -> mov     cx, _ZN11CWaterLevel12m_aTrianglesE.field_6[esi]
			MemoryVP::Patch<void*>(0x6E5966, &CWaterlevel::Triangles->field_6); // = 0xC22854 + 0x6  -> mov     _ZN11CWaterLevel12m_aTrianglesE.field_6[esi], cx
			MemoryVP::Patch<void*>(0x6E7E9A, &CWaterlevel::Triangles->field_6); // = 0xC22854 + 0x6  -> and     byte ptr _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8], 0FEh
			MemoryVP::Patch<void*>(0x6E7EA8, &CWaterlevel::Triangles->field_6); // = 0xC22854 + 0x6  -> mov     ax, _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8]
			MemoryVP::Patch<void*>(0x6E7EBD, &CWaterlevel::Triangles->field_6); // = 0xC22854 + 0x6  -> mov     _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8], ax
			MemoryVP::Patch<void*>(0x6E7EC6, &CWaterlevel::Triangles->field_6); // = 0xC22854 + 0x6  -> or      byte ptr _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8], 4
			MemoryVP::Patch<void*>(0x6E7EDA, &CWaterlevel::Triangles->field_6); // = 0xC22854 + 0x6  -> and     byte ptr _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8], 0FBh
			MemoryVP::Patch<void*>(0x6EFBD3, &CWaterlevel::Triangles->field_6); // = 0xC22854 + 0x6  -> test    byte ptr _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8], 1
			MemoryVP::Patch<void*>(0x6EFCA3, &CWaterlevel::Triangles->field_6); // = 0xC22854 + 0x6  -> and     byte ptr _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8], 0FEh
		}

		void TrianglesandQuadslist_Limit()
		{
			MemoryVP::Patch<void*>(0x6E57AA, CWaterlevel::QuadsandTrianglesList); //= 0xC215F6 + 0x0  -> mov     _ZN11CWaterLevel23m_QuadsAndTrianglesListE[eax*2], cx; CWaterLevel::m_QuadsAndTrianglesList
			MemoryVP::Patch<void*>(0x6E57B2, CWaterlevel::QuadsandTrianglesList + 1); //= 0xC215F6 + 0x2  -> mov     _ZN11CWaterLevel23m_QuadsAndTrianglesListE+2[eax*2], 0
			MemoryVP::Patch<void*>(0x6E57C8, CWaterlevel::QuadsandTrianglesList + 1); //= 0xC215F6 + 0x2  -> mov     _ZN11CWaterLevel23m_QuadsAndTrianglesListE+2[eax*2], dx
			MemoryVP::Patch<void*>(0x6E58F2, CWaterlevel::QuadsandTrianglesList + 1); //= 0xC215F6 + 0x2  -> lea     ecx, (_ZN11CWaterLevel23m_QuadsAndTrianglesListE+2)[eax*2]
			MemoryVP::Patch<void*>(0x6E86A1, CWaterlevel::QuadsandTrianglesList + 1); //= 0xC215F6 + 0x2  -> lea     eax, (_ZN11CWaterLevel23m_QuadsAndTrianglesListE+2)[eax*2]
			MemoryVP::Patch<void*>(0x6E6387, (char*)CWaterlevel::QuadsandTrianglesList + 3); //= 0xC215F6 + 0x3  -> test    byte ptr _ZN11CWaterLevel23m_QuadsAndTrianglesListE+3[eax*2], 0C0h
			MemoryVP::Patch<void*>(0x6E8699, (char*)CWaterlevel::QuadsandTrianglesList + 3); //= 0xC215F6 + 0x3  -> test    byte ptr _ZN11CWaterLevel23m_QuadsAndTrianglesListE+3[eax*2], 0C0h
			MemoryVP::Patch<void*>(0x6E57DE, CWaterlevel::QuadsandTrianglesList + 2); //= 0xC215F6 + 0x4  -> mov     _ZN11CWaterLevel23m_QuadsAndTrianglesListE+4[eax*2], dx
			MemoryVP::Patch<void*>(0x6E57E8, CWaterlevel::QuadsandTrianglesList + 3); //= 0xC215F6 + 0x6  -> mov     _ZN11CWaterLevel23m_QuadsAndTrianglesListE+6[eax*2], 0

		}

		void init()
		{
			Vertices_limit();
			Quads_Limit();
			TrianglesandQuadslist_Limit();
			Triangles_Limit();
		}
	}
}