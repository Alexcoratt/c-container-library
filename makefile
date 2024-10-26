PROJECT_NAME=ctc

CC?=clang
CFLAGS+=-Wall -std=c11 -Iinclude

BUILD_DIR?=build
SOURCE_DIR?=src

# basic targets
tests: DynamicArray_demo

mkBuildDir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi

# objects
DynamicArray: mkBuildDir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/DynamicArray.o ${SOURCE_DIR}/DynamicArray.c

# tests
DynamicArray_demo: DynamicArray
	${CC} ${CFLAGS} -o ${BUILD_DIR}/DynamicArray_demo ${SOURCE_DIR}/DynamicArray_demo.c -lm ${BUILD_DIR}/DynamicArray.o