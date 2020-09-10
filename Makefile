############################################################
#                Only test on CentOS 7                     #
############################################################
LIBNAME=libwafse
OUTDIR=target
#############################################################
CC = gcc
CFLAGS = -Wall -Werror -MD -fPIC -O2 -c

## need link json-c and hyperscan
LFLAGS = `pkg-config --libs   json-c libhs`
INCS =   `pkg-config --cflags json-c libhs` \
		 -Iinc	                            \
		 -Isrc/database/inc                 \
		 -Isrc/hyperscan/inc                \
         -Isrc/transform/inc
#############################################################

SOURCES = src/engine.c                                  \
          src/database/src/db_loader.c                  \
          src/hyperscan/src/hs_wrapper.c                \
          src/transform/src/tf_common.c                 \
          src/transform/src/tf_spaces.c                 \
          src/transform/src/tf_url_decode.c             \
          src/transform/src/tf_html_entities_decode.c   \
          src/transform/src/tf_base64_decode.c          \
          src/transform/src/tf_js_decode.c              \
          src/transform/src/tf_css_decode.c

OBJS=$(SOURCES:%.c=${OUTDIR}/%.o)
#############################################################

all: ${LIBNAME}.a ${LIBNAME}.so

${LIBNAME}.a: ${OBJS}
	@ echo "[AR] $@"
	@ ar crs ${OUTDIR}/$@ $^
	@ ls -lh ${OUTDIR}/$@

${LIBNAME}.so: ${OBJS}
	@ echo "[SO] $@"
	@ ${CC} -shared -o ${OUTDIR}/$@ $^
	@ ls -lh ${OUTDIR}/$@


.PYONY: clean
clean:
	@ rm -rf ${OUTDIR}
	@ echo "ALL Clear !!!"

test:test/test.c
	@ ${CC} ${CFLAGS} ${INCS} $< -o $@ -Ltarget -lwafse

#############################################################
${OUTDIR}/%.o:%.c
	@ mkdir -p $(@D)
	@ echo "[CC] $^"
	@ ${CC} ${CFLAGS} ${INCS} $< -o $@ ${LFLAGS}

