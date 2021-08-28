#include <Windows.h>

Bool MEM_Alloc(Pointer * ptr, Uint64 size)
{
    Pointer tmp = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
    if (tmp)
    {
        *ptr = tmp;
    }
    return tmp != null;
}

Bool MEM_Realloc(Pointer * ptr, Uint64 size)
{
    Pointer tmp = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ptr, size);
    if (tmp)
    {
        *ptr = tmp;
    }
    return tmp != null;
}

Bool MEM_Free(Pointer * ptr)
{
    return HeapFree(GetProcessHeap(), 0, ptr);
}