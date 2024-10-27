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
void *atDynamicArrayNoRangeCheck(DynamicArray *, size_t index);

const void *atConstDynamicArray(const DynamicArray *, size_t index);
const void *atConstDynamicArrayNoRangeCheck(const DynamicArray *, size_t index);

void *getDynamicArrayFront(DynamicArray *);
void *getDynamicArrayBack(DynamicArray *);

const void *getConstDynamicArrayFront(const DynamicArray *);
const void *getConstDynamicArrayBack(const DynamicArray *);

// getting
size_t getDynamicArraySize(const DynamicArray *);
size_t getDynamicArrayMaxSize(const DynamicArray *);

size_t getDynamicArrayByteSize(const DynamicArray *);
size_t getDynamicArrayMaxByteSize(const DynamicArray *);

bool isDynamicArrayEmpty(const DynamicArray *);

// setting
void resizeDynamicArray(DynamicArray *, size_t newSize);

void setDynamicArrayValue(DynamicArray *, size_t index, const void *value);
void setDynamicArrayValueNoRangeCheck(DynamicArray *, size_t index, const void *value);

void setDynamicArrayFrontValue(DynamicArray *, const void *value);
void setDynamicArrayBackValue(DynamicArray *, const void *value);

void pushBackDynamicArray(DynamicArray *, const void *value);
void popBackDynamicArray(DynamicArray *);

// special
void mapDynamicArray(DynamicArray *, ProcessItemFunc func);

// default implementations
size_t getMaxSizeDefaultImpl(size_t currentSize);

#endif