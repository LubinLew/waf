LIBNAME = libtf.a
OBJDIR = target/src
CC = gcc
CFLAGS = -g -Wall -c
DMACRO := 
LFLAGS = 
INCS = -Iinc

ifeq ($(DEBUG),1)
	DMACRO += -D__DEBUG -D__TF_TEST
endif

#############################################################

SRCLIST = src/tf_common.c                 \
          src/tf_spaces.c                 \
          src/tf_url_decode.c             \
          src/tf_html_entities_decode.c   \
          src/tf_base64_decode.c          \
          src/tf_js_decode.c
	
	
	
#############################################################
.PYONY: all clean

all:targetdir build
	@ls -lh target/${LIBNAME}

targetdir:
	mkdir -p ${OBJDIR}
	
build:$(SRCLIST:%.c=target/%.o)
	ar crs target/${LIBNAME} $^
	
clean:
	rm -rf target

#############################################################
test_macro:targetdir


url_test:src/tf_url_decode.c ${OBJDIR}/tf_common.o
	${CC} ${CFLAGS} -D__DEBUG -D__TF_URL_TEST $<
	${CC} tf_url_decode.o ${OBJDIR}/tf_common.o -o $@

space_test:src/tf_spaces.c ${OBJDIR}/tf_common.o
	${CC} ${CFLAGS} -D__DEBUG -D__TF_SPACE_TEST $<
	${CC} tf_spaces.o ${OBJDIR}/tf_common.o -o $@

entity_test:src/tf_html_entities_decode.c ${OBJDIR}/tf_common.o 
	${CC} ${CFLAGS} -D__DEBUG -D__TF_HTML_ENTITY_TEST $<
	${CC} tf_html_entities_decode.o ${OBJDIR}/tf_common.o -o $@

base64_test:src/tf_base64_decode.c ${OBJDIR}/tf_common.o
	${CC} ${CFLAGS} -D__DEBUG -D__TF_BASE64_TEST $<
	${CC} tf_base64_decode.o ${OBJDIR}/tf_common.o -o $@

js_test:src/tf_js_decode.c ${OBJDIR}/tf_common.o
	${CC} ${CFLAGS} -D__DEBUG -D__TF_JS_TEST $<
	${CC} tf_js_decode.o ${OBJDIR}/tf_common.o -o $@


test:url_test space_test entity_test base64_test js_test

#############################################################
target/%.o: %.c
	${CC} ${CFLAGS} ${DMACRO} ${INCS} $< -o $@ ${LFLAGS}
	
