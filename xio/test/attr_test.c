#include "globus_xio.h"
#include "globus_common.h"
#include "test_common.h"
#include "globus_xio_test_transport.h"


int
attr_main(
    int                                     argc,
    char **                                 argv)
{
    int                                     rc;
    globus_xio_stack_t                      stack;
    globus_xio_target_t                     target;
    globus_result_t                         res;
    globus_xio_attr_t                       attr;
    globus_xio_attr_t                       cp_attr;
    globus_xio_driver_t                     test_driver;
    globus_xio_driver_t                     debug_driver;
    globus_xio_handle_t                     handle;
    globus_byte_t *                         buffer;
    globus_size_t                           len = 1024;

    rc = globus_module_activate(GLOBUS_XIO_MODULE);
    globus_assert(rc == 0);

    buffer = globus_malloc(len);

    /*
     *  init a bunch of structures
     */
    res = globus_xio_driver_load("test", &test_driver);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);

    res = globus_xio_driver_load("debug", &debug_driver);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);

    res = globus_xio_attr_init(NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }
    res = globus_xio_stack_init(NULL, NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }
    res = globus_xio_target_init(NULL, NULL, "whatever", NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }
    res = globus_xio_target_init(&target, NULL, "whatever", NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }
    
    res = globus_xio_attr_init(&attr);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);

    res = globus_xio_stack_init(&stack, NULL);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);

    res = globus_xio_target_init(&target, NULL, "whatever", stack);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("target_init() should have failed. empty stack\n");
    }

    res = globus_xio_stack_push_driver(stack, debug_driver);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("stack_push() should have failed. transform\n");
    }

    res = globus_xio_stack_push_driver(stack, test_driver);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);

    res = globus_xio_stack_push_driver(stack, test_driver);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("stack_push() should have failed. transport twice\n");
    }

    res = globus_xio_stack_push_driver(stack, debug_driver);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);

    res = globus_xio_target_init(&target, NULL, "whatever", stack);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);
    res = globus_xio_target_destroy(target);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);
    res = globus_xio_target_init(&target, NULL, "whatever", stack);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);
    /*
     *  do some operations
     */
    res = globus_xio_attr_copy(&cp_attr, attr);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);

    /*
     *  destroy the structures
     */
    res = globus_xio_attr_cntl(NULL, NULL, 0);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }

    res = globus_xio_attr_copy(&cp_attr, NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }

    res = globus_xio_attr_copy(NULL, attr);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }

    res = globus_xio_attr_copy(NULL, NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }

    res = globus_xio_attr_destroy(NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }

    res = globus_xio_target_destroy(NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }

    res = globus_xio_stack_destroy(NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }

    /*
     *  use things before they are destroyed 
     */
    res = globus_xio_open(NULL, NULL, NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }

    res = globus_xio_open(NULL, NULL, target);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }

    res = globus_xio_open(&handle, NULL, NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }

    res = globus_xio_open(&handle, NULL, target);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);

    /* reads */
    res = globus_xio_read(NULL, NULL, -1, 0, NULL, NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }
    res = globus_xio_read(NULL, globus_l_test_info.buffer, -1, 0, NULL, NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }
    res = globus_xio_read(NULL, buffer, 1, 0, NULL, NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }
    res = globus_xio_read(handle, buffer, 
            len, 0, NULL, NULL);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);

    /* writes */
    res = globus_xio_write(NULL, NULL, -1, 0, NULL, NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }
    res = globus_xio_write(NULL, buffer, -1, 0, NULL, NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }
    res = globus_xio_write(NULL, buffer, 1, 0, NULL, NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }
    res = globus_xio_write(handle, buffer,
            len, 0, NULL, NULL);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);

    res = globus_xio_close(NULL, NULL);
    if(res == GLOBUS_SUCCESS)
    {
        failed_exit("bad parameter init() should have failed.\n");
    }

    res = globus_xio_close(handle, NULL);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);

    globus_free(buffer);

    res = globus_xio_attr_destroy(attr);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);
    res = globus_xio_stack_destroy(stack);
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);

    res = globus_xio_driver_unload(debug_driver); 
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);
    res = globus_xio_driver_unload(test_driver); 
    test_res(GLOBUS_XIO_TEST_FAIL_NONE, res, __LINE__);

    rc = globus_module_deactivate(GLOBUS_XIO_MODULE);
    globus_assert(rc == 0);

    fprintf(stdout, "Success.\n");

    return 0;
}
