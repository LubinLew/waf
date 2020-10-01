#include <tf_header.h>
#include <tf_common.h>


int main(int argc, const char* argv[])
{
	int i = 0;
	uint8_t* buf, *tmp;
	size_t len;


	test_util_t arr[] = {
		{"%30",               "0"},
		{"\\x31",             "1"},
		{"%u0032",            "2"},
		{"\\u0033",           "3"},
		{"%%34",              "%4"},
		{"\\\\X35",           "\\5"},
		{"%%u0036",           "%6"},
		{"\\\\u0037",         "\\7"},
		{"%41%",              "a%"},
		{"%42%4",             "b%4"},
		{"%43%44",            "cd"},
		{"\\x45\\",           "e\\"},
		{"\\x46\\x",          "f\\x"},
		{"\\x47\\x4",         "g\\x4"},
		{"\\x48\\x49",        "hi"},
		{"\\U004A\\",		  "j\\"},
		{"\\U004B\\u",		  "k\\u"},
		{"\\U004C\\u0",		  "l\\u0"},
		{"\\U004d\\u00", 	  "m\\u00"},
		{"\\U004e\\u004",	  "n\\u004"},
		{"\\U004f\\u0050",	  "op"},
		{"\\x66\\x69\\x6c\\x74\\x65\\x72",	  "filter"},
		{"\\x63\\x6f\\x6e\\x73\\x74\\\x72\x75\\x63\\x74\\x6f\\x72", "const\\ructor"},
	};

	for (i = 0; i < sizeof(arr)/sizeof(test_util_t); i++) {
		buf = (uint8_t*)strdup(arr[i].target);
		tmp = buf;
		len = strlen((char*)buf);
		printf("=[%d]Decode: [%s] [len:%zd]\n", i, buf, len);
		buf = tf_js_decode(buf, &len);
		printf("=Result: [%s][%s][len:%zd/%zd]\n\n", buf, _cmp_result(buf, arr[i].match),len, strlen((char*)buf));
		free(tmp);
	}

	return 0;
}



