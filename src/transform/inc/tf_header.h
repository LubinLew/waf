/* 
 * web transform library
 * Copyright (c) LubinLew
 *
*/
#ifndef __TF_HEADER_H__
#define __TF_HEADER_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/*-----------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint8_t* 
ts_delete_space(uint8_t *data, size_t *len);

uint8_t* 
ts_compress_space(uint8_t *data, size_t *len);


uint8_t* 
tf_remove_comment(uint8_t* data, size_t* len);


uint8_t* 
tf_url_decode(uint8_t *data, size_t *len);

uint8_t* 
tf_html_entity_decode(uint8_t* data, size_t* len);

uint8_t* 
tf_js_decode(uint8_t* data, size_t* len);

uint8_t* 
tf_css_decode(uint8_t* data, size_t* len);



uint8_t* 
tf_base64_decode(uint8_t *data, size_t *len);

uint8_t* 
tf_base64url_decode(uint8_t *data, size_t *len);

/*-----------------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TF_HEADER_H__ */

