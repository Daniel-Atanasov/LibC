#pragma once

Bool MEM_Alloc(Pointer * ptr, Uint64 size);
Bool MEM_Realloc(Pointer * ptr, Uint64 size);
Bool MEM_Free(Pointer * ptr);

#define T_Alloc_2(type, ptr)        MEM_Alloc(ptr, sizeof(type))
#define T_Alloc_3(type, ptr, count) MEM_Alloc(ptr, sizeof(type) * count)

#define T_Alloc(...) OverloadName(T_Alloc, __VA_ARGS__)(__VA_ARGS__)

#define T_Realloc(type, ptr, count) MEM_Realloc(ptr, sizeof(type) * count)

#define T_Free(type, ptr) MEM_Free(ptr)