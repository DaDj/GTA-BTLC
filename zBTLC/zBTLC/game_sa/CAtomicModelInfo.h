#pragma once
#include "plbase/PluginBase_SA.h"
#include "CBaseModelInfo.h"

class CAtomicModelInfo : public CBaseModelInfo {
public:
	// vtable

	void SetAtomic(struct RpAtomic *atomic);

	struct RpAtomic *GetAtomicFromDistance(float distance);
};

VALIDATE_SIZE(CAtomicModelInfo, 0x20);