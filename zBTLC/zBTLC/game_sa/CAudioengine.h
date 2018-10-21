#pragma once

class CAudioEngine
{
public:
	void				ReportFrontendAudioEvent(int eventID, float volumechange, float speed);
};

extern CAudioEngine&		AudioEngine;