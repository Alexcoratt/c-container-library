#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "type_definitions.h"

#define DYNAMIC_ARRAY_VALUE_TYPE string
#include "DynamicArray.h"

void printItem(void *itemPtr) {
    printf("\"%s\" ", *(string *)itemPtr);
}

void printDynamicArray(const char *name, DynamicArray_string *darr) {
    puts(name);
    mapDynamicArray_string(darr, printItem);
    putchar('\n');
}

char *allocString(const char *str) {
    if (str == NULL)
        return NULL;

    const size_t size = strlen(str) + 1;
    char *res = (char *)malloc(size * sizeof(char));
    memcpy(res, str, size);
    return res;
}

void delString(char *str) {
    free(str);
}

int main(int argc, char **argv) {
    const char dynamicArrayName[] = "DynamicArray";

    DynamicArray_string darr;
    initDynamicArray_string(&darr, 0, getMaxSizeDefaultImpl);

    puts("----- Dynamic array filling -----");
    for (int i = 0; i < argc; ++i) {
        char *str = allocString(argv[i]);
        pushBackDynamicArray_string(&darr, &str);

        printf("Iteration %d:\n", i + 1);
        printDynamicArray(dynamicArrayName, &darr);
    }

    puts("----- Dynamic array cleaning -----");
    for (int i = 0; i < argc; ++i) {
        delString(*atBackDynamicArray_string(&darr));
        popBackDynamicArray_string(&darr);

        printf("Iteration %d:\n", i + 1);
        printDynamicArray(dynamicArrayName, &darr);
    }

    termDynamicArray_string(&darr);

    return 0;
}