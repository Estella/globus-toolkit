/*
 * globus_ftp_client_modification_time_test.c
 */
#include "globus_ftp_client.h"
#include "globus_ftp_client_test_common.h"

static globus_mutex_t lock;
static globus_cond_t cond;
static globus_bool_t done;
static globus_bool_t error = GLOBUS_FALSE;
#define SIZE 42

static
void
done_cb(
	void *					user_arg,
	globus_ftp_client_handle_t *		handle,
	globus_object_t *			err)
{
    char * tmpstr;

    if(err)
    {
	tmpstr = globus_object_printable_to_string(err);
	printf("%s\n", tmpstr); 
        error = GLOBUS_TRUE;
	globus_libc_free(tmpstr);
    }
    globus_mutex_lock(&lock);
    done = GLOBUS_TRUE;
    globus_cond_signal(&cond);
    globus_mutex_unlock(&lock);
       
}

int main(int argc,
	 char *argv[])
{
    globus_ftp_client_handle_t			handle;
    globus_ftp_client_operationattr_t 		attr;
    globus_ftp_client_handleattr_t		handle_attr;
    globus_byte_t				buffer[SIZE];
    globus_size_t				buffer_length = sizeof(buffer);
    globus_result_t				result;
    globus_abstime_t				modification_time;
    time_t					t;
    struct tm *					tm;
    char *					src;
    char *					dst;

    globus_module_activate(GLOBUS_FTP_CLIENT_MODULE);
    globus_ftp_client_handleattr_init(&handle_attr);
    globus_ftp_client_operationattr_init(&attr);
    
    test_parse_args(argc, 
		    argv,
		    &handle_attr,
		    &attr,
		    &src,
		    &dst);

    globus_mutex_init(&lock, GLOBUS_NULL);
    globus_cond_init(&cond, GLOBUS_NULL);

    globus_ftp_client_handle_init(&handle, &handle_attr);

    done = GLOBUS_FALSE;
    result = globus_ftp_client_modification_time(&handle,
				   src,
				   &attr,
				   &modification_time,
				   done_cb,
				   0);
    if(result != GLOBUS_SUCCESS)
    {
	fprintf(stderr, globus_object_printable_to_string(globus_error_get(result)));
	error = GLOBUS_TRUE;
	done = GLOBUS_TRUE;
    }
    globus_mutex_lock(&lock);
    while(!done)
    {
	globus_cond_wait(&cond, &lock);
    }
    globus_mutex_unlock(&lock);

    globus_ftp_client_handle_destroy(&handle);

    globus_module_deactivate_all();

    if(test_abort_count && error)
    {
	return 0;
    }
    if(error == GLOBUS_SUCCESS)
    {
	/* Convert timestamp to UTC */
	t = (time_t) modification_time.tv_sec - timezone;

	printf("Last modified %s",  ctime(&t));
    }
    return error;
}
