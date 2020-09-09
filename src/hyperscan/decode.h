#ifndef __DECODE_H__
#define __DECODE_H__


typedef enum http_fields {
	HTTP_FIELD_URL,
	HTTP_FIELD_HOST,
	HTTP_FIELD_ARGS, /* url parameter and  post form */
	HTTP_FIELD_COOKIE,
	HTTP_FILED_REFERER,
	HTTP_FIELD_USER_AGENT,
	HTTP_FIELD_CONTENT_LENGTH
} http_fields_t;



#endif  /* __DECODE_H__ */

