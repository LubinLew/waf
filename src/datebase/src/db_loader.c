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
#include <db_loader.h>


/* everything is stored in the db_mgt_t structure */
static db_mgt_t* 
_database_alloc(int count, size_t file_size)
{
	size_t bucket = sizeof(signature_info_t) * (count + 1);
	db_mgt_t* mgt = malloc(file_size + bucket);
	if (!mgt) {
		perror("malloc failed, ");
		return NULL;
	}
	mgt->count = count;
	mgt->bucket = (signature_info_t*)mgt->memory;
	mgt->mem_pos = mgt->memory + bucket;

	return mgt;
}




static char* 
_store_string_oject(db_mgt_t* mgt, struct json_object* jo_str)
{
	const char* data = json_object_get_string(jo_str);
	char* pos = mgt->mem_pos;
	size_t len = strlen(data) + 1; // store '\0'
	memcpy(mgt->mem_pos, data, len);
	mgt->mem_pos += len;

	return pos;
}


int 
database_open(const char* path, db_mgt_t** pmgt) 
{

	int     i, arr_cnt;
	int32_t count;
	int32_t version;

	struct json_object *parsed_json;
	struct json_object *jo_signs;
	struct json_object *jo_version;

	int   fd;
	char* bytes;
	struct stat st;

	db_mgt_t* mgt;
	
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
	json_object_object_get_ex(parsed_json, "signs", &jo_signs);
	json_object_object_get_ex(parsed_json, "version", &jo_version);
	version = json_object_get_int(jo_version);
	count = json_object_array_length(jo_signs);

	mgt = _database_alloc(count, st.st_size);
	mgt->version = version;

	for(i = 0;i < arr_cnt; i++) {
		signature_info_t* sign_tmp;

		struct json_object *jo_id;
		struct json_object *jo_pattern;
		struct json_object *jo_flags;
		struct json_object *jo_level;
		struct json_object *jo_category_id;
		struct json_object *jo_category_str;
		struct json_object *jo_sub_category_id;
		struct json_object *jo_sub_category_str;
		struct json_object *jo_cve_id;
		struct json_object *jo_desc;

		struct json_object *jo_one_sign;

		jo_one_sign = json_object_array_get_idx(jo_signs, i);
		json_object_object_get_ex(jo_one_sign, "id",       &jo_id);
		json_object_object_get_ex(jo_one_sign, "pattern",  &jo_pattern);
		json_object_object_get_ex(jo_one_sign, "flags",    &jo_flags);
		json_object_object_get_ex(jo_one_sign, "level",    &jo_level);
		json_object_object_get_ex(jo_one_sign, "category-id",   &jo_category_id);
		json_object_object_get_ex(jo_one_sign, "category-str",   &jo_category_str);
		json_object_object_get_ex(jo_one_sign, "sub_category-id",   &jo_sub_category_id);
		json_object_object_get_ex(jo_one_sign, "sub_category-str",   &jo_sub_category_str);
		json_object_object_get_ex(jo_one_sign, "description",     &jo_desc);

		sign_tmp                   = &mgt->bucket[i];
		sign_tmp->id               = json_object_get_int(jo_id);
		sign_tmp->pattern          = _store_string_oject(mgt, jo_pattern);
		sign_tmp->flags            = _store_string_oject(jo_flags);
		sign_tmp->risk_level       = json_object_get_int(jo_level);
		sign_tmp->category_id      = json_object_get_int(mgt, jo_category_id);
		sign_tmp->category_str     = _store_string_oject(mgt, jo_category_str);
		sign_tmp->sub_category_id  = json_object_get_int(mgt, jo_sub_category_id);
		sign_tmp->sub_category_str = _store_string_oject(mgt, jo_sub_category_str);
		sign_tmp->description_str  = _store_string_oject(mgt, jo_desc);
	}	

	/* cleanup */
	json_object_put(parsed_json);
	munmap(bytes, st.st_size);

	*pmgt = mgt;
	return 0;
}

 void 
 database_close(db_mgt_t* mgt)
{
	if (mgt) {
		free(mgt);
	}
}


