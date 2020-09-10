LIBNAME = libdbl.a
CFLAGS = -Wall -O2
LFLAGS = `pkg-config --libs json-c`
INCS   = `pkg-config --cflags json-c` -Iinc -I../../inc

all: ${LIBNAME}

${LIBNAME}: ../../inc/engine.h
	gcc ${CFLAGS} ${INCS} src/db_loader.c -o $@ ${LFLAGS}