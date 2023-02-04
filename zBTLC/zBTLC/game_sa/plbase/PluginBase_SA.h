
#pragma once
#include <cstddef>
#include <cstdint>
#include "../../BTLC_BASE/other_shared.h"
#include "../../Patch/MemoryMgr.h"
#include "../../Patch/calling.hpp"
#include "../../Patch/hooking.hpp"
#include "../../stdafx.h"


// Forward some structures
struct RwRaster;

// Structure validation macros

#define VALIDATE_SIZE(struc, size) static_assert(sizeof(struc) == size, "Invalid structure size of " #struc)
#define VALIDATE_OFFSET(struc, member, offset) \
	static_assert(offsetof(struc, member) == offset, "The offset of " #member " in " #struc " is not " #offset "...")


//VALIDATE_SIZE(bool, 1);
//VALIDATE_SIZE(char, 1);
//VALIDATE_SIZE(short, 2);
//VALIDATE_SIZE(int, 4);
//VALIDATE_SIZE(float, 4);

// Basic types for structures describing
//typedef unsigned char bool;

#define __parent_class_vtable__ private:\
                                 virtual void __dummy_virtual_func(){}\
                             public:\

// Main Library
namespace plugin
{
    // Core functionalities
	namespace Core
	{
		// unsigned int GetVersion();
    };
    
    // Post processing effects
	namespace PostProcess
	{
		//PLUGIN_API void PostProcessCreate();
		//PLUGIN_API void PostProcessDestroy();           
		//PLUGIN_API RwRaster*& GetGameScreenRaster();
	};
};


// Tricks library -- Used internally for some dirty tricks
namespace plugin
{
	struct dummy_func_t { };                // Dummy func tag type
	static const dummy_func_t dummy;        // Dummy func tag object

					
											
			// meta templates for constructors, destructors and new/delete operators

	template<typename ClassType, typename OverloadedDecl = void()>
	struct ctor_meta;

	template<typename ClassType>
	struct dtor_meta;

	template<typename ClassType>
	struct del_dtor_meta;

	template<typename ClassType, typename OverloadedDecl = void *(unsigned int)>
	struct op_new_meta;

	template<typename ClassType, typename OverloadedDecl = void *(unsigned int)>
	struct op_new_array_meta;

	template<typename ClassType, typename OverloadedDecl = void(void *)>
	struct op_delete_meta;

	template<typename ClassType, typename OverloadedDecl = void *(unsigned int)>
	struct op_delete_array_meta;

	// vtable description
	template<typename ClassType>
	struct vtable_meta;

	// stack_object

	template <typename T>
	struct stack_object {
	private:
		T object;
	public:
		template<typename ...ArgTypes>
		stack_object(ArgTypes... args) : object(args...) {}
		T *operator->() { return &object; }
		T &get_object() { return object; }
	};

	template <typename T>
	struct stack_object_no_default {
		stack_object_no_default() {}
		stack_object_no_default(stack_object_no_default &&) = delete;
		stack_object_no_default &operator=(stack_object_no_default &&) = delete;
	protected:
		char objBuff[sizeof(T)];
	public:
		T *operator->() { return reinterpret_cast<T *>(objBuff); }
		T &get_object() { return *reinterpret_cast<T *>(objBuff); }
	};

	// custom new/delete

	template <typename ClassType, typename... ArgTypes>
	ClassType *operator_new(ArgTypes... args) {
		return new ClassType(args...);
	}

	template <typename ClassType>
	ClassType *operator_new_array(size_t size) {
		return new ClassType[size];
	}

	template <typename ClassType>
	void operator_delete(ClassType *data) {
		delete data;
	}

	template <typename ClassType>
	void operator_delete_array(ClassType *data) {
		delete[] data;
	}

											
											
											// Gets the virtual method table from the object @self
	inline void** GetVMT(const void* self)
	{
		return *(void***)(self);
	}

	// Gets the virtual method from @self in the table index @index 
	inline void* GetVMT(const void* self, size_t index)
	{
		return GetVMT(self)[index];
	}
}

using plugin::GetVMT;

typedef int8_t    int8;
typedef int16_t   int16;
typedef int32_t   int32;
typedef int64_t   int64;
typedef uint8_t   uint8;
typedef uint16_t  uint16;
typedef uint32_t  uint32;
typedef uint64_t  uint64;
typedef intptr_t  intptr;
typedef uintptr_t uintptr;

typedef uint8     bool8;
typedef uint16    bool16;
typedef uint32    bool32;