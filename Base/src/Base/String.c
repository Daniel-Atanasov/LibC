Int64 STR_SeekNull(Char * first)
{
    assert(first != null);

    Int64 size = 0;
    while (first[size] != '\0')
    {
        size++;
    };
    return size;
}

Bool STR_CreateEmpty(String * str)
{
    assert(str != null);

    str->size = 0;
    str->data = null;
    return true;
}

Bool STR_CreateFromNull(String * str, Char * first)
{
    assert(str != null);
    assert(first != null);

    Int64 size = STR_SeekNull(first);
    return STR_CreateWithSize(str, first, size);
}

Bool STR_CreateWithSize(String * str, Char * first, Int64 size)
{
    assert(str != null);
    assert(first != null);

    Bool success = STR_Resize(str, size);
    if (!success)
    {
        return false;
    }

    for (Int64 idx = 0; idx < size; idx++)
    {
        str->data[idx] = first[idx];
    }

    return true;
}

Bool STR_Destroy(String * str)
{
    assert(str != null);

    Bool success = SYS_FreeMemory(&str->data);
    if (success)
    {
        str->size = 0;
    }
    return success;
}

Bool STR_ViewFromNull(String * str, Char * first)
{
    assert(str != null);
    assert(first != null);

    Int64 size = STR_SeekNull(first);
    return STR_ViewWithSize(str, first, size);
}

Bool STR_ViewWithSize(String * str, Char * first, Int64 size)
{
    assert(str != null);
    assert(first != null);

    str->size = size;
    str->data = first;
    return true;
}

Bool STR_Resize(String * str, Int64 size)
{
    assert(str != null);

    // NOTE@Daniel:
    //   We always keep the string zero terminated

    Bool success = SYS_ReallocMemory(&str->data, size + 1);
    if (success)
    {
        str->data[size] = '\0';
        str->size = size;
    }
    return success;
}

Bool STR_Equal(String * a, String * b)
{
    assert(a != null);
    assert(b != null);

    if (a->size != b->size)
    {
        return false;
    }

    for (Int64 idx = 0; idx < a->size; idx++)
    {
        if (a->data[idx] != b->data[idx])
        {
            return false;
        }
    }

    return true;
}