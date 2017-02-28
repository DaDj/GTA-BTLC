#pragma once
#include "plbase/PluginBase_SA.h"
#include "CEntity.h"

#pragma pack(push, 4)
class  CBuilding : public CEntity {
public:
	void ReplaceWithNewModel(int newModelIndex);
};
#pragma pack(pop)

VALIDATE_SIZE(CBuilding, 0x38);