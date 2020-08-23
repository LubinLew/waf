/* 
 * Base64 Decode
 * Copyright (c) LubinLew
 *
 * https://github.com/LubinLew/nginx-study/blob/master/src/core/ngx_string.c#L1158
 *
*/

#include "tf_common.h"

extern uint8_t g_base64_charset[];
extern uint8_t g_base64url_charset[];


static uint8_t *
_tf_decode_base64_internal(uint8_t *data, size_t *plen, const uint8_t *charset)
{
    uint8_t* pret = data;
    uint8_t* ch = data;
    uint8_t* end = data + *plen - 1;
    uint8_t  ch1, ch2, ch3;
    size_t len = 0;

    /* check base64 string */
    while (ch < end) {
        if (unlikely('=' == ch[0])) {
            _DBG("Find base64 padding('=') [%p]", ch);
            break;
        }

        if (unlikely(_NG == ch[0])) {
            _DBG("Invalid base64 char [%c]", ch[0]);
            return pret;
        }

        ++ch;
    }
    /* ch is new end now, exclude padding '=' */
    len = ch - data;
    _DBG("base64 string len [%zd]", len);
    ch = data;

    if (len % 4 == 1) {
        _DBG("Invalid base64 len [%zd]", len);
        return pret;
    }

    while (len > 3) {
        ch1 = (uint8_t)(charset[ch[0]] << 2 | charset[ch[1]] >> 4);
        ch2 = (uint8_t)(charset[ch[1]] << 4 | charset[ch[2]] >> 2);
        ch3 = (uint8_t)(charset[ch[2]] << 6 | charset[ch[3]]);
        _DBG("base64 convert [%s] to [%c%c%c]",  _str_output(ch, ch+4), ch1, ch2, ch3);
        *(data++) = ch1;
        *(data++) = ch2;
        *(data++) = ch3;
        ch += 4;
        len -= 4;
    }

    if (len > 1) {
        *data++ = (uint8_t)(charset[ch[0]] << 2 | charset[ch[1]] >> 4);
    }

    if (len > 2) {
        *data++ = (uint8_t)(charset[ch[1]] << 4 | charset[ch[2]] >> 2);
    }

    *plen = data - pret;
    *data = '\0';
    return pret;
}

uint8_t* 
tf_base64_decode(uint8_t *data, size_t *len)
{
    return _tf_decode_base64_internal(data, len, g_base64_charset);
}

uint8_t* 
tf_base64url_decode(uint8_t *data, size_t *len)
{
    return _tf_decode_base64_internal(data, len, g_base64url_charset);
}


#ifdef __TF_BASE64_TEST
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

#endif /* __BASE64_TEST */