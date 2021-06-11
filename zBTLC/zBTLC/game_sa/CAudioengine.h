#pragma once

class CAudioEngine
{
public:
	void	ReportFrontendAudioEvent(int eventID, float volumechange, float speed);
	char	IsRadioRetuneinProgress();
	static char GetCurrentRadioStationID();
};

extern CAudioEngine&		AudioEngine;