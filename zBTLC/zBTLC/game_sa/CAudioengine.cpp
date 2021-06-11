#include "CAudioengine.h"

CAudioEngine&				AudioEngine = *(CAudioEngine*)0xB6BC90;

 void CAudioEngine::ReportFrontendAudioEvent(int eventID, float volumechange, float speed)
 {
	 ((void(__thiscall *)(CAudioEngine*,long, float,float))0x506EA0)(this,eventID, volumechange, speed);
 }

 char CAudioEngine::IsRadioRetuneinProgress()
 {
	return ((char(__thiscall *)(CAudioEngine*))0x506FF0)(this);
 }

 char CAudioEngine::GetCurrentRadioStationID()
 {
	 return ((char(__cdecl *)())0x507040)();
 }

