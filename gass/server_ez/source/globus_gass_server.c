/******************************************************************************
gassd.c
 
Description:
    Simple File Server Implementation using GASS Server API
 
CVS Information:
 
    $Source$
    $Date$
    $Revision$
    $Author$
******************************************************************************/

/******************************************************************************
                             Include header files
******************************************************************************/
#include "globus_gass_server_ez.h"

#include <stdio.h>
#include <stdlib.h>

extern char *optarg;
extern int optind, opterr, optopt;

static globus_bool_t done = GLOBUS_FALSE;
#define GASSD_DEFAULT_OPTIONS (GLOBUS_GASS_SERVER_EZ_LINE_BUFFER |\
			       GLOBUS_GASS_SERVER_EZ_TILDE_EXPAND |\
			       GLOBUS_GASS_SERVER_EZ_TILDE_USER_EXPAND |\
			       GLOBUS_GASS_SERVER_EZ_READ_ENABLE |\
			       GLOBUS_GASS_SERVER_EZ_WRITE_ENABLE |\
			       GLOBUS_GASS_SERVER_EZ_STDOUT_ENABLE |\
			       GLOBUS_GASS_SERVER_EZ_STDERR_ENABLE)

globus_mutex_t mutex;
globus_cond_t cond;

#if defined(BUILD_LITE)
static int globus_sleepy_callback(globus_time_t time_can_block,
				  void *        user_args)
{
    globus_libc_usleep(10000);

    return GLOBUS_FALSE;
}
#endif


void client_shutdown_callback()
{
    globus_mutex_lock(&mutex);
    done = GLOBUS_TRUE;
    globus_cond_signal(&cond);
    globus_mutex_unlock(&mutex);
}

