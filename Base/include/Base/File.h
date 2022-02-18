#pragma once

typedef Pointer File;

typedef enum MoveMethod
{
    FILE_MoveFromStart,
    FILE_MoveFromCurrent,
    FILE_MoveFromEnd
} MoveMethod;

Bool FILE_Open(File * file, String * filename);
Bool FILE_Size(File * file, Int64 * size);
Bool FILE_MoveCursor(File * file, Int64 amount, MoveMethod how);
Bool FILE_Read(File * file, Buffer buffer, Uint64 size);
Bool FILE_Write(File * file, Buffer buffer, Uint64 size);
Bool FILE_Close(File * file);

#define FILE_Seek_2(file, pos)      FILE_MoveCursor(file, amount, FILE_MoveFromCurrent)
#define FILE_Seek_3(file, pos, how) FILE_MoveCursor(file, amount, how)

#define FILE_Seek(...) OverloadName(FILE_Seek, __VA_ARGS__)(__VA_ARGS__)