#include <stdlib.h>
#include <string.h>

#include "DynamicArray.h"

// DynamicArray functions
void initDynamicArray(DynamicArray *darr, size_t size, size_t typeSize, GetMaxSizeFunc getMaxSize) {
    darr->size = size;
    darr->typeSize = typeSize;

    darr->getMaxSize = getMaxSize;

    darr->maxSize = getMaxSize(size);
    darr->values = malloc(getDynamicArrayMaxByteSize(darr));
}

size_t getDynamicArrayMaxByteSize(const DynamicArray *darr) {
    return darr->maxSize * darr->typeSize * sizeof(char);
}

size_t getDynamicArrayByteSize(const DynamicArray *darr) {
    return darr->size * darr->typeSize * sizeof(char);
}

void termDynamicArray(DynamicArray *darr) {
    free(darr->values);
}

void mapDynamicArray(DynamicArray *darr, ProcessItemFunc func) {
    const size_t size = getDynamicArraySize(darr);
    for (size_t i = 0; i < size; ++i)
        func(atDynamicArrayNoRangeCheck(darr, i));
}

size_t getDynamicArraySize(const DynamicArray *darr) {
    return darr->size;
}

size_t getDynamicArrayMaxSize(const DynamicArray *darr) {
    return darr->maxSize;
}

void *atDynamicArrayNoRangeCheck(DynamicArray *darr, size_t index) {
    return ((char *)darr->values) + index * darr->typeSize;
}

void *getDynamicArrayBack(DynamicArray *darr) {
    return atDynamicArray(darr, darr->size - 1);
}

void *getDynamicArrayFront(DynamicArray *darr) {
    return atDynamicArray(darr, 0);
}

void *atDynamicArray(DynamicArray *darr, size_t index) {
    if (index < darr->size)
        return atDynamicArrayNoRangeCheck(darr, index);
    return NO_VALUE;
}

const void *getDynamicArrayConstBack(const DynamicArray *darr) {
    return atConstDynamicArray(darr, darr->size - 1);
}

const void *getDynamicArrayConstFront(const DynamicArray *darr) {
    return atConstDynamicArray(darr, 0);
}

const void *atConstDynamicArray(const DynamicArray *darr, size_t index) {
    if (index < darr->size)
        return atConstDynamicArrayNoRangeCheck(darr, index);
    return NO_VALUE;
}

const void *atConstDynamicArrayNoRangeCheck(const DynamicArray *darr, size_t index) {
    return ((const char *)darr->values) + index * darr->typeSize;
}

bool isDynamicArrayEmpty(const DynamicArray *darr) {
    return darr->size == 0;
}

void setDynamicArrayValue(DynamicArray *darr, size_t index, const void *value) {
    if (index < darr->size)
        setDynamicArrayValueNoRangeCheck(darr, index, value);
}

void setDynamicArrayValueNoRangeCheck(DynamicArray *darr, size_t index, const void *value) {
    memcpy(
        atDynamicArrayNoRangeCheck(darr, index),
        value,
        darr->typeSize
    );
}

void popBackDynamicArray(DynamicArray *darr) {
    if (!isDynamicArrayEmpty(darr))
        resizeDynamicArray(darr, darr->size - 1);
}

void pushBackDynamicArray(DynamicArray *darr, const void *value) {
    resizeDynamicArray(darr, darr->size + 1);
    setDynamicArrayBackValue(darr, value);
}

void resizeDynamicArray(DynamicArray *darr, size_t newSize) {
    darr->size = newSize;
    if (newSize > darr->maxSize) {
        darr->maxSize = darr->getMaxSize(newSize);
        darr->values = realloc(darr->values, getDynamicArrayMaxByteSize(darr));
    }
}

void setDynamicArrayBackValue(DynamicArray *darr, const void *value) {
    if (!isDynamicArrayEmpty(darr))
        setDynamicArrayValueNoRangeCheck(darr, darr->size - 1, value);
}

void setDynamicArrayFrontValue(DynamicArray *darr, const void *value) {
    if (!isDynamicArrayEmpty(darr))
        setDynamicArrayValueNoRangeCheck(darr, 0, value);
}

// default implementations
#define MAX(A, B) ((A) > (B) ? (A) : (B))

#ifndef DYN_ARRAY_MAX_SIZE_RATIO
    #define DYN_ARRAY_MAX_SIZE_RATIO 1.5F
#endif

#ifndef DYN_ARRAY_MIN_SIZE
    #define DYN_ARRAY_MIN_SIZE 4LU
#endif

size_t getMaxSizeDefaultImpl(size_t currentSize) {
    size_t res = currentSize * DYN_ARRAY_MAX_SIZE_RATIO;
    return MAX(res, DYN_ARRAY_MIN_SIZE);
}