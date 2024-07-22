#pragma once
#include "plbase/PluginBase_SA.h"
#include "CPed.h"
#include "CVector.h"


#define FUNC_GTASA_crc32fromBlock 0x53CED0
#define FUNC_GTASA_crc32FromString 0x53CF00
#define FUNC_GTASA_crc32FromUpcaseString 0x53CF30
#define FUNC_GTASA_crc32Continue 0x53CF70

#define FUNC_FindPlayerCoors 0x56E010
#define FUNC_GetRandomBool 0x4D9C80
#define FUNC_FindPlayerPed 0x56E210

// Calculates GTA SA CRC32 from block of memory
static auto GTASA_crc32fromBlock = (unsigned int (__cdecl*)(void *block, size_t num))FUNC_GTASA_crc32fromBlock;

// Calculates GTA SA CRC32 from string
static auto GTASA_crc32FromString = (unsigned int (__cdecl*)(const char* str))FUNC_GTASA_crc32FromString;

// Calculates GTA SA CRC32 from string characters that are first turned into upper case.
static auto GTASA_crc32FromUpcaseString = (unsigned int (__cdecl*)(const char* str))FUNC_GTASA_crc32FromUpcaseString;

// Continues CRC32 calculation using another string
static auto GTASA_crc32FromStringContinue = (unsigned int (__cdecl*)(int crc, const char *str))FUNC_GTASA_crc32Continue;

// Writes player coordinates to outPoint
static auto FindPlayerCoors = (void (__cdecl*)(CVector *outPoint, int playerIndex))FUNC_FindPlayerCoors;

// Returns bool depending on randomized value.
// Uses probability value whereas 0.0 means always FALSE, 1.0 or more means always TRUE.
static auto GetRandomBool = (bool (__cdecl*)(float probability))FUNC_GetRandomBool;

// Returns pointer to player ped
//CPlayerPed* FindPlayerPed(int index = -1);