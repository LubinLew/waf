TOPDIR = ../..
TARGET = ngx_array_test

CC = cc
CFLAGS = -c -pipe -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g -MD
LFLAGS = -ldl -pthread
DFLAGS = 

INCS = \
   -I ${TOPDIR}/conf            \
   -I ${TOPDIR}/core            \
   -I ${TOPDIR}/event           \
   -I ${TOPDIR}/event/modules   \
   -I ${TOPDIR}/os/unix

DEPS = \
  ngx_alloc.o      \
  ngx_palloc.o     \
  ngx_array.o      \
  ngx_array_test.o

all : ${TARGET}

clean:
	@ rm -f *.o ${TARGET}


${TARGET} : ${DEPS}
	${CC} ${INCS} -o $@ $^

ngx_array_test.o : ngx_array_test.c
#	${CC} -E -P ${INCS} $< > ngx_array_test.i
	${CC} ${CFLAGS} ${INCS} -o $@ $<

ngx_alloc.o : ${TOPDIR}/os/unix/ngx_alloc.c
	${CC} ${CFLAGS} ${INCS} -o $@ $<

ngx_palloc.o : ${TOPDIR}/core/ngx_palloc.c
	${CC} ${CFLAGS} ${INCS} -o $@ $<

ngx_array.o :${TOPDIR}/core/ngx_array.c
	${CC} ${CFLAGS} ${INCS} -o $@ $<