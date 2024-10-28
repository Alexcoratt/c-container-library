#include "default_functions_impl.h"
#include "auxillary_macros.h"

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