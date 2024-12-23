#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "DynamicArray.h"

typedef char *String;

void printItem(void *itemPtr) {
    printf("\"%s\" ", *(String *)itemPtr);
}

void printDynamicArray(const char *name, DynamicArray *darr) {
    puts(name);
    mapDynamicArray(darr, printItem);
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

    DynamicArray darr;
    initDynamicArray(&darr, 0, sizeof(String), getMaxSizeDefaultImpl);

    puts("----- Dynamic array filling -----");
    for (int i = 0; i < argc; ++i) {
        char *str = allocString(argv[i]);
        pushBackDynamicArray(&darr, &str);

        printf("Iteration %d:\n", i + 1);
        printDynamicArray(dynamicArrayName, &darr);
    }

    puts("----- Dynamic array cleaning -----");
    for (int i = 0; i < argc; ++i) {
        delString(*(String *)getDynamicArrayBack(&darr));
        popBackDynamicArray(&darr);

        printf("Iteration %d:\n", i + 1);
        printDynamicArray(dynamicArrayName, &darr);
    }

    termDynamicArray(&darr);

    return 0;
}