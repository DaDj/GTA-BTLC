#pragma once
#include "CAEAudioChannel.h"

class  CAEStreamingChannel {
public:
	CAEAudioChannel base;
	unsigned char field_60;
	unsigned char field_61;
	unsigned char field_62;
	unsigned char field_63;
	unsigned char field_64;
	unsigned char m_bFxEnabled;
	unsigned char field_66;
	unsigned char field_67;
	unsigned long field_68;
	unsigned char field_6C[393216];
	unsigned long field_6006C;
	unsigned long m_pStreamingDecoder;
	unsigned long field_60074;
	unsigned long field_60078;
	unsigned char field_6007C[8];
	unsigned long field_60084;
	int field_60088;
	int field_6008C;
	IDirectSoundBuffer8* m_pSoundBuffer; // IDirectSoundBuffer
	unsigned long field_60094;


	static void MyInit();

	bool RemoveFX();

	bool AddFX();

	bool SetBassEQ(IDirectSoundFXParamEq * type, float gain);

};


