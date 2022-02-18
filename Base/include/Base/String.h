#pragma once

// TODO@Daniel:
//   Just change this to a wrapper of normal allocations
//   A string is just a normal block of memory with a guaranteed zero at the end

typedef struct String
{
    Int64 size;
    Char * data;
} String;

Int64 STR_SeekNull(Char * first);

Bool STR_CreateEmpty(String * str);
Bool STR_CreateFromNull(String * str, Char * first);
Bool STR_CreateWithSize(String * str, Char * first, Int64 size);
Bool STR_Destroy(String * str);

Bool STR_ViewFromNull(String * str, Char * first);
Bool STR_ViewWithSize(String * str, Char * first, Int64 size);

Bool STR_Resize(String * str, Int64 size);
Bool STR_Equal(String * a, String * b);

#define STR_Create_1(str)              STR_CreateEmpty(str)
#define STR_Create_2(str, first)       STR_CreateFromNull(str, first)
#define STR_Create_3(str, first, size) STR_CreateWithSize(str, first, size)

#define STR_Create(...) OverloadName(STR_Create, __VA_ARGS__)(__VA_ARGS__)

#define STR_View_2(str, first)       STR_ViewFromNull(str, first)
#define STR_View_3(str, first, size) STR_ViewWithSize(str, first, size)

#define STR_View(...) OverloadName(STR_View, __VA_ARGS__)(__VA_ARGS__)