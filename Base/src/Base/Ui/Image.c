typedef struct ImageData
{
    Int32 w;
    Int32 h;
    Color data[];
} ImageData;

constant Uint64 SizeOffset = offsetof(ImageData, data);

Bool IMG_Create(Image * image, Int32 w, Int32 h)
{
    assert(image != null);

    return SYS_AllocMemory(image, SizeOffset + sizeof(Color) * w * h);
}

Int32 IMG_Width(Image * image)
{
    assert(image != null);
    assert(*image != null);

    return cast(ImageData*, *image)->w;
}

Int32 IMG_Height(Image * image)
{
    assert(image != null);
    assert(*image != null);

    return cast(ImageData*, image)->h;
}

Color * IMG_At(Image * image, Int32 x, Int32 y)
{
    assert(image != null);
    assert(*image != null);

    return cast(ImageData*, *image)->data + (x + y * IMG_Width(image));
}

Bool IMG_Destroy(Image * image)
{
    assert(image != null);

    return SYS_FreeMemory(image);
}