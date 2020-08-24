#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <json.h> /* yum install json-c-devel */
#include <db_common.h>

/* everything is stored in the mgt_t struct */
static mgt_t* mgt_alloc_memory(int count, size_t size)
{
	size_t bucket = sizeof(sign_t) * (count + 1);
	mgt_t* mgt = malloc(size + bucket);
	mgt->count = count;
	mgt->bucket = (sign_t*)mgt->memory;
	mgt->mem_pos = mgt->memory + bucket;

	return mgt;
}

 void mgt_close_db(mgt_t* mgt)
{
	if (mgt) {
		free(mgt);
	}
}


static char* mgt_store_string_oject(mgt_t* mgt, struct json_object* jo_str)
{
	const char*data = json_object_get_string(jo_str);
	char* pos = mgt->mem_pos;
	size_t len = strlen(data) + 1; // store '\0'
	memcpy(mgt->mem_pos, data, len);
	mgt->mem_pos += len;
	return pos;
}


int mgt_open_db(const char* path, mgt_t** pmgt) 
{

	int     i, arr_cnt;
	int32_t count;
	int32_t version;

	struct json_object *parsed_json;
	struct json_object *jo_count;
	struct json_object *jo_signs;
	struct json_object *jo_version;

	int   fd;
	char* bytes;
	struct stat st;

	mgt_t* mgt;
	
    fd = open(path, O_RDONLY);
    if (fd < 0) {
		fprintf(stderr, "open %s failed, %s\n", path, strerror(errno));
        return -1;
    }
   
    if (fstat(fd, &st) < 0) {
		fprintf(stderr, "fstat %s failed, %s\n", path, strerror(errno));
        close(fd);
        return -1;
    }

    bytes = (char *)mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == bytes) {
		fprintf(stderr, "mmap %s failed, %s\n", path, strerror(errno));
        close(fd);
        return -1;
    }
	close(fd);


	parsed_json = json_tokener_parse(bytes);

	json_object_object_get_ex(parsed_json, "count", &jo_count);
	json_object_object_get_ex(parsed_json, "signs", &jo_signs);
	json_object_object_get_ex(parsed_json, "version", &jo_version);

	count   = json_object_get_int(jo_count);
	version = json_object_get_int(jo_version);
	arr_cnt = json_object_array_length(jo_signs);
	if (count != arr_cnt) {
		fprintf(stderr, "sign count not match, %d/%d\n", count, arr_cnt);
		json_object_put(parsed_json);
		munmap(bytes, st.st_size);
		return -1;
	}

	mgt = mgt_alloc_memory(count, st.st_size);
	mgt->version = version;

	for(i = 0;i < arr_cnt; i++) {
		sign_t* sign_tmp;
		struct json_object *jo_id;
		struct json_object *jo_pattern;
		struct json_object *jo_flags;
		struct json_object *jo_cve_id;
		struct json_object *jo_cnnvd_id;
		struct json_object *jo_category;
		struct json_object *jo_level;
		struct json_object *jo_server;
		struct json_object *jo_desc;
		struct json_object *jo_one_sign;

		jo_one_sign = json_object_array_get_idx(jo_signs, i);
		json_object_object_get_ex(jo_one_sign, "id",       &jo_id);
		json_object_object_get_ex(jo_one_sign, "level",    &jo_level);
		json_object_object_get_ex(jo_one_sign, "flags",    &jo_flags);
		json_object_object_get_ex(jo_one_sign, "pattern",  &jo_pattern);
		json_object_object_get_ex(jo_one_sign, "cve-id",   &jo_cve_id);
		json_object_object_get_ex(jo_one_sign, "cnnvd-id", &jo_cnnvd_id);
		json_object_object_get_ex(jo_one_sign, "server",   &jo_server);
		json_object_object_get_ex(jo_one_sign, "category", &jo_category);
		json_object_object_get_ex(jo_one_sign, "desc",     &jo_desc);

		sign_tmp           = &mgt->bucket[i];
		sign_tmp->id       = json_object_get_int(jo_id);
		sign_tmp->level    = json_object_get_int(jo_level);
		sign_tmp->flags    = json_object_get_int(jo_flags);
		sign_tmp->pattern  = mgt_store_string_oject(mgt, jo_pattern);
		sign_tmp->cve_id   = mgt_store_string_oject(mgt, jo_cve_id);
		sign_tmp->cnnvd_id = mgt_store_string_oject(mgt, jo_cnnvd_id);
		sign_tmp->server   = mgt_store_string_oject(mgt, jo_server);
		sign_tmp->category = mgt_store_string_oject(mgt, jo_category);
		sign_tmp->desc     = mgt_store_string_oject(mgt, jo_desc);
	}	

	json_object_put(parsed_json);
	munmap(bytes, st.st_size);

	*pmgt = mgt;
	return 0;
}


#ifdef __JSON_TEST

int main(void)
{
	int i, ret;
	mgt_t* mgt;
	sign_t* sign;

	ret = mgt_open_db("./db.json", &mgt);
	if (ret != 0) {
		printf("failed\n");
		return -1;
	}

	for (i = 0; i < mgt->count; i++) {
		sign = &mgt->bucket[i];
		printf("=== [%d] CVE:%s, CNNVD:%s, %s\n", sign->id, sign->cve_id, sign->cnnvd_id, sign->category);
		printf("=== [%d], %s, %s\n\n", sign->level, sign->server, sign->desc);
	}

	mgt_close_db(mgt);

	return 0;
}

#endif /* __JSON_TEST */

