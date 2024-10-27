#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>
#include <stdbool.h>

#define NO_VALUE NULL

typedef void (*ProcessItemFunc)(void *);
typedef size_t (*GetMaxSizeFunc)(size_t currentSize);

typedef struct {
    size_t size;
    size_t maxSize;
    void *values;

    size_t typeSize;

    GetMaxSizeFunc getMaxSize;
} DynamicArray;

// basic methods
void initDynamicArray(DynamicArray *, size_t size, size_t typeSize, GetMaxSizeFunc getMaxSize);
void termDynamicArray(DynamicArray *);

// value access
void *atDynamicArray(DynamicArray *, size_t index);
void *atNoRangeCheckDynamicArray(DynamicArray *, size_t index);

const void *atConstDynamicArray(const DynamicArray *, size_t index);
const void *atNoRangeCheckConstDynamicArray(const DynamicArray *, size_t index);

void *atFrontDynamicArray(DynamicArray *);
void *atBackDynamicArray(DynamicArray *);

const void *atFrontConstDynamicArray(const DynamicArray *);
const void *atBackConstDynamicArray(const DynamicArray *);

// getting
size_t getSizeDynamicArray(const DynamicArray *);
size_t getMaxSizeDynamicArray(const DynamicArray *);

size_t getByteSizeDynamicArray(const DynamicArray *);
size_t getMaxByteSizeDynamicArray(const DynamicArray *);

bool isEmptyDynamicArray(const DynamicArray *);

// setting
void resizeDynamicArray(DynamicArray *, size_t newSize);

void setValueDynamicArray(DynamicArray *, size_t index, const void *value);
void setValueNoRangeCheckDynamicArray(DynamicArray *, size_t index, const void *value);

void setDynamicArrayFrontValue(DynamicArray *, const void *value);
void setBackValueDynamicArray(DynamicArray *, const void *value);

void pushBackDynamicArray(DynamicArray *, const void *value);
void popBackDynamicArray(DynamicArray *);

// special
void mapDynamicArray(DynamicArray *, ProcessItemFunc func);

// default implementations
size_t getMaxSizeDefaultImpl(size_t currentSize);

#endif