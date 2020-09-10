############################################################
#                Only test on CentOS 7                     #             
############################################################
LIBNAME=libwafse.a
OUTDIR=target
#############################################################
CC = gcc
CFLAGS = -Wall -MD -O2 -c

## need link json-c and hyperscan
LFLAGS = `pkg-config --libs   json-c libhs`
INCS =   `pkg-config --cflags json-c libhs` \
		 -Iinc	                            \
		 -Isrc/database/inc                 \
		 -Isrc/hyperscan/inc                \
         -Isrc/transform/inc
#############################################################

SOURCES = src/engine.c                              \
          src/database/db_loader.c                  \
          src/hyperscan/hs_wrapper.c                \
          src/transform/tf_common.c                 \
          src/transform/tf_spaces.c                 \
          src/transform/tf_url_decode.c             \
          src/transform/tf_html_entities_decode.c   \
          src/transform/tf_base64_decode.c          \
          src/transform/tf_js_decode.c              \
          src/transform/tf_css_decode.c

OBJS=$(SOURCES:%.c=${OUTDIR}/%.o)
#############################################################

all: ${LIBNAME}

${LIBNAME}: ${OBJS}
	ar crs ${OUTDIR}/$@ $^
	@ls -lh ${OUTDIR}/$@


.PYONY: clean
clean:
	@rm -rf ${OUTDIR}
	@echo "ALL Clear !!!"

test:
	@echo "${OBJS}"
#############################################################
${OUTDIR}/%.o:%.c
	@mkdir -p $(@D)
	@echo "[CC] $^ -o $@"
	@${CC} ${CFLAGS} ${INCS} $< -o $@ ${LFLAGS}
