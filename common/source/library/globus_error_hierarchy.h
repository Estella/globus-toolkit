
#ifndef GLOBUS_ERROR_HIERARCHY_H
#define GLOBUS_ERROR_HIERARCHY_H


#include "globus_common.h"

#include "globus_object.h"
#include "globus_error.h"

#ifndef EXTERN_C_BEGIN
#ifdef __cplusplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#endif
#endif
 
EXTERN_C_BEGIN

/* the following code all generated by running the script
 * ./globus_error_hierarchy.h.sh declarations < globus_error_hierarchy.idl
 */

extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_NO_AUTHENTICATION_DEFINITION;

#define GLOBUS_ERROR_TYPE_NO_AUTHENTICATION \
        (&GLOBUS_ERROR_TYPE_NO_AUTHENTICATION_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_NO_AUTHENTICATION   */
extern globus_object_t *
globus_error_construct_no_authentication (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_NO_AUTHENTICATION   */
extern globus_object_t *
globus_error_initialize_no_authentication (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_NO_CREDENTIALS_DEFINITION;

#define GLOBUS_ERROR_TYPE_NO_CREDENTIALS \
        (&GLOBUS_ERROR_TYPE_NO_CREDENTIALS_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_NO_CREDENTIALS   */
extern globus_object_t *
globus_error_construct_no_credentials (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * no_credentials_file);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_NO_CREDENTIALS   */
extern globus_object_t *
globus_error_initialize_no_credentials (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * no_credentials_file);

/* return the no_credentials_file instance data of an error
 * derived from GLOBUS_ERROR_TYPE_NO_CREDENTIALS   */
extern globus_object_t *
globus_error_no_credentials_get_no_credentials_file (globus_object_t * error)
;

/* set the no_credentials_file instance data of an error
 * derived from GLOBUS_ERROR_TYPE_NO_CREDENTIALS   */
extern void
globus_error_no_credentials_set_no_credentials_file (
    globus_object_t * error,
    globus_object_t * value)
;


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_NO_TRUST_DEFINITION;

#define GLOBUS_ERROR_TYPE_NO_TRUST \
        (&GLOBUS_ERROR_TYPE_NO_TRUST_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_NO_TRUST   */
extern globus_object_t *
globus_error_construct_no_trust (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * no_trust_truster,
    globus_object_t * no_trust_trustee);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_NO_TRUST   */
extern globus_object_t *
globus_error_initialize_no_trust (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * no_trust_truster,
    globus_object_t * no_trust_trustee);

/* return the no_trust_truster instance data of an error
 * derived from GLOBUS_ERROR_TYPE_NO_TRUST   */
extern globus_object_t *
globus_error_no_trust_get_no_trust_truster (globus_object_t * error)
;

/* set the no_trust_truster instance data of an error
 * derived from GLOBUS_ERROR_TYPE_NO_TRUST   */
extern void
globus_error_no_trust_set_no_trust_truster (
    globus_object_t * error,
    globus_object_t * value)
;

/* return the no_trust_trustee instance data of an error
 * derived from GLOBUS_ERROR_TYPE_NO_TRUST   */
extern globus_object_t *
globus_error_no_trust_get_no_trust_trustee (globus_object_t * error)
;

/* set the no_trust_trustee instance data of an error
 * derived from GLOBUS_ERROR_TYPE_NO_TRUST   */
extern void
globus_error_no_trust_set_no_trust_trustee (
    globus_object_t * error,
    globus_object_t * value)
;


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_INVALID_CREDENTIALS_DEFINITION;

#define GLOBUS_ERROR_TYPE_INVALID_CREDENTIALS \
        (&GLOBUS_ERROR_TYPE_INVALID_CREDENTIALS_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_INVALID_CREDENTIALS   */
extern globus_object_t *
globus_error_construct_invalid_credentials (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * invalid_credentials_start_time,
    globus_object_t * invalid_credentials_end_time,
    globus_object_t * invalid_credentials_attempt_time);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_INVALID_CREDENTIALS   */
extern globus_object_t *
globus_error_initialize_invalid_credentials (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * invalid_credentials_start_time,
    globus_object_t * invalid_credentials_end_time,
    globus_object_t * invalid_credentials_attempt_time);

/* return the invalid_credentials_start_time instance data of an error
 * derived from GLOBUS_ERROR_TYPE_INVALID_CREDENTIALS   */
extern globus_object_t *
globus_error_invalid_credentials_get_invalid_credentials_start_time (globus_object_t * error)
;

/* set the invalid_credentials_start_time instance data of an error
 * derived from GLOBUS_ERROR_TYPE_INVALID_CREDENTIALS   */
extern void
globus_error_invalid_credentials_set_invalid_credentials_start_time (
    globus_object_t * error,
    globus_object_t * value)
;

/* return the invalid_credentials_end_time instance data of an error
 * derived from GLOBUS_ERROR_TYPE_INVALID_CREDENTIALS   */
extern globus_object_t *
globus_error_invalid_credentials_get_invalid_credentials_end_time (globus_object_t * error)
;

/* set the invalid_credentials_end_time instance data of an error
 * derived from GLOBUS_ERROR_TYPE_INVALID_CREDENTIALS   */
extern void
globus_error_invalid_credentials_set_invalid_credentials_end_time (
    globus_object_t * error,
    globus_object_t * value)
;

/* return the invalid_credentials_attempt_time instance data of an error
 * derived from GLOBUS_ERROR_TYPE_INVALID_CREDENTIALS   */
extern globus_object_t *
globus_error_invalid_credentials_get_invalid_credentials_attempt_time (globus_object_t * error)
;

/* set the invalid_credentials_attempt_time instance data of an error
 * derived from GLOBUS_ERROR_TYPE_INVALID_CREDENTIALS   */
extern void
globus_error_invalid_credentials_set_invalid_credentials_attempt_time (
    globus_object_t * error,
    globus_object_t * value)
;


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_ACCESS_FAILED_DEFINITION;

#define GLOBUS_ERROR_TYPE_ACCESS_FAILED \
        (&GLOBUS_ERROR_TYPE_ACCESS_FAILED_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_ACCESS_FAILED   */
extern globus_object_t *
globus_error_construct_access_failed (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * access_failed_resource,
    globus_object_t * access_failed_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_ACCESS_FAILED   */
extern globus_object_t *
globus_error_initialize_access_failed (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * access_failed_resource,
    globus_object_t * access_failed_operation);

/* return the access_failed_resource instance data of an error
 * derived from GLOBUS_ERROR_TYPE_ACCESS_FAILED   */
extern globus_object_t *
globus_error_access_failed_get_access_failed_resource (globus_object_t * error)
;

/* set the access_failed_resource instance data of an error
 * derived from GLOBUS_ERROR_TYPE_ACCESS_FAILED   */
extern void
globus_error_access_failed_set_access_failed_resource (
    globus_object_t * error,
    globus_object_t * value)
;

/* return the access_failed_operation instance data of an error
 * derived from GLOBUS_ERROR_TYPE_ACCESS_FAILED   */
extern globus_object_t *
globus_error_access_failed_get_access_failed_operation (globus_object_t * error)
;

/* set the access_failed_operation instance data of an error
 * derived from GLOBUS_ERROR_TYPE_ACCESS_FAILED   */
extern void
globus_error_access_failed_set_access_failed_operation (
    globus_object_t * error,
    globus_object_t * value)
;


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_NO_AUTHORIZATION_DEFINITION;

#define GLOBUS_ERROR_TYPE_NO_AUTHORIZATION \
        (&GLOBUS_ERROR_TYPE_NO_AUTHORIZATION_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_NO_AUTHORIZATION   */
extern globus_object_t *
globus_error_construct_no_authorization (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * access_failed_resource,
    globus_object_t * access_failed_operation,
    globus_object_t * no_authorization_identity);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_NO_AUTHORIZATION   */
extern globus_object_t *
globus_error_initialize_no_authorization (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * access_failed_resource,
    globus_object_t * access_failed_operation,
    globus_object_t * no_authorization_identity);

/* return the no_authorization_identity instance data of an error
 * derived from GLOBUS_ERROR_TYPE_NO_AUTHORIZATION   */
extern globus_object_t *
globus_error_no_authorization_get_no_authorization_identity (globus_object_t * error)
;

/* set the no_authorization_identity instance data of an error
 * derived from GLOBUS_ERROR_TYPE_NO_AUTHORIZATION   */
extern void
globus_error_no_authorization_set_no_authorization_identity (
    globus_object_t * error,
    globus_object_t * value)
;


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_NOT_AVAILABLE_DEFINITION;

#define GLOBUS_ERROR_TYPE_NOT_AVAILABLE \
        (&GLOBUS_ERROR_TYPE_NOT_AVAILABLE_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_NOT_AVAILABLE   */
extern globus_object_t *
globus_error_construct_not_available (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * access_failed_resource,
    globus_object_t * access_failed_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_NOT_AVAILABLE   */
extern globus_object_t *
globus_error_initialize_not_available (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * access_failed_resource,
    globus_object_t * access_failed_operation);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_DEPLETED_DEFINITION;

#define GLOBUS_ERROR_TYPE_DEPLETED \
        (&GLOBUS_ERROR_TYPE_DEPLETED_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_DEPLETED   */
extern globus_object_t *
globus_error_construct_depleted (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * access_failed_resource,
    globus_object_t * access_failed_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_DEPLETED   */
extern globus_object_t *
globus_error_initialize_depleted (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * access_failed_resource,
    globus_object_t * access_failed_operation);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_QUOTA_DEPLETED_DEFINITION;

#define GLOBUS_ERROR_TYPE_QUOTA_DEPLETED \
        (&GLOBUS_ERROR_TYPE_QUOTA_DEPLETED_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_QUOTA_DEPLETED   */
extern globus_object_t *
globus_error_construct_quota_depleted (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * access_failed_resource,
    globus_object_t * access_failed_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_QUOTA_DEPLETED   */
extern globus_object_t *
globus_error_initialize_quota_depleted (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * access_failed_resource,
    globus_object_t * access_failed_operation);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_OFFLINE_DEFINITION;

#define GLOBUS_ERROR_TYPE_OFFLINE \
        (&GLOBUS_ERROR_TYPE_OFFLINE_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_OFFLINE   */
extern globus_object_t *
globus_error_construct_offline (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * access_failed_resource,
    globus_object_t * access_failed_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_OFFLINE   */
extern globus_object_t *
globus_error_initialize_offline (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * access_failed_resource,
    globus_object_t * access_failed_operation);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_ABORTED_DEFINITION;

#define GLOBUS_ERROR_TYPE_ABORTED \
        (&GLOBUS_ERROR_TYPE_ABORTED_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_ABORTED   */
extern globus_object_t *
globus_error_construct_aborted (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * aborted_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_ABORTED   */
extern globus_object_t *
globus_error_initialize_aborted (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * aborted_operation);

/* return the aborted_operation instance data of an error
 * derived from GLOBUS_ERROR_TYPE_ABORTED   */
extern globus_object_t *
globus_error_aborted_get_aborted_operation (globus_object_t * error)
;

/* set the aborted_operation instance data of an error
 * derived from GLOBUS_ERROR_TYPE_ABORTED   */
extern void
globus_error_aborted_set_aborted_operation (
    globus_object_t * error,
    globus_object_t * value)
;


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_USER_CANCELLED_DEFINITION;

#define GLOBUS_ERROR_TYPE_USER_CANCELLED \
        (&GLOBUS_ERROR_TYPE_USER_CANCELLED_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_USER_CANCELLED   */
extern globus_object_t *
globus_error_construct_user_cancelled (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * aborted_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_USER_CANCELLED   */
extern globus_object_t *
globus_error_initialize_user_cancelled (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * aborted_operation);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_INTERNAL_ERROR_DEFINITION;

#define GLOBUS_ERROR_TYPE_INTERNAL_ERROR \
        (&GLOBUS_ERROR_TYPE_INTERNAL_ERROR_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_INTERNAL_ERROR   */
extern globus_object_t *
globus_error_construct_internal_error (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * aborted_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_INTERNAL_ERROR   */
extern globus_object_t *
globus_error_initialize_internal_error (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * aborted_operation);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_SYSTEM_ABORTED_DEFINITION;

#define GLOBUS_ERROR_TYPE_SYSTEM_ABORTED \
        (&GLOBUS_ERROR_TYPE_SYSTEM_ABORTED_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_SYSTEM_ABORTED   */
extern globus_object_t *
globus_error_construct_system_aborted (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * aborted_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_SYSTEM_ABORTED   */
extern globus_object_t *
globus_error_initialize_system_aborted (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * aborted_operation);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_BAD_DATA_DEFINITION;

#define GLOBUS_ERROR_TYPE_BAD_DATA \
        (&GLOBUS_ERROR_TYPE_BAD_DATA_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_BAD_DATA   */
extern globus_object_t *
globus_error_construct_bad_data (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_BAD_DATA   */
extern globus_object_t *
globus_error_initialize_bad_data (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_NULL_REFERENCE_DEFINITION;

#define GLOBUS_ERROR_TYPE_NULL_REFERENCE \
        (&GLOBUS_ERROR_TYPE_NULL_REFERENCE_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_NULL_REFERENCE   */
extern globus_object_t *
globus_error_construct_null_reference (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_NULL_REFERENCE   */
extern globus_object_t *
globus_error_initialize_null_reference (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_TYPE_MISMATCH_DEFINITION;

#define GLOBUS_ERROR_TYPE_TYPE_MISMATCH \
        (&GLOBUS_ERROR_TYPE_TYPE_MISMATCH_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_TYPE_MISMATCH   */
extern globus_object_t *
globus_error_construct_type_mismatch (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_TYPE_MISMATCH   */
extern globus_object_t *
globus_error_initialize_type_mismatch (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_BAD_FORMAT_DEFINITION;

#define GLOBUS_ERROR_TYPE_BAD_FORMAT \
        (&GLOBUS_ERROR_TYPE_BAD_FORMAT_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_BAD_FORMAT   */
extern globus_object_t *
globus_error_construct_bad_format (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_BAD_FORMAT   */
extern globus_object_t *
globus_error_initialize_bad_format (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_NAME_UNKNOWN_DEFINITION;

#define GLOBUS_ERROR_TYPE_NAME_UNKNOWN \
        (&GLOBUS_ERROR_TYPE_NAME_UNKNOWN_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_NAME_UNKNOWN   */
extern globus_object_t *
globus_error_construct_name_unknown (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_NAME_UNKNOWN   */
extern globus_object_t *
globus_error_initialize_name_unknown (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_OUT_OF_RANGE_DEFINITION;

#define GLOBUS_ERROR_TYPE_OUT_OF_RANGE \
        (&GLOBUS_ERROR_TYPE_OUT_OF_RANGE_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_OUT_OF_RANGE   */
extern globus_object_t *
globus_error_construct_out_of_range (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_OUT_OF_RANGE   */
extern globus_object_t *
globus_error_initialize_out_of_range (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_TOO_LARGE_DEFINITION;

#define GLOBUS_ERROR_TYPE_TOO_LARGE \
        (&GLOBUS_ERROR_TYPE_TOO_LARGE_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_TOO_LARGE   */
extern globus_object_t *
globus_error_construct_too_large (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_TOO_LARGE   */
extern globus_object_t *
globus_error_initialize_too_large (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_TOO_SMALL_DEFINITION;

#define GLOBUS_ERROR_TYPE_TOO_SMALL \
        (&GLOBUS_ERROR_TYPE_TOO_SMALL_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_TOO_SMALL   */
extern globus_object_t *
globus_error_construct_too_small (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_TOO_SMALL   */
extern globus_object_t *
globus_error_initialize_too_small (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_COMMUNICATION_FAILED_DEFINITION;

#define GLOBUS_ERROR_TYPE_COMMUNICATION_FAILED \
        (&GLOBUS_ERROR_TYPE_COMMUNICATION_FAILED_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_COMMUNICATION_FAILED   */
extern globus_object_t *
globus_error_construct_communication_failed (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * communication_failed_local_resource,
    globus_object_t * communication_failed_remote_resource);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_COMMUNICATION_FAILED   */
extern globus_object_t *
globus_error_initialize_communication_failed (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * communication_failed_local_resource,
    globus_object_t * communication_failed_remote_resource);

/* return the communication_failed_local_resource instance data of an error
 * derived from GLOBUS_ERROR_TYPE_COMMUNICATION_FAILED   */
extern globus_object_t *
globus_error_communication_failed_get_communication_failed_local_resource (globus_object_t * error)
;

/* set the communication_failed_local_resource instance data of an error
 * derived from GLOBUS_ERROR_TYPE_COMMUNICATION_FAILED   */
extern void
globus_error_communication_failed_set_communication_failed_local_resource (
    globus_object_t * error,
    globus_object_t * value)
;

/* return the communication_failed_remote_resource instance data of an error
 * derived from GLOBUS_ERROR_TYPE_COMMUNICATION_FAILED   */
extern globus_object_t *
globus_error_communication_failed_get_communication_failed_remote_resource (globus_object_t * error)
;

/* set the communication_failed_remote_resource instance data of an error
 * derived from GLOBUS_ERROR_TYPE_COMMUNICATION_FAILED   */
extern void
globus_error_communication_failed_set_communication_failed_remote_resource (
    globus_object_t * error,
    globus_object_t * value)
;


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_UNREACHABLE_DEFINITION;

#define GLOBUS_ERROR_TYPE_UNREACHABLE \
        (&GLOBUS_ERROR_TYPE_UNREACHABLE_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_UNREACHABLE   */
extern globus_object_t *
globus_error_construct_unreachable (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * communication_failed_local_resource,
    globus_object_t * communication_failed_remote_resource);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_UNREACHABLE   */
extern globus_object_t *
globus_error_initialize_unreachable (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * communication_failed_local_resource,
    globus_object_t * communication_failed_remote_resource);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_PROTOCOL_MISMATCH_DEFINITION;

#define GLOBUS_ERROR_TYPE_PROTOCOL_MISMATCH \
        (&GLOBUS_ERROR_TYPE_PROTOCOL_MISMATCH_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_PROTOCOL_MISMATCH   */
extern globus_object_t *
globus_error_construct_protocol_mismatch (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * communication_failed_local_resource,
    globus_object_t * communication_failed_remote_resource);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_PROTOCOL_MISMATCH   */
extern globus_object_t *
globus_error_initialize_protocol_mismatch (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * communication_failed_local_resource,
    globus_object_t * communication_failed_remote_resource);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_PROTOCOL_VIOLATED_DEFINITION;

#define GLOBUS_ERROR_TYPE_PROTOCOL_VIOLATED \
        (&GLOBUS_ERROR_TYPE_PROTOCOL_VIOLATED_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_PROTOCOL_VIOLATED   */
extern globus_object_t *
globus_error_construct_protocol_violated (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * communication_failed_local_resource,
    globus_object_t * communication_failed_remote_resource,
    globus_object_t * protocol_violated_version);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_PROTOCOL_VIOLATED   */
extern globus_object_t *
globus_error_initialize_protocol_violated (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * communication_failed_local_resource,
    globus_object_t * communication_failed_remote_resource,
    globus_object_t * protocol_violated_version);

/* return the protocol_violated_version instance data of an error
 * derived from GLOBUS_ERROR_TYPE_PROTOCOL_VIOLATED   */
extern globus_object_t *
globus_error_protocol_violated_get_protocol_violated_version (globus_object_t * error)
;

/* set the protocol_violated_version instance data of an error
 * derived from GLOBUS_ERROR_TYPE_PROTOCOL_VIOLATED   */
extern void
globus_error_protocol_violated_set_protocol_violated_version (
    globus_object_t * error,
    globus_object_t * value)
;


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_INVALID_USE_DEFINITION;

#define GLOBUS_ERROR_TYPE_INVALID_USE \
        (&GLOBUS_ERROR_TYPE_INVALID_USE_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_INVALID_USE   */
extern globus_object_t *
globus_error_construct_invalid_use (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * invalid_use_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_INVALID_USE   */
extern globus_object_t *
globus_error_initialize_invalid_use (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * invalid_use_operation);

/* return the invalid_use_operation instance data of an error
 * derived from GLOBUS_ERROR_TYPE_INVALID_USE   */
extern globus_object_t *
globus_error_invalid_use_get_invalid_use_operation (globus_object_t * error)
;

/* set the invalid_use_operation instance data of an error
 * derived from GLOBUS_ERROR_TYPE_INVALID_USE   */
extern void
globus_error_invalid_use_set_invalid_use_operation (
    globus_object_t * error,
    globus_object_t * value)
;


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_ALREADY_DONE_DEFINITION;

#define GLOBUS_ERROR_TYPE_ALREADY_DONE \
        (&GLOBUS_ERROR_TYPE_ALREADY_DONE_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_ALREADY_DONE   */
extern globus_object_t *
globus_error_construct_already_done (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * invalid_use_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_ALREADY_DONE   */
extern globus_object_t *
globus_error_initialize_already_done (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * invalid_use_operation);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_ALREADY_REGISTERED_DEFINITION;

#define GLOBUS_ERROR_TYPE_ALREADY_REGISTERED \
        (&GLOBUS_ERROR_TYPE_ALREADY_REGISTERED_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_ALREADY_REGISTERED   */
extern globus_object_t *
globus_error_construct_already_registered (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * invalid_use_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_ALREADY_REGISTERED   */
extern globus_object_t *
globus_error_initialize_already_registered (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * invalid_use_operation);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_ALREADY_CANCELLED_DEFINITION;

#define GLOBUS_ERROR_TYPE_ALREADY_CANCELLED \
        (&GLOBUS_ERROR_TYPE_ALREADY_CANCELLED_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_ALREADY_CANCELLED   */
extern globus_object_t *
globus_error_construct_already_cancelled (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * invalid_use_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_ALREADY_CANCELLED   */
extern globus_object_t *
globus_error_initialize_already_cancelled (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * invalid_use_operation);


extern const globus_object_type_t
             GLOBUS_ERROR_TYPE_NOT_INITIALIZED_DEFINITION;

#define GLOBUS_ERROR_TYPE_NOT_INITIALIZED \
        (&GLOBUS_ERROR_TYPE_NOT_INITIALIZED_DEFINITION)

/* allocate and initialize an error of type
 * GLOBUS_ERROR_TYPE_NOT_INITIALIZED   */
extern globus_object_t *
globus_error_construct_not_initialized (
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * invalid_use_operation);

/* initialize and return an error of type
 * GLOBUS_ERROR_TYPE_NOT_INITIALIZED   */
extern globus_object_t *
globus_error_initialize_not_initialized (
    globus_object_t * error,
    globus_module_descriptor_t * base_source,
    globus_object_t * base_cause,
    globus_object_t * invalid_use_operation);



EXTERN_C_END

#endif /* GLOBUS_ERROR_HIERARCHY_H */

