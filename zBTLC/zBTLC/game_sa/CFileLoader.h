
#include "plbase/PluginBase_SA.h"
#include "RenderWare.h"
#include "CVector.h"
#include "CEntity.h"

struct CFileObjectInstance
{
	CVector position;
	RtQuat rotation;
	int modelID;
	int interiorID;
	int lod;
};

struct My_Objectnames
{
	char mName[24];
};

class CFileLoader {
public:

	static My_Objectnames Objectnamelist[20000];
    // load txd from file
    static RwTexDictionary *LoadTexDictionary(char const* filename);
    // save txd to file
    static void SaveTexDictionary(RwTexDictionary* dictionary, char const* filename);
    // copy textures from dictionary to baseDictionary
    static void AddTexDictionaries(RwTexDictionary* dictionary, RwTexDictionary* baseDictionary);

	static CEntity *LoadObjectInstance(CFileObjectInstance *inst, char *modelname);

	static CEntity *LoadObjectInstance_a(const char *line);
};