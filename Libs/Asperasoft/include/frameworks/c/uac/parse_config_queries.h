// Config option name followed by xml location based on a user, trunk or docroot node.

// See discussion at the top of "parse_config_option_set.h"

// No multiple inclusion security, please!

    // Queries to find user options at.
#ifdef as_uac_user_option_query
as_uac_user_option_query( transfer_in_bandwidth_aggregate_trunk_id )    hcn_transfer, hcn_in, hcn_bandwidth, hcn_aggregate, hcn_trunk_id
as_uac_user_option_query( transfer_in_bandwidth_flow_target_rate_cap )  hcn_transfer, hcn_in, hcn_bandwidth, hcn_flow, hcn_target_rate, hcn_cap
as_uac_user_option_query( transfer_in_bandwidth_flow_target_rate_default )  hcn_transfer, hcn_in, hcn_bandwidth, hcn_flow, hcn_target_rate, hcn_default
as_uac_user_option_query( transfer_in_bandwidth_flow_target_rate_lock ) hcn_transfer, hcn_in, hcn_bandwidth, hcn_flow, hcn_target_rate, hcn_lock
as_uac_user_option_query( transfer_in_bandwidth_flow_min_rate_cap )     hcn_transfer, hcn_in, hcn_bandwidth, hcn_flow, hcn_min_rate, hcn_cap
as_uac_user_option_query( transfer_in_bandwidth_flow_min_rate_default ) hcn_transfer, hcn_in, hcn_bandwidth, hcn_flow, hcn_min_rate, hcn_default
as_uac_user_option_query( transfer_in_bandwidth_flow_min_rate_lock )    hcn_transfer, hcn_in, hcn_bandwidth, hcn_flow, hcn_min_rate, hcn_lock
as_uac_user_option_query( transfer_in_bandwidth_flow_policy_allowed )   hcn_transfer, hcn_in, hcn_bandwidth, hcn_flow, hcn_policy, hcn_allowed
as_uac_user_option_query( transfer_in_bandwidth_flow_policy_default )   hcn_transfer, hcn_in, hcn_bandwidth, hcn_flow, hcn_policy, hcn_default
as_uac_user_option_query( transfer_in_bandwidth_flow_policy_lock )      hcn_transfer, hcn_in, hcn_bandwidth, hcn_flow, hcn_policy, hcn_lock
as_uac_user_option_query( transfer_in_bandwidth_flow_priority_cap )     hcn_transfer, hcn_in, hcn_bandwidth, hcn_flow, hcn_priority, hcn_cap
as_uac_user_option_query( transfer_in_bandwidth_flow_priority_default ) hcn_transfer, hcn_in, hcn_bandwidth, hcn_flow, hcn_priority, hcn_default
as_uac_user_option_query( transfer_in_bandwidth_flow_priority_lock )    hcn_transfer, hcn_in, hcn_bandwidth, hcn_flow, hcn_priority, hcn_lock
as_uac_user_option_query( transfer_out_bandwidth_aggregate_trunk_id )   hcn_transfer, hcn_out, hcn_bandwidth, hcn_aggregate, hcn_trunk_id
as_uac_user_option_query( transfer_out_bandwidth_flow_target_rate_cap ) hcn_transfer, hcn_out, hcn_bandwidth, hcn_flow, hcn_target_rate, hcn_cap
as_uac_user_option_query( transfer_out_bandwidth_flow_target_rate_default ) hcn_transfer, hcn_out, hcn_bandwidth, hcn_flow, hcn_target_rate, hcn_default
as_uac_user_option_query( transfer_out_bandwidth_flow_target_rate_lock )    hcn_transfer, hcn_out, hcn_bandwidth, hcn_flow, hcn_target_rate, hcn_lock
as_uac_user_option_query( transfer_out_bandwidth_flow_min_rate_cap )    hcn_transfer, hcn_out, hcn_bandwidth, hcn_flow, hcn_min_rate, hcn_cap
as_uac_user_option_query( transfer_out_bandwidth_flow_min_rate_default )    hcn_transfer, hcn_out, hcn_bandwidth, hcn_flow, hcn_min_rate, hcn_default
as_uac_user_option_query( transfer_out_bandwidth_flow_min_rate_lock )   hcn_transfer, hcn_out, hcn_bandwidth, hcn_flow, hcn_min_rate, hcn_lock
as_uac_user_option_query( transfer_out_bandwidth_flow_policy_allowed )  hcn_transfer, hcn_out, hcn_bandwidth, hcn_flow, hcn_policy, hcn_allowed
as_uac_user_option_query( transfer_out_bandwidth_flow_policy_default )  hcn_transfer, hcn_out, hcn_bandwidth, hcn_flow, hcn_policy, hcn_default
as_uac_user_option_query( transfer_out_bandwidth_flow_policy_lock )     hcn_transfer, hcn_out, hcn_bandwidth, hcn_flow, hcn_policy, hcn_lock
as_uac_user_option_query( transfer_out_bandwidth_flow_priority_cap )    hcn_transfer, hcn_out, hcn_bandwidth, hcn_flow, hcn_priority, hcn_cap
as_uac_user_option_query( transfer_out_bandwidth_flow_priority_default ) hcn_transfer, hcn_out, hcn_bandwidth, hcn_flow, hcn_priority, hcn_default
as_uac_user_option_query( transfer_out_bandwidth_flow_priority_lock )   hcn_transfer, hcn_out, hcn_bandwidth, hcn_flow, hcn_priority, hcn_lock

