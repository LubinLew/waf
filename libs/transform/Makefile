CC := gcc
CFLAGS := -g -Wall
LFLAGS := `pkg-config --libs json-c`
LIBINCS := `pkg-config --cflags json-c`
LOCALINCS := -Iinc

vpath %.c src
vpath %.h inc

tf_common.o:tf_common.c
	${CC} ${CFLAGS} -c $< -o $@

url_test:tf_url_decode.c tf_common.o
	${CC} ${CFLAGS} -c -D__DEBUG -D__TF_URL_TEST $<
	${CC} tf_url_decode.o tf_common.o -o $@

space_test:tf_spaces.c tf_common.o
	${CC} ${CFLAGS} -c -D__DEBUG -D__TF_SPACE_TEST $<
	${CC} tf_spaces.o tf_common.o -o $@

entity_test:tf_html_entities_decode.c tf_common.o 
	${CC} ${CFLAGS} -c -D__DEBUG -D__TF_HTML_ENTITY_TEST $<
	${CC} tf_html_entities_decode.o tf_common.o -o $@

base64_test:tf_base64_decode.c tf_common.o
	${CC} ${CFLAGS} -c -D__DEBUG -D__TF_BASE64_TEST $<
	${CC} tf_base64_decode.o tf_common.o -o $@

js_test:tf_js_decode.c tf_common.o
	${CC} ${CFLAGS} -c -D__DEBUG -D__TF_JS_TEST $<
	${CC} tf_js_decode.o tf_common.o -o $@


test:url_test space_test entity_test base64_test js_test


clean:
	rm -f *.o url_test space_test entity_test base64_test js_test
	
