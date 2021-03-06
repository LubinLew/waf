/* 
 * Html entities Decode
 * Copyright (c) LubinLew
 *
 * https://www.w3schools.com/charsets/ref_html_entities_4.asp
 * https://www.freeformatter.com/html-entities.html
 *
 * PHP
 * https://github.com/php/php-src/blob/master/ext/mbstring/libmbfl/filters/html_entities.c
 * https://github.com/php/php-src/blob/master/ext/mbstring/libmbfl/filters/mbfilter_htmlent.c#L177
*/

#include <stdlib.h>
#include <string.h>
#include "tf_common.h"



/* 
 * A html Entity has 3 formats.
	&	&amp;	&#38;	&#x26;	ampersand
	<	&lt;	&#60;	&#x3C;	less than
	>	&gt;	&#62;	&#x3E;	greater than
	 	&nbsp;	&#160;	&#xA0;	no-break space = non-breaking space
	"   &quot;  &#34;   &#x22;
	'   &apos;  &#39;

support entities:
   https://www.freeformatter.com/html-entities.html#ascii-characters
*/



/*
  *start = '&'
  *end  = ';'
*/
static inline uint8_t 
_tf_html_entiry_convert(uint8_t* start, uint8_t* end)
{
	uint8_t ch1, ch2, ch3;
	size_t len = end - start - 1; /* exclude '&' and ';' */
	++start; /* skip '&' */

	switch (*start) {
	case '#' :
		if ('x' == start[1]) { /* hexadecimal */
			len -= 2; /* exclude '#' and 'x' */
			start += 2;
			_DBG("[HEX]len = %zd", len);
			/* skip 0, such as &#x000032; */
			while (*start == '0') {
				++start;
				--len;
			}

			switch (len) {
			case 1: /* control charset */
				return _chr(_hex(start[0]));
			case 2:
				ch1 = _hex(start[0]);
				ch2 = _hex(start[1]);
				if ((ch1 | ch2) != _NG) {
					return _chr(_HEX2VAL(ch1, ch2));
				} 
				return _NG;
			default:
				return _NG;
			}

		} else { /* decimal */
			++start; /* skip '#' */
			--len; /* exclude '#' */
			_DBG("[DEC]len = %zd", len);
			switch (len) {
			case 1: /* &#1 ~ &#9 */
				ch1 = _num(start[0]);
				return _chr(ch1);
			case 2:
				ch1 = _num(start[0]);
				ch2 = _num(start[1]);
				if ((ch1 | ch2) != _NG) {
					return _chr(_DEC2VAL(ch1, ch2));
				}
				
				return _NG;
			case 3:
				ch1 = _num(start[0]);
				if (ch1 != 1) {
					return _NG;
				}
				ch2 = _num(start[1]);
				ch3 = _num(start[2]);
				if ((ch2 | ch3) != _NG) {
					return _chr(100 + _DEC2VAL(ch2, ch3));
				}
				return _NG;
			default:
				return _NG;
			}
		}
		break;

	case 'a' : /* &amp; */
		if ((3 == len) && (_4cmp("amp;", start))) {
			return '&';
		} else if ((4 == len) && (_4cmp("apos", start))) { /* &apos;  */
			return '\'';
		} else {
			return _NG;
		}
		 break;

	case 'l' : /* &lt; */
		if ((2 == len) && (_2cmp("lt", start))) {
			return '<';
		} else {
			return _NG;
		}
		break;

	case 'g' : /* &gt; */
		if ((2 == len) && (_2cmp("gt", start))) {
			return '>';
		} else {
			return _NG;
		}
		break;

	case 'n' : /* &nbsp; */
		if ((4 == len) && (_4cmp("nbsp", start))) {
			return _SP;
		} else {
			return _NG;
		}
		break;

	case 'q': /* &quot; */
		if ((4 == len) && (_4cmp("quot", start))) {
			return '"';
		} else {
			return _NG;
		}
		break;

	default:
		return _NG;
	}

	return _NG;
}

/* decode html entity inplace */
uint8_t* 
tf_html_entity_decode(uint8_t* data, size_t* len)
{
	uint8_t* ch   = data;
	uint8_t* pret = data;
	uint8_t* end  = data + *len;
	uint8_t* entity_start = NULL;
	uint8_t  ret;

	_DBG("ch postion [%p], end [%p]", ch, end);

	while (ch < end) {
		switch (*ch) {
		case '&' :
			if (entity_start) {/* normal */
				_DBG("Invalid Format [%s]", _str_output(entity_start, ch+1));
				_copy(entity_start, ch, data);
			} else {
				_DBG("Find & [%p]", ch);
			}
			entity_start = ch++;
			break;

		case ';' :
			if (entity_start) { /* convert */
				_DBG("Find ; [%s]", _str_output(entity_start, ch+1));
				ret = _tf_html_entiry_convert(entity_start, ch);
				 if (ret != _NG){
					_CORDBG("Valid Format [%s] > [%c]", _str_output(entity_start, ch+1), ret);
					*(data++) = ret;
					++ch;
				} else {
					++ch;
					_DBG("Invalid Format [%s]", _str_output(entity_start, ch+1));
					_copy(entity_start, ch, data);
				}

				entity_start = NULL;
			} else { /* normal */
				_DBG("Normal Character [%c]", ch[0]);
				*(data++) = *(ch++);
			}
			break;

		default: /* normal */
			if (!entity_start) {
				_DBG("Normal Character [%c]", ch[0]);
				*(data++) = *(ch++);
			}else {
//				_DBG("+ Keep data [%c]", ch[0]);
				++ch;
			}
			break;
		}
	}

	if (entity_start) { /* normal */
		_DBG("Remain data [%s]", _str_output(entity_start, ch));
		_copy(entity_start, ch, data);
	}

	*len = data - pret;
	*data = '\0';

	return pret;
}

#ifdef  __TF_HTML_ENTITY_TEST
int main(int argc, const char* argv[])
{
	int i = 0;
	uint8_t* buf, *tmp;
	size_t len;

	const test_util_t arr[] = {
		{"&amp;&#38;&#x26;",    "&&&"},
		{"&lt;&#60;&#x3C;",     "<<<"},
		{"&gt;&#62;&#x3e;",     ">>>"},
		{"&quot;&#34;&#x22;",	"\"\"\""},
		{"&apos;&#39;&#x27;",	"'''"},
	};

	for (i = 0; i < sizeof(arr)/sizeof(test_util_t); i++) {
		buf = (uint8_t*)strdup(arr[i].target);
		tmp = buf;
		len = strlen((char*)buf);
		printf("=[%d]Decode: [%s]\n", i, buf);
		buf = tf_html_entity_decode(buf, &len);
		printf("=Result: [%s][%s][len:%zd/%zd]\n\n", buf, _cmp_result(buf, arr[i].match), len, strlen((char*)buf));
		free(tmp);
	}

	return 0;
}

#endif /* __TF_HTML_ENTITY_TEST */
