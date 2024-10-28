#include <stdlib.h>

#ifndef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    #include <string.h>
#endif

#include "DynamicArray.h"

// DynamicArray functions
#ifdef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    void DYNAMIC_ARRAY_FUNCTION(init)(DYNAMIC_ARRAY *darr, size_t size, GetMaxSizeFunc getMaxSize) {
        darr->size = size;
        darr->getMaxSize = getMaxSize;

        darr->maxSize = getMaxSize(size);
        darr->values = malloc(DYNAMIC_ARRAY_FUNCTION(getMaxByteSize)(darr));
    }

    #define DYNAMIC_ARRAY_VALUE_TYPE_SIZE(DARR_PTR) sizeof(DYNAMIC_ARRAY_VALUE_TYPE)

#else
    void initDynamicArray(DynamicArray *darr, size_t size, size_t typeSize, GetMaxSizeFunc getMaxSize) {
        darr->size = size;
        darr->typeSize = typeSize;

        darr->getMaxSize = getMaxSize;

        darr->maxSize = getMaxSize(size);
        darr->values = malloc(DYNAMIC_ARRAY_FUNCTION(getMaxByteSize)(darr));
    }

    #define DYNAMIC_ARRAY_VALUE_TYPE_SIZE(DARR_PTR) DARR_PTR->typeSize * sizeof(char)

#endif

size_t DYNAMIC_ARRAY_FUNCTION(getMaxByteSize)(const DYNAMIC_ARRAY *darr) {
    return darr->maxSize * DYNAMIC_ARRAY_VALUE_TYPE_SIZE(darr);
}

size_t DYNAMIC_ARRAY_FUNCTION(getByteSize)(const DYNAMIC_ARRAY *darr) {
    return darr->size * DYNAMIC_ARRAY_VALUE_TYPE_SIZE(darr);
}

void DYNAMIC_ARRAY_FUNCTION(term)(DYNAMIC_ARRAY *darr) {
    free(darr->values);
}

// TODO: send to the end of the file
void DYNAMIC_ARRAY_FUNCTION(map)(DYNAMIC_ARRAY *darr, ProcessItemFunc func) {
    const size_t size = DYNAMIC_ARRAY_FUNCTION(getSize)(darr);
    for (size_t i = 0; i < size; ++i)
        func(DYNAMIC_ARRAY_FUNCTION(atNoRangeCheck)(darr, i));
}

size_t DYNAMIC_ARRAY_FUNCTION(getSize)(const DYNAMIC_ARRAY *darr) {
    return darr->size;
}

size_t DYNAMIC_ARRAY_FUNCTION(getMaxSize)(const DYNAMIC_ARRAY *darr) {
    return darr->maxSize;
}

DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atNoRangeCheck)(DYNAMIC_ARRAY *darr, size_t index) {
#ifdef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    return darr->values + index;
#else
    return (char *)darr->values + index * darr->typeSize;
#endif
}

DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atBack)(DYNAMIC_ARRAY *darr) {
    return DYNAMIC_ARRAY_FUNCTION(at)(darr, darr->size - 1);
}

DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atFront)(DYNAMIC_ARRAY *darr) {
    return DYNAMIC_ARRAY_FUNCTION(at)(darr, 0);
}

DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(at)(DYNAMIC_ARRAY *darr, size_t index) {
    if (index < darr->size)
        return DYNAMIC_ARRAY_FUNCTION(atNoRangeCheck)(darr, index);
    return NO_VALUE;
}

const DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atBackConst)(const DYNAMIC_ARRAY *darr) {
    return DYNAMIC_ARRAY_FUNCTION(atConst)(darr, darr->size - 1);
}

const DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atFrontConst)(const DYNAMIC_ARRAY *darr) {
    return DYNAMIC_ARRAY_FUNCTION(atConst)(darr, 0);
}

const DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atConst)(const DYNAMIC_ARRAY *darr, size_t index) {
    if (index < darr->size)
        return DYNAMIC_ARRAY_FUNCTION(atNoRangeCheckConst)(darr, index);
    return NO_VALUE;
}

const DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atNoRangeCheckConst)(const DYNAMIC_ARRAY *darr, size_t index) {
#ifdef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    return darr->values + index;
#else
    return (const char *)darr->values + index * darr->typeSize;
#endif
}

bool DYNAMIC_ARRAY_FUNCTION(isEmpty)(const DYNAMIC_ARRAY *darr) {
    return darr->size == 0;
}

void DYNAMIC_ARRAY_FUNCTION(setValue)(DYNAMIC_ARRAY *darr, size_t index, const DYNAMIC_ARRAY_VALUE_TYPE *value) {
    if (index < darr->size)
        DYNAMIC_ARRAY_FUNCTION(setValueNoRangeCheck)(darr, index, value);
}

void DYNAMIC_ARRAY_FUNCTION(setValueNoRangeCheck)(DYNAMIC_ARRAY *darr, size_t index, const DYNAMIC_ARRAY_VALUE_TYPE *value) {
#ifdef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    *DYNAMIC_ARRAY_FUNCTION(atNoRangeCheck)(darr, index) = *value;
#else
    memcpy(
        DYNAMIC_ARRAY_FUNCTION(atNoRangeCheck)(darr, index),
        value,
        darr->typeSize
    );
#endif
}

void DYNAMIC_ARRAY_FUNCTION(popBack)(DYNAMIC_ARRAY *darr) {
    if (!DYNAMIC_ARRAY_FUNCTION(isEmpty)(darr))
        DYNAMIC_ARRAY_FUNCTION(resize)(darr, darr->size - 1);
}

void DYNAMIC_ARRAY_FUNCTION(pushBack)(DYNAMIC_ARRAY *darr, const DYNAMIC_ARRAY_VALUE_TYPE *value) {
    DYNAMIC_ARRAY_FUNCTION(resize)(darr, darr->size + 1);
    DYNAMIC_ARRAY_FUNCTION(setBackValue)(darr, value);
}

void DYNAMIC_ARRAY_FUNCTION(resize)(DYNAMIC_ARRAY *darr, size_t newSize) {
    darr->size = newSize;
    if (newSize > darr->maxSize) {
        darr->maxSize = darr->getMaxSize(newSize);
        darr->values = realloc(darr->values, DYNAMIC_ARRAY_FUNCTION(getMaxByteSize)(darr));
    }
}

void DYNAMIC_ARRAY_FUNCTION(setBackValue)(DYNAMIC_ARRAY *darr, const DYNAMIC_ARRAY_VALUE_TYPE *value) {
    if (!DYNAMIC_ARRAY_FUNCTION(isEmpty)(darr))
        DYNAMIC_ARRAY_FUNCTION(setValueNoRangeCheck)(darr, darr->size - 1, value);
}

void DYNAMIC_ARRAY_FUNCTION(setFrontValue)(DYNAMIC_ARRAY *darr, const DYNAMIC_ARRAY_VALUE_TYPE *value) {
    if (!DYNAMIC_ARRAY_FUNCTION(isEmpty)(darr))
        DYNAMIC_ARRAY_FUNCTION(setValueNoRangeCheck)(darr, 0, value);
}