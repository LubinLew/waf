/* 
 * delete space and compress space
 * Copyright (c) LubinLew
 *
*/

#include "tf_common.h"


extern uint8_t g_space_charset[];

#define _is_space(_chr) unlikely(g_space_charset[_chr])
#define _not_space(_chr) likely(!g_space_charset[_chr])

uint8_t* ts_delete_space(uint8_t* data, size_t* len)
{
	uint8_t* ch   = data;
	uint8_t* pret = data;
	uint8_t* end  = data + *len;

	while (ch < end) {
		if (_not_space(*ch)) {
			*(data++) = *ch;
		}
		++ch;
	}

	*len = data - pret;
	*data = '\0';
	return pret;
}



uint8_t* ts_compress_space(uint8_t* data, size_t* len)
{
	uint8_t* ch   = data;
	uint8_t* pret = data;
	uint8_t* end  = data + *len;
	bool_t   last_is_space = TS_FALSE; 

	while (ch < end) {
		if (_is_space(*ch)) {
			if (TS_FALSE == last_is_space) {
				*(data++) = _SP;
				last_is_space = TS_TRUE;
			}
		} else {
			*(data++) = *ch;
			last_is_space = TS_FALSE;
		}
		++ch;
	}

	*len = data - pret;
	*data = '\0';
	return pret;
}

#ifdef __TF_SPACE_TEST
int main(int argc, char* argv[])
{
	int i = 0;
	uint8_t* buf, *tmp;
	size_t len;

	const uint8_t* urls[] = {
		(uint8_t*)"  lefttrimspace",
		(uint8_t*)"righttrimspace  ",
		(uint8_t*)"middle          spaces",
		(uint8_t*)"    mix condition     "
	};

	for (i = 0; i < sizeof(urls)/sizeof(char*); i++) {
		buf = (uint8_t*)strdup((char*)urls[i]);
		tmp = buf;
		len = strlen((char*)buf) + 1;
		printf("=[%d]proc space: [%s][len:%zd]\n", i, buf, len);
		buf = ts_compress_space(buf, &len);
		printf("=compress: [%s][len:%zd]\n", buf, len);
		buf = ts_delete_space(buf, &len);
		printf("=delete  : [%s][len:%zd]\n\n", buf, len);
		free(tmp);
	}

	return 0;
}
#endif /* __TF_SPACE_TEST */

