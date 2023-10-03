#pragma once

#include "plbase/PluginBase_SA.h"
#include "CPed.h"
#include "eCopType.h"

#pragma pack(push, 4)
class CCopPed : public CPed {
public:
	int field_79C;
	eCopType       m_copType;
    int field_7A4;
	class CCopPed *m_pCopPartner;
	CPed          *m_apCriminalsToKill[5];
	char field_7C0;

	static void My_Init();
	CCopPed* MySetCopWeapons(eCopType copType);

	// we can use modelIds as copType too!
    CCopPed(eCopType copType);

	void SetPartner(CCopPed* partner);
	void AddCriminalToKill(CPed* criminal);
	void RemoveCriminalToKill(CPed* likeUnused, int criminalIdx);
	void ClearCriminalsToKill();
};
#pragma pack(pop)

//VALIDATE_SIZE(CCopPed, 0x7C4);