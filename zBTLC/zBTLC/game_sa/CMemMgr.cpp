#include "CMemMgr.h"


CMemMgr::CMemMgr()
{
}


CMemMgr::~CMemMgr()
{
}

int CMemMgr::Calloc( size_t a2, size_t a3)
{
	return ((int(__cdecl *)( size_t, size_t))0x72F460)( a2, a3);
}
