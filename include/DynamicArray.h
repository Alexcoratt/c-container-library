#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

// TEST
// ---
#define DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
#define DYNAMIC_ARRAY_VALUE_TYPE int
// ---

#include <stddef.h>
#include <stdbool.h>
#include "auxillary_macros.h"

typedef void (*ProcessItemFunc)(void *);
typedef size_t (*GetMaxSizeFunc)(size_t currentSize);

#define DEFAULT_DYNAMIC_ARRAY DynamicArray

#ifdef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    #define DYNAMIC_ARRAY CONCAT_MACROS(CONCAT_MACROS(DEFAULT_DYNAMIC_ARRAY, _), DYNAMIC_ARRAY_VALUE_TYPE)
#else
    #define DYNAMIC_ARRAY_VALUE_TYPE void
    #define DYNAMIC_ARRAY DEFAULT_DYNAMIC_ARRAY
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

// basic methods
#ifdef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    void DYNAMIC_ARRAY_FUNCTION(init)(DYNAMIC_ARRAY *, size_t size, GetMaxSizeFunc getMaxSize);
#else
    void DYNAMIC_ARRAY_FUNCTION(init)(DYNAMIC_ARRAY *, size_t size, size_t typeSize, GetMaxSizeFunc getMaxSize);
#endif

void DYNAMIC_ARRAY_FUNCTION(term)(DYNAMIC_ARRAY *);

// value access
DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(at)(DYNAMIC_ARRAY *, size_t index);
DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atNoRangeCheck)(DYNAMIC_ARRAY *, size_t index);

const DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atConst)(const DYNAMIC_ARRAY *, size_t index);
const DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atNoRangeCheckConst)(const DYNAMIC_ARRAY *, size_t index);

DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atFront)(DYNAMIC_ARRAY *);
DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atBack)(DYNAMIC_ARRAY *);

const DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atFrontConst)(const DYNAMIC_ARRAY *);
const DYNAMIC_ARRAY_VALUE_TYPE *DYNAMIC_ARRAY_FUNCTION(atBackConst)(const DYNAMIC_ARRAY *);

// getting
size_t DYNAMIC_ARRAY_FUNCTION(getSize)(const DYNAMIC_ARRAY *);
size_t DYNAMIC_ARRAY_FUNCTION(getMaxSize)(const DYNAMIC_ARRAY *);

size_t DYNAMIC_ARRAY_FUNCTION(getByteSize)(const DYNAMIC_ARRAY *);
size_t DYNAMIC_ARRAY_FUNCTION(getMaxByteSize)(const DYNAMIC_ARRAY *);

bool DYNAMIC_ARRAY_FUNCTION(isEmpty)(const DYNAMIC_ARRAY *);

// setting
void DYNAMIC_ARRAY_FUNCTION(resize)(DYNAMIC_ARRAY *, size_t newSize);

void DYNAMIC_ARRAY_FUNCTION(setValue)(DYNAMIC_ARRAY *, size_t index, const DYNAMIC_ARRAY_VALUE_TYPE *value);
void DYNAMIC_ARRAY_FUNCTION(setValueNoRangeCheck)(DYNAMIC_ARRAY *, size_t index, const DYNAMIC_ARRAY_VALUE_TYPE *value);

void DYNAMIC_ARRAY_FUNCTION(setFrontValue)(DYNAMIC_ARRAY *, const DYNAMIC_ARRAY_VALUE_TYPE *value);
void DYNAMIC_ARRAY_FUNCTION(setBackValue)(DYNAMIC_ARRAY *, const DYNAMIC_ARRAY_VALUE_TYPE *value);

void DYNAMIC_ARRAY_FUNCTION(pushBack)(DYNAMIC_ARRAY *, const DYNAMIC_ARRAY_VALUE_TYPE *value);
void DYNAMIC_ARRAY_FUNCTION(popBack)(DYNAMIC_ARRAY *);

// special
void DYNAMIC_ARRAY_FUNCTION(map)(DYNAMIC_ARRAY *, ProcessItemFunc func);

// default implementations
size_t getMaxSizeDefaultImpl(size_t currentSize);

#endif