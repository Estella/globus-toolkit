
#if !defined(_GLOBUS_I_GRAM_HTTP_H)
    #define _GLOBUS_I_GRAM_HTTP_H

#ifndef EXTERN_C_BEGIN
#    ifdef __cplusplus
#        define EXTERN_C_BEGIN extern "C" {
#        define EXTERN_C_END }
#    else
#        define EXTERN_C_BEGIN
#        define EXTERN_C_END
#    endif
#endif

EXTERN_C_BEGIN

#include <globus_io.h>

#define GRAM_GOES_HTTP 1
#define GLOBUS_GRAM_HTTP_BUFSIZE     64000

#define GLOBUS_GRAM_HTTP_QUERY_JOB_STATUS      1
#define GLOBUS_GRAM_HTTP_QUERY_JOB_CANCEL      2
#define GLOBUS_GRAM_HTTP_QUERY_JOB_REGISTER    3
#define GLOBUS_GRAM_HTTP_QUERY_JOB_UNREGISTER  4
#define GLOBUS_GRAM_HTTP_QUERY_JOB_START_TIME  5


typedef struct
{
    globus_mutex_t             mutex;
    globus_cond_t              cond;
    volatile globus_bool_t     done;
    volatile int               errorcode;
} globus_gram_http_monitor_t;

typedef void (*globus_gram_http_callback_t)( void  *               arg,
					     globus_io_handle_t *  handle,
					     globus_byte_t *       message,
					     globus_size_t         msgsize,
					     int                   errorcode);


/*
 * part of GRAM_CLIENT activation
 */
int
globus_gram_http_activate();

/*
 * part of GRAM_CLIENT deactivation 
 */
int
globus_gram_http_deactivate();


/*
 * creates a default set of TCP attributes (authentication with self, SSL
 * wrappers around messages)
 */
int
globus_gram_http_setup_attr( globus_io_attr_t *    attr );


/*
 * attaches to URL, returns io handle. If attr==NULL, the default set
 * will be used (see globus_gram_http_setup_attr)
 */
int
globus_gram_http_attach( char *                https_url,
			 globus_io_handle_t *  handle,
			 globus_io_attr_t *    attr );


/* 
 * sets up and registers a listener. returns port and host. user_ptr
 * must contain the read callback to be used. 
 */
int
globus_gram_http_allow_attach( unsigned short *             port,
			       char **                      host,
			       void *                       user_ptr,
			       globus_gram_http_callback_t  user_callback,
			       void *                       user_callback_arg);

/*
 * kills the listener at the specified URL.
 */
int
globus_gram_http_callback_disallow( char *  url );


/*
 * callback that frees the handle after close
 */
void
globus_gram_http_close_callback( void *                arg,
				 globus_io_handle_t *  handle,
				 globus_result_t       result);

/*
 * callback that frees the handle and sendbuf after write
 */
void
globus_gram_http_close_after_write( void *                arg,
				    globus_io_handle_t *  handle,
				    globus_result_t       result,
				    globus_byte_t *       buf,
				    globus_size_t         nbytes);

/*
 * callback to bridge between globus_io_read_callback_t and
 * globus_gram_client_callback_func_t
 */

void
globus_gram_http_client_callback( void *                arg,
				  globus_io_handle_t *  handle,
				  globus_byte_t *       buf,
				  globus_size_t         nbytes,
				  int                   errorcode );

int
globus_gram_http_post( char *                         url,
		       globus_io_attr_t *             attr,
		       globus_byte_t *                message,
		       globus_size_t                  msgsize,
		       globus_gram_http_monitor_t *   monitor);

int
globus_gram_http_post_and_get( char *                         url,
			       globus_io_attr_t *             attr,
			       globus_byte_t *                message,
			       globus_size_t *                msgsize,
			       globus_gram_http_monitor_t *   monitor);


/* Frame a request message with HTTP headers */
int
globus_gram_http_frame_request(globus_byte_t *	  uri,
			       globus_byte_t *	  hostname,
			       globus_byte_t *    msg,
			       globus_size_t	  msgsize,
			       globus_byte_t **   framedmsg,
			       globus_size_t *	  framedsize);

/* Frame a response message with HTTP headers */
int
globus_gram_http_frame_response(int		   code,
				globus_byte_t *    msg,
				globus_size_t      msgsize,
				globus_byte_t **   framedmsg,
				globus_size_t *    framedsize);

/************************ "HTTP" pack/unpack functions *********************/

/* These functions pack and unpack GRAM requests into HTTP format
   There are now no fixed-buffer forms left; the  _alloc forms
   allocate enough memory for their needs return values, memory which
   must be freed by the caller.

   The returned buffers are always null-terminated, so we
   don't even need to worry about the buffer_size returns. 

   --Steve A  7/20/99, 7/22/99
*/

extern
int
globus_i_gram_pack_http_job_request(
    int job_state_mask		/* integer (IN) */,
    const char *callback_url	/* user's state listener URL (IN) */,
    const char *description	/* user's RSL (IN) */,
    globus_byte_t **query_startp /* OUT */,
    globus_size_t *query_sizep	/* OUT; optional (NULL OK) */);

extern
int
globus_i_gram_unpack_http_job_request(
    globus_byte_t *query,	/* IN */
    globus_size_t query_size,	/* IN */
    int *job_state_maskp,	/* OUT */
    globus_byte_t **client_contact_strp,	/* OUT */
    globus_size_t *client_contact_strsizep, /* OUT, optional */
    globus_byte_t **rslp,	/* OUT */
    globus_size_t *rslsizep); /* OUT, optional */


extern
int
globus_i_gram_pack_http_job_request_result(
    int gram_status_code	/* IN */,
    const char *graml_job_contact /* IN */,
    globus_byte_t **reply_startp /* OUT */,
    globus_size_t *reply_sizep	/* OUT, optionally NULL */);




extern
int
globus_i_gram_unpack_http_job_request_result(
    globus_byte_t *query,
    globus_size_t query_size,
    int *result_statusp /* GLOBUS_SUCCESS or a failure */,
    globus_byte_t **result_contactp /* NULL if not SUCCESS */,
    globus_size_t *result_contactsizep);


int
globus_i_gram_http_pack_status_message(
    const char *graml_job_contact /* IN */,
    int status			/* IN */,
    int failure_code		/* IN */,
    globus_byte_t *message	/* OUT */,
    globus_size_t *message_sizep /* OUT */);


EXTERN_C_END

#endif

