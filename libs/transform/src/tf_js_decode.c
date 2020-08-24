/* 
 * Javascript Decode
 * Copyright (c) LubinLew
 *
 * [ES-7.0]https://www.ecma-international.org/ecma-262/7.0/#sec-escape-string
*/

#include "tf_common.h"


/** 
 *> For those code units being replaced whose value is 0x00FF or less, 
 *> a two-digit escape sequence of the form %xx is used. 
 *> For those characters being replaced whose code unit value is greater than 0x00FF, 
 *> a four-digit escape sequence of the form %uxxxx is used.
 *
 * We Just Decode ASCII
 * javascript will encode ascii to %XX or %u00XX or \u00XX
 * 
*/

static inline void 
_tf_js_2byte_decode(uint8_t** psrc, uint8_t** pdst)
{
	uint8_t* src = *psrc;
	uint8_t* dst = *pdst;
	uint8_t  val;
	
	if (_NG !=_chr(src[1]) && _NG != _chr(src[2])) {
		val = _chr(_HEXCHR2VAL(src[1], src[2]));
		if (val != _NG) {
			_DBG("Valid Format [%s] > [%c]", _str_output(src, src+3), val);
			*dst++ = val;
			*psrc = src + 4;
			*pdst = dst;
			return;
		} 
	}
	
	/* step by one */
	_DBG("Invalid Format [%s]", _str_output(src, src+3));
	*dst++ = '%';
	*psrc = src + 1;
	*pdst = dst;
	return;
}

static inline void 
_tf_js_4byte_decode(uint8_t** psrc, uint8_t** pdst)
{
	uint8_t* src = *psrc;
	uint8_t* dst = *pdst;
	uint8_t  val;
	
	if ('0' == src[2] && '0' == src[3] && \
		_NG !=_hex(src[4]) && _NG != _hex(src[5])) {
		val = _chr(_HEXCHR2VAL(src[4], src[5]));
		if (val != _NG) {		
			_DBG("Valid Format [%s] > [%c]", _str_output(src, src+6), val);
			*dst++ = val;
			*psrc = src + 6;
			*pdst = dst;
			return;
		}
	}

	/* step by 2 (%u) */
	_DBG("Invalid Format [%s]", _str_output(src, src+6));
	*dst++ = src[0]; /* % or \ */
	*dst++ = 'u';
	*psrc = src + 2;
	*pdst = dst;
	return;
}

uint8_t* 
tf_js_decode(uint8_t* data, size_t* len)
{
	uint8_t* ch   = data;
	uint8_t* pret = data;
	uint8_t* end  = data + *len - 5; /* for %uxxxx format */

	_DBG("ch postion [%p], end [%p]", ch, end);

	while (ch < end) {
		if ('%' == ch[0]) {
			if ('u' == _chr(ch[1])) {/* %uxxxx */
				_tf_js_4byte_decode(&ch, &data);
			} else { /* %xx */
				_tf_js_2byte_decode(&ch, &data);
			}
		} else if ('\\' == ch[0]) {
			if ('u' == _chr(ch[1])) {/* \uxxxx */
				_tf_js_4byte_decode(&ch, &data);
			}
		} else {	
			_DBG("Normal Character [%c]", ch[0]);
			*data++ = *ch++;
		}
	}

	/* keep last 5 bytes, if last 6 characters are not %uxxxx format */
	end += 5;
	_DBG("ch postion [%p], end [%p]", ch, end);
	if (likely(ch < end)) {
		*(data++) = ch[0];
		*(data++) = ch[1];
	}

	*len = data - pret;
	return pret;
}


#ifdef __TF_JS_TEST
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
		len = strlen((char*)buf) + 1;
		printf("=[%d]Decode: [%s]\n", i, buf);
		buf = tf_js_decode(buf, &len);
		printf("=Result: [%s][len:%zd/%zd]\n\n", buf, len, strlen((char*)buf));
		free(tmp);
	}

	return 0;
}

#endif /* __TF_JS_TEST */


