
#include "CFileLoader.h"

 My_Objectnames CFileLoader::Objectnamelist[20000] = {};

// Converted from RwTexDictionary* CFileLoader::LoadTexDictionary(char const*filename) 0x5B3860
RwTexDictionary *CFileLoader::LoadTexDictionary(char const* filename) {
    return ((RwTexDictionary *(__cdecl *)(char const*))0x5B3860)(filename);
}

// Converted from cdecl void CFileLoader::SaveTexDictionary(RwTexDictionary *,char const*filename) 0x5B38C0
void CFileLoader::SaveTexDictionary(RwTexDictionary* dictionary, char const* filename) {
    ((void(__cdecl *)(RwTexDictionary*, char const*))0x5B38C0)(dictionary, filename);
}

// Converted from cdecl void CFileLoader::AddTexDictionaries(RwTexDictionary *dictionary,RwTexDictionary *baseDictionary) 0x5B3910
void CFileLoader::AddTexDictionaries(RwTexDictionary* dictionary, RwTexDictionary* baseDictionary) {
    ((void(__cdecl *)(RwTexDictionary*, RwTexDictionary*))0x5B3910)(dictionary, baseDictionary);
}

CEntity *CFileLoader::LoadObjectInstance(CFileObjectInstance * inst, char * modelname)
{
	return  ((CEntity *(__cdecl *)(CFileObjectInstance*, char *))0x538090)(inst, modelname);
}

CEntity * CFileLoader::LoadObjectInstance_a(const char * line)
{
	char modelName[24]; // [sp+0h] [bp-40h]@1
	CFileObjectInstance pos; // [sp+18h] [bp-28h]@1
	sscanf(
		line,
		"%d %s %d %f %f %f %f %f %f %f %d",
		&pos.modelID,
		modelName,
		&pos.interiorID,
		&pos,
		&pos.position.y,
		&pos.position.z,
		&pos.rotation,
		&pos.rotation.imag.y,
		&pos.rotation.imag.z,
		&pos.rotation.real,
		&pos.lod);

	strcpy(Objectnamelist[pos.modelID].mName,modelName);
	return LoadObjectInstance(&pos, modelName);
}
