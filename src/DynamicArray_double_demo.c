#include <stdio.h>
#include <stdlib.h>

#define DYNAMIC_ARRAY_VALUE_TYPE double
#include "DynamicArray.h"

void printItem(void *itemPtr) {
    printf("%lf ", *(double *)itemPtr);
}

void printDynamicArray(const char *name, DYNAMIC_ARRAY *darr) {
    puts(name);
    DYNAMIC_ARRAY_FUNCTION(map)(darr, printItem);
    putchar('\n');
}

int main(int argc, char **argv) {
    const char dynamicArrayName[] = "DynamicArray";

    DYNAMIC_ARRAY darr;
    DYNAMIC_ARRAY_FUNCTION(init)(&darr, 0, getMaxSizeDefaultImpl);

    puts("----- Dynamic array filling -----");
    for (int i = 0; i < argc; ++i) {
        double str = strtod(argv[i], NULL);
        DYNAMIC_ARRAY_FUNCTION(pushBack)(&darr, &str);

        printf("Iteration %d:\n", i + 1);
        printDynamicArray(dynamicArrayName, &darr);
    }

    puts("----- Dynamic array cleaning -----");
    for (int i = 0; i < argc; ++i) {
        DYNAMIC_ARRAY_FUNCTION(popBack)(&darr);

        printf("Iteration %d:\n", i + 1);
        printDynamicArray(dynamicArrayName, &darr);
    }

    DYNAMIC_ARRAY_FUNCTION(term)(&darr);

    return 0;
}