#include <termios.h>
#include <unistd.h>
#include <stdlib.h> /* for system() */


static struct termios old_terminal;
static struct termios new_terminal;


void
terminal_create(void)
{
    tcgetattr(STDIN_FILENO, &old_terminal);
    new_terminal = old_terminal;
    /* input modes */
    new_terminal.c_iflag &= IGNBRK; /* Ignore BREAK condition on input */
    /* output modes */
    new_terminal.c_iflag &= BRKINT;
    /* control modes */
    /* local modes */
    new_terminal.c_lflag &= ~ISIG;
    new_terminal.c_lflag &= ~ECHO;
    new_terminal.c_lflag &= ~ICANON;

    /* TCSANOW: the change occurs immediately */
    tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal);
}


void
terminal_destory(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal);
}


int
terminal_disable_sig(void)
{
    new_terminal = old_terminal;
    new_terminal.c_iflag &= IGNBRK;
    new_terminal.c_iflag &= BRKINT;
    new_terminal.c_lflag &= ~ISIG;
    new_terminal.c_lflag &= ~ECHO;
    new_terminal.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal);
    return 0;
}


int
terminal_enable_sig(void)
{
    new_terminal = old_terminal;
    new_terminal.c_iflag &= IGNBRK;
    new_terminal.c_iflag &= BRKINT;
    new_terminal.c_lflag &= ISIG;
    new_terminal.c_lflag &= ~ECHO;
    new_terminal.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal);
    return 0;
}

/*****************************************************************************/
#ifdef __TERMINAL_TEST
int
main(int argc, char *argv[])
{
    terminal_create();
    terminal_disable_sig();
    system("ping 127.0.0.1 -c 5");
    terminal_enable_sig();
    terminal_destory();
    
    return 0;
}

#endif