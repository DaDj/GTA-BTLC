#include "CAudioengine.h"

CAudioEngine&				AudioEngine = *(CAudioEngine*)0xB6BC90;

 void CAudioEngine::ReportFrontendAudioEvent(int eventID, float volumechange, float speed)
 {
	 ((void(__thiscall *)(CAudioEngine*,long, float,float))0x506EA0)(this,eventID, volumechange, speed);
 }

