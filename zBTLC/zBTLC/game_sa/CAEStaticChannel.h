#pragma once
#include "CAEAudioChannel.h"

class CAEStaticChannel : public CAEAudioChannel {
public:
    char field_60;
    char field_61;
    char field_62;
    char field_63;
    unsigned int m_nCurrentBufferOffset;
    int field_68;
    int field_6C;
    int m_nSyncTime;
    int field_74;
    unsigned int m_dwLockOffset;
    unsigned int m_nNumLockBytes;
    short field_80;
    short field_82;
    void *m_pBuffer;
    short field_88;
    char field_8A;
    char field_8B;
    int field_8C;
};
