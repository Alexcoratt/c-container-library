#include <stdio.h>
#include <math.h>

#include "type_definitions.h"
#include "default_functions_impl.h"

#define DYNAMIC_ARRAY_VALUE_TYPE int
#include "DynamicArray.h"
#undef DYNAMIC_ARRAY_VALUE_TYPE
#undef DYNAMIC_ARRAY_H

#define DYNAMIC_ARRAY_VALUE_TYPE string
#include "DynamicArray.h"
#undef DYNAMIC_ARRAY_VALUE_TYPE
#undef DYNAMIC_ARRAY_H

#undef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
#undef DYNAMIC_ARRAY
#include "DynamicArray.h"

int hash(const char *);
void printInt(int *);
void printDouble(double *);
void printString(string *);

int main(int argc, char **argv) {
    DynamicArray_int hashes;
    initDynamicArray_int(&hashes, 0, getMaxSizeDefaultImpl);

    DynamicArray_string strings;
    initDynamicArray_string(&strings, 0, getMaxSizeDefaultImpl);

    DynamicArray sineArray;
    initDynamicArray(&sineArray, 0, sizeof(double), getMaxSizeDefaultImpl);

    puts("----- fill -----");
    for (int i = 0; i < argc; ++i) {
        const int h = hash(argv[i]);
        const double s = sin(h);

        pushBackDynamicArray_int(&hashes, &h);
        pushBackDynamicArray(&sineArray, &s);
        pushBackDynamicArray_string(&strings, argv + i);

        printf("iter %d:\n", i);
        
        mapDynamicArray_int(&hashes, (ProcessItemFunc)printInt);
        putchar('\n');

        mapDynamicArray(&sineArray, (ProcessItemFunc)printDouble);
        putchar('\n');

        mapDynamicArray_string(&strings, (ProcessItemFunc)printString);
        putchar('\n');
    }

    puts("----- clean -----");
    for (int i = 0; !isEmptyDynamicArray_int(&hashes); ++i) {
        popBackDynamicArray_int(&hashes);
        popBackDynamicArray_string(&strings);

        printf("iter %d:\n", i);

        mapDynamicArray_int(&hashes, (ProcessItemFunc)printInt);
        putchar('\n');

        mapDynamicArray_string(&strings, (ProcessItemFunc)printString);
        putchar('\n');
    }

    mapDynamicArray(&sineArray, (ProcessItemFunc)printDouble);
    putchar('\n');

    termDynamicArray_int(&hashes);
    termDynamicArray(&sineArray);
    termDynamicArray_string(&strings);

    return 0;
}

int hash(const char *str) {
    int res = 1;
    for (; *str; ++str)
        res += *str * res;
    return res;
}

void printInt(int *value) { printf("%d ", *value); }
void printDouble(double *value) { printf("%lf ", *value); }
void printString(string *value) { printf("\"%s\" ", *value); }