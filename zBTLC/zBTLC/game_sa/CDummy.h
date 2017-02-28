#pragma once
#include "plbase/PluginBase_SA.h"
#include "CEntity.h"

#pragma pack(push, 4)
class  CDummy : public CEntity {
public:
};
#pragma pack(pop)

VALIDATE_SIZE(CDummy, 0x38);