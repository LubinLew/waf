/* 
 * common functions
 * Copyright (c) LubinLew
 *
*/
#define __EXCLUDE_EXTERN_TBL
#include "tf_common.h"
/*------------------------------------------- DEC CHARSET -------------------------------------------*/

/*
 * 0 ~ 9
*/
const uint8_t g_dec_charset[] = {
    /* 0x00~0x0F */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0x10~0x1F */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0x20~0x2F */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0x30~0x3F */ 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0x40~0x4F */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0x50~0x5F */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0x60~0x6F */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0x70~0x7F */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0x80~0x8F */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0x90~0x9F */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0xA0~0xAF */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0xB0~0xBF */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0xC0~0xCF */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0xD0~0xDF */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0xE0~0xEF */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
    /* 0xF0~0xFF */ _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG};
/*------------------------------------------- HEX CHARSET -------------------------------------------*/

/*
 * 0 ~ 9
 * a ~ f
 * A ~ F
*/
const uint8_t g_hex_charset[] = {
/* 0x00~0x0F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x10~0x1F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x20~0x2F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x30~0x3F */0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x40~0x4F */_NG, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x50~0x5F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x60~0x6F */_NG, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x70~0x7F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x80~0x8F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x90~0x9F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xA0~0xAF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xB0~0xBF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xC0~0xCF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xD0~0xDF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xE0~0xEF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xF0~0xFF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG
};


/*------------------------------------------- WHITE-SPACE -------------------------------------------*/

/*
* white-space characters: 
*  space,(0x20)
*  form-feed('\f'),(0x0C)
*  newline('\n'),(0x0A)
*  carriage return ('\r'),(0x0D)
*  horizontal tab('\t'),(0x09)
*  vertical tab('\v').(0x0B)
*  non-breaking space (0xA0)
*/
const uint8_t g_space_charset[] = {
/* 0x00~0x0F */0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
/* 0x10~0x1F */0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0x20~0x2F */1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0x30~0x3F */0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0x40~0x4F */0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0x50~0x5F */0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0x60~0x6F */0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0x70~0x7F */0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0x80~0x8F */0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0x90~0x9F */0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0xA0~0xAF */1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0xB0~0xBF */0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0xC0~0xCF */0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0xD0~0xDF */0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0xE0~0xEF */0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 0xF0~0xFF */0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


/*------------------------------------------- URL-CHARSET -------------------------------------------*/

/*
 * Control characters: [0x00 ~ 0x1F, 0x7F] convert to SP(0x20)
 * Numbers: [0x30 ~ 0x39] Do Nothing
 * Lowercase letters: [0x61 ~ 0x7A] Do Nothing
 * Uppercase letters: [0x41 ~ 0x5A] convert to lowercase
 * Plus character: [0x2B] convert to SP(0x20)
 * non-breaking space: [0xA0] convert to SP(0x20)
*/
const uint8_t g_url_charset[] = {
/* 0x00~0x0F */_SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP,
/* 0x10~0x1F */_SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP,
/* 0x20~0x2F */_SP, '!', '"', '#', '$', '%', '&','\'', '(', ')', '*', _SP, ',', '-', '.', '/',
/* 0x30~0x3F */'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
/* 0x40~0x4F */'@', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
/* 0x50~0x5F */'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', '_',
/* 0x60~0x6F */'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
/* 0x70~0x7F */'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', _SP,
/* 0x80~0x8F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x90~0x9F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xA0~0xAF */_SP, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xB0~0xBF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xC0~0xCF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xD0~0xDF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xE0~0xEF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xF0~0xFF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG
};

/*----------------------------------------- PINTABLE-ACSII-CHARSET ------------------------------------------*/

/* the only one difference with g_url_charset is Plus character
 * Control characters: [0x00 ~ 0x1F, 0x7F] convert to SP(0x20)
 * Numbers: [0x30 ~ 0x39] Do Nothing
 * Lowercase letters: [0x61 ~ 0x7A] Do Nothing
 * Uppercase letters: [0x41 ~ 0x5A] convert to lowercase
 * non-breaking space: [0xA0] convert to SP(0x20)
*/
const uint8_t g_ascii_charset[] = {
/* 0x00~0x0F */_SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP,
/* 0x10~0x1F */_SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP, _SP,
/* 0x20~0x2F */_SP, '!', '"', '#', '$', '%', '&','\'', '(', ')', '*', '+', ',', '-', '.', '/',
/* 0x30~0x3F */'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
/* 0x40~0x4F */'@', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
/* 0x50~0x5F */'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', '_',
/* 0x60~0x6F */'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
/* 0x70~0x7F */'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', _SP,
/* 0x80~0x8F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x90~0x9F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xA0~0xAF */_SP, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xB0~0xBF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xC0~0xCF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xD0~0xDF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xE0~0xEF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xF0~0xFF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG
};


/*------------------------------------------ BASE64-CHARSET ------------------------------------------*/
/* https://tools.ietf.org/html/rfc4648#section-4 */
const uint8_t g_base64_charset[] = {
 /* 0x00~0x0F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
 /* 0x10~0x1F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
 /* 0x20~0x2F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,  62, _NG, _NG, _NG,  63,
 /* 0x30~0x3F */ 52,  53,  54,  55,  56,  57,  58,  59,  60,  61, _NG, _NG, _NG, _NG, _NG, _NG,
 /* 0x40~0x4F */_NG,  0,    1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,
 /* 0x50~0x5F */ 15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25, _NG, _NG, _NG, _NG, _NG,
 /* 0x60~0x6F */_NG,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,
 /* 0x70~0x7F */ 41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51, _NG, _NG, _NG, _NG, _NG,
 /* 0x80~0x8F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
 /* 0x90~0x9F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
 /* 0xA0~0xAF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
 /* 0xB0~0xBF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
 /* 0xC0~0xCF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
 /* 0xD0~0xDF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
 /* 0xE0~0xEF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
 /* 0xF0~0xFF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG
 };
 /*----------------------------------------- BASE64URL-CHARSET -----------------------------------------*/
/* https://tools.ietf.org/html/rfc4648#section-5 */
const uint8_t g_base64url_charset[] = {
/* 0x00~0x0F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x10~0x1F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x20~0x2F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,  62, _NG, _NG,
/* 0x30~0x3F */ 52,  53,  54,  55,  56,  57,  58,  59,  60,  61, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x40~0x4F */_NG,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,
/* 0x50~0x5F */ 15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25, _NG, _NG, _NG, _NG,  63,
/* 0x60~0x6F */_NG,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,
/* 0x70~0x7F */ 41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51, _NG, _NG, _NG, _NG, _NG,
/* 0x80~0x8F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0x90~0x9F */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xA0~0xAF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xB0~0xBF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xC0~0xCF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xD0~0xDF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xE0~0xEF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG,
/* 0xF0~0xFF */_NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG, _NG
};