as_uac_user_option_query( transfer_encryption_allowed_cipher )          hcn_transfer, hcn_encryption, hcn_allowed_cipher
as_uac_user_option_query( transfer_encryption_content_protection_required )                 hcn_transfer, hcn_encryption, hcn_content_protection_required 
as_uac_user_option_query( transfer_encryption_content_protection_strong_pass_required )     hcn_transfer, hcn_encryption, hcn_content_protection_strong_pass_required 

as_uac_user_option_query( transfer_protocol_options_bind_ip_address )   hcn_transfer, hcn_protocol_options, hcn_bind_ip_address
as_uac_user_option_query( transfer_protocol_options_bind_udp_port )     hcn_transfer, hcn_protocol_options, hcn_bind_udp_port
as_uac_user_option_query( transfer_protocol_options_disable_batching )  hcn_transfer, hcn_protocol_options, hcn_disable_batching
as_uac_user_option_query( transfer_protocol_options_sessini_optimization ) hcn_transfer, hcn_protocol_options, hcn_sessini_optimization
as_uac_user_option_query( transfer_protocol_options_max_sock_buffer )   hcn_transfer, hcn_protocol_options, hcn_max_sock_buffer
as_uac_user_option_query( transfer_protocol_options_min_sock_buffer )   hcn_transfer, hcn_protocol_options, hcn_min_sock_buffer
as_uac_user_option_query( transfer_protocol_options_rate_instru_type )  hcn_transfer, hcn_protocol_options, hcn_rate_instru_type

as_uac_user_option_query( user_value )                                  hcn_user_value
as_uac_user_option_query( name )                                        hcn_name
as_uac_user_option_query( group )                                       hcn_group
as_uac_user_option_query( realm )                                       hard_config_parent, hard_config_parent, hcn_name
as_uac_user_option_query( authorization_transfer_in_value )             hcn_authorization, hcn_transfer, hcn_in, hcn_value
as_uac_user_option_query( authorization_transfer_in_external_provider_url )         hcn_authorization, hcn_transfer, hcn_in, hcn_external_provider, hcn_url
as_uac_user_option_query( authorization_transfer_in_external_provider_soap_action ) hcn_authorization, hcn_transfer, hcn_in, hcn_external_provider, hcn_soap_action
as_uac_user_option_query( authorization_transfer_out_value )            hcn_authorization, hcn_transfer, hcn_out, hcn_value
as_uac_user_option_query( authorization_transfer_out_external_provider_url )        hcn_authorization, hcn_transfer, hcn_out, hcn_external_provider, hcn_url
as_uac_user_option_query( authorization_transfer_out_external_provider_soap_action ) hcn_authorization, hcn_transfer, hcn_out, hcn_external_provider, hcn_soap_action

as_uac_user_option_query( token_encryption_key )                        hcn_authorization, hcn_token, hcn_encryption_key
as_uac_user_option_query( token_encryption_type )                       hcn_authorization, hcn_token, hcn_encryption_type
as_uac_user_option_query( token_life_seconds )                          hcn_authorization, hcn_token, hcn_life_seconds

as_uac_user_option_query( file_create_mode )                            hcn_file_system, hcn_file_create_mode
as_uac_user_option_query( file_create_grant_mask )                      hcn_file_system, hcn_file_create_grant_mask
as_uac_user_option_query( directory_create_mode )                       hcn_file_system, hcn_directory_create_mode
as_uac_user_option_query( directory_create_grant_mask )                 hcn_file_system, hcn_directory_create_grant_mask

as_uac_user_option_query( read_block_size )                             hcn_file_system, hcn_read_block_size
as_uac_user_option_query( write_block_size )                            hcn_file_system, hcn_write_block_size
as_uac_user_option_query( use_file_cache )                              hcn_file_system, hcn_use_file_cache
as_uac_user_option_query( max_file_cache_buffer )                       hcn_file_system, hcn_max_file_cache_buffer
as_uac_user_option_query( ring_buf_units )                              hcn_file_system, hcn_ring_buf_units
as_uac_user_option_query( resume_suffix )                               hcn_file_system, hcn_resume_suffix
as_uac_user_option_query( preserve_attributes )                         hcn_file_system, hcn_preserve_attributes
as_uac_user_option_query( overwrite )                                   hcn_file_system, hcn_overwrite
as_uac_user_option_query( file_manifest )                               hcn_file_system, hcn_file_manifest
as_uac_user_option_query( file_manifest_path )                          hcn_file_system, hcn_file_manifest_path
as_uac_user_option_query( pre_calculate_job_size )                      hcn_file_system, hcn_pre_calculate_job_size
as_uac_user_option_query( storage_rc_adaptive )                         hcn_file_system, hcn_storage_rc, hcn_adaptive
as_uac_user_option_query( storage_rc_buf_min )                          hcn_file_system, hcn_storage_rc, hcn_buf_min
as_uac_user_option_query( storage_rc_buf_target )                       hcn_file_system, hcn_storage_rc, hcn_buf_target
as_uac_user_option_query( storage_rc_buf_delta )                        hcn_file_system, hcn_storage_rc, hcn_buf_delta

as_uac_user_option_query( file_exclude )                                hcn_file_system, hcn_excludes

as_uac_user_option_query( precedence )                                  hcn_precedence

#undef as_uac_user_option_query
#endif

    // Queries to find trunk options at.
#ifdef as_uac_trunk_option_query
as_uac_trunk_option_query( trunk_name )                                 hcn_name
as_uac_trunk_option_query( trunk_id )                                   hcn_id
as_uac_trunk_option_query( trunk_on )                                   hcn_on
as_uac_trunk_option_query( trunk_capacity )                             hcn_capacity
as_uac_trunk_option_query( trunk_mcast_iface_address )                  hcn_mcast_iface_address
as_uac_trunk_option_query( trunk_mcast_group_address )                  hcn_mcast_group_address
as_uac_trunk_option_query( trunk_mcast_port )                           hcn_mcast_port
as_uac_trunk_option_query( trunk_target_queue )                         hcn_target_queue
as_uac_trunk_option_query( trunk_min_queue )                            hcn_min_queue
as_uac_trunk_option_query( trunk_tightness_in )                         hcn_tightness_in
as_uac_trunk_option_query( trunk_tightness_out )                        hcn_tightness_out
as_uac_trunk_option_query( trunk_qb_over_qmax )                         hcn_qb_over_qmax

#undef as_uac_trunk_option_query
#endif

    // Queries to find docroots at.
#ifdef as_uac_docroot_option_query
as_uac_docroot_option_query( absolute )                                 hcn_absolute
as_uac_docroot_option_query( show_as )                                  hcn_show_as
as_uac_docroot_option_query( description )                              hcn_description
as_uac_docroot_option_query( filter )                                   hcn_filter

as_uac_docroot_option_query( read_allowed )                             hcn_read_allowed
as_uac_docroot_option_query( write_allowed )                            hcn_write_allowed
as_uac_docroot_option_query( dir_allowed )                              hcn_dir_allowed

#undef as_uac_docroot_option_query
#endif


#ifdef as_uac_central_server_option_query
as_uac_central_server_option_query( address )                           hcn_address
as_uac_central_server_option_query( port )                              hcn_port

#undef as_uac_central_server_option_query
#endif


#ifdef as_uac_database_option_query
as_uac_database_option_query( adapter )                                 hcn_adapter
as_uac_database_option_query( server )                                  hcn_server
as_uac_database_option_query( port )                                    hcn_port
as_uac_database_option_query( user )                                    hcn_user
as_uac_database_option_query( password )                                hcn_password
as_uac_database_option_query( database_name )                           hcn_database_name
as_uac_database_option_query( threads )                                 hcn_threads
as_uac_database_option_query( exit_on_database_error )                  hcn_exit_on_database_error
as_uac_database_option_query( session_progress )                        hcn_session_progress
as_uac_database_option_query( session_progress_interval )               hcn_session_progress_interval
as_uac_database_option_query( file_events )                             hcn_file_events
as_uac_database_option_query( file_progress )                           hcn_file_progress
as_uac_database_option_query( file_errors )                             hcn_file_errors
as_uac_database_option_query( file_progress_interval )                  hcn_file_progress_interval
as_uac_database_option_query( files_per_session )                       hcn_files_per_session
as_uac_database_option_query( ignore_empty_files )                      hcn_ignore_empty_files
as_uac_database_option_query( ignore_skipped_files )                    hcn_ignore_skipped_files
as_uac_database_option_query( ignore_no_transfer_files )                hcn_ignore_no_transfer_files
as_uac_database_option_query( rate_events )                             hcn_rate_events

#undef as_uac_database_option_query
#endif


#ifdef as_uac_http_server_option_query
as_uac_http_server_option_query(cert_file)                              hcn_cert_file
as_uac_http_server_option_query(key_file)                               hcn_key_file
as_uac_http_server_option_query(bind_address)                           hcn_bind_address
as_uac_http_server_option_query(mgmt_address)                           hcn_mgmt_address
as_uac_http_server_option_query(file_root)                              hcn_file_root
as_uac_http_server_option_query(restartable_transfers)                  hcn_restartable_transfers
as_uac_http_server_option_query(session_activity_timeout)               hcn_session_activity_timeout
as_uac_http_server_option_query(http_port)                              hcn_http_port
as_uac_http_server_option_query(https_port)                             hcn_https_port
as_uac_http_server_option_query(enable_http)                            hcn_enable_http
as_uac_http_server_option_query(enable_https)                           hcn_enable_https
as_uac_http_server_option_query(reset_key)                              hcn_reset_key

#undef as_uac_http_server_option_query
#endif


#ifdef as_uac_conf_V1_option_query
as_uac_conf_V1_option_query(FASP_AUTH_AuthorizationRequired)            hcn_FASP_AUTH, use_attribute_AuthorizationRequired
as_uac_conf_V1_option_query(FASP_AUTH_AuthorizationURL)                 hcn_FASP_AUTH, use_attribute_AuthorizationURL
as_uac_conf_V1_option_query(FASP_AUTH_AuthorizationSOAPAction)          hcn_FASP_AUTH, use_attribute_AuthorizationSOAPAction
as_uac_conf_V1_option_query(FASP_AUTH_TargetRateCapPerFlow)             hcn_FASP_AUTH, use_attribute_TargetRateCapPerFlow
as_uac_conf_V1_option_query(FASP_AUTH_MinRateCapPerFlow)                hcn_FASP_AUTH, use_attribute_MinRateCapPerFlow
as_uac_conf_V1_option_query(FASP_AUTH_AllowedCipher)                    hcn_FASP_AUTH, use_attribute_AllowedCipher

as_uac_conf_V1_option_query(CENTRAL_HttpPort)                           hcn_CENTRAL, use_attribute_HttpPort
as_uac_conf_V1_option_query(CENTRAL_HttpAddress)                        hcn_CENTRAL, use_attribute_HttpAddress

as_uac_conf_V1_option_query(DATABASE_Adapter)                           hcn_DATABASE, use_attribute_Adapter
as_uac_conf_V1_option_query(DATABASE_Server)                            hcn_DATABASE, use_attribute_Server
as_uac_conf_V1_option_query(DATABASE_Port)                              hcn_DATABASE, use_attribute_Port
as_uac_conf_V1_option_query(DATABASE_User)                              hcn_DATABASE, use_attribute_User
as_uac_conf_V1_option_query(DATABASE_Password)                          hcn_DATABASE, use_attribute_Password
as_uac_conf_V1_option_query(DATABASE_DatabaseName)                      hcn_DATABASE, use_attribute_DatabaseName
as_uac_conf_V1_option_query(DATABASE_ExitOnDatabaseError)               hcn_DATABASE, use_attribute_ExitOnDatabaseError
as_uac_conf_V1_option_query(DATABASE_Threads)                           hcn_DATABASE, use_attribute_Threads
as_uac_conf_V1_option_query(DATABASE_SessionProgress)                   hcn_DATABASE, use_attribute_SessionProgress
as_uac_conf_V1_option_query(DATABASE_SessionProgressInterval)           hcn_DATABASE, use_attribute_SessionProgressInterval
as_uac_conf_V1_option_query(DATABASE_FileEvents)                        hcn_DATABASE, use_attribute_FileEvents
as_uac_conf_V1_option_query(DATABASE_FileProgress)                      hcn_DATABASE, use_attribute_FileProgress
as_uac_conf_V1_option_query(DATABASE_FileProgressInterval)              hcn_DATABASE, use_attribute_FileProgressInterval
as_uac_conf_V1_option_query(DATABASE_FilesPerSession)                   hcn_DATABASE, use_attribute_FilesPerSession
as_uac_conf_V1_option_query(DATABASE_IgnoreEmptyFiles)                  hcn_DATABASE, use_attribute_IgnoreEmptyFiles
as_uac_conf_V1_option_query(DATABASE_IgnoreSkippedFiles)                hcn_DATABASE, use_attribute_IgnoreSkippedFiles
as_uac_conf_V1_option_query(DATABASE_IgnoreNoTransferFiles)             hcn_DATABASE, use_attribute_IgnoreNoTransferFiles
as_uac_conf_V1_option_query(DATABASE_RateEvents)                        hcn_DATABASE, use_attribute_RateEvents

as_uac_conf_V1_option_query(FASP_BindIpAddress)                         hcn_FASP, use_attribute_BindIpAddress
as_uac_conf_V1_option_query(FASP_BindUdpPort)                           hcn_FASP, use_attribute_BindUdpPort
as_uac_conf_V1_option_query(FASP_LogStatsInterval)                      hcn_FASP, use_attribute_LogStatsInterval
as_uac_conf_V1_option_query(FASP_SessiniOptimization)                   hcn_FASP, use_attribute_SessiniOptimization
as_uac_conf_V1_option_query(FASP_DisableBatching)                       hcn_FASP, use_attribute_DisableBatching
as_uac_conf_V1_option_query(FASP_FileCreateMode)                        hcn_FASP, use_attribute_FileCreateMode
as_uac_conf_V1_option_query(FASP_FileCreateGrantMask)                   hcn_FASP, use_attribute_FileCreateGrantMask
as_uac_conf_V1_option_query(FASP_DirectoryCreateMode)                   hcn_FASP, use_attribute_DirectoryCreateMode
as_uac_conf_V1_option_query(FASP_DirectoryCreateGrantMask)              hcn_FASP, use_attribute_DirectoryCreateGrantMask
as_uac_conf_V1_option_query(FASP_ReadBlockSize)                         hcn_FASP, use_attribute_ReadBlockSize
as_uac_conf_V1_option_query(FASP_WriteBlockSize)                        hcn_FASP, use_attribute_WriteBlockSize
as_uac_conf_V1_option_query(FASP_MaxSockBuffer)                         hcn_FASP, use_attribute_MaxSockBuffer
as_uac_conf_V1_option_query(FASP_MinSockBuffer)                         hcn_FASP, use_attribute_MinSockBuffer
as_uac_conf_V1_option_query(FASP_Exclude)                               hcn_FASP
as_uac_conf_V1_option_query(FASP_ResumeSuffix)                          hcn_FASP, use_attribute_ResumeSuffix
as_uac_conf_V1_option_query(FASP_UseFileCache)                          hcn_FASP, use_attribute_UseFileCache
as_uac_conf_V1_option_query(FASP_MaxFileCacheBuffer)                    hcn_FASP, use_attribute_MaxFileCacheBuffer
as_uac_conf_V1_option_query(FASP_LicenseFile)                           hcn_FASP, use_attribute_LicenseFile
as_uac_conf_V1_option_query(FASP_PreserveAttributes)                    hcn_FASP, use_attribute_PreserveAttributes
as_uac_conf_V1_option_query(FASP_Overwrite)                             hcn_FASP, use_attribute_Overwrite
as_uac_conf_V1_option_query(FASP_FileManifest)                          hcn_FASP, use_attribute_FileManifest
as_uac_conf_V1_option_query(FASP_FileManifestPath)                      hcn_FASP, use_attribute_FileManifestPath
as_uac_conf_V1_option_query(FASP_PreCalculateJobSize)                   hcn_FASP, use_attribute_PreCalculateJobSize

as_uac_conf_V1_option_query(WEB_SshPort)                                hcn_WEB, use_attribute_SshPort
as_uac_conf_V1_option_query(WEB_UdpPort)                                hcn_WEB, use_attribute_UdpPort
as_uac_conf_V1_option_query(WEB_Policy)                                 hcn_WEB, use_attribute_Policy
as_uac_conf_V1_option_query(WEB_BandwidthCap)                           hcn_WEB, use_attribute_BandwidthCap
as_uac_conf_V1_option_query(WEB_MinRate)                                hcn_WEB, use_attribute_MinRate
as_uac_conf_V1_option_query(WEB_LockPolicy)                             hcn_WEB, use_attribute_LockPolicy
as_uac_conf_V1_option_query(WEB_LockTargetRate)                         hcn_WEB, use_attribute_LockTargetRate
as_uac_conf_V1_option_query(WEB_LockMinRate)                            hcn_WEB, use_attribute_LockMinRate
as_uac_conf_V1_option_query(WEB_PathMTU)                                hcn_WEB, use_attribute_PathMTU
as_uac_conf_V1_option_query(WEB_DetectBW)                               hcn_WEB, use_attribute_DetectBW
as_uac_conf_V1_option_query(WEB_TargetRate)                             hcn_WEB, use_attribute_TargetRate
as_uac_conf_V1_option_query(WEB_Encryption)                             hcn_WEB, use_attribute_Encryption
as_uac_conf_V1_option_query(WEB_HttpFallback)                           hcn_WEB, use_attribute_HttpFallback
as_uac_conf_V1_option_query(WEB_HttpFallbackPort)                       hcn_WEB, use_attribute_HttpFallbackPort
as_uac_conf_V1_option_query(WEB_HttpsFallbackPort)                      hcn_WEB, use_attribute_HttpsFallbackPort

as_uac_conf_V1_option_query(WEB_AsperaServer)                           hcn_WEB, use_attribute_AsperaServer
as_uac_conf_V1_option_query(WEB_Version)                                hcn_WEB, use_attribute_Version
as_uac_conf_V1_option_query(WEB_LinkCapacity)                           hcn_WEB, use_attribute_LinkCapacity

#undef as_uac_conf_V1_option_query
#endif


#ifdef as_uac_vlink_V1_option_query
as_uac_vlink_V1_option_query(ID)                                        use_attribute_ID

as_uac_vlink_V1_option_query(On)                                        use_attribute_On
as_uac_vlink_V1_option_query(InboundAggregateCapKbps)                   use_attribute_InboundAggregateCapKbps
as_uac_vlink_V1_option_query(OutboundAggregateCapKbps)                  use_attribute_OutboundAggregateCapKbps
as_uac_vlink_V1_option_query(McastInterfaceAddress)                     use_attribute_McastInterfaceAddress
as_uac_vlink_V1_option_query(McastGroupAddress)                         use_attribute_McastGroupAddress

as_uac_vlink_V1_option_query(UpDown)                                    use_attribute_UpDown
as_uac_vlink_V1_option_query(CapacityIn)                                use_attribute_CapacityIn
as_uac_vlink_V1_option_query(CapacityOut)                               use_attribute_CapacityOut
as_uac_vlink_V1_option_query(IF_ADDRESS)                                use_attribute_IF_ADDRESS
as_uac_vlink_V1_option_query(MCAST_ADDRESS)                             use_attribute_MCAST_ADDRESS

as_uac_vlink_V1_option_query(TargetQueue)                               use_attribute_TargetQueue
as_uac_vlink_V1_option_query(MinQueue)                                  use_attribute_MinQueue
as_uac_vlink_V1_option_query(TightnessIn)                               use_attribute_TightnessIn
as_uac_vlink_V1_option_query(TightnessOut)                              use_attribute_TightnessOut
as_uac_vlink_V1_option_query(QB_OVER_QMAX)                              use_attribute_QB_OVER_QMAX

#undef as_uac_vlink_V1_option_query
#endif


#ifdef as_uac_http_session_start_option_query
as_uac_http_session_start_option_query(id)                              hcn_id
as_uac_http_session_start_option_query(operation)                       hcn_operation
as_uac_http_session_start_option_query(token)                           hcn_token
as_uac_http_session_start_option_query(cookie)                          hcn_cookie
as_uac_http_session_start_option_query(source)                          hard_config_search_terminator
as_uac_http_session_start_option_query(destination)                     hcn_destination
as_uac_http_session_start_option_query(createdir)                       hcn_createdir
as_uac_http_session_start_option_query(mustbedir)                       hcn_mustbedir
as_uac_http_session_start_option_query(encryption)                      hcn_encryption
as_uac_http_session_start_option_query(resume)                          hcn_resume
as_uac_http_session_start_option_query(overwrite)                       hcn_overwrite
as_uac_http_session_start_option_query(user)                            hcn_user
as_uac_http_session_start_option_query(rate_limit)                      hcn_rate, hcn_limit
as_uac_http_session_start_option_query(license)                         hcn_license
as_uac_http_session_start_option_query(transfer_precalc)                hcn_pretransfer, hcn_precalculate

#undef as_uac_http_session_start_option_query
#endif


#ifdef as_uac_http_session_end_option_query
as_uac_http_session_end_option_query(reason)                            hcn_reason
as_uac_http_session_end_option_query(code)                              hcn_code
as_uac_http_session_end_option_query(file_count)                        hcn_stats, hcn_aggregate, hcn_files
as_uac_http_session_end_option_query(byte_count)                        hcn_stats, hcn_aggregate, hcn_bytes

#undef as_uac_http_session_end_option_query
#endif
