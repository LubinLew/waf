/* 
 * URL Decode
 * Copyright (c) LubinLew
 *
 * [RFC3986]https://tools.ietf.org/html/rfc3986 [Uniform Resource Identifier (URI): Generic Syntax]
 * [RFC1630]https://tools.ietf.org/html/rfc1630 [Universal Resource Identifiers in WWW]
 * [RFC1738]https://tools.ietf.org/html/rfc1738 [Uniform Resource Locators (URL)]
*/


#include <stdlib.h>
#include <string.h>
#include "tf_common.h"


/* decode Percent-Encoding data inplace */
uint8_t* tf_url_decode(uint8_t* data, size_t* len)
{
	uint8_t* ch   = data;
	uint8_t* pret = data;
	uint8_t* end  = data + *len - 3; /* ensure ch[2] not overflow, last char is data[len - 1] */
	uint8_t  ret  = 0;
	uint8_t ch1, ch2;

	_DBG("ch postion [%p], end [%p:%s]", ch, end, end);

	while (ch < end) {
		if (unlikely('%' == *ch)) {
			
			ch1 = g_hex_charset[ch[1]];
			ch2 = g_hex_charset[ch[2]];

			/* invalid %AB format */
			if (unlikely((ch1|ch2) == _NG)) {
				_DBG("Invalid Format [%c%c%c], val[%d,%d]", ch[0], ch[1], ch[2], ch1, ch2);
				*(data++) = g_url_charset[ch[0]];
				++ch;
				continue;
			}

			/* decode Percent-Encoding data */
			if(likely((ret = g_url_charset[_HEX2VAL(ch1, ch2)]) != _NG)) {
				_CORDBG("Valid Format [%c%c%c] > [%c]", ch[0], ch[1], ch[2], ret);
				*(data++) = ret;	
			} else { /* convert failed, so keep it */
				_DBG("Invalid Format [%c%c%c], val[%d,%d]", ch[0], ch[1], ch[2], ch1, ch2);
				*(data++) = '%'; /* = *ch */
				*(data++) = g_url_charset[ch[1]];
				*(data++) = g_url_charset[ch[2]];
			}
			ch += 3; /* step by 3(%AB) */
			continue;
		} else { /* normal characters */	
			_DBG("Normal Character [%c]", ch[0]);
			*(data++) = g_url_charset[ch[0]];
			++ch;
		}
	}

	/* keep last 2 bytes, if last 3 characters are not Percent-Encoding data */
	_DBG("ch postion [%p], end+2 [%p]", ch, end+2);
	if (likely(ch < (end + 2))) {
		_DBG("Add last 2 bytes [%c%c]", ch[0], ch[1]);
		*(data++) = ch[0];
		*(data++) = ch[1];
	}
	
	*len = data - pret;
	*data = '\0';

	return pret;
}


#ifdef  __TF_URL_TEST
int main(int argc, const char* argv[])
{
	int i = 0;
	uint8_t* buf, *tmp;
	size_t len;

	const uint8_t* urls[] = {
		(uint8_t*)"abcdefghijklmnopqrstuvwxy%5A",
		(uint8_t*)"ab%20%20cd%",
		(uint8_t*)"ef%21%28gk%A",
		(uint8_t*)"inVALID+format:%FF%ZX:end",
		(uint8_t*)"\"java\r\nscript\"",
		(uint8_t*)"filename: /%E4%B8%AD%E6%96%87%E8%B7%AF%E5%BE%84",
		(uint8_t*)"test%A0test",
		(uint8_t*)"%%35%%%%%%%%%%%"
	};

	for (i = 0; i < sizeof(urls)/sizeof(char*); i++) {
		buf = (uint8_t*)strdup((char*)urls[i]);
		tmp = buf;
		len = strlen((char*)buf);
		printf("=[%d]Decode: [%s]\n", i, buf);
		buf = tf_url_decode(buf, &len);
		printf("=Result: [%s][len:%zd/%zd]\n\n", buf, len, strlen((char*)buf));
		free(tmp);
	}

	return 0;
}

#endif /* __TF_URL_TEST */

