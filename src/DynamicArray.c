#include <stdlib.h>
#include <string.h>

#include "DynamicArray.h"

// DynamicArray functions
void initDynamicArray(DynamicArray *darr, size_t size, size_t typeSize, GetMaxSizeFunc getMaxSize) {
    darr->size = size;
    darr->typeSize = typeSize;

    darr->getMaxSize = getMaxSize;

    darr->maxSize = getMaxSize(size);
    darr->values = malloc(getMaxByteSizeDynamicArray(darr));
}

size_t getMaxByteSizeDynamicArray(const DynamicArray *darr) {
    return darr->maxSize * darr->typeSize * sizeof(char);
}

size_t getByteSizeDynamicArray(const DynamicArray *darr) {
    return darr->size * darr->typeSize * sizeof(char);
}

void termDynamicArray(DynamicArray *darr) {
    free(darr->values);
}

void mapDynamicArray(DynamicArray *darr, ProcessItemFunc func) {
    const size_t size = getSizeDynamicArray(darr);
    for (size_t i = 0; i < size; ++i)
        func(atNoRangeCheckDynamicArray(darr, i));
}

size_t getSizeDynamicArray(const DynamicArray *darr) {
    return darr->size;
}

size_t getMaxSizeDynamicArray(const DynamicArray *darr) {
    return darr->maxSize;
}

void *atNoRangeCheckDynamicArray(DynamicArray *darr, size_t index) {
    return ((char *)darr->values) + index * darr->typeSize;
}

void *atBackDynamicArray(DynamicArray *darr) {
    return atDynamicArray(darr, darr->size - 1);
}

void *atFrontDynamicArray(DynamicArray *darr) {
    return atDynamicArray(darr, 0);
}

void *atDynamicArray(DynamicArray *darr, size_t index) {
    if (index < darr->size)
        return atNoRangeCheckDynamicArray(darr, index);
    return NO_VALUE;
}

const void *atBackConstDynamicArray(const DynamicArray *darr) {
    return atConstDynamicArray(darr, darr->size - 1);
}

const void *atFrontConstDynamicArray(const DynamicArray *darr) {
    return atConstDynamicArray(darr, 0);
}

const void *atConstDynamicArray(const DynamicArray *darr, size_t index) {
    if (index < darr->size)
        return atNoRangeCheckConstDynamicArray(darr, index);
    return NO_VALUE;
}

const void *atNoRangeCheckConstDynamicArray(const DynamicArray *darr, size_t index) {
    return ((const char *)darr->values) + index * darr->typeSize;
}

bool isEmptyDynamicArray(const DynamicArray *darr) {
    return darr->size == 0;
}

void setValueDynamicArray(DynamicArray *darr, size_t index, const void *value) {
    if (index < darr->size)
        setValueNoRangeCheckDynamicArray(darr, index, value);
}

void setValueNoRangeCheckDynamicArray(DynamicArray *darr, size_t index, const void *value) {
    memcpy(
        atNoRangeCheckDynamicArray(darr, index),
        value,
        darr->typeSize
    );
}

void popBackDynamicArray(DynamicArray *darr) {
    if (!isEmptyDynamicArray(darr))
        resizeDynamicArray(darr, darr->size - 1);
}

void pushBackDynamicArray(DynamicArray *darr, const void *value) {
    resizeDynamicArray(darr, darr->size + 1);
    setBackValueDynamicArray(darr, value);
}

void resizeDynamicArray(DynamicArray *darr, size_t newSize) {
    darr->size = newSize;
    if (newSize > darr->maxSize) {
        darr->maxSize = darr->getMaxSize(newSize);
        darr->values = realloc(darr->values, getMaxByteSizeDynamicArray(darr));
    }
}

void setBackValueDynamicArray(DynamicArray *darr, const void *value) {
    if (!isEmptyDynamicArray(darr))
        setValueNoRangeCheckDynamicArray(darr, darr->size - 1, value);
}

void setFrontValueDynamicArray(DynamicArray *darr, const void *value) {
    if (!isEmptyDynamicArray(darr))
        setValueNoRangeCheckDynamicArray(darr, 0, value);
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