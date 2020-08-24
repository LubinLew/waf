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

			} else { /* %xx */

			}

		} else if ('\\' == ch[0]) {
			if ('u' == _chr(ch[1])) {/* \uxxxx */

			}

		} else {
		}
		
	}

}


