#include "CCarFxRender.h"
#include "CTxdStore.h"
#include "CClothesBuilder.h"

RwTexture **CCarFxRender::ms_aDirtTextures = (RwTexture **)0xC02BD0; 
RwTexture *CCarFxRender::ms_aDirtTextures_2[16] = {}; 
RwTexture *CCarFxRender::ms_aDirtTextures_3[16] = {};
RwTexture *CCarFxRender::ms_aDirtTextures_4[16] = {};
RwTexture *CCarFxRender::ms_aDirtTextures_5[16] = {};
RwTexture *CCarFxRender::ms_aDirtTextures_6[16] = {};

void CCarFxRender::Shutdown()
{
	((void(__cdecl *)())0x5D5AD0)();
}

void CCarFxRender::InitialiseDirtTexture()
{
	((void(__cdecl *)())0x5D5BC0)();
}

void CCarFxRender::MyShutdown()
{
	Shutdown();
	for (int i = 0; i < 16; i++)
	{
		RwTextureDestroy(ms_aDirtTextures_2[i]);
		//RwTextureDestroy(ms_aDirtTextures_3[i]);
		//RwTextureDestroy(ms_aDirtTextures_4[i]);
		//RwTextureDestroy(ms_aDirtTextures_5[i]);
		//RwTextureDestroy(ms_aDirtTextures_6[i]);
	}
}

void CCarFxRender::MyInitialiseDirtTextures()
{
	InitialiseDirtTexture();
	MyInitialiseDirtTextureSingle("vehicle_genericmud_truck", ms_aDirtTextures_2);
}

void CCarFxRender::MyInitialiseDirtTextureSingle(char* name, RwTexture** dirtTextureArray )
{
	RwTexture* texture;

	int Textureindex = CTxdStore::FindTxdSlot("VEHICLE");
	if (Textureindex == -1)
	{
		Textureindex = CTxdStore::AddTxdSlot("VEHICLE");
		CTxdStore::LoadTxd(Textureindex, "MODELS\\GENERIC\\VEHICLE.TXD");
		CTxdStore::AddRef(Textureindex);
	}
	CTxdStore::PushCurrentTxd();
	CTxdStore::SetCurrentTxd(Textureindex);
	//texture = RwReadTexture("vehicle_genericmud_truck", 0);
	texture = RwReadTexture(name, 0);
	texture->filterAddressing = 2;

	for (int texid = 0; texid < 16; texid++)
	{
		dirtTextureArray[texid] = CClothesBuilder::CopyTexture(texture);;
		RwTextureSetName(dirtTextureArray[texid], name);

		RwRaster* Dirtraster = dirtTextureArray[texid]->raster;
		RwUInt8* dirtArray = RwRasterLock(Dirtraster, 0, 3);
		RwUInt8* PointertoPixel = dirtArray;
		int width_counter = 0;
		int alpha = (4080 - (texid * 255)) / 16;

		for (int i = 1; i < texture->raster->height; i++)
		{
			PointertoPixel = (dirtArray + width_counter);

			for (int i2 = 0; i2 < texture->raster->width; i2++)
			{
				*(PointertoPixel + 0) = *(PointertoPixel + 0) / 16 * texid + alpha;
				*(PointertoPixel + 1) = *(PointertoPixel + 1) / 16 * texid + alpha;
				*(PointertoPixel + 2) = *(PointertoPixel + 2) / 16 * texid + alpha;
				PointertoPixel += 4;
			}
			width_counter = i * texture->raster->width * 4;
		}
		RwRasterUnlock(Dirtraster);
	}
	CTxdStore::PopCurrentTxd();
}



void CCarFxRender::MyInit()
{
	MemoryVP::InjectHook(0x53CA75, &CCarFxRender::MyShutdown, PATCH_CALL);
	MemoryVP::InjectHook(0x53CA61, &CCarFxRender::MyShutdown, PATCH_CALL);
	MemoryVP::InjectHook(0x5B8FFD, &CCarFxRender::MyInitialiseDirtTextures, PATCH_CALL);
}
