#include "../game_sa/eax4.h"
#include "../game_sa/CAEStaticChannel.h"
#include "../game_sa/common.h"

class CMySoundeffects
{
public:
	static int gCurrentEnvironment ;
	static void __fastcall SetChannelAdditionalFX(CAEStaticChannel * channel, int, bool compressed);
	static void Init();
	static int SetReverbEnv();
	static float CMySoundeffects::GetDirectionalMikeAttenuation(const CVector& soundDir);
	static void CMySoundeffects::GetPositionRelativeToCamera(CVector* vecOut, const CVector* vecPos);
	CMySoundeffects();
};