PROJECT_NAME=ctc

CC?=clang
CFLAGS+=-Wall -std=c11 -Iinclude

BUILD_DIR?=build
SOURCE_DIR?=src

# basic targets
tests: dynarray_demo

mkBuildDir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi

# tests
dynarray_demo: mkBuildDir
	${CC} ${CFLAGS} -o ${BUILD_DIR}/dynarray_demo ${SOURCE_DIR}/dynarray_demo.c