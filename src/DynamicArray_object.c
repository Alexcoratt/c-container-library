#include "DynamicArray_object.h"

struct DYNAMIC_ARRAY_OBJECT_METHODS CONCAT_MACROS(methods_, DYNAMIC_ARRAY) = {
    DYNAMIC_ARRAY_FUNCTION(term),
    DYNAMIC_ARRAY_FUNCTION(at),
    DYNAMIC_ARRAY_FUNCTION(atNoRangeCheck),
    DYNAMIC_ARRAY_FUNCTION(atConst),
    DYNAMIC_ARRAY_FUNCTION(atNoRangeCheckConst),
    DYNAMIC_ARRAY_FUNCTION(atFront),
    DYNAMIC_ARRAY_FUNCTION(atBack),
    DYNAMIC_ARRAY_FUNCTION(atFrontConst),
    DYNAMIC_ARRAY_FUNCTION(atBackConst),
    DYNAMIC_ARRAY_FUNCTION(getSize),
    DYNAMIC_ARRAY_FUNCTION(getMaxSize),
    DYNAMIC_ARRAY_FUNCTION(getByteSize),
    DYNAMIC_ARRAY_FUNCTION(getMaxByteSize),
    DYNAMIC_ARRAY_FUNCTION(isEmpty),
    DYNAMIC_ARRAY_FUNCTION(resize),
    DYNAMIC_ARRAY_FUNCTION(setValue),
    DYNAMIC_ARRAY_FUNCTION(setValueNoRangeCheck),
    DYNAMIC_ARRAY_FUNCTION(setFrontValue),
    DYNAMIC_ARRAY_FUNCTION(setBackValue),
    DYNAMIC_ARRAY_FUNCTION(pushBack),
    DYNAMIC_ARRAY_FUNCTION(popBack),
    DYNAMIC_ARRAY_FUNCTION(map),
};

#ifdef DYNAMIC_ARRAY_USER_DEFINED_VALUE_TYPE
    void CONCAT_MACROS(init, DYNAMIC_ARRAY_OBJECT)(DYNAMIC_ARRAY_OBJECT *obj, size_t size, GetMaxSizeFunc getMaxSize) {
        DYNAMIC_ARRAY_FUNCTION(init)(&obj->darr, size, getMaxSize);
        obj->methods = &CONCAT_MACROS(methods_, DYNAMIC_ARRAY);
    }
#else
    void CONCAT_MACROS(init, DYNAMIC_ARRAY_OBJECT)(DYNAMIC_ARRAY_OBJECT *obj, size_t size, size_t typeSize, GetMaxSizeFunc getMaxSize) {
        DYNAMIC_ARRAY_FUNCTION(init)(&obj->darr, size, typeSize, getMaxSize);
        obj->methods = &CONCAT_MACROS(methods_, DYNAMIC_ARRAY);
    }
#endif