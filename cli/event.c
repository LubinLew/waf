#include <sys/epoll.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <errno.h>

#include "event.h"

#define MAX_EVENTS 10

typedef struct  {
    int epoll_fd;
    input_cb inputcb;
} event_data_t;

static event_data_t g_event_data;


int
event_create(input_cb cb)
{
    if (!cb) {
        errno = EINVAL;
        return -1;
    }

    memset(&g_event_data, 0x00, sizeof(event_data_t));
    g_event_data.inputcb = cb;

    return 0;
}


int
event_dispatch(void)
{
    int n, nfds;
    int epollfd;

    struct epoll_event ev;
    struct epoll_event events[MAX_EVENTS];
    
    /** creates an epoll instance
     * the size argument is ignored, but must be greater than zero 
     */
    epollfd = epoll_create(1);
    if (epollfd == -1) {
        perror("epoll_create");
        return -1;
    }
    g_event_data.epoll_fd = epollfd;
    

    ev.events = EPOLLIN;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) == -1) {
        perror("epoll_ctl: STDIN_FILENO");
        return -1;
    }

    for (;;) {
        nfds = epoll_wait(epollfd, events, 1, -1);
        if (nfds == -1) {
            perror("epoll_pwait");
            return -1;
        }

        for (n = 0; n < nfds; ++n) {
            if (events[n].data.fd == STDIN_FILENO) {
                g_event_data.inputcb(STDIN_FILENO, 0);
            }
        }
    }

    return 0;
}


int
event_close(void)
{
    return close(g_event_data.epoll_fd); 
}

/*********************************************************************/
#ifdef __TEST_EVENT
#include <termios.h>

void 
terminal_create(void)
{
    struct termios terminal;
    tcgetattr(STDIN_FILENO, &terminal);
    terminal = terminal;
    terminal.c_lflag &= ~ECHO;
    terminal.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}


int
input_callback(int fd, size_t len)
{
    ssize_t ret;
    uint8_t buf[1024] = {0};
    ret = read(fd, buf, 1024);
    if (ret == -1) {
        perror("read");
        return -1;
    }
    printf("[%zd]%s\n", ret, buf);

    return 0;
}


int
main(int argc, char *argv[])
{
    terminal_create();
    event_create(input_callback);
    event_dispatch();
    event_close();

    return 0;
}


#endif

