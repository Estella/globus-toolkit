/******************************************************************************
globus_thread_windows.c

Description:

  Bindings for the Globus threads package, to be used when Globus has been
  configured to use Windows.

CVS Information:

  $Source: 
  $Date: 
  $Revision: 
  $State: 
  $Author: Michael Lebman
******************************************************************************/

#include "globus_common.h"
#include "globus_i_thread.h"
//#include "globus_time.h"


// Global data
globus_list_t * internalThreadList= GLOBUS_NULL;

/******************************************************************************
                              Module definition
******************************************************************************/

/*
 * globus_i_thread_pre_activate()
 *
 * Since globus_module depends on threads and globus_thread depends on
 * globus_module, we need this bootstrapping function.
 * 
 */
int globus_i_thread_pre_activate(void)
{
    globus_mutex_init( &globus_libc_mutex, NULL );

    return 1;
}

/*
 * globus_l_thread_activate()
 */
static int globus_l_thread_activate(void)
{
    return globus_module_activate(GLOBUS_THREAD_COMMON_MODULE);
}
/* globus_l_thread_activate() */


/*
 * globus_l_thread_deactivate()
 */
static int globus_l_thread_deactivate(void)
{
	// This could be nasty, but we should probably destroy the list
	// of thread objects and maybe even call the destructor functions
	// for any TLS
	// TODO

    return globus_module_deactivate(GLOBUS_THREAD_COMMON_MODULE);
}
/* globus_l_thread_deactivate() */

globus_module_descriptor_t globus_i_thread_module =
{
    "globus_thread",
    globus_l_thread_activate,
    globus_l_thread_deactivate,
    GLOBUS_NULL,
    GLOBUS_NULL
};


/* THREAD FUNCTIONS */

int globus_l_thread_ithread_matches( void * current_ithread, 
	void * targetThreadID )
{
	// validate parameters
	if ( current_ithread == NULL || targetThreadID == NULL )
		return 0;

	// the current_ithread is of type globus_i_thread_t
	// the targetThreadID is of type unsigned long
	if ( ((globus_i_thread_t *)current_ithread)->threadID == 
		(* (unsigned long *)targetThreadID ) )
		return 1;

	return 0;
}

unsigned int __stdcall UserFunctionLauncher( void * arg )
{
	globus_i_thread_t * internalThread;
	globus_list_t * subList;
	TLS_DataDestructionInfo * dataDestructionInfo;

	internalThread= (globus_i_thread_t *)arg;

	// call the user function
	(*internalThread->userFunctionInfo.userFunction)(
	 internalThread->userFunctionInfo.userArg );

	// call the TLS destructors
	while ( !globus_list_empty( 
	 internalThread->dataDestructionInfoList ) )
	{
		// get the first item in the list
		dataDestructionInfo= (TLS_DataDestructionInfo *)
		 globus_list_first( internalThread->dataDestructionInfoList );

		// call the destructor function
		(*dataDestructionInfo->destructorFunction)( 
		 dataDestructionInfo->TLS_Data );

		// remove the item from the list
		globus_list_remove( &internalThread->dataDestructionInfoList,
		 internalThread->dataDestructionInfoList );

		// deallocate it
		free( dataDestructionInfo );
	}

	// remove the internal thread object from the global list
	subList= globus_list_search_pred( internalThreadList,
	 globus_l_thread_ithread_matches, &internalThread->threadID );
	globus_list_remove( &internalThreadList, subList ); 

	// delete the internal thread object associated with this thread
	free( internalThread );

	return 0;
}


/*
 * globus_thread_create
 */
