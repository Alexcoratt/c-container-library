#include <stdbool.h>
#include <stdlib.h>

#ifndef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    #include <string.h>
#endif

#include "DynamicArray.h"

typedef DYNAMIC_ARRAY_VALUE_TYPE value_t;

// DynamicArray functions
#ifdef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    DYNAMIC_ARRAY_METHOD(void, init, size_t size, GetMaxSizeFunc getMaxSize) {
        darr->size = size;
        darr->getMaxSize = getMaxSize;

        darr->maxSize = getMaxSize(size);
        darr->values = malloc(DYNAMIC_ARRAY_FUNCTION(getMaxByteSize)(darr));
    }

    #define VALUE_TYPE_SIZE(DARR_PTR) sizeof(value_t)

#else
    DYNAMIC_ARRAY_METHOD(void, init, size_t size, size_t typeSize, GetMaxSizeFunc getMaxSize) {
        darr->size = size;
        darr->typeSize = typeSize;

        darr->getMaxSize = getMaxSize;

        darr->maxSize = getMaxSize(size);
        darr->values = malloc(DYNAMIC_ARRAY_FUNCTION(getMaxByteSize)(darr));
    }

    #define VALUE_TYPE_SIZE(DARR_PTR) DARR_PTR->typeSize * sizeof(char)

#endif

DYNAMIC_ARRAY_CONST_METHOD(size_t, getMaxByteSize) {
    return darr->maxSize * VALUE_TYPE_SIZE(darr);
}

DYNAMIC_ARRAY_CONST_METHOD(size_t, getByteSize) {
    return darr->size * VALUE_TYPE_SIZE(darr);
}

DYNAMIC_ARRAY_METHOD(void, term) { free(darr->values); }

// TODO: send to the end of the file
void DYNAMIC_ARRAY_FUNCTION(map)(DYNAMIC_ARRAY *darr, void (*func)(value_t *)) {
    const size_t size = DYNAMIC_ARRAY_FUNCTION(getSize)(darr);
    for (size_t i = 0; i < size; ++i)
        func(DYNAMIC_ARRAY_FUNCTION(atNoRangeCheck)(darr, i));
}

DYNAMIC_ARRAY_CONST_METHOD(size_t, getSize) { return darr->size; }
DYNAMIC_ARRAY_CONST_METHOD(size_t, getMaxSize) { return darr->maxSize; }

DYNAMIC_ARRAY_METHOD(value_t *, atNoRangeCheck, size_t index) {
#ifdef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    return darr->values + index;
#else
    return (char *)darr->values + index * darr->typeSize;
#endif
}

DYNAMIC_ARRAY_METHOD(value_t *, atBack) {
    return DYNAMIC_ARRAY_FUNCTION(at)(darr, darr->size - 1);
}

DYNAMIC_ARRAY_METHOD(value_t *, atFront) {
    return DYNAMIC_ARRAY_FUNCTION(at)(darr, 0);
}

DYNAMIC_ARRAY_METHOD(value_t *, at, size_t index) {
    if (index < darr->size)
        return DYNAMIC_ARRAY_FUNCTION(atNoRangeCheck)(darr, index);
    return NO_VALUE;
}

DYNAMIC_ARRAY_CONST_METHOD(const value_t *, atBackConst) {
    return DYNAMIC_ARRAY_FUNCTION(atConst)(darr, darr->size - 1);
}

DYNAMIC_ARRAY_CONST_METHOD(const value_t *, atFrontConst) {
    return DYNAMIC_ARRAY_FUNCTION(atConst)(darr, 0);
}

DYNAMIC_ARRAY_CONST_METHOD(const value_t *, atConst, size_t index) {
    if (index < darr->size)
        return DYNAMIC_ARRAY_FUNCTION(atNoRangeCheckConst)(darr, index);
    return NO_VALUE;
}

DYNAMIC_ARRAY_CONST_METHOD(const value_t *, atNoRangeCheckConst, size_t index) {
#ifdef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    return darr->values + index;
#else
    return (const char *)darr->values + index * darr->typeSize;
#endif
}

DYNAMIC_ARRAY_CONST_METHOD(bool, isEmpty) {
    return darr->size == 0;
}

DYNAMIC_ARRAY_METHOD(void, setValue, size_t index, const value_t *value) {
    if (index < darr->size)
        DYNAMIC_ARRAY_FUNCTION(setValueNoRangeCheck)(darr, index, value);
}

DYNAMIC_ARRAY_METHOD(void, setValueNoRangeCheck, size_t index, const value_t *value) {
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

DYNAMIC_ARRAY_METHOD(void, popBack) {
    if (!DYNAMIC_ARRAY_FUNCTION(isEmpty)(darr))
        DYNAMIC_ARRAY_FUNCTION(resize)(darr, darr->size - 1);
}

DYNAMIC_ARRAY_METHOD(void, pushBack, const value_t *value) {
    DYNAMIC_ARRAY_FUNCTION(resize)(darr, darr->size + 1);
    DYNAMIC_ARRAY_FUNCTION(setBackValue)(darr, value);
}

DYNAMIC_ARRAY_METHOD(void, resize, size_t newSize) {
    darr->size = newSize;
    if (newSize > darr->maxSize) {
        darr->maxSize = darr->getMaxSize(newSize);
        darr->values = realloc(darr->values, DYNAMIC_ARRAY_FUNCTION(getMaxByteSize)(darr));
    }
}

DYNAMIC_ARRAY_METHOD(void, setBackValue, const value_t *value) {
    if (!DYNAMIC_ARRAY_FUNCTION(isEmpty)(darr))
        DYNAMIC_ARRAY_FUNCTION(setValueNoRangeCheck)(darr, darr->size - 1, value);
}

DYNAMIC_ARRAY_METHOD(void, setFrontValue, const value_t *value) {
    if (!DYNAMIC_ARRAY_FUNCTION(isEmpty)(darr))
        DYNAMIC_ARRAY_FUNCTION(setValueNoRangeCheck)(darr, 0, value);
}