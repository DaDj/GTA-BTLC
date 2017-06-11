#pragma once
#include "../game_sa/common.h"
struct CAnimationStyleUnkData
{
	int		animID;
	int		unkFrameData;
};

class CAnimationStyleDescriptor
{
	public:
	char						name[16];
	char						IFPName[16];
	DWORD						unk;
	DWORD						animsCount;
	const char**				namesPtr;
	CAnimationStyleUnkData*		unkDataPtr;
	static	void My_init();

};


extern CAnimationStyleDescriptor *animationStyles;