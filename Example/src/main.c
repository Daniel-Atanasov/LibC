#include <stdio.h>

int main()
{
    Int * i;

    Bool success = T_Alloc(Int, &i);
    if (!success) {
        puts("Allocation failed");
        return 1;
    }

    printf("%d\n", *i);

    success = T_Free(Int, &i);
    if (!success) {
        puts("Deallocation failed");
        return 1;
    }
}