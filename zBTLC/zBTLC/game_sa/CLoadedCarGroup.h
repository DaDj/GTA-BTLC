#pragma once
#include "plbase/PluginBase_SA.h"

class CLoadedCarGroup {
public:
    short m_members[22]; // model ids
    short field_2C;
};

VALIDATE_SIZE(CLoadedCarGroup, 0x2E);