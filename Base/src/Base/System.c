#include <Windows.h>

typedef struct Allocation
{
    Uint64 size;
    Byte data[];
} Allocation;

constant Uint64 SizeOffset = offsetof(Allocation, data);

internal Pointer ModuleHandle;
internal Pointer ProcessHeap;

// NOTE@Daniel:
//   Only works on link.exe
extern IMAGE_DOS_HEADER __ImageBase;
Pointer SYS_GetModuleHandle()
{
    return &__ImageBase;
}

internal Allocation * MEM_GetInfo(Pointer ptr)
{
    assert(ptr != null);

    return ptr - SizeOffset;
}

Uint64 MEM_Size(Pointer ptr)
{
    return MEM_GetInfo(ptr)->size;
}

Bool SYS_AllocMemory(Pointer * ptr, Uint64 size)
{
    assert(ptr != null);

    // TODO@Daniel:
    //   A size of 0 should be represented as null

    size += SizeOffset;
    Pointer tmp = HeapAlloc(ProcessHeap, HEAP_ZERO_MEMORY, size);
    if (tmp)
    {
        *ptr = tmp + SizeOffset;
    }
    return tmp != null;
}

Bool SYS_ReallocMemory(Pointer * ptr, Uint64 size)
{
    assert(ptr != null);

    size += SizeOffset;

    if (*ptr == null)
    {
        return SYS_AllocMemory(ptr, size);
    }

    Pointer tmp = HeapReAlloc(ProcessHeap, HEAP_ZERO_MEMORY, MEM_GetInfo(*ptr), size);
    if (tmp)
    {
        *ptr = tmp + SizeOffset;
    }
    return tmp != null;
}

Bool SYS_FreeMemory(Pointer * ptr)
{
    assert(ptr != null);

    if (*ptr == null)
    {
        return true;
    }

    Bool success = HeapFree(ProcessHeap, 0, MEM_GetInfo(*ptr));
    if (success)
    {
        *ptr = null;
    }
    return success;
}

Int32 main()
{
    ModuleHandle = &__ImageBase;
    ProcessHeap = GetProcessHeap();

    assert(ProcessHeap != null);

    return SYS_Main();
}