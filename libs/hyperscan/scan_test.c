#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include <signs_scan.h>

int main(int argc, char* argv[])
{
	int ret;
	context_t ctx;

	ret = waf_hs_create("./db.json");
	if (ret != 0) {
		return -1;
	}

	ctx.scan_level = 1;
	
	ret = waf_hs_scan("AAAAAAAAAAAAAA",  14, &ctx);
	if (0 == ret) {
		printf("%d\n", ctx.match_info->id);
	}

	ret = waf_hs_scan("BBBBBBBBBBBBBB", 14, &ctx);
	if (0 == ret) {
		printf("%d\n", ctx.match_info->id);
	}
	
	ret = waf_hs_scan("CCCCCCCCCCCCCC", 14, &ctx);
	if (0 == ret) {
		printf("%d\n", ctx.match_info->id);
	}


	waf_hs_free();

	return 0;
}

