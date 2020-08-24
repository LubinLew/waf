#ifndef __DB_COMMON_H__
#define __DB_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------*/
typedef struct _sign {
	int   id;
	int   level;
	int   flags;
	char* pattern;
	char* cve_id;
	char* cnnvd_id;
	char* desc;
	char* category;
	char* server;
} sign_t;

typedef struct _mgt {
	int     version;
	int     count;
	sign_t* bucket;
	char*   mem_pos;
	char    memory[0];
} mgt_t;


typedef struct _context {
	int     scan_level;
	int     match_from;
	int     match_to;
	sign_t* match_info;
} context_t;

/*-------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif /* __DB_COMMON_H__ */