int globus_thread_create( 
	globus_thread_t * thread,
    globus_threadattr_t *attr, 
	globus_thread_func_t func,
	void * user_arg )
{
	unsigned long threadHandle;
	unsigned long threadID;
	globus_i_thread_t * internalThread;

	/* validate the data */
	//if ( thread == NULL || func == NULL )
		//return GLOBUS_NULL_POINTER_PARAMETER;
	if ( func == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	// block all other threads
	if ( globus_libc_lock() != 0 )
		return GLOBUS_FAILURE;

	// create an internal thread object
	internalThread= (globus_i_thread_t *)malloc( 
	 sizeof(globus_i_thread_t) );
	if ( internalThread == NULL )
		return GLOBUS_FAILURE;
	// initialize it
	internalThread->userFunctionInfo.userFunction= func;
	internalThread->userFunctionInfo.userArg= user_arg;
	internalThread->dataDestructionInfoList= GLOBUS_NULL;

	/* call _beginthreadex to create the thread */
	threadHandle= _beginthreadex( NULL, 0, 
	 UserFunctionLauncher, internalThread, 0, 
	 (unsigned *)&threadID );

	if ( threadHandle == 0 )
	{
		free( internalThread );
		if ( thread != NULL )
			thread->threadID= 0;

		globus_libc_unlock();

		/* how should we report the error- just return an error code?
		 *  log it? FOR NOW- just return the errno
		 */
		return errno;
	}

	// while we still have a pointer to the internal thread, set the
	// thread ID
	internalThread->threadID= threadID;

	// add the internal thread to the list of internal threads
	globus_list_insert( &internalThreadList, internalThread );

	/* we have to close the handle, otherwise a memory leak will occur */
	CloseHandle( (HANDLE)threadHandle );

	// if the user passed in a globus thread object, store the
	// thread ID in it
	if ( thread != NULL )
	{
		thread->threadID= threadID;
	}

	globus_libc_unlock();
	return 0;
}

/*
 * globus_thread_exit()
 */
/* NOTE: Windows does not support the return of the exit code to the 
 *  calling thread and consequently it will not be able to support
 *  the status parameter unless we supply an enormous hack
 */
void globus_thread_exit( void * status )
{
	_endthreadex( 0 );
} /* globus_thread_exit() */


/*
 * globus_thread_yield
 */
void globus_thread_yield(void)
{
	Sleep(0);
} /* globus_thread_yield() */


/*
 * globus_i_am_only_thread()
 */
globus_bool_t globus_i_am_only_thread(void)
{
	return GLOBUS_FALSE;
}
 
/*
 * globus_thread_self()
 */
/* QUESTION: Should we dynamically create a globus_thread_t so that it can live past the
 *  return, or should we just create a struct on the stack? In order to protect against
 *  memory leaks, I suggest that we create it on the stack and insist that the user make
 *  a copy upon the immediate return from the call.  Michael Lebman, 2-4-02
*/
globus_thread_t globus_thread_self(void)
{
	globus_thread_t thread;
	thread.threadID= GetCurrentThreadId();
	return thread;
} /* globus_thread_self() */

long globus_thread_get_threadID_as_long( void )
{
	return GetCurrentThreadId();
}

/*
 * globus_thread_equal()
 */
int globus_thread_equal(
	globus_thread_t t1,
	globus_thread_t t2 )
{
	if ( t1.threadID == t2.threadID )
		return 1;
	return 0;
} /* globus_thread_equal() */


/*
 * globus_thread_once()
 */
int globus_thread_once(
	globus_thread_once_t *once_control,
	void (*init_routine)(void) )
{
	/* validate the data */
	if ( once_control == NULL || init_routine == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	// block all other threads
	if ( globus_libc_lock() != 0 )
		return GLOBUS_FAILURE;

	// check the once control
	if ( *once_control == GLOBUS_THREAD_ONCE_CALLED )
	{
		globus_libc_unlock();
		return GLOBUS_FAILURE;
	}

	// call the initialization routine
	init_routine();

	// set the once control
	*once_control= GLOBUS_THREAD_ONCE_CALLED;

	// unblock
	globus_libc_unlock();

	return GLOBUS_SUCCESS;
} /* globus_thread_once() */


/* THREAD LOCAL STORAGE FUNCTIONS */

/*
 * globus_thread_key_create()
 */
int globus_thread_key_create(
	globus_thread_key_t *key,
	globus_thread_key_destructor_func_t destructor_func )
{
	/* validate the data */
	if ( key == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	key->TLSIndex = TlsAlloc();
	if ( key->TLSIndex == TLS_OUT_OF_INDEXES )
	{
		key->destructorFunction= NULL;
		return -1; /* per the documentation on our website */
	}

	// insert the destructor function pointer into the key so
	// it will be available when the user calls 
	// globus_thread_setspecific()
	key->destructorFunction= destructor_func;

	return GLOBUS_SUCCESS;
} /* globus_thread_key_create() */


/*
 * globus_thread_key_delete()
 */
/* WARNING! This function should never be called unless the key was created by a DLL
 *  that is detaching from the process
 */
int globus_thread_key_delete(globus_thread_key_t key)
{
    int rc;
	
	rc= TlsFree( key.TLSIndex );
	
	// reset the data so that it appears to be invalid
	key.TLSIndex= TLS_OUT_OF_INDEXES;
	key.destructorFunction= NULL;

	if ( rc == 0 ) /* operation failed */
		return GLOBUS_FAILURE;

	return GLOBUS_SUCCESS;
} /* globus_thread_key_delete() */


/*
 * globus_thread_setspecific()
 */
int globus_thread_setspecific(
	globus_thread_key_t key,
	void *value )
{
	int rc;
	TLS_DataDestructionInfo * dataDestructionInfo;
	unsigned long threadID;
	globus_list_t * subList;
	globus_i_thread_t * internalThread;

	/* validate the data */
	if ( value == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	rc = TlsSetValue(key.TLSIndex, value);
	if ( rc == 0 ) /* operation failed */
		return GLOBUS_FAILURE;

	// get the current thread ID
	threadID= GetCurrentThreadId();

	if ( key.destructorFunction == NULL ) // nothin' to store
		return GLOBUS_SUCCESS;

	// create a data destruction info object
	dataDestructionInfo= (TLS_DataDestructionInfo* )
	 malloc( sizeof(TLS_DataDestructionInfo) );
	if ( dataDestructionInfo == NULL )
		return GLOBUS_FAILURE;

	// store the data in the destruction object
	dataDestructionInfo->destructorFunction= key.destructorFunction;
	dataDestructionInfo->TLS_Data= value;

	// find the thread object associated with the current thread
	// get the internal thread object associated with this thread
	subList= globus_list_search_pred( internalThreadList,
	 globus_l_thread_ithread_matches, &threadID );
	internalThread= (globus_i_thread_t *)
		globus_list_first( subList );

	// store the data destruction object in the internal thread object
	globus_list_insert( &internalThread->dataDestructionInfoList, 
	 dataDestructionInfo );

	return GLOBUS_SUCCESS;
} /* globus_thread_setspecific() */


/*
 * globus_thread_getspecific()
 */
void * globus_thread_getspecific(globus_thread_key_t key)
{
	return TlsGetValue(key.TLSIndex);
} /* globus_thread_getspecific() */


/* MUTEX FUNCTIONS */

/*
 * globus_mutexattr_init()
 */
int globus_mutexattr_init(globus_mutexattr_t *attr)
{
	/* validate the data */
	if ( attr == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;
	
	attr->securityAttributes= NULL; /* for now */
	return GLOBUS_SUCCESS;
}

/*
 * globus_mutexattr_destroy()
 */
int globus_mutexattr_destroy(globus_mutexattr_t *attr)
{
	/* validate the data */
	if ( attr == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	return GLOBUS_SUCCESS;
}

/*
 * globus_mutex_init()
 */
int globus_mutex_init(globus_mutex_t *mut, globus_mutexattr_t *attr)
{
	/* validate the data */
	//if ( mut == NULL || attr == NULL )
	if ( mut == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	if ( attr == NULL )
		*mut= CreateMutex( NULL, FALSE, NULL );
	else
		*mut= CreateMutex( attr->securityAttributes, FALSE, NULL );
	if ( *mut == NULL )
		return GLOBUS_FAILURE;

	return GLOBUS_SUCCESS;
} /* globus_mutex_init() */


/*
 *  globus_mutex_destroy()
 */
int globus_mutex_destroy(globus_mutex_t *mut)
{
	int rc; 

	/* validate the data */
	if ( mut == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	rc= CloseHandle( *mut );
	if ( rc == 0 )
		return GLOBUS_FAILURE;

	return GLOBUS_SUCCESS;
} /* globus_mutex_destroy() */


/* 
 *  globus_mutex_lock()
 */
int globus_mutex_lock(globus_mutex_t *mut)
{
    int rc;

	/* validate the data */
	if ( mut == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	rc= WaitForSingleObject( *mut, INFINITE );
	if ( rc == WAIT_ABANDONED )
		return GLOBUS_SUCCESS;
	//if ( rc != WAIT_OBJECT_0 )
	if ( rc == WAIT_FAILED )
	{
		int error= GetLastError();
		fprintf( stderr, "globus_mutex_lock() failed; errno is %d\n", error );
		return GLOBUS_FAILURE;
	}

	return GLOBUS_SUCCESS;
} /* globus_mutex_lock() */


/* 
 *  globus_mutex_trylock()
 */
int globus_mutex_trylock(globus_mutex_t *mut)
{
    int rc;

	/* validate the data */
	if ( mut == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	rc= WaitForSingleObject( *mut, 0 );
	if ( rc != WAIT_OBJECT_0 )
		return GLOBUS_FAILURE;

	return GLOBUS_SUCCESS;
} /* globus_mutex_trylock() */


/*
 *  globus_mutex_unlock()
 */
int globus_mutex_unlock(globus_mutex_t *mut)
{
    int rc;

	/* validate the data */
	if ( mut == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	rc= ReleaseMutex( *mut );
	if ( rc == 0 )
		return GLOBUS_FAILURE;

	return GLOBUS_SUCCESS;

} /* globus_mutex_unlock() */


/* CONDITION VARIABLE FUNCTIONS */

/*
 * globus_condattr_init()
 */
int globus_condattr_init(globus_condattr_t *attr)
{
	/* validate the data */
	if ( attr == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;
	
	attr->securityAttributes= NULL; /* for now */
	return GLOBUS_SUCCESS;
}

/*
 * globus_condattr_destroy()
 */
int globus_condattr_destroy(globus_condattr_t *attr)
{
	/* validate the data */
	if ( attr == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;
	
	return GLOBUS_SUCCESS;
}

/*
 * globus_cond_init()
 */
int globus_cond_init(
	globus_cond_t *cv,
	globus_condattr_t *attr)
{
	/* validate the data */
	//if ( cv == NULL || attr == NULL )
	if ( cv == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	if ( attr == NULL )
		cv->events[SINGLE_NOTIFICATION_EVENT]= CreateEvent( NULL, FALSE, FALSE, NULL );
	else
		cv->events[SINGLE_NOTIFICATION_EVENT]= CreateEvent( attr->securityAttributes, FALSE, FALSE, NULL );
	if ( cv->events[SINGLE_NOTIFICATION_EVENT] == NULL )
		return GLOBUS_FAILURE;
	if ( attr == NULL )
		cv->events[BROADCAST_EVENT]= CreateEvent( NULL, TRUE, FALSE, NULL );
	else
		cv->events[BROADCAST_EVENT]= CreateEvent( attr->securityAttributes, TRUE, FALSE, NULL );
	if ( cv->events[BROADCAST_EVENT] == NULL )
		return GLOBUS_FAILURE;
	cv->numberOfWaiters= 0;

	return GLOBUS_SUCCESS;
} /* globus_cond_init() */


/*
 *  globus_cond_destroy()
 */
int globus_cond_destroy(globus_cond_t *cv)
{
    int rc; 

	/* validate the data */
	if ( cv == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	rc= CloseHandle( cv->events[SINGLE_NOTIFICATION_EVENT] );
	if ( rc == 0 )
		return GLOBUS_FAILURE;

	rc= CloseHandle( cv->events[BROADCAST_EVENT] );
	if ( rc == 0 )
		return GLOBUS_FAILURE;

	return GLOBUS_SUCCESS;
} /* globus_cond_destroy() */


/*
 *  globus_cond_wait()
 */
int globus_cond_wait(
	globus_cond_t *cv,
	globus_mutex_t *mut)
{
	//globus_abstime_t abstime= { INFINITE, INFINITE };
	return globus_cond_timedwait_rel( cv, mut, INFINITE );
} /* globus_cond_wait() */

/*
 *  globus_cond_timedwait()
 */
/*	UNIX uses absolute time stamps for its condition wait functionality, while
 *   Windows uses relative time. To accommodate this difference, the absolute
 *   time will be converted to relative time and the function mapped to a new
 *   function, globus_cond_timedwait_rel()	
 */
int globus_cond_timedwait(
	globus_cond_t *cv, 
	globus_mutex_t *mut,
	globus_abstime_t *abstime )
{
	long milliseconds;

	/* validate the data */
	if ( cv == NULL || mut == NULL || abstime == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	/* if the number of seconds is not "INFINITE" (0xFFFFFFFF)*/
	/* convert the absolute time in seconds and nanoseconds to the number of
	 *  milliseconds from now when the specified absolute time will occur
	 */
	milliseconds= abstime->tv_sec;
	if ( milliseconds != INFINITE )
	{
		globus_abstime_t now;
		globus_reltime_t relativeTime;
		// get the time now
		GlobusTimeAbstimeGetCurrent( now ); /* #define'd in globus_time.h */
		// get the difference between the time specified and now
		GlobusTimeAbstimeDiff( relativeTime, *abstime, now ); /* #define'd in globus_time.h */
		// convert the difference to milliseconds
		GlobusTimeReltimeToMilliSec( milliseconds, relativeTime ); /* #define'd in globus_time.h */
	}
	return globus_cond_timedwait_rel( cv, mut, milliseconds );
}

int globus_cond_timedwait_rel(
	globus_cond_t *cv, 
	globus_mutex_t *mut,
	long milliseconds )
{
    DWORD rc;

	/* validate the data */
	if ( cv == NULL || mut == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	/* increment the waiter count; if the broadcast event is signaled we will use 
	 * this count to determine when to reset the event
	 */
	cv->numberOfWaiters++;

	/* release the mutex */
	/* ordinarily, we would check the return value, but because the user expects that
	 * the mutex will be locked when this function returns, we should not bail before
	 * attempting to reacquire the mutex
	 */
	globus_mutex_unlock( mut );

	/* wait on the events */
	/* don't check for errors before reacquiring the mutex */
	/* rc= WaitForMultipleObjects( 2, cv->events, FALSE, abstime->tv_sec); */
	rc= WaitForMultipleObjects( 2, cv->events, FALSE, milliseconds );

	/* reacquire the mutex */
	if ( globus_mutex_lock( mut ) == GLOBUS_FAILURE )
		return GLOBUS_FAILURE;

	/* decrement the waiter count */
	/* check to make sure the wait returned successfully before changing the waiter count */
	if ( rc == WAIT_OBJECT_0 || rc == WAIT_OBJECT_0 + 1 )
		cv->numberOfWaiters--;

	/* determine whether the event signaled was the broadcast event */
	if ( rc - WAIT_OBJECT_0 == BROADCAST_EVENT ) 
	{
		if ( cv->numberOfWaiters == 0 )
			rc= ResetEvent( cv->events[BROADCAST_EVENT] ); 
	}

	return GLOBUS_SUCCESS;
} /* globus_cond_timedwait() */

/*
 *  globus_cond_signal()
 */
int globus_cond_signal(globus_cond_t *cv)
{
	int rc;

	/* validate the data */
	if ( cv == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	rc= SetEvent( cv->events[SINGLE_NOTIFICATION_EVENT] );
	if ( rc == 0 )
		return GLOBUS_FAILURE;

	return GLOBUS_SUCCESS;
} /* globus_cond_signal () */


/*
 *  globus_cond_broadcast()
 */
int globus_cond_broadcast(globus_cond_t *cv)
{
	int rc;

	/* validate the data */
	if ( cv == NULL )
		return GLOBUS_NULL_POINTER_PARAMETER;

	rc= SetEvent( cv->events[BROADCAST_EVENT] );
	if ( rc == 0 )
		return GLOBUS_FAILURE;

	return GLOBUS_SUCCESS;
} /* globus_cond_broadcast() */

