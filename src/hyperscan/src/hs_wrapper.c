/* 
 * hyperscan
 * Copyright (c) LubinLew
 *
*/


#include <hs.h>
#include <hs_header.h>


struct _hs_mgt {
    risk_level_t risk_level;
    hs_database_t* db;
    hs_scratch_t*  scratch;
    match_event_handler cb;
    db_mgt_t* mdb;
    signature_info_t* match;
};

const static int g_compile_flags[256] = {


};


static unsigned int
_hs_flags_covert(const char* flag_str)
{
    char* ch = flag_str;
    unsigned int flags = 0;
    while (*ch) {
        switch (*ch) {
        case 'i' :
            flags |= HS_FLAG_CASELESS;
            break;
        case 'd' :
            flags |= HS_FLAG_DOTALL;
            break;
        case 'm' :
            flags |= HS_FLAG_MULTILINE;
            break;
        case 's' :
            flags |= HS_FLAG_SINGLEMATCH;
            break;
        case 'e' :
            flags |= HS_FLAG_ALLOWEMPTY;
            break;
        case 'u' :
            flags |= HS_FLAG_UTF8;
            break;
        case 'p' :
            flags |= HS_FLAG_UCP;
            break;
        case 'f' :
            flags |= HS_FLAG_PREFILTER;
            break;
        case 'l' :
            flags |= HS_FLAG_SOM_LEFTMOST
        case 'c' :
            flags |= HS_FLAG_COMBINATION;
            break;
        case 'q' :
            flags |= HS_FLAG_QUIET;
            break;
        default:
            fprintf(stderr, "Invalid flags [%c] !\n", *ch);
            break;
        }
        ++ch;
    }

    return flags;
}


int 
hs_create_database(db_mgt_t* mdb, hs_mgt_t** pmgt)
{
    int i, ret;
    int count = mdb->count;
    const char* pattern;
    unsigned int* ids;
    unsigned int* flags;
    hs_error_t ret;

    hs_mgt_t* mgt;
    *pmgt = NULL;
    mgt = calloc(sizeof(hs_mgt_t), 1);
    if (!mgt) {
        return -1;
    }
    
    mgt->mdb = mdb;

    pattern = calloc(sizeof(char*), count);
    ids     = calloc(sizeof(unsigned int), count);
    flags   = calloc(sizeof(unsigned int), count);

    for (i = 0; i < mdb->count; i++) {
        pattern[i] = mdb->bucket[i].pattern;
        ids[i]     = i; /* here, not use the real id, this index can quickly search signature info */
        flags[i]   = _hs_flags_covert(mdb->bucket[i].flags);
    }

    ret = hs_compile_ext_multi(pattern, flags, ids, NULL, count, 
                        HS_MODE_BLOCK, NULL, &mgt->db, &compile_err);
    if (ret) {
        fprintf(stderr, "ERROR: Unable to compile pattern: %s\n", compile_err->message);
        hs_free_compile_error(compile_err);
        free(mgt);
        return -1;
    }

    if (hs_alloc_scratch(mgt->db, &mgt->scratch) != HS_SUCCESS) {
        fprintf(stderr, "ERROR: Unable to allocate scratch space. Exiting.\n");
        hs_free_database(mgt->db);
        free(mgt);
        return -1;
    }

    *pmgt = mgt;
    return 0;
}


static int 
_hs_match_event_handler(unsigned int id, unsigned long long from,
           unsigned long long to, unsigned int flags, void *context)
{
    hs_mgt_t* mgt = (hs_mgt_t*)context;
    signature_info_t* info = &mgt->mdb->bucket[id];

    /* check risk level */
    if (info->risk_level > mgt->risk_level) {
        return 0; /* continue scanning */
    }

    /* check whitelist */
    if ((mgt->wcb) && (mgt->wcb(info->id))) {
        return 0; /* continue scanning */
    }

    /* store result */
    mgt->match = info;
    return 1; /* stop scanning */
}



signature_info_t* 
hs_scan_database(hs_mgt_t* mgt, unsigned char* data, size_t length)
{
    int ret;
    ret = hs_scan(mgt->db, (const char *)data, (unsigned int)length, 0,
                  mgt->scratch, _hs_match_event_handler, (void*)mgt);
    if (HS_SCAN_TERMINATED == ret) {
        return mgt->match;
    }

    return NULL;
}


int
hs_set_scan_level(hs_mgt_t* mgt, risk_level_t level)
{
    mgt->risk_level = level;
    return 0;
}


int 
hs_destroy_database(hs_mgt_t* mgt)
{
    if (mgt) {
        if (mgt->scratch) {
            hs_free_scratch(mgt->scratch);
        }

        if (mgt->db) {
            hs_free_database(mgt->db);
        }

        free(mgt);
    }

}


