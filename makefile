PROJECT_NAME=ctc

CC?=clang
CFLAGS+=-Wall -std=c11 -Iinclude

BUILD_DIR?=build
SOURCE_DIR?=src

# basic targets
tests: DynamicArray_demo DynamicArray_default_demo

mkBuildDir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi

clean:
	rm -f ${BUILD_DIR}/*.o

# objects
DynamicArray_default: mkBuildDir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/DynamicArray_default.o ${SOURCE_DIR}/DynamicArray.c

default_functions_impl: mkBuildDir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/default_functions_impl.o ${SOURCE_DIR}/default_functions_impl.c

# tests
DynamicArray_demo: DynamicArray_default default_functions_impl
	${CC} ${CFLAGS} -c -include include/type_definitions.h -DDYNAMIC_ARRAY_VALUE_TYPE=string -o ${BUILD_DIR}/DynamicArray_string.o ${SOURCE_DIR}/DynamicArray.c
	${CC} ${CFLAGS} -c -DDYNAMIC_ARRAY_VALUE_TYPE=int -o ${BUILD_DIR}/DynamicArray_int.o ${SOURCE_DIR}/DynamicArray.c
	${CC} ${CFLAGS} -o ${BUILD_DIR}/DynamicArray_demo ${SOURCE_DIR}/DynamicArray_demo.c ${BUILD_DIR}/DynamicArray_string.o ${BUILD_DIR}/DynamicArray_int.o ${BUILD_DIR}/DynamicArray_default.o ${BUILD_DIR}/default_functions_impl.o -lm

DynamicArray_default_demo: DynamicArray_default
	${CC} ${CFLAGS} -o ${BUILD_DIR}/DynamicArray_default_demo ${SOURCE_DIR}/DynamicArray_default_demo.c ${BUILD_DIR}/DynamicArray_default.o ${BUILD_DIR}/default_functions_impl.o