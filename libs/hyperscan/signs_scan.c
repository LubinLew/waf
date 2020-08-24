#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include <hs.h>
#include <db_parse.h>



typedef unsigned int       INITU;
typedef unsigned long long INTULL;



static hs_database_t* g_hs_database;
static hs_scratch_t*  g_hs_scratch;
static mgt_t*         g_mgt;

int waf_hs_create(const char* path)
{
	int i;
	int count;
	int ret = HS_SUCCESS;
	hs_compile_error_t* hs_err;
	const char** expressions;
	unsigned*	flags;
	unsigned*	ids;

	ret = mgt_open_db(path, &g_mgt);
	if (ret != 0) {
		return -1;
	}

	count = g_mgt->count;
	expressions = calloc(sizeof(char*), count);
	flags = calloc(sizeof(unsigned), count);
	ids = calloc(sizeof(unsigned), count);
	
	for (i = 0; i < count; i++) {
		expressions[i] = g_mgt->bucket[i].pattern;
		flags[i] = (unsigned)g_mgt->bucket[i].flags;
		ids[i] = (unsigned)i;
	}
	
	ret = hs_compile_ext_multi(expressions,flags, ids, NULL,  count, \
							HS_MODE_BLOCK, NULL, &g_hs_database, &hs_err);
	free(ids);
	free(flags);
	free(expressions);

	if (ret != HS_SUCCESS) {
		fprintf(stderr, "hs_compile_ext_multi faild, %s\n", hs_err->message);
		hs_free_compile_error(hs_err);
		return -1;
	}

	ret = hs_alloc_scratch(g_hs_database, &g_hs_scratch);
	if (ret != HS_SUCCESS) {
		hs_free_database(g_hs_database);
		g_hs_database = NULL;
		return -1;
	}

	return 0;
}



static int hs_match_handler(INITU id, INTULL from, INTULL to, INITU flags, void *context)
{
	context_t* ctx = (context_t*)context;

	sign_t* match = &g_mgt->bucket[id];
	if (match->level < ctx->scan_level) {
		return 0;
	}

	ctx->match_from = from;
	ctx->match_to   = to;
	ctx->match_info = match;
	return 1;
}


int waf_hs_scan(const char* target, size_t length, context_t* ctx)
{
	int ret = HS_SUCCESS;
	ret = hs_scan(g_hs_database, target, (unsigned)length, 0, \
				  g_hs_scratch, hs_match_handler, (void*)ctx);
	if (HS_SCAN_TERMINATED == ret) {
		return 0;
	}

	return -1;
}

void waf_hs_free(void)
{
	if (g_hs_scratch) {
		hs_free_scratch(g_hs_scratch);
	}

	if (g_hs_database) {
		hs_free_database(g_hs_database);
	}

	if (g_mgt) {
		mgt_close_db(g_mgt);
	}
}



