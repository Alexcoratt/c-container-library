PROJECT_NAME=ctc

CC?=clang
CFLAGS+=-Wall -std=c11

BUILD_DIR?=build
SOURCE_DIR?=src

# basic targets
main: mkBuildDir
	${CC} ${CFLAGS} -o ${BUILD_DIR}/${PROJECT_NAME} ${SOURCE_DIR}/main.c

mkBuildDir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi