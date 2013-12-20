// Basic contents of all user, trunk and docroot option sets.

//  Example:  If you add a line:
//
//  as_uac_user_option( foo, char_ptr, "Woo hoo!", 0, 0 )
//
// to the user option section, two things will happen:
//
//  1) A new member "_foo" of type "const char *" will appear
//     in the structure as_uac_user_option_set returned by
//     as_uac_user_get_option_set and as_uac_user_get_option_set_by_name.
//     If not overridden by something in an XML file, it will
//     point to a global const char * "Woo Hoo!".
//
//  2) A function 
//     const char *as_uac_user_default_get_foo( as_uac_conf_node *user );
//     will appear if you include "uac.h".  It returns the value of 
//     foo found in the config xml file(s) or "Woo Hoo!" if none are
//     found.
//
//  In order for this to work, you also need to specify where in the
//  XML file the value for foo can be found.  To do this, go to
//  parse_config_queries.h and add a new entry for foo.  For instance,
//  if you wanted the string foo to be the contents of the node
//  <foo><bar><value>My foo!</value></bar></foo> starting from
//  the user root node, you would add:
//
//  as_uac_user_option_query( foo ) hcn_foo, hcn_bar, hcn_value
//
//  You will need to add a new entry to the big enum at the top of
//  parse_config_option_meta.h.  All options need to have unique
//  indices to facilitate internationalization (I18N).
//
//  Finally, if any of these lines are missing from "parse_hard_config_names.h",
//  they will need to be added:
//
//  hard_config_name( foo )
//  hard_config_name( bar )
//  hard_config_name( value )

// To set a default string list of "exclude_this" and "exclude_that", you'd do this:
// as_uac_user_option(file_exclusions, string_list, "exclude_this\000exclude_that\000\032", hcn_exclude)

// To set a default cron that is 50000 24/7:
//as_uac_trunk_option(trunk_capacity, cron, 50000, 0)

// To set a default complex cron (Note the unescaped double quotes):
//as_uac_trunk_option(trunk_capacity, cron, "<conf><schedule format="cron"><change_points><change_point><epoch>0 8-18 * * *</epoch><value>54321</value></change_point><change_point><epoch>0 19-7 * * *</epoch><value>12345</value></change_point></change_points></schedule></conf>", 0)


// No file wide multiple inclusion security, please!

#ifndef UAC_UNLIMITED_RATE
#define UAC_UNLIMITED_RATE (0xFFFFFFFFFFFFFL * 1000)
#endif

#ifndef UAC_POLICY_DEFINES
#define UAC_POLICY_DEFINES

#define UAC_TRANSFER_POLICY_ANY         0
#define UAC_TRANSFER_POLICY_FIXED       0
#define UAC_TRANSFER_POLICY_HIGH        3
#define UAC_TRANSFER_POLICY_REGULAR     4
#define UAC_TRANSFER_POLICY_FAIR        4
#define UAC_TRANSFER_POLICY_LOW         5
#define UAC_TRANSFER_POLICY_TRICKLE     5

#endif


    // Name, type (int32_t, u_int32_t, int64_t, u_int64_t, char_ptr, double, lookup or cron), default value, param.
#ifdef as_uac_user_option
as_uac_user_option(user_value, int64_t, 0, 0)
as_uac_user_option(name, trimmed_char_ptr, 0, 0)
as_uac_user_option(group, trimmed_char_ptr, 0, 0)
as_uac_user_option(realm, trimmed_char_ptr, 0, 0)
as_uac_user_option(authorization_transfer_in_value, trimmed_char_ptr, "allow", 0)
as_uac_user_option(authorization_transfer_in_external_provider_url, trimmed_char_ptr, 0, 0)
as_uac_user_option(authorization_transfer_in_external_provider_soap_action, trimmed_char_ptr, 0, 0)
as_uac_user_option(authorization_transfer_out_value, trimmed_char_ptr, "allow", 0)
as_uac_user_option(authorization_transfer_out_external_provider_url, trimmed_char_ptr, 0, 0)
as_uac_user_option(authorization_transfer_out_external_provider_soap_action, trimmed_char_ptr, 0, 0)
as_uac_user_option(token_encryption_type, lookup, aes-128, "aes-128:16;aes-192:24;aes-256:32")
as_uac_user_option(token_encryption_key, trimmed_char_ptr, 0, 0)
as_uac_user_option(token_life_seconds, u_int32_t, 1200, 0)
as_uac_user_option(transfer_in_bandwidth_aggregate_trunk_id, u_int32_t, 0, 0)
as_uac_user_option(transfer_in_bandwidth_flow_target_rate_cap, u_int64_t, Unlimited, "1000;Unlimited:0xFFFFFFFFFFFFF")
as_uac_user_option(transfer_in_bandwidth_flow_target_rate_default, u_int64_t, 10000, "1000")
as_uac_user_option(transfer_in_bandwidth_flow_target_rate_lock, boolean, 0, 0)
as_uac_user_option(transfer_in_bandwidth_flow_min_rate_cap, u_int64_t, Unlimited, "1000;Unlimited:0xFFFFFFFFFFFFF")
as_uac_user_option(transfer_in_bandwidth_flow_min_rate_default, u_int64_t, 0, "1000")
as_uac_user_option(transfer_in_bandwidth_flow_min_rate_lock, boolean, 0, 0)
as_uac_user_option(transfer_in_bandwidth_flow_policy_allowed, lookup, any, "any:0;high:3;fair:4;regular:4;low:5;trickle:5")
as_uac_user_option(transfer_in_bandwidth_flow_policy_default, lookup, fair, "fixed:0;high:3;fair:4;regular:4;low:5;trickle:5")
as_uac_user_option(transfer_in_bandwidth_flow_policy_lock, boolean, 0, 0)
as_uac_user_option(transfer_in_bandwidth_flow_priority_cap, lookup, high, "high:1;normal:2")
as_uac_user_option(transfer_in_bandwidth_flow_priority_default, lookup, normal, "high:1;normal:2")
as_uac_user_option(transfer_in_bandwidth_flow_priority_lock, boolean, 0, 0)
as_uac_user_option(transfer_out_bandwidth_aggregate_trunk_id, u_int32_t, 0, 0)
as_uac_user_option(transfer_out_bandwidth_flow_target_rate_cap, u_int64_t, Unlimited, "1000;Unlimited:0xFFFFFFFFFFFFF")
as_uac_user_option(transfer_out_bandwidth_flow_target_rate_default, u_int64_t, 10000, "1000")
as_uac_user_option(transfer_out_bandwidth_flow_target_rate_lock, boolean, 0, 0)
as_uac_user_option(transfer_out_bandwidth_flow_min_rate_cap, u_int64_t, Unlimited, "1000;Unlimited:0xFFFFFFFFFFFFF")
as_uac_user_option(transfer_out_bandwidth_flow_min_rate_default, u_int64_t, 0, "1000")
as_uac_user_option(transfer_out_bandwidth_flow_min_rate_lock, boolean, 0, 0)
as_uac_user_option(transfer_out_bandwidth_flow_policy_allowed, lookup, any, "any:0;high:3;fair:4;regular:4;low:5;trickle:5")
as_uac_user_option(transfer_out_bandwidth_flow_policy_default, lookup, fair, "fixed:0;high:3;fair:4;regular:4;low:5;trickle:5")
as_uac_user_option(transfer_out_bandwidth_flow_policy_lock, boolean, 0, 0)
as_uac_user_option(transfer_out_bandwidth_flow_priority_cap, lookup, high, "high:1;normal:2")
as_uac_user_option(transfer_out_bandwidth_flow_priority_default, lookup, normal, "high:1;normal:2")
as_uac_user_option(transfer_out_bandwidth_flow_priority_lock, boolean, 0, 0)
as_uac_user_option(transfer_encryption_allowed_cipher, lookup, any, "any:-1;none:0;aes-128:1")
as_uac_user_option(transfer_encryption_content_protection_required, boolean, 0, 0)
as_uac_user_option(transfer_encryption_content_protection_strong_pass_required, boolean, 0, 0)
as_uac_user_option(transfer_protocol_options_bind_ip_address, trimmed_char_ptr, 0, 0)
as_uac_user_option(transfer_protocol_options_bind_udp_port, u_int32_t, 33001, 0)
as_uac_user_option(transfer_protocol_options_disable_batching, boolean, 0, 0)
as_uac_user_option(transfer_protocol_options_sessini_optimization, boolean, 0, 0)
as_uac_user_option(transfer_protocol_options_max_sock_buffer, u_int32_t, 0, 0)
as_uac_user_option(transfer_protocol_options_min_sock_buffer, u_int32_t, 0, 0)
as_uac_user_option(transfer_protocol_options_rate_instru_type, u_int32_t, 0, 0)

as_uac_user_option(file_create_mode, octal_32, Undefined, "1;Undefined:37777777777")
as_uac_user_option(file_create_grant_mask, octal_32, 644, "1;Undefined:37777777777")
as_uac_user_option(directory_create_mode, octal_32, Undefined, "1;Undefined:37777777777")
as_uac_user_option(directory_create_grant_mask, octal_32, 755, "1;Undefined:37777777777")
as_uac_user_option(read_block_size, u_int64_t, 0, 0)
as_uac_user_option(write_block_size, u_int64_t, 0, 0)
as_uac_user_option(use_file_cache, boolean, 1, 0)
as_uac_user_option(max_file_cache_buffer, u_int64_t, 0, 0)
as_uac_user_option(ring_buf_units, u_int32_t, 0, 0)
as_uac_user_option(resume_suffix, trimmed_char_ptr, ".aspx", 0)
as_uac_user_option(preserve_attributes, trimmed_char_ptr, 0, 0)
as_uac_user_option(overwrite, trimmed_char_ptr, "allow", 0)
as_uac_user_option(file_manifest, trimmed_char_ptr, "disable", 0)
as_uac_user_option(file_manifest_path, trimmed_char_ptr, 0, 0)
as_uac_user_option(pre_calculate_job_size, lookup, any, "any:0;no:1;yes:2")
as_uac_user_option(storage_rc_adaptive, boolean, 0, 0)
as_uac_user_option(storage_rc_buf_min, double, 0, 0)
as_uac_user_option(storage_rc_buf_target, double, 0, 0)
as_uac_user_option(storage_rc_buf_delta, double, 0, 0)
as_uac_user_option(file_exclude, string_list, 0, hcn_exclude)

/* Only used for groups, but it's technically present at the node and user level (all fields have to be present in all three). */
/* Higher value = lower precedence */
as_uac_user_option(precedence, double, 1000.0, 0)

#ifndef UAC_SKIP_UNDEF
#undef as_uac_user_option
#endif
#endif

#ifdef as_uac_trunk_option
as_uac_trunk_option(trunk_name, trimmed_char_ptr, 0, 0)
as_uac_trunk_option(trunk_id, u_int32_t, 0, 0)
as_uac_trunk_option(trunk_on, boolean, 0, 0)
as_uac_trunk_option(trunk_capacity, cron, 50000, 0)
as_uac_trunk_option(trunk_mcast_iface_address, trimmed_char_ptr, 0, 0)
as_uac_trunk_option(trunk_mcast_group_address, trimmed_char_ptr, 0, 0)
as_uac_trunk_option(trunk_mcast_port, u_int32_t, 0, 0)
as_uac_trunk_option(trunk_target_queue, u_int32_t, 0, 0)
as_uac_trunk_option(trunk_min_queue, u_int32_t, 0, 0)
as_uac_trunk_option(trunk_tightness_in, double, 0, 0)
as_uac_trunk_option(trunk_tightness_out, double, 0, 0)
as_uac_trunk_option(trunk_qb_over_qmax, double, 0, 0)

#ifndef UAC_SKIP_UNDEF
#undef as_uac_trunk_option
#endif
#endif

#ifdef as_uac_docroot_option
as_uac_docroot_option(absolute, trimmed_char_ptr, "", 0)
as_uac_docroot_option(show_as, trimmed_char_ptr, "", 0)
as_uac_docroot_option(description, char_ptr, 0, 0)
as_uac_docroot_option(filter, trimmed_char_ptr, "*", 0)

as_uac_docroot_option(read_allowed, boolean, 1, 0)
as_uac_docroot_option(write_allowed, boolean, 1, 0)
as_uac_docroot_option(dir_allowed, boolean, 1, 0)

#ifndef UAC_SKIP_UNDEF
#undef as_uac_docroot_option
#endif
#endif


#ifdef as_uac_central_server_option
as_uac_central_server_option(address, trimmed_char_ptr, "127.0.0.1", 0 )
as_uac_central_server_option(port, u_int32_t, 40001, 0 )

#ifndef UAC_SKIP_UNDEF
#undef as_uac_central_server_option
#endif
#endif


#ifdef as_uac_database_option
as_uac_database_option(adapter, trimmed_char_ptr, "mysql", 0 )
as_uac_database_option(server, trimmed_char_ptr, "127.0.0.1", 0 )
as_uac_database_option(port, u_int32_t, 4406, 0 )
as_uac_database_option(user, trimmed_char_ptr, 0, 0 )
as_uac_database_option(password, trimmed_char_ptr, 0, 0 )
as_uac_database_option(database_name, trimmed_char_ptr, 0, 0 )
as_uac_database_option(threads, u_int32_t, 10, 0 )                    /* default 10 */
as_uac_database_option(exit_on_database_error, boolean, 0, 0 )        /* default no */
as_uac_database_option(session_progress, boolean, 1, 0 )              /* default yes */
as_uac_database_option(session_progress_interval, u_int64_t, 1, 0 )   /* default 1s */
as_uac_database_option(file_events, boolean, 1, 0 )                   /* default yes */
as_uac_database_option(file_progress, boolean, 1, 0 )                 /* default yes */
as_uac_database_option(file_errors, boolean, 1, 0)                    /* default yes */
as_uac_database_option(file_progress_interval, u_int64_t, 1, 0 )      /* default 1s */
as_uac_database_option(files_per_session, u_int64_t, 0, 0 )           /* default 0, unlimited */
as_uac_database_option(ignore_empty_files, boolean, 0, 0 )            /* default no */
as_uac_database_option(ignore_skipped_files, boolean, 0, 0 )          /* default no */
as_uac_database_option(ignore_no_transfer_files, boolean, 0, 0 )      /* default no */
as_uac_database_option(rate_events, boolean, 1, 0 )                   /* default yes */

#ifndef UAC_SKIP_UNDEF
#undef as_uac_database_option
#endif
#endif


#ifdef as_uac_http_server_option
as_uac_http_server_option(cert_file, trimmed_char_ptr, 0, 0 )
as_uac_http_server_option(key_file, trimmed_char_ptr, 0, 0 )
as_uac_http_server_option(bind_address, trimmed_char_ptr, "0.0.0.0", 0 )
as_uac_http_server_option(mgmt_address, trimmed_char_ptr, 0, 0 )
as_uac_http_server_option(file_root, trimmed_char_ptr, 0, 0 )
as_uac_http_server_option(restartable_transfers, boolean, 1, 0 )
as_uac_http_server_option(session_activity_timeout, u_int64_t, 0, 0 )
as_uac_http_server_option(http_port, u_int32_t, 8080, 0 )
as_uac_http_server_option(https_port, u_int32_t, 8443, 0 )
as_uac_http_server_option(enable_http, boolean, 0, 0 )
as_uac_http_server_option(enable_https, boolean, 0, 0 )
as_uac_http_server_option(reset_key, trimmed_char_ptr, "default_reset_key", 0 )

#ifndef UAC_SKIP_UNDEF
#undef as_uac_http_server_option
#endif
#endif


#ifdef as_uac_conf_V1_option
as_uac_conf_V1_option(FASP_AUTH_AuthorizationRequired, boolean, 0, 0 )
as_uac_conf_V1_option(FASP_AUTH_AuthorizationURL, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_AUTH_AuthorizationSOAPAction, trimmed_char_ptr, 0, 0 )

as_uac_conf_V1_option(FASP_AUTH_TargetRateCapPerFlow, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_AUTH_MinRateCapPerFlow, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_AUTH_AllowedCipher, trimmed_char_ptr, 0, 0 )

as_uac_conf_V1_option(CENTRAL_HttpPort, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(CENTRAL_HttpAddress, trimmed_char_ptr, 0, 0 )

as_uac_conf_V1_option(DATABASE_Adapter, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_Server, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_Port, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_User, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_Password, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_DatabaseName, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_ExitOnDatabaseError, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_Threads, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_SessionProgress, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_SessionProgressInterval, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_FileEvents, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_FileProgress, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_FileProgressInterval, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_FilesPerSession, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_IgnoreEmptyFiles, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_IgnoreSkippedFiles, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_IgnoreNoTransferFiles, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(DATABASE_RateEvents, trimmed_char_ptr, 0, 0 )

as_uac_conf_V1_option(FASP_BindIpAddress, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_BindUdpPort, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_LogStatsInterval, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_SessiniOptimization, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_DisableBatching, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_FileCreateMode, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_FileCreateGrantMask, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_DirectoryCreateMode, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_DirectoryCreateGrantMask, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_ReadBlockSize, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_WriteBlockSize, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_MaxSockBuffer, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_MinSockBuffer, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_Exclude, string_list, 0, use_attribute_Exclude )
as_uac_conf_V1_option(FASP_ResumeSuffix, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_UseFileCache, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_MaxFileCacheBuffer, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_LicenseFile, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_PreserveAttributes, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_Overwrite, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_FileManifest, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_FileManifestPath, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(FASP_PreCalculateJobSize, trimmed_char_ptr, 0, 0 )

as_uac_conf_V1_option(WEB_SshPort, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_UdpPort, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_Policy, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_BandwidthCap, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_MinRate, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_LockPolicy, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_LockTargetRate, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_LockMinRate, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_PathMTU, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_DetectBW, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_TargetRate, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_Encryption, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_HttpFallback, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_HttpFallbackPort, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_HttpsFallbackPort, trimmed_char_ptr, 0, 0 )

as_uac_conf_V1_option(WEB_AsperaServer, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_Version, trimmed_char_ptr, 0, 0 )
as_uac_conf_V1_option(WEB_LinkCapacity, trimmed_char_ptr, 0, 0 )

#ifndef UAC_SKIP_UNDEF
#undef as_uac_conf_V1_option
#endif
#endif


#ifdef as_uac_vlink_V1_option
as_uac_vlink_V1_option(ID, trimmed_char_ptr, 0, 0 )

as_uac_vlink_V1_option(UpDown, trimmed_char_ptr, 0, 0 )
as_uac_vlink_V1_option(CapacityIn, trimmed_char_ptr, 0, 0 )
as_uac_vlink_V1_option(CapacityOut, trimmed_char_ptr, 0, 0 )
as_uac_vlink_V1_option(IF_ADDRESS, trimmed_char_ptr, 0, 0 )
as_uac_vlink_V1_option(MCAST_ADDRESS, trimmed_char_ptr, 0, 0 )

as_uac_vlink_V1_option(On, trimmed_char_ptr, 0, 0 )
as_uac_vlink_V1_option(InboundAggregateCapKbps, trimmed_char_ptr, 0, 0 )
as_uac_vlink_V1_option(OutboundAggregateCapKbps, trimmed_char_ptr, 0, 0 )
as_uac_vlink_V1_option(McastInterfaceAddress, trimmed_char_ptr, 0, 0 )
as_uac_vlink_V1_option(McastGroupAddress, trimmed_char_ptr, 0, 0 )

as_uac_vlink_V1_option(TargetQueue, trimmed_char_ptr, 0, 0 )
as_uac_vlink_V1_option(MinQueue, trimmed_char_ptr, 0, 0 )
as_uac_vlink_V1_option(TightnessIn, trimmed_char_ptr, 0, 0 )
as_uac_vlink_V1_option(TightnessOut, trimmed_char_ptr, 0, 0 )
as_uac_vlink_V1_option(QB_OVER_QMAX, trimmed_char_ptr, 0, 0 )

#ifndef UAC_SKIP_UNDEF
#undef as_uac_vlink_V1_option
#endif
#endif


#ifdef as_uac_http_session_start_option
as_uac_http_session_start_option(id, trimmed_char_ptr, 0, 0 )
as_uac_http_session_start_option(operation, lookup, 0, "get:0;put:1")
as_uac_http_session_start_option(token, trimmed_char_ptr, 0, 0 )
as_uac_http_session_start_option(cookie, trimmed_char_ptr, 0, 0 )
as_uac_http_session_start_option(source, string_list, 0, hcn_source )
as_uac_http_session_start_option(destination, trimmed_char_ptr, 0, 0 )
as_uac_http_session_start_option(createdir, boolean, 0, "no:yes" )
as_uac_http_session_start_option(mustbedir, boolean, 0, "no:yes" )
as_uac_http_session_start_option(encryption, boolean, 0, "No:Yes" )
as_uac_http_session_start_option(resume, lookup, 0, "off:0;sparse-md5:1;full-md5:2" )
as_uac_http_session_start_option(overwrite, lookup, 1, "yes:0;older:1;no:2" )
as_uac_http_session_start_option(user, trimmed_char_ptr, 0, 0 )
as_uac_http_session_start_option(rate_limit, u_int64_t, 0, 0 )
as_uac_http_session_start_option(license, trimmed_char_ptr, 0, 0 )
as_uac_http_session_start_option(transfer_precalc, boolean, 0, "no:yes" )

#ifndef UAC_SKIP_UNDEF
#undef as_uac_http_session_start_option
#endif
#endif


#ifdef as_uac_http_session_end_option
as_uac_http_session_end_option(reason, char_ptr, "Unknown", 0 )
as_uac_http_session_end_option(code, int64_t, 0, 0 )
as_uac_http_session_end_option(file_count, int64_t, 0, 0 )
as_uac_http_session_end_option(byte_count, int64_t, 0, 0 )

#ifndef UAC_SKIP_UNDEF
#undef as_uac_http_session_end_option
#endif
#endif

// Set parse_config_queries.h for where these live in the xml file.
