#include <tf_header.h>
#include <tf_common.h>
	
int main(int argc, const char* argv[])
{
	int i = 0;
	uint8_t* buf, *tmp;
	size_t len;

	test_util_t arr[] = {
		{"%30",              "0"},
		{"%31%",             "1%"},
		{"%32%3",            "2%3"},
		{"%33%34",           "34"},
		{"%%35",             "%5"},
		{"%%%36",			 "%%6"},
		{"%A0A0",			 " a0"},
		{"%A1",			     "%a1"},
		{"%CC", 			 "%cc"},
	};

	for (i = 0; i < sizeof(arr)/sizeof(test_util_t); i++) {
		buf = (uint8_t*)strdup((char*)arr[i].target);
		tmp = buf;
		len = strlen((char*)buf);
		printf("=[%d]Decode: [%s] expect [%s]\n", i, arr[i].target, arr[i].match);
		buf = tf_url_decode(buf, &len);
		printf("=Result: [%s][%s][len:%zd/%zd]\n\n", buf, _cmp_result(buf, arr[i].match), len, strlen((char*)buf));
		free(tmp);
	}

	return 0;
}

