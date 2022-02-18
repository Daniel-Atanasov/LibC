#pragma once

typedef Pointer Image;

Bool IMG_Create(Image * image, Int32 w, Int32 h);
Int32 IMG_Width(Image * image);
Int32 IMG_Height(Image * image);
Color * IMG_At(Image * image, Int32 x, Int32 y);
Bool IMG_Destroy(Image * image);