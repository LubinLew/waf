#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <json.h>


static void 
show_usage(const char* argv[])
{

    exit(EXIT_FAILURE);
}

int main(int argc, const char* argv[])
{
    int flags, opt;
    int nsecs, tfnd;
    
    nsecs = 0;
    tfnd = 0;
    flags = 0;
    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
        case 'n':
            flags = 1;
            break;
        case 't':
            nsecs = atoi(optarg);
            tfnd = 1;
            break;
        default: /* '?' */
            show_usage(argv);
            break; /* never go here */
        }
    }
    
    printf("flags=%d; tfnd=%d; optind=%d\n", flags, tfnd, optind);
    
    if (optind >= argc) {
        show_usage(argv);
    }
    
    printf("name argument = %s\n", argv[optind]);
    
    /* Other code omitted */
    
    exit(EXIT_SUCCESS);
}





