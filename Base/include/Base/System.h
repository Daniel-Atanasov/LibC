#pragma once

Pointer SYS_GetModuleHandle();

Bool SYS_AllocMemory(Pointer * ptr, Uint64 size);
Bool SYS_ReallocMemory(Pointer * ptr, Uint64 size);
Bool SYS_FreeMemory(Pointer * ptr);

void MEM_Copy(Pointer restrict src, Int64 size, Pointer restrict dst);
void MEM_Swap(Pointer restrict src, Int64 size, Pointer restrict dst);

#define SYS_Alloc_2(type, ptr)        SYS_AllocMemory(ptr, sizeof(type))
#define SYS_Alloc_3(type, ptr, count) SYS_AllocMemory(ptr, sizeof(type) * count)

#define SYS_Alloc(...) OverloadName(SYS_Alloc, __VA_ARGS__)(__VA_ARGS__)

#define SYS_Realloc(type, ptr, count) SYS_ReallocMemory(ptr, sizeof(type) * count)

#define SYS_Free(type, ptr) SYS_FreeMemory(ptr)

#define Main SYS_Main

extern Int32 SYS_Main();