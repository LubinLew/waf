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
			*dst++ = val;
			*psrc = src + 4;
			*pdst = dst;
			return;
		} 
	}

	/* step by one */
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
			*dst++ = val;
			*psrc = src + 6;
			*pdst = dst;
			return;
		}
	}

	/* step by 2 (%u) */
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
	uint8_t* entity_start = NULL;
	uint8_t ret;

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
int main(int argv, const char* argv[])
{


	return 0;

}

#endif /* __TF_JS_TEST */