int main(int argc, char **argv)
{
    unsigned short port = 0U;
    char *url;
    globus_bool_t silent=GLOBUS_FALSE;
    unsigned long default_options=GASSD_DEFAULT_OPTIONS;
    unsigned long options=0UL;
    signed char c;
    int rc;
    
    globus_module_activate(GLOBUS_NEXUS_MODULE);

    globus_mutex_init(&mutex, NULL);
    globus_cond_init(&cond, NULL);
    
    while((c = getopt(argc, argv, "vcp:slturwoen:h")) != EOF)
    {
	switch (c)
	{
	case 'p':
	    port = (unsigned short) atoi(optarg);
	    break;
	case 's':
	    silent = GLOBUS_TRUE;
	    break;
	case 'l':
	    options |= GLOBUS_GASS_SERVER_EZ_LINE_BUFFER;
	    break;
	case 't':
	    options |= GLOBUS_GASS_SERVER_EZ_TILDE_EXPAND;
	    break;
	case 'u':
	    options |= GLOBUS_GASS_SERVER_EZ_TILDE_USER_EXPAND;
	    break;
	case 'r':
	    options |= GLOBUS_GASS_SERVER_EZ_READ_ENABLE;
	    break;
	case 'w':
	    options |= GLOBUS_GASS_SERVER_EZ_WRITE_ENABLE;
	    break;
	case 'o':
	    options |= GLOBUS_GASS_SERVER_EZ_STDOUT_ENABLE;
	    break;
	case 'e':
	    options |= GLOBUS_GASS_SERVER_EZ_STDERR_ENABLE;
	    break;
	case 'c':
	    options |= GLOBUS_GASS_SERVER_EZ_CLIENT_SHUTDOWN_ENABLE;
	    break;
	case 'v':
	    if(GLOBUS_RELEASE_NOT_BETA)
	    {
		globus_libc_printf("Globus Version %d.%d.%d\n"
				   "GASS Protocol Version %d\n",
				   globus_release_major(),
				   globus_release_minor(),
				   globus_release_patch(),
				   GLOBUS_GASS_PROTO_VERSION);
	    }
	    else
	    {
		globus_libc_printf("Globus Version %d.%d.%db%d\n"
				   "GASS Protocol Version %d\n",
				   globus_release_major(),
				   globus_release_minor(),
				   globus_release_patch(),
				   globus_release_beta(),
				   GLOBUS_GASS_PROTO_VERSION);
	    }
	    return 0;
	case 'n':
	    switch(optarg[0])
	    {
	    case 's':
		silent = GLOBUS_FALSE;
		break;
	    case 'l':
		options &= ~GLOBUS_GASS_SERVER_EZ_LINE_BUFFER;
		break;
	    case 't':
		options &= ~GLOBUS_GASS_SERVER_EZ_TILDE_EXPAND;
		break;
	    case 'u':
		options &= ~GLOBUS_GASS_SERVER_EZ_TILDE_USER_EXPAND;
		break;
	    case 'r':
		options &= ~GLOBUS_GASS_SERVER_EZ_READ_ENABLE;
		break;
	    case 'w':
		options &= ~GLOBUS_GASS_SERVER_EZ_WRITE_ENABLE;
		break;
	    case 'o':
		options &= ~GLOBUS_GASS_SERVER_EZ_STDOUT_ENABLE;
		break;
	    case 'e':
		options &= ~GLOBUS_GASS_SERVER_EZ_STDERR_ENABLE;
		break;
	    case 'c':
		options &= ~GLOBUS_GASS_SERVER_EZ_CLIENT_SHUTDOWN_ENABLE;
		break;
	    default:
		globus_libc_printf("Disabling unknown option %s\n", optarg);
	    }
	    break;
	case 'h':
	case '?':
	    globus_libc_printf("usage: %s\n"
		   "\t-p port\t\t\tSpecify port for server\n"
		   "\t-s silent mode\t\tDon't output server URL\n"
		   "\t-l line buffer\t\tLine buffer files when writing\n"
		   "\t-t tilde expand\t\tExpand URLs starting with ~ to $HOME\n"
		   "\t-u user expand\t\tExpand URLs starting with ~user to user's home\n"
		   "\t-r read enable\t\tEnable read access to the local file systems\n"
		   "\t-w write enable\t\tEnable write access to the local file system\n"
		   "\t-c client shutdown\tEnable client to shutdown gassd\n"
		   "\t   enable\n"
		   "\t-o stdout enable\tAllow writes to /dev/stdout\n"
		   "\t-e stderr enable\tAllow writes to /dev/stderr\n"
		   "\t-n [sclturwoe]\t\tDisable the specified option\n", argv[0]);
	    exit(0);
	}
    }
    if(options == 0)
    {
        options = default_options;
    }
    
#   if defined(BUILD_LITE)
    {
        globus_callback_register_periodic(GLOBUS_NULL,
					  0,
					  0,
					  globus_sleepy_callback,
					  GLOBUS_NULL,
					  GLOBUS_NULL,
					  GLOBUS_NULL);
    }
#   endif
    rc = globus_gass_server_ez_init(
	&port,
	&url,
	options,
	options & GLOBUS_GASS_SERVER_EZ_CLIENT_SHUTDOWN_ENABLE
	? client_shutdown_callback
	: (globus_gass_server_ez_client_shutdown_t) GLOBUS_NULL);
    if(rc != GLOBUS_SUCCESS)
    {
	if(port == 0)
	{
	    globus_libc_printf("Error: Cannot listen on port\n");
	    return -1;
	}
	else
	{
	    globus_libc_printf("Error: Failed to initialize gass server library\n");
	}
    }
    if(!silent)
    {
	globus_libc_printf("%s\n",url);
	fflush(stdout);
    }

    /* need to either cond_wait,
       call globus_gass_simple_server_poll() occasionally, or be
       running with threaded globus_nexus to service gass requests
       */
    globus_mutex_lock(&mutex);
    while(!done)
    {
	globus_cond_wait(&cond, &mutex);
    }
    globus_mutex_unlock(&mutex);

    globus_cond_destroy(&cond);
    globus_mutex_destroy(&mutex);
    
    globus_gass_server_ez_shutdown(port);

    globus_module_deactivate(GLOBUS_NEXUS_MODULE);
    return 0;
}

