#pragma once

#include "plbase/PluginBase_SA.h"

#pragma pack(push, 4)
class CWantedAudio
{
protected:
	void *vmt;
public:
	char field_4[12];
	int field_10;
	char field_14[108];
};
#pragma pack(pop)

VALIDATE_SIZE(CWantedAudio, 0x80);