#pragma once
#include "plbase/PluginBase_SA.h"
#include "CAtomicModelInfo.h"

class CTimeModelInfo : public CAtomicModelInfo {
public:
	tTimeInfo m_timeInfo;

	void FindOtherTimeModel(char *modelName);
};

VALIDATE_SIZE(CTimeModelInfo, 0x24);