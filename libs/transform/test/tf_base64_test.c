#include <tf_header.h>
#include <tf_common.h>


int main(int argc, const char *argv[])
{
    int i = 0;
    uint8_t *buf, *tmp;
    size_t len;

    const uint8_t *urls[] = {
        (uint8_t *)"aGVsbG8lMjB3b3JsZA==",
    };

    for (i = 0; i < sizeof(urls) / sizeof(char *); i++)
    {
        buf = (uint8_t *)strdup((char *)urls[i]);
        tmp = buf;
        len = strlen((char *)buf) + 1;
        printf("=[%d]Decode: [%s]\n", i, buf);
        buf = tf_base64_decode(buf, &len);
        printf("=Result: [%s][len:%zd/%zd]\n\n", buf, len, strlen((char *)buf));
        free(tmp);
    }

    return 0;
}

