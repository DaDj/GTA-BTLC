#pragma once


#include "plbase/PluginBase_SA.h"
#include "CAEAudioEntity.h"

class  CAEExplosionAudioEntity : public CAEAudioEntity {
public:
    char field_7C;
private:
    char _pad7D[3];
public:
};

VALIDATE_SIZE(CAEExplosionAudioEntity, 0x80);