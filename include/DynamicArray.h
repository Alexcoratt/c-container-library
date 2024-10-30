#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>
#include <stdbool.h>
#include "auxillary_macros.h"

typedef size_t (*GetMaxSizeFunc)(size_t currentSize);

#define DYNAMIC_ARRAY_DEFAULT_NAME DynamicArray

#ifdef DYNAMIC_ARRAY_VALUE_TYPE
    #define DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
#endif

#ifdef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    #define DYNAMIC_ARRAY CONCAT_MACROS(CONCAT_MACROS(DYNAMIC_ARRAY_DEFAULT_NAME, _), DYNAMIC_ARRAY_VALUE_TYPE)
#else
    #define DYNAMIC_ARRAY_VALUE_TYPE void
    #define DYNAMIC_ARRAY DYNAMIC_ARRAY_DEFAULT_NAME
#endif

typedef struct {
    size_t size;
    size_t maxSize;
    DYNAMIC_ARRAY_VALUE_TYPE *values;

    GetMaxSizeFunc getMaxSize;

#ifndef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    size_t typeSize;
#endif
} DYNAMIC_ARRAY;

#define DYNAMIC_ARRAY_FUNCTION(FUNC) CONCAT_MACROS(FUNC, DYNAMIC_ARRAY)

#define DYNAMIC_ARRAY_METHOD(RETURN_TYPE, NAME, ...) DEFINE_METHOD(DYNAMIC_ARRAY *darr, RETURN_TYPE, DYNAMIC_ARRAY_FUNCTION(NAME), ##__VA_ARGS__)
#define DYNAMIC_ARRAY_CONST_METHOD(RETURN_TYPE, NAME, ...) DEFINE_METHOD(const DYNAMIC_ARRAY *darr, RETURN_TYPE, DYNAMIC_ARRAY_FUNCTION(NAME), ##__VA_ARGS__)

// basic methods
#ifdef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    DYNAMIC_ARRAY_METHOD(void, init, size_t size, GetMaxSizeFunc getMaxSize);
#else
    DYNAMIC_ARRAY_METHOD(void, init, size_t size, size_t typeSize, GetMaxSizeFunc getMaxSize);
#endif

DYNAMIC_ARRAY_METHOD(void, term);

// value access
DYNAMIC_ARRAY_METHOD(DYNAMIC_ARRAY_VALUE_TYPE *, at, size_t index);
DYNAMIC_ARRAY_METHOD(DYNAMIC_ARRAY_VALUE_TYPE *, atNoRangeCheck, size_t index);

DYNAMIC_ARRAY_CONST_METHOD(const DYNAMIC_ARRAY_VALUE_TYPE *, atConst, size_t index);
DYNAMIC_ARRAY_CONST_METHOD(const DYNAMIC_ARRAY_VALUE_TYPE *, atNoRangeCheckConst, size_t index);

DYNAMIC_ARRAY_METHOD(DYNAMIC_ARRAY_VALUE_TYPE *, atFront);
DYNAMIC_ARRAY_METHOD(DYNAMIC_ARRAY_VALUE_TYPE *, atBack);

DYNAMIC_ARRAY_CONST_METHOD(const DYNAMIC_ARRAY_VALUE_TYPE *, atFrontConst);
DYNAMIC_ARRAY_CONST_METHOD(const DYNAMIC_ARRAY_VALUE_TYPE *, atBackConst);

// getting
DYNAMIC_ARRAY_CONST_METHOD(size_t, getSize);
DYNAMIC_ARRAY_CONST_METHOD(size_t, getMaxSize);

DYNAMIC_ARRAY_CONST_METHOD(size_t, getByteSize);
DYNAMIC_ARRAY_CONST_METHOD(size_t, getMaxByteSize);

DYNAMIC_ARRAY_CONST_METHOD(bool, isEmpty);

// setting
DYNAMIC_ARRAY_METHOD(void, resize, size_t newSize);

DYNAMIC_ARRAY_METHOD(void, setValue, size_t index, const DYNAMIC_ARRAY_VALUE_TYPE *value);
DYNAMIC_ARRAY_METHOD(void, setValueNoRangeCheck, size_t index, const DYNAMIC_ARRAY_VALUE_TYPE *value);

DYNAMIC_ARRAY_METHOD(void, setFrontValue, const DYNAMIC_ARRAY_VALUE_TYPE *value);
DYNAMIC_ARRAY_METHOD(void, setBackValue, const DYNAMIC_ARRAY_VALUE_TYPE *value);

DYNAMIC_ARRAY_METHOD(void, pushBack, const DYNAMIC_ARRAY_VALUE_TYPE *value);
DYNAMIC_ARRAY_METHOD(void, popBack);

// special
DYNAMIC_ARRAY_METHOD(void, map, void (*func)(DYNAMIC_ARRAY_VALUE_TYPE *));

#endif