OUTDIR = objs

TOPDIR = ../..

CFLAGS += -c -pipe -O0 -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g
LFLAGS = -ldl -pthread -lssl -lcrypto -lz -lpcre

INCS += \
  -I ${TOPDIR}/conf            \
  -I ${TOPDIR}/core            \
  -I ${TOPDIR}/event           \
  -I ${TOPDIR}/event/modules   \
  -I ${TOPDIR}/os/unix



# os part
SOURCES +=                                        \
    ${TOPDIR}/os/unix/ngx_time.c                  \
    ${TOPDIR}/os/unix/ngx_errno.c                 \
    ${TOPDIR}/os/unix/ngx_alloc.c                 \
    ${TOPDIR}/os/unix/ngx_files.c                 \
    ${TOPDIR}/os/unix/ngx_socket.c

# core part
SOURCES +=                               \
    ${TOPDIR}/core/ngx_times.c           \
    ${TOPDIR}/core/ngx_log.c             \
    ${TOPDIR}/core/ngx_palloc.c          \
    ${TOPDIR}/core/ngx_array.c           \
    ${TOPDIR}/core/ngx_list.c            \
    ${TOPDIR}/core/ngx_hash.c            \
    ${TOPDIR}/core/ngx_rbtree.c          \
    ${TOPDIR}/core/ngx_crc32.c           \
    ${TOPDIR}/core/ngx_buf.c             \
    ${TOPDIR}/core/ngx_queue.c           \
    ${TOPDIR}/core/ngx_string.c          \
    ${TOPDIR}/core/ngx_parse.c           \
    ${TOPDIR}/core/ngx_conf_file.c

OBJS=$(SOURCES:%.c=${OUTDIR}/test/objs/%.o)
#############################################################
.DEFAULT_GOAL := all
.PHONY: all clean

all: ${OUTDIR}/${TARGET}

${OUTDIR}/${TARGET} : ${OBJS}
	@ echo "[LINK] ${TARGET} ..."
	@ ${CC} -o $@ $^ ${LFLAGS}
	@ ls -lh ${OUTDIR}/${TARGET}

clean:
	@ rm -rf ${OUTDIR}
	@ echo "ALL Clear !!!"

#############################################################
${OUTDIR}/test/objs/%.o:%.c
	@ mkdir -p $(@D)
	@ echo "[CC]   $^"
	@ ${CC} ${CFLAGS} ${DFLAGS} ${INCS} $< -o $@
