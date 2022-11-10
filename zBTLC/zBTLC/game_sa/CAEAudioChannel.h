#pragma once
#include <dsound.h>

#pragma pack(push, 1)
class CAEAudioChannel {
public:
    void *vtable;
    IDirectSound8 *m_pDirectSound;
    IDirectSoundBuffer8 *m_pDirectSoundBuffer;
    IDirectSound3DBuffer *m_pDirectSound3DBuffer;
    char gap10[24];
    unsigned int m_dwFlags;
    unsigned int m_dwLengthInBytes;
    int field_30;
    float m_fVolume;
    char field_38;
    char field_39;
    short field_3A;
    int m_dwFrequency;
    int m_dwOriginalFrequency;
    bool m_bLooped;
    char field_45;
    char field_46;
    short field_47;
    short field_49;
    int field_4B;
    int field_4F;
    short field_53;
    short m_wBitsPerSample;
    short field_57;
    char _pad0[3];
    unsigned int dwBufferStatus;
};
#pragma pack(pop)

