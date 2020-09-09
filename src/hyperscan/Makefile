LIBNAME = libhs_wrapper.a
#############################################################
OBJDIR = target/src
CFLAGS = -Wall -MD -O0 -ggdb -c
LFLAGS = 
MACRO = -D__DEBUG
INCS =
CC = gcc


TEST_INCS   = -Iinc -Isrc
TEST_CFLAGS = -g -Wall
TEST_LFLAGS = -Ltarget -ltf
TEST_MACRO  = -D__DEBUG

#############################################################

SRCLIST = src/tf_common.c                 \
          src/tf_spaces.c                 \
          src/tf_url_decode.c             \
          src/tf_html_entities_decode.c   \
          src/tf_base64_decode.c          \
          src/tf_js_decode.c
	
	
	
#############################################################
.PYONY: all clean

all: ${LIBNAME}
	@ls -lh target/${LIBNAME}

${LIBNAME}: $(SRCLIST:%.c=target/%.o)
	ar crs target/$@ $^
	
clean:
	@rm -f target/src/{*.o,*.d}
	@rm -f target/test/{*.o,*.d}
	@rm -f target/${LIBNAME}
	@echo "ALL Clear !!!"

#############################################################
test:url_test space_test entity_test base64_test js_test


url_test:${LIBNAME}
	${CC} ${TEST_CFLAGS} ${TEST_MACRO} ${TEST_INCS} test/tf_url_test.c -o $@ ${TEST_LFLAGS} 

space_test:src/tf_spaces.c ${OBJDIR}/tf_common.o
	${CC} ${CFLAGS} -D__DEBUG -D__TF_SPACE_TEST $<
	${CC} tf_spaces.o ${OBJDIR}/tf_common.o -o $@

entity_test:src/tf_html_entities_decode.c ${OBJDIR}/tf_common.o 
	${CC} ${CFLAGS} -D__DEBUG -D__TF_HTML_ENTITY_TEST $<
	${CC} tf_html_entities_decode.o ${OBJDIR}/tf_common.o -o $@

base64_test:src/tf_base64_decode.c ${OBJDIR}/tf_common.o
	${CC} ${CFLAGS} -D__DEBUG -D__TF_BASE64_TEST $<
	${CC} tf_base64_decode.o ${OBJDIR}/tf_common.o -o $@

js_test:${LIBNAME}
	${CC} ${TEST_CFLAGS} ${TEST_MACRO} ${TEST_INCS} test/tf_js_test.c -o $@ ${TEST_LFLAGS} 




#############################################################
target/%.o: %.c
	${CC} ${CFLAGS} ${MACRO} ${INCS} $< -o $@ ${LFLAGS}
	
