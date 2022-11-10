#include "CAEStreamingChannel.h"
#include "../game_sa/eax4.h"
#include "plbase/PluginBase_SA.h"
#include "../Patch/MemoryMgr.h"
#include "../BTLC_BASE/other_shared.h"
#include "../game_sa/common.h"

void CAEStreamingChannel::MyInit()
{

	MemoryVP::InjectHook(0x4D94C1, &CAEStreamingChannel::SetBassEQ, PATCH_JUMP);
	MemoryVP::InjectHook(0x4D94DA, &CAEStreamingChannel::SetBassEQ, PATCH_CALL);
	MemoryVP::InjectHook(0x4D94F6, &CAEStreamingChannel::SetBassEQ, PATCH_CALL);
}

bool CAEStreamingChannel::RemoveFX()
{
	return ((bool(__thiscall *)(CAEStreamingChannel *))0x4F1C20)(this);
}

bool CAEStreamingChannel::AddFX()
{
	return ((bool(__thiscall *)(CAEStreamingChannel *))0x4F1AE0)(this);
}

bool CAEStreamingChannel::SetBassEQ(IDirectSoundFXParamEq *paramEq, float gain)
{
	//always return false. Bass is fucked with the dsound.
	//it for some reason has nullptr/acces violation on paramEQ.
	return false;
	

	/*
	_GUID* GUID = (_GUID*)(0x8593B0);
	_GUID* GUIDInterface = (_GUID*)(0x8592D0);
	DSFXParamEq (*EQParamslist)[6] = (DSFXParamEq(*)[6])0x8CBA70;
	DSFXParamEq *EQParamslistCurrent;

	if (paramEq) 
	{
		if (m_bFxEnabled || AddFX())
		{
			for (int i = 0; i < 2; i++)
			{
				int test = base.m_pDirectSoundBuffer->GetObjectInPath(*GUID, 0, *GUIDInterface, (LPVOID*)paramEq);
				if (test > 0)
				{
					EQParamslistCurrent = EQParamslist[i]; //wtf? 
					EQParamslistCurrent->fGain  = EQParamslistCurrent->fGain + gain;
					paramEq->SetAllParameters(EQParamslistCurrent);
					paramEq->Release() ;
				}

			}
		}
	}
	else if (m_bFxEnabled)
	{
		RemoveFX();
	}

	return m_bFxEnabled;
	*/

	//	return ((bool(__thiscall *)(CAEStreamingChannel *, IDirectSoundFXParamEq*,float))0x4EF1E0)(this, type, gain);
}
