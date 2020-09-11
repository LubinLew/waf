#include <stdio.h>
#include <unistd.h>

#include <engine.h>


static int whitelist_callback(uint32_t id);


int main(int argc, const char* argv[])
{
    int ret;
    engine_mgt_t* instance;

    /* init */
	instance = waf_engine_init();
    if (!instance) {
        return -1;
    }

    /* setting */
    ret = waf_engine_set_database(instance, "test.json");
    if (ret) {
        return -1;
    }

    waf_engine_set_level(instance, RISK_LVL_SUPER);
    waf_engine_set_whitelist_cb(instance, whitelist_callback);

    /* scanning */






    /* cleanup */
    waf_engine_exit(instance);
    exit(EXIT_SUCCESS);
}

static int 
whitelist_callback(uint32_t id)
{
    return 1;
}


