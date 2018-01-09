#pragma once
#include "plbase/PluginBase_SA.h"
#include "CClumpModelInfo.h"

class  CPedModelInfo : public CClumpModelInfo {
public:
    int m_nAnimType;
    unsigned int m_nPedType;
    unsigned int m_nStatType;
    unsigned short m_nCarsCanDriveMask;
    unsigned short m_nPedFlags;
    CColModel *m_pHitColModel;
    unsigned char m_nRadio1;
    unsigned char m_nRadio2;
    unsigned char m_nRace;
    char field_3B;
    short m_nPedAudioType;
    short m_nVoice1;
    short m_nVoice2;
    short m_nVoiceId;
};

