#pragma once
#include "plbase/PluginBase_SA.h"
#include "CDummy.h"

#pragma pack(push, 4)
class CDummyObject : public CDummy {
public:
};
#pragma pack(pop)

VALIDATE_SIZE(CDummyObject, 0x38);