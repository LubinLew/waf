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
	uint8_t* end  = data + *len - 2; /* ensure ch[2] not overflow, last char is data[len - 1] */
	uint8_t  ret  = 0;
	uint8_t ch1, ch2;

	_DBG("ch postion [%p], end [%p:%s]", ch, end, end);

	while (ch < end) {
		if (unlikely('%' == *ch)) {
			
			ch1 = _hex(ch[1]);
			ch2 = _hex(ch[2]);

			/* invalid %AB format */
			if (unlikely((ch1|ch2) == _NG)) {
				_DBG("Invalid Format [%c%c%c], val[%d,%d]", ch[0], ch[1], ch[2], ch1, ch2);
				*(data++) = _chr(ch[0]);
				++ch;
				continue;
			}

			/* decode Percent-Encoding data */
			if(likely((ret = _chr(_HEX2VAL(ch1, ch2))) != _NG)) {
				_CORDBG("Valid Format [%c%c%c] > [%c]", ch[0], ch[1], ch[2], ret);
				*(data++) = ret;	
			} else { /* convert failed, so keep it */
				_DBG("Invalid Format [%c%c%c], val[%d,%d]", ch[0], ch[1], ch[2], ch1, ch2);
				*(data++) = '%'; /* = *ch */
				*(data++) = _chr(ch[1]);
				*(data++) = _chr(ch[2]);
			}
			ch += 3; /* step by 3(%AB) */
			continue;
		} else { /* normal characters */	
			_DBG("Normal Character [%c]", ch[0]);
			*(data++) = _chr(ch[0]);
			++ch;
		}
	}

	/* keep last 2 bytes, if last 3 characters are not Percent-Encoding data */
	end += 2;
	if (ch < end) {
		_DBG("Add remain %ld bytes [%s]", end-ch, _str_output(ch, end));
		_copy(ch, end, data);
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

	test_util_t arr[] = {
		{"%30",              "0"},
		{"%31%",             "1%"},
		{"%32%3",            "2%3"},
		{"%33%34",           "34"}
	};

	for (i = 0; i < sizeof(arr)/sizeof(test_util_t); i++) {
		buf = (uint8_t*)strdup((char*)arr[i].target);
		tmp = buf;
		len = strlen((char*)buf);
		printf("=[%d]Decode: [%s]\n", i, buf);
		buf = tf_url_decode(buf, &len);
		printf("=Result: [%s][%s][len:%zd/%zd]\n\n", buf, _cmp_result(buf, arr[i].match), len, strlen((char*)buf));
		free(tmp);
	}

	return 0;
}

#endif /* __TF_URL_TEST */

