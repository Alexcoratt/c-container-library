#include <stdio.h>
#include "dynarray.h"

typedef char *string;

DEFINE_DYN_ARRAY(string, NULL)

void printArray(const DynArray_string *arr, const char *arrName) {
    size_t size = CALL_PTR(arr, size);

    if (arrName == NULL)
        arrName = "array";

    for (size_t i = 0; i < size; ++i)
        printf("%s[%lu] = \"%s\"\n", arrName, i, CALL_PTR(arr, getNoRangeCheck, i));
}

int main(int argc, char **argv) {
    DynArray_string arr;
    initDynArray_string(&arr, 0, NULL);

    puts("----- Array filling -----");
    for (int i = 0; i < argc; ++i) {
        CALL(arr, pushBack, argv[i]);
        printf("Iteration %d:\n", i);
        printArray(&arr, "arr");
        putchar('\n');
    }

    puts("----- Array cleaning -----");
    while (CALL(arr, size) != 0) {
        printf("Popped value: \"%s\"\n", CALL(arr, popBack));
        puts("Current array appearance:\n");
        printArray(&arr, "arr");
        putchar('\n');
    }

    puts("Finished!");

    CALL(arr, term);

    return 0;
}