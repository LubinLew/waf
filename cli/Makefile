CC=gcc
CFLAGS=-Wall -g



test_terminal: terminal.c
	${CC} ${CFLAGS} -D__TERMINAL_TEST $< -o $@

test_event: event.c
	${CC} ${CFLAGS} -D__TEST_EVENT $< -o $@

clean:
	rm -f test_terminal test_event