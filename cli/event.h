#ifndef __EVENT_H__
#define __EVENT_H__
/****************************************************************************/


typedef int (*input_cb)(int fd, size_t len);


/*
 * Return 0: Success
       -1: Failure, check the errno
*/
int event_create(input_cb cb);


/*
 * Return -1: Failure, check the errno
 * should never return
*/
int event_dispatch(void);


/*
 * Return 0: Success
       -1: Failure, check the errno
*/
int event_close(void);


/****************************************************************************/
#endif /* __EVENT_H__ */

