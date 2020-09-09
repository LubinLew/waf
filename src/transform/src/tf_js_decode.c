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
 * !!! We Just Decode ASCII
 * javascript could encode ascii to 4 format:
 *    1) %HH
 *  2) \xHH
 *  3) %u00HH
 *  4) \u00HH
*/

static inline void 
_tf_js_2byte_decode(uint8_t** psrc, uint8_t** pdst)
{
    uint8_t* src = *psrc;
    uint8_t* dst = *pdst;
    uint8_t  idx = 1;
    uint8_t  val;
    uint8_t  ch1, ch2;

    /* %HH or \xHH */
    if (likely('\\' == src[0])) {
        ++idx;
    }

    ch1 = _hex(src[idx]);
    ch2 = _hex(src[idx+1]);
    
    if ((ch1 | ch2) != _NG) {
        val = _chr(_HEX2VAL(ch1, ch2));
        if (val != _NG) {
            _CORDBG("Valid Format [%s] > [%c]", _str_output(src, src+2+idx), val);
            *dst++ = val;
            *psrc = src + 2 + idx;
            *pdst = dst;
            return;
        } 
    }
    
    /* step by 1 or 2 */
    _DBG("Invalid Format [%s]", _str_output(src, src+2+idx));
    *dst++ = src[0]; /* % or \ */
    if (likely('\\' == src[0])) {
        *dst++ = src[1]; /* 'x' */
    }
    
    *psrc = src + idx;
    *pdst = dst;
    return;
}

static inline void 
_tf_js_4byte_decode(uint8_t** psrc, uint8_t** pdst, uint8_t* end)
{
    uint8_t* src = *psrc;
    uint8_t* dst = *pdst;
    uint8_t  val;

    if (likely((src+5) < end)) {
        if ('0' == src[2] && '0' == src[3] && \
            _NG !=_hex(src[4]) && _NG != _hex(src[5])) {
            val = _chr(_HEXCHR2VAL(src[4], src[5]));
            if (val != _NG) {        
                _CORDBG("Valid Format [%s] > [%c]", _str_output(src, src+6), val);
                *dst++ = val;
                *psrc = src + 6;
                *pdst = dst;
                return;
            }
        }
            
        /* step by 2 (%u) */
        _DBG("Invalid Format [%s]", _str_output(src, src+6));
    } else { /* bytes not enougth  */
        _DBG("Length wrong [%s]", _str_output(src, end));
    }
    
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
    uint8_t* end  = data + *len - 3; /* for \xHH format */

    _DBG("ch postion [%p], end [%p]", ch, end+3);

    while (ch <= end) {
        if ('%' == ch[0]) {
            if ('u' == _chr(ch[1])) {/* %uxxxx */
                _tf_js_4byte_decode(&ch, &data, end+3);
            } else { /* %HH */
                _tf_js_2byte_decode(&ch, &data);
            }
        } else if ('\\' == ch[0]) {
            if ('u' == _chr(ch[1])) {/* \uxxxx */
                _tf_js_4byte_decode(&ch, &data, end+3);
            } else if ('x' == _chr(ch[1])) { /* \xHH */
                _tf_js_2byte_decode(&ch, &data);
            } else {
                _DBG("Normal Character [%c]", ch[0]);
                *data++ = *ch++;
            }
        } else {
            _DBG("Normal Character [%c]", ch[0]);
            *data++ = *ch++;
        }
    }

    /* keep last 3 bytes, if last 4 characters are not \xHH format */
    end += 3;
    if (ch < end) {
        _DBG("Add last %ld bytes [%s]", end-ch, _str_output(ch, end));
        if (unlikely((ch+3) == end)) {/* remain 3 bytes */
            if (unlikely('%' == ch[0])) {
                _tf_js_2byte_decode(&ch, &data);
            } else {
                _copy(ch, end, data);
            }
        } else { /* remain 1 or 2 bytes */
            _copy(ch, end, data);
        }
    }
    *len = data - pret;
    *data = '\0';
    return pret;
}


