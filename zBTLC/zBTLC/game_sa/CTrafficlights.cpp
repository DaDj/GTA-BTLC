#include "CTrafficlights.h"


void CTrafficLights::DisplayActualLight(CEntity * entity)
{
	MemoryVP::Patch<char>(0x49DAC6 + 4, 13);
	plugin::Call<0x49DAB0, CEntity*>(entity);
}