#ifndef AUXILLARY_MACROS_H
#define AUXILLARY_MACROS_H

#define NO_VALUE NULL

#define CONCAT(LEFT, RIGHT) LEFT ## RIGHT
#define CONCAT_MACROS(LEFT, RIGHT) CONCAT(LEFT, RIGHT)

#define MAX(A, B) ((A) > (B) ? (A) : (B))

#endif