PROJECT_NAME=ctc

CC?=clang
CFLAGS+=-Wall -std=c11 -Iinclude

BUILD_DIR?=build
SOURCE_DIR?=src

# basic targets
tests: DynamicArray_demo

mkBuildDir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi

clean:
	rm -f ${BUILD_DIR}/*.o

# objects
DynamicArray_default: mkBuildDir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/DynamicArray_default.o ${SOURCE_DIR}/DynamicArray.c

# tests
DynamicArray_demo: DynamicArray_default_demo DynamicArray_string_demo DynamicArray_double_demo

DynamicArray_string_demo: mkBuildDir
	${CC} ${CFLAGS} -c -include include/type_definitions.h -DDYNAMIC_ARRAY_VALUE_TYPE=string -o ${BUILD_DIR}/DynamicArray_string.o ${SOURCE_DIR}/DynamicArray.c
	${CC} ${CFLAGS} -o ${BUILD_DIR}/DynamicArray_string_demo ${SOURCE_DIR}/DynamicArray_string_demo.c -lm ${BUILD_DIR}/DynamicArray_string.o

DynamicArray_double_demo: mkBuildDir
	${CC} ${CFLAGS} -c -DDYNAMIC_ARRAY_VALUE_TYPE=double -o ${BUILD_DIR}/DynamicArray_double.o ${SOURCE_DIR}/DynamicArray.c
	${CC} ${CFLAGS} -o ${BUILD_DIR}/DynamicArray_double_demo ${SOURCE_DIR}/DynamicArray_double_demo.c -lm ${BUILD_DIR}/DynamicArray_double.o

DynamicArray_default_demo: DynamicArray_default
	${CC} ${CFLAGS} -o ${BUILD_DIR}/DynamicArray_default_demo ${SOURCE_DIR}/DynamicArray_default_demo.c -lm ${BUILD_DIR}/DynamicArray_default.o