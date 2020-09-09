
CFLAGS := -g -Wall
LFLAGS := `pkg-config --libs json-c`
INCS := `pkg-config --cflags json-c` -I.

all:waf_scan_lib


waf_scan_lib:
	gcc ${CFLAGS} -c -fPIC ${INCS} db_parse.c  -o db_parse.o
	gcc ${CFLAGS} -c -fPIC -I. -I/usr/include/hs/ signs_scan.c -o signs_scan.o
	ar rcs libwaf_scan.a db_parse.o signs_scan.o
	

jsontest:db_parse.c
	gcc ${CFLAGS} -D__JSON_TEST ${INCS} $^ -o $@ ${LFLAGS}

scan_test:scan_test.c waf_scan_lib
	gcc ${CFLAGS} ${INCS} $< -o $@ ${LFLAGS} -lm -lstdc++ -L. -lwaf_scan -lhs 
	
