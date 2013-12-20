#ifndef as_uac_meta_data_defined
#define as_uac_meta_data_defined

typedef enum {
    unknown_as_uac_index = 0,


        /*
            The following comment will become true as soon as clients begin
            doing their own translations using this list:

            Do not under any circumstances remove entries from this list or
            add entries anywhere but at the end!  Deleting or inserting items
            will change the remaining values and screw up backward
            compatibility.
         */

    as_uac_user_option_index_user_value = 1,
    as_uac_user_option_index_name,
    as_uac_user_option_index_group,
    as_uac_user_option_index_realm,
    as_uac_user_option_index_authorization_value,
    as_uac_user_option_index_authorization_transfer_in_value,
    as_uac_user_option_index_authorization_transfer_in_external_provider_url,
    as_uac_user_option_index_authorization_transfer_in_external_provider_soap_action,
    as_uac_user_option_index_authorization_transfer_out_value,
    as_uac_user_option_index_authorization_transfer_out_external_provider_url,
    as_uac_user_option_index_authorization_transfer_out_external_provider_soap_action,
    as_uac_user_option_index_token_encryption_type,
    as_uac_user_option_index_token_encryption_key,
    as_uac_user_option_index_token_life_seconds,
    as_uac_user_option_index_transfer_in_bandwidth_aggregate_trunk_id,
    as_uac_user_option_index_transfer_in_bandwidth_flow_target_rate_cap,
    as_uac_user_option_index_transfer_in_bandwidth_flow_target_rate_default,
    as_uac_user_option_index_transfer_in_bandwidth_flow_target_rate_lock,
    as_uac_user_option_index_transfer_in_bandwidth_flow_min_rate_cap,
    as_uac_user_option_index_transfer_in_bandwidth_flow_min_rate_default,
    as_uac_user_option_index_transfer_in_bandwidth_flow_min_rate_lock,
    as_uac_user_option_index_transfer_in_bandwidth_flow_policy_allowed,
    as_uac_user_option_index_transfer_in_bandwidth_flow_policy_default,
    as_uac_user_option_index_transfer_in_bandwidth_flow_policy_lock,
    as_uac_user_option_index_transfer_in_bandwidth_flow_priority_cap,
    as_uac_user_option_index_transfer_in_bandwidth_flow_priority_default,
    as_uac_user_option_index_transfer_in_bandwidth_flow_priority_lock,
    as_uac_user_option_index_transfer_out_bandwidth_aggregate_trunk_id,
    as_uac_user_option_index_transfer_out_bandwidth_flow_target_rate_cap,
    as_uac_user_option_index_transfer_out_bandwidth_flow_target_rate_default,
    as_uac_user_option_index_transfer_out_bandwidth_flow_target_rate_lock,
    as_uac_user_option_index_transfer_out_bandwidth_flow_min_rate_cap,
    as_uac_user_option_index_transfer_out_bandwidth_flow_min_rate_default,
    as_uac_user_option_index_transfer_out_bandwidth_flow_min_rate_lock,
    as_uac_user_option_index_transfer_out_bandwidth_flow_policy_allowed,
    as_uac_user_option_index_transfer_out_bandwidth_flow_policy_default,
    as_uac_user_option_index_transfer_out_bandwidth_flow_policy_lock,
    as_uac_user_option_index_transfer_out_bandwidth_flow_priority_cap,
    as_uac_user_option_index_transfer_out_bandwidth_flow_priority_default,
    as_uac_user_option_index_transfer_out_bandwidth_flow_priority_lock,
    as_uac_user_option_index_transfer_encryption_allowed_cipher,
    as_uac_user_option_index_transfer_protocol_options_bind_ip_address,
    as_uac_user_option_index_transfer_protocol_options_bind_udp_port,
    as_uac_user_option_index_transfer_protocol_options_disable_batching,
    as_uac_user_option_index_transfer_protocol_options_sessini_optimization,
    as_uac_user_option_index_transfer_protocol_options_max_sock_buffer,
    as_uac_user_option_index_transfer_protocol_options_min_sock_buffer,
    as_uac_user_option_index_transfer_protocol_options_rate_instru_type,
    as_uac_user_option_index_file_create_mode,
    as_uac_user_option_index_file_create_grant_mask,
    as_uac_user_option_index_directory_create_mode,
    as_uac_user_option_index_directory_create_grant_mask,
    as_uac_user_option_index_read_block_size,
    as_uac_user_option_index_write_block_size,
    as_uac_user_option_index_use_file_cache,
    as_uac_user_option_index_max_file_cache_buffer,
    as_uac_user_option_index_ring_buf_units,
    as_uac_user_option_index_resume_suffix,
    as_uac_user_option_index_preserve_attributes,
    as_uac_user_option_index_overwrite,
    as_uac_user_option_index_file_manifest,
    as_uac_user_option_index_file_manifest_path,
    as_uac_user_option_index_pre_calculate_job_size,
    as_uac_user_option_index_storage_rc_adaptive,
    as_uac_user_option_index_storage_rc_buf_min,
    as_uac_user_option_index_storage_rc_buf_target,
    as_uac_user_option_index_storage_rc_buf_delta,
    as_uac_user_option_index_file_exclude,
    as_uac_user_option_index_precedence,
    as_uac_trunk_option_index_trunk_name,
    as_uac_trunk_option_index_trunk_id,
    as_uac_trunk_option_index_trunk_on,
    as_uac_trunk_option_index_trunk_capacity,
    as_uac_trunk_option_index_trunk_mcast_iface_address,
    as_uac_trunk_option_index_trunk_mcast_group_address,
    as_uac_trunk_option_index_trunk_mcast_port,
    as_uac_trunk_option_index_trunk_target_queue,
    as_uac_trunk_option_index_trunk_min_queue,
    as_uac_trunk_option_index_trunk_tightness_in,
    as_uac_trunk_option_index_trunk_tightness_out,
    as_uac_trunk_option_index_trunk_qb_over_qmax,
    as_uac_docroot_option_index_absolute,
    as_uac_docroot_option_index_show_as,
    as_uac_docroot_option_index_description,
    as_uac_docroot_option_index_filter,
    as_uac_docroot_option_index_read_allowed,
    as_uac_docroot_option_index_write_allowed,
    as_uac_docroot_option_index_dir_allowed,
    as_uac_central_server_option_index_address,
    as_uac_central_server_option_index_port,
    as_uac_database_option_index_adapter,
    as_uac_database_option_index_server,
    as_uac_database_option_index_port,
    as_uac_database_option_index_user,
    as_uac_database_option_index_password,
    as_uac_database_option_index_database_name,
    as_uac_database_option_index_threads,
    as_uac_database_option_index_exit_on_database_error,
    as_uac_database_option_index_session_progress,
    as_uac_database_option_index_session_progress_interval,
    as_uac_database_option_index_file_events,
    as_uac_database_option_index_file_progress,
    as_uac_database_option_index_file_errors,
    as_uac_database_option_index_file_progress_interval,
    as_uac_database_option_index_files_per_session,
    as_uac_database_option_index_ignore_empty_files,
    as_uac_database_option_index_ignore_skipped_files,
    as_uac_database_option_index_ignore_no_transfer_files,
    as_uac_database_option_index_rate_events,
    as_uac_http_server_option_index_cert_file,
    as_uac_http_server_option_index_key_file,
    as_uac_http_server_option_index_bind_address,
    as_uac_http_server_option_index_mgmt_address,
    as_uac_http_server_option_index_file_root,
    as_uac_http_server_option_index_restartable_transfers,
    as_uac_http_server_option_index_session_activity_timeout,
    as_uac_http_server_option_index_http_port,
    as_uac_http_server_option_index_https_port,
    as_uac_http_server_option_index_enable_http,
    as_uac_http_server_option_index_enable_https,
    as_uac_http_server_option_index_reset_key,
    as_uac_http_session_start_option_index_id,
    as_uac_http_session_start_option_index_operation,
    as_uac_http_session_start_option_index_token,
    as_uac_http_session_start_option_index_cookie,
    as_uac_http_session_start_option_index_source,
    as_uac_http_session_start_option_index_destination,
    as_uac_http_session_start_option_index_createdir,
    as_uac_http_session_start_option_index_mustbedir,
    as_uac_http_session_start_option_index_encryption,
    as_uac_http_session_start_option_index_resume,
    as_uac_http_session_start_option_index_overwrite,
    as_uac_http_session_start_option_index_user,
    as_uac_http_session_start_option_index_rate_limit,
    as_uac_http_session_start_option_index_license,
    as_uac_http_session_start_option_index_transfer_precalc,
    as_uac_http_session_end_option_index_reason,
    as_uac_http_session_end_option_index_code,
    as_uac_http_session_end_option_index_file_count,
    as_uac_http_session_end_option_index_byte_count,
    as_uac_user_option_index_transfer_encryption_content_protection_required,
    as_uac_user_option_index_transfer_encryption_content_protection_strong_pass_required,

    final_as_uac_option_index

} e_as_uac_option_indices;

typedef struct
{
    e_as_uac_option_indices index;

    const char *value_limits;
    const char *field_label;
    const char *grouping;
    const char *help_text;

} as_uac_meta_data;

#endif

#ifndef as_uac_declare_option_storage
extern const as_uac_meta_data as_uac_option_storage[];
#else
#undef as_uac_declare_option_storage

as_uac_meta_data as_uac_option_storage[] =
{
    {
        as_uac_user_option_index_transfer_in_bandwidth_flow_target_rate_cap,
        "",
        "Incoming Target Rate Cap (Kbps):",
        "|WINUSERS:Incoming Bandwidth|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "The Target Rate Cap for incoming transfers.\nThis is the maximum target rate that a transfer can request, in kilobits per second.\nNo transfer may be adjusted above this setting, at any time.\nThe default setting of Unlimited signifies no Target Rate Cap.\nClients requesting transfers with initial rates above the Target Rate Cap will be slowed down."
    },

    {
        as_uac_user_option_index_transfer_in_bandwidth_flow_min_rate_cap,
        "",
        "Incoming Minimum Rate Cap (Kbps):",
        "|WINUSERS:Incoming Bandwidth|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "The Minimum Rate Cap for incoming transfers.\nThis is the highest Minimum Rate that a transfer can request, in kilobits per second.\nThe Minimum Rate is the level beyond which a transfer will not slow down, despite network congestion or availability.\nThe default value of Unlimited effectively turns off the Minimum Rate Cap."
    },

    {
        as_uac_user_option_index_transfer_in_bandwidth_flow_policy_allowed,
        "",
        "Incoming Bandwidth Policy Allowed:",
        "|WINUSERS:Incoming Bandwidth|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "The value chosen sets the allowed Bandwidth Policy for incoming transfers.\nAspera transfers use fixed, high, fair and low policies to accommodate network-sharing requirements.\nWhen set to any, the server will not deny any transfer based on policy setting.\nWhen set to high, transfers with a Policy of high and less aggressive transfer policies (e.g. fair or low) will be permitted.\nFixed transfers will be denied.\nWhen set to low, only transfers with a Bandwidth Policy of low will be allowed."
    },

    {
        as_uac_user_option_index_transfer_in_bandwidth_flow_priority_cap,
        "",
        "Incoming Priority Cap:",
        "|JAVA:General|",
        "Priority cap, takes value \"high\" or \"normal\".\nTo allow high priority, use \"high\".\nTo enforce normal priority, use \"normal\"."
    },

    {
        as_uac_user_option_index_transfer_out_bandwidth_flow_target_rate_cap,
        "",
        "Outgoing Target Rate Cap (Kbps):",
        "|WINUSERS:Outgoing Bandwidth|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "The Target Rate Cap for outgoing transfers.\nThis is the maximum target rate that a transfer can request, in kilobits per second.\nNo transfer may be adjusted above this setting, at any time.\nThe default setting of Unlimited signifies no Target Rate Cap.\nClients requesting transfers with initial rates above the Target Rate Cap will be slowed down."
    },

    {
        as_uac_user_option_index_transfer_out_bandwidth_flow_min_rate_cap,
        "",
        "Outgoing Minimum Rate Cap (Kbps):",
        "|WINUSERS:Outgoing Bandwidth|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "The Minimum Rate Cap for outgoing transfers.\nThis is the highest Minimum Rate that a transfer can request, in kilobits per second.\nThe Minimum Rate is the level beyond which a transfer will not slow down, despite network congestion or availability.\nThe default value of Unlimited effectively turns off the Minimum Rate Cap."
    },

    {
        as_uac_user_option_index_transfer_out_bandwidth_flow_policy_allowed,
        "",
        "Outgoing Bandwidth Policy Allowed:",
        "|WINUSERS:Outgoing Bandwidth|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "The value chosen sets the allowed Bandwidth Policy for outgoing transfers.\nAspera transfers use fixed, high, fair and low policies to accommodate network-sharing requirements.\nWhen set to any, the server will not deny any transfer based on policy setting.\nWhen set to high, transfers with a Policy of high and less aggressive transfer policies (e.g. fair or low) will be permitted.\nFixed transfers will be denied.\nWhen set to low, only transfers with a Bandwidth Policy of low will be allowed."
    },

    {
        as_uac_user_option_index_transfer_out_bandwidth_flow_priority_cap,
        "",
        "Outgoing Priority Cap:",
        "|JAVA:General|",
        "Priority cap, takes value \"high\" or \"normal\".\nTo allow high priority, use \"high\".\nTo enforce normal priority, use \"normal\"."
    },

    {
        as_uac_user_option_index_transfer_encryption_allowed_cipher,
        "",
        "Encryption Allowed:",
        "|WINUSERS:Encryption|JAVA_TOP:Authorization|JAVA_TOP_P2P:Authorization|JAVA_USER:Authorization|",
        "Describes the type of transfer encryption accepted by this computer.\nWhen set to any the computer allows both encrypted and non-encrypted transfers.\nWhen set to none the computer restricts transfers to non-encrypted transfers only.\nWhen set to aes-128 the computer restricts transfers to encrypted transfers only."
    },

    {
        as_uac_user_option_index_user_value,
        "",
        "User Specific Settings:",
        "|JAVA:General|",
        "(User Options) Help Text for user_value"
    },

    {
        as_uac_user_option_index_name,
        "",
        "Name:",
        "|JAVA:General|",
        "(User Options) Help Text for Name"
    },

    {
        as_uac_user_option_index_group,
        "",
        "Force membership in Group:",
        "|JAVA:General|",
        "(User Options) Help Text for group"
    },

    {
        as_uac_user_option_index_realm,
        "",
        "Realm:",
        "|JAVA:General|",
        "(User Options) Help Text for realm"
    },

    {
        as_uac_user_option_index_authorization_value,
        "",
        "Authorization Settings:",
        "|JAVA:General|",
        "(User Options) Help Text for authorization_value"
    },

    {
        as_uac_user_option_index_authorization_transfer_in_value,
        "choices:allow;deny;token;;",
        "Incoming Transfers:",
        "|JAVA_TOP:Authorization|JAVA_TOP_P2P:Authorization|JAVA_USER:Authorization|",
        "The default setting of allow allows users to transfer to this computer.\nSetting this to deny will prevent transfers to this computer.\nWhen set to token, only transfers initiated with valid tokens will be allowed to transfer to this computer.\nToken-based transfers are typically employed by web applications such as Faspex and require a Token Encryption Key."
    },

    {
        as_uac_user_option_index_authorization_transfer_in_external_provider_url,
        "subtype:url;;empty_desc:<None>;;",
        "Incoming External Provider URL:",
        "|JAVA_TOP:Authorization|JAVA_TOP_P2P:Authorization|JAVA_USER:Authorization|",
        "The value entered should be the URL of the external authorization provider for incoming transfers.\nThe default empty setting disables external authorization.\nAspera servers can be configured to check with an external authorization provider.\nThis SOAP authorization mechanism can be useful to organizations requiring custom authorization rules."
    },

    {
        as_uac_user_option_index_authorization_transfer_in_external_provider_soap_action,
        "empty_desc:<None>;;",
        "Incoming External Provider SOAP Action:",
        "|JAVA_TOP:Authorization|JAVA_TOP_P2P:Authorization|JAVA_USER:Authorization|",
        "The SOAP action required by the external authorization provider for incoming transfers.\nRequired if External Authorization is enabled."
    },

    {
        as_uac_user_option_index_authorization_transfer_out_value,
        "choices:allow;deny;token;;",
        "Outgoing Transfers:",
        "|JAVA_TOP:Authorization|JAVA_TOP_P2P:Authorization|JAVA_USER:Authorization|",
        "The default setting of allow allows users to transfer from this computer.\nSetting this to deny will prevent transfers from this computer.\nWhen set to require token, only transfers initiated with valid tokens will be allowed to transfer from this computer.\nToken-based transfers are typically employed by web applications such as Faspex and require a Token Encryption Key."
    },

    {
        as_uac_user_option_index_authorization_transfer_out_external_provider_url,
        "subtype:url;;empty_desc:<None>;;",
        "Outgoing External Provider URL:",
        "|JAVA_TOP:Authorization|JAVA_TOP_P2P:Authorization|JAVA_USER:Authorization|",
        "The value entered should be the URL of the external authorization provider for outgoing transfers.\nThe default empty setting disables external authorization.\nAspera servers can be configured to check with an external authorization provider.\nThis SOAP authorization mechanism can be useful to organizations requiring custom authorization rules."
    },

    {
        as_uac_user_option_index_authorization_transfer_out_external_provider_soap_action,
        "empty_desc:<None>;;",
        "Outgoing External Provider SOAP Action:",
        "|JAVA_TOP:Authorization|JAVA_TOP_P2P:Authorization|JAVA_USER:Authorization|",
        "The SOAP action required by the external authorization provider for outgoing transfers.\nRequired if External Authorization is enabled."
    },

    {
        as_uac_user_option_index_token_encryption_type,
        "",
        "Token Encryption Cipher:",
        "|JAVA_TOP:Authorization|JAVA_TOP_P2P:Authorization|JAVA_USER:Authorization|",
        "The cipher used to generate encrypted authorization tokens (not used to encrypt transfer data).\nOnly used with token-based authorization (primarily used with web-based transfer applications)."
    },

    {
        as_uac_user_option_index_token_encryption_key,
        "empty_desc:<None>;;",
        "Token Encryption Key:",
        "|JAVA_TOP:Authorization|JAVA_TOP_P2P:Authorization|JAVA_USER:Authorization|",
        "This is the secret passphrase used to generate encrypted authorization tokens (not used to encrypt transfer data).\nOnly used with token-based authorization (primarily used with web-based transfer applications)."
    },

    {
        as_uac_user_option_index_token_life_seconds,
        "",
        "Token Life (seconds):",
        "|JAVA_TOP:Authorization|JAVA_TOP_P2P:Authorization|JAVA_USER:Authorization|",
        "Sets the time before authorization tokens expire.\nOnly used with token-based authorization (primarily used with web-based transfer applications)."
    },

    {
        as_uac_user_option_index_transfer_in_bandwidth_aggregate_trunk_id,
        "subtype:trunk_id;;",
        "Incoming Vlink ID:",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "\nThe value sets the Vlink ID for incoming transfers.\nVlinks are a mechanism to define aggregate transfer policies.\nThe default setting of 0 disables this Vlink.\nOne Vlink (the virtual equivalent of a network trunk) represents a bandwidth allowance that may be allocated to a node, group, or user.\nVlink IDs are defined in each Vlink created in the Aspera Console or GUI.\nThe Vlink ID is a unique numeric identifier."
    }, 

    {
        as_uac_user_option_index_transfer_in_bandwidth_flow_target_rate_default,
        "",
        "Incoming Target Rate Default (Kbps):",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "This value represents the initial transfer rate for incoming transfers, in kilobits per second.\nUsers may be able to modify this rate in real time as allowed by the software in use."
    },

    {
        as_uac_user_option_index_transfer_in_bandwidth_flow_target_rate_lock,
        "",
        "Incoming Target Rate Lock:",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "After an incoming transfer is started, its target rate may be modified in real time.\nThe default setting of false gives users the ability to adjust the transfer rate.\nA setting of true prevents real-time modification of the transfer rate."
    },

    {
        as_uac_user_option_index_transfer_in_bandwidth_flow_min_rate_default,
        "",
        "Incoming Minimum Rate Default (Kbps):",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "This value represents the initial minimum rate for incoming transfers, in kilobits per second.\nUsers may be able to modify this rate in real time as allowed by the software in use.\nThis setting is not relevant to transfers with a Policy of Fixed."
    },

    {
        as_uac_user_option_index_transfer_in_bandwidth_flow_min_rate_lock,
        "",
        "Incoming Minimum Rate Lock:",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "After an incoming transfer is started, its minimum rate may be modified in real time.\nThe default setting of false gives users the ability to adjust the transfer's minimum rate.\nA setting of true prevents real-time modification of the transfer rate.\nThis setting is not relevant to transfers with a Policy of Fixed."
    },

    {
        as_uac_user_option_index_transfer_in_bandwidth_flow_policy_default,
        "",
        "Incoming Bandwidth Policy Default:",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "The value chosen sets the default Bandwidth Policy for incoming transfers.\nAspera transfers use fixed, high, fair and low policies to accommodate network-sharing requirements."
    },

    {
        as_uac_user_option_index_transfer_in_bandwidth_flow_policy_lock,
        "",
        "Incoming Bandwidth Policy Lock:",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "After an incoming transfer is started, its Policy may be modified in real time.\nThe default setting of false gives users the ability to adjust the transfer's Policy.\nA setting of true prevents real-time modification of the Policy."
    },

    {
        as_uac_user_option_index_transfer_in_bandwidth_flow_priority_default,
        "",
        "Incoming Priority Default:",
        "|JAVA:General|",
        "(User Options) Help Text for transfer_in_bandwidth_flow_priority_default"
    },

    {
        as_uac_user_option_index_transfer_in_bandwidth_flow_priority_lock,
        "",
        "Incoming Priority Lock:",
        "|JAVA:General|",
        "(User Options) Help Text for transfer_in_bandwidth_flow_priority_lock"
    },

    {
        as_uac_user_option_index_transfer_out_bandwidth_aggregate_trunk_id,
        "subtype:trunk_id;;",
        "Outgoing Vlink ID:",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "\nThe value sets the Vlink ID for outgoing transfers.\nVlinks are a mechanism to define aggregate transfer policies.\nThe default setting of 0 disables Vlinks.\nOne Vlink is the virtual equivalent of a network trunk and represents a bandwidth allowance that may be allocated to a node, group, or user.\nVlink IDs are defined in each Vlink created in the Aspera Console or GUI. The Vlink ID is a unique numeric identifier."
    },

    {
        as_uac_user_option_index_transfer_out_bandwidth_flow_target_rate_default,
        "",
        "Outgoing Target Rate Default (Kbps):",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "This value represents the initial rate for outgoing transfers, in kilobits per second.\nUsers may be able to modify this rate in real time as allowed by the software in use."
    },

    {
        as_uac_user_option_index_transfer_out_bandwidth_flow_target_rate_lock,
        "",
        "Outgoing Target Rate Lock:",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "After an outgoing transfer is started, its target rate may be modified in real time.\nThe default setting of false gives users the ability to adjust the transfer rate.\nA setting of true prevents real-time modification of the transfer rate."
    },

    {
        as_uac_user_option_index_transfer_out_bandwidth_flow_min_rate_default,
        "",
        "Outgoing Minimum Rate Default (Kbps):",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "This value represents the initial minimum rate for outgoing transfers, in kilobits per second.\nUsers may be able to modify this rate in real time as allowed by the software in use.\nThis setting is not relevant to transfers with a Policy of Fixed."
    },

    {
        as_uac_user_option_index_transfer_out_bandwidth_flow_min_rate_lock,
        "",
        "Outgoing Minimum Rate Lock:",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "After an outgoing transfer is started, its minimum rate may be modified in real time.\nThe default setting of false gives users the ability to adjust the transfer's minimum rate.\nA setting of true prevents real-time modification of the transfer rate.\nThis setting is not relevant to transfers with a Policy of Fixed."
    },

    {
        as_uac_user_option_index_transfer_out_bandwidth_flow_policy_default,
        "",
        "Outgoing Bandwidth Policy Default:",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "The value chosen sets the default Bandwidth Policy for outgoing transfers.\nAspera transfers use fixed, high, fair and low policies to accommodate network-sharing requirements."
    },

    {
        as_uac_user_option_index_transfer_out_bandwidth_flow_policy_lock,
        "",
        "Outgoing Bandwidth Policy Lock:",
        "|JAVA_TOP:Bandwidth|JAVA_TOP_P2P:Bandwidth|JAVA_USER:Bandwidth|",
        "After an outgoing transfer is started, its Policy may be modified in real time.\nThe default setting of false gives users the ability to adjust the transfer's Policy.\nA setting of true prevents real-time modification of the Policy."
    },

    {
        as_uac_user_option_index_transfer_out_bandwidth_flow_priority_default,
        "",
        "Outgoing Priority Default:",
        "|JAVA:General|",
        "(User Options) Help Text for transfer_out_bandwidth_flow_priority_default"
    },

    {
        as_uac_user_option_index_transfer_out_bandwidth_flow_priority_lock,
        "",
        "Outgoing Priority Lock:",
        "|JAVA:General|",
        "(User Options) Help Text for transfer_out_bandwidth_flow_priority_lock"
    },

    {
        as_uac_user_option_index_transfer_protocol_options_bind_ip_address,
        "subtype:ip_address;;empty_desc:<Default Interface>;;",
        "Bind IP Address:",
        "|JAVA_TOP:Advanced Network Options|JAVA_TOP_P2P:Advanced Network Options|JAVA_USER:Advanced Network Options|",
        "Specify an IP address for the server to bind its UDP connection.\nIf a valid IP address is given, the server sends and receives UDP packets ONLY on the interface corresponding to that IP address"
    },

    {
        as_uac_user_option_index_transfer_protocol_options_bind_udp_port,
        "range:1;65535;;",
        "Bind UDP Port:",
        "|JAVA_TOP:Advanced Network Options|JAVA_TOP_P2P:Advanced Network Options|JAVA_USER:Advanced Network Options|",
        "Specify a port number for the server to bind its UDP connection.\nValid port numbers range between 1 and 65535."
    },

    {
        as_uac_user_option_index_transfer_protocol_options_disable_batching,
        "",
        "Disable Packet Batching:",
        "|JAVA_TOP:Advanced Network Options|JAVA_TOP_P2P:Advanced Network Options|JAVA_USER:Advanced Network Options|",
        "When set to true, send UDP datagrams individually, not in batches.\nThis results in smoother data traffic at a cost of higher CPU usage."
    },

    {
        as_uac_user_option_index_transfer_protocol_options_sessini_optimization,
        "",
        "Sessini optimization:",
        "|JAVA:General|",
        "(User Options) Help Text for transfer_protocol_options_sessini_optimization"
    },

    {
        as_uac_user_option_index_transfer_protocol_options_max_sock_buffer,
        "",
        "Maximum Socket Buffer (bytes):",
        "|JAVA_TOP:Advanced Network Options|JAVA_TOP_P2P:Advanced Network Options|JAVA_USER:Advanced Network Options|",
        "Upper bound the UDP socket buffer of an Aspera transfer below the input value.\nThe default of 0 will cause the Aspera sender to use its default internal buffer size, which may be different for different operating systems."
    },

    {
        as_uac_user_option_index_transfer_protocol_options_min_sock_buffer,
        "",
        "Minimum Socket Buffer (bytes):",
        "|JAVA_TOP:Advanced Network Options|JAVA_TOP_P2P:Advanced Network Options|JAVA_USER:Advanced Network Options|",
        "Set the minimum UDP socket buffer size for an Aspera transfer."
    },

    {
        as_uac_user_option_index_transfer_protocol_options_rate_instru_type,
        "",
        "Rate instrumentation type:",
        "|JAVA:General|",
        "(User Options) Help Text for transfer_protocol_options_rate_instru_type"
    },

    {
        as_uac_user_option_index_file_create_mode,
        "",
        "File Create Mode:",
#ifdef WIN32
        "|JAVA:General|",
#else
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
#endif
        "Specify file creation mode (permissions).\nIf specified, create files with these permissions (for example 0755), irrespective of\nFile Create Grant Mask and permissions of the file on the source computer.\nDoes not apply to Windows."
    },

    {
        as_uac_user_option_index_file_create_grant_mask,
        "",
        "File Create Grant Mask:",
#ifdef WIN32
        "|JAVA:General|",
#else
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
#endif
        "Used to determine mode for newly created files if File Create Mode is not specified.\nIf specified, file modes will be set to their original modes plus the Grant Mask values.\nOnly takes effect when File Create Mode is not specified.\nDoes not apply to Windows."
    },

    {
        as_uac_user_option_index_directory_create_mode,
        "",
        "Directory Create Mode:",
#ifdef WIN32
        "|JAVA:General|",
#else
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
#endif
        "Specify directory creation mode (permissions).\nIf specified, create directories with these permissions irrespective of \nDirectory Create Grant Mask and permissions of the directory on the source computer.\nDoes not apply to Windows."
    },

    {
        as_uac_user_option_index_directory_create_grant_mask,
        "",
        "Directory Create Grant Mask:",
#ifdef WIN32
        "|JAVA:General|",
#else
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
#endif
        "Used to determine mode for newly created directories if Directory Create Mode is not specified.\nIf specified, directory modes will be set to their original modes plus the Grant Mask values.\nOnly takes effect when Directory Create Mode is not specified.\nDoes not apply to Windows."
    },

    {
        as_uac_user_option_index_read_block_size,
        "",
        "Read Block Size (bytes):",
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
        "This is a performance tuning parameter for an Aspera sender.\nIt represents the number of bytes an Aspera sender reads at a time from the source disk drive.\nOnly takes effect when server is sender.\nThe default of 0 will cause the Aspera sender to use its default internal buffer size, which may be different for different operating systems."
    },

    {
        as_uac_user_option_index_write_block_size,
        "",
        "Write Block Size (bytes):",
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
        "This is a performance tuning parameter for an Aspera receiver.\nNumber of bytes an Aspera receiver writes data at a time onto disk drive.\nOnly takes effect when server is receiver.\nThe default of 0 will cause the Aspera receiver to use its default internal buffer size, which may be different for different operating systems."
    },

    {
        as_uac_user_option_index_use_file_cache,
        "",
        "Use File Cache:",
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
        "This is a performance tuning parameter for an Aspera receiver.\nEnable or disable per-file memory caching at the data receiver.\nFile level memory caching improves data write speed on Windows platforms in particular, but will use more memory.\n\nWe suggest using a file cache on systems that are transferring data at speeds close to the performance of their storage device,\nand disabling it for systems with very high concurrency (because memory utilization will grow with the number of concurrent transfers)."
    },

    {
        as_uac_user_option_index_max_file_cache_buffer,
        "",
        "Max File Cache Buffer (bytes):",
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
        "This is a performance tuning parameter for an Aspera receiver.\nThis value corresponds to the maximal size allocated for per-file memory cache (see Use File Cache).\nThe default of 0 will cause the Aspera receiver to use its internal buffer size, which may be different for different operating systems."
    },

    {
        as_uac_user_option_index_ring_buf_units,
        "",
        "Ring buffer units:",
        "|JAVA:General|",
        "(User Options) Help Text for ring_buf_units"
    },

    {
        as_uac_user_option_index_resume_suffix,
        "",
        "Resume Suffix:",
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
        "Extension name of a class of special files holding meta data information of regular data files.\nUseful in the context of resuming partially completed transfers.\nDuring resume mode (-k1/2/3), each data file has a corresponding metadata file with the same name and the pre-specified resume suffix."
    },

    {
        as_uac_user_option_index_preserve_attributes,
        "choices:none;times;;empty_desc:<N/A>;;",
        "Preserve Attributes:",
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
        "Configure file creation policy.\nWhen set to none, do not preserve the timestamp of source files.\nWhen set to times, preserve the timestamp of the source files at destination."
    },

    {
        as_uac_user_option_index_overwrite,
        "choices:allow;deny;;",
        "Overwrite:",
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
        "Overwrite is an Aspera server setting that determines whether Aspera clients are allowed to overwrite files on the server.\nBy default it is set to allow, meaning that clients uploading files to the servers will be allowed to overwrite existing files as long as file permissions allow that action.\nIf set to deny, clients uploading files to the server will not be able to overwrite existing files, regardless of file permissions."
    },

    {
        as_uac_user_option_index_file_manifest,
        "choices:text;disable;;empty_desc:<None>;;",
        "File Manifest:",
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
        "When set to text a text file \"receipt\" of all files within each transfer session is generated.\nIf set to disable no File Manifest is created.\nThe file manifest is a file containing a list of everything that was transferred in a given transfer session.\nThe filename of the File Manifest itself is automatically generated based on the transfer session's unique ID.\nThe location where each manifest is written is specified by the File Manifest Path value.\nIf no File Manifest Path is specified, the file will be generated under the destination path at the receiver, and under the first source path at the sender."

    },

    {
        as_uac_user_option_index_file_manifest_path,
        "subtype:directory;;empty_desc:<None>;;",
        "File Manifest Path:",
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
        "Specify the location where the manifest file is created (see File Manifest)"
    },

    {
        as_uac_user_option_index_pre_calculate_job_size,
        "",
        "Pre-Calculate Job Size:",
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
        "Configure the policy of calculating total job size before data transfer.\nIf set to any, follow client configurations (-o PreCalculateJobSize).\nIf set to no, disable calculating job size before transferring.\nIf set to yes, enable calculating job size before transferring."
    },

    {
        as_uac_user_option_index_storage_rc_adaptive,
        "",
        "Storage Rate Control:",
        "|JAVA_TOP:Advanced File Handling|JAVA_TOP_P2P:Advanced File Handling|JAVA_USER:Advanced File Handling|",
        "Enable/Disable disk rate control.\nWhen enabled, adjust transfer rate according to the speed of receiving I/O storage, if it becomes a bottleneck."
    },

    {
        as_uac_user_option_index_storage_rc_buf_min,
        "",
        "RC Buffer minimum:",
        "|JAVA:General|",
        "(User Options) Help Text for storage_rc_buf_min"
    },

    {
        as_uac_user_option_index_storage_rc_buf_target,
        "",
        "RC Buffer target:",
        "|JAVA:General|",
        "(User Options) Help Text for storage_rc_buf_target"
    },

    {
        as_uac_user_option_index_storage_rc_buf_delta,
        "",
        "RC Buffer delta:",
        "|JAVA:General|",
        "(User Options) Help Text for storage_rc_buf_delta"
    },

    {
        as_uac_user_option_index_file_exclude,
        "",
        "File Exclude Pattern:",
        "|JAVA:General|",
        "(User Options) Help Text for file_exclude"
    },

    {
        as_uac_user_option_index_precedence,
        "",
        "Group precedence:",
        "|JAVA:General|",
        "(User Options) Help Text for precedence"
    },

    {
        as_uac_trunk_option_index_trunk_id,
        "",
        "Vlink ID:",
        "|JAVA:General|",
        "Numeric identifier for the Vlink"
    },

    {
        as_uac_trunk_option_index_trunk_name,
        "empty_desc:<Nameless>;;",
        "Vlink Name:",
        "|JAVA_TRUNK:General|",
        "Informal name of the Vlink"
    },

    {
        as_uac_trunk_option_index_trunk_on,
        "",
        "On:",
        "|JAVA_TRUNK:General|",
        "Set to \"false\" to disable the Vlink."
    },

    {
        as_uac_trunk_option_index_trunk_capacity,
        "",
        "Capacity:",
        "|JAVA_TRUNK:General|",
        "Total bandwidth capacity of the Vlink trunk in Kbps"
    },

    {
        as_uac_trunk_option_index_trunk_mcast_iface_address,
        "",
        "Trunk Multicast Interface Address:",
        "|JAVA:General|",
        "(Trunk) Help Text for trunk_mcast_iface_address"
    },

    {
        as_uac_trunk_option_index_trunk_mcast_group_address,
        "ip_address;;",
        "Trunk Multicast Group Address:",
        "|JAVA:General|",
        "(Trunk) Help Text for trunk_mcast_group_address"
    },

    {
        as_uac_trunk_option_index_trunk_mcast_port,
        "range:1;65535;;",
        "Multicast Port:",
        "|JAVA_TRUNK:General|",
        "UDP Port on which to share Vlink status information"
    },

    {
        as_uac_trunk_option_index_trunk_target_queue,
        "",
        "Target Queue:",
        "|JAVA:General|",
        "(Trunk) Help Text for trunk_target_queue"
    },

    {
        as_uac_trunk_option_index_trunk_min_queue,
        "",
        "Minimum Queue:",
        "|JAVA:General|",
        "(Trunk) Help Text for trunk_min_queue"
    },

    {
        as_uac_trunk_option_index_trunk_tightness_in,
        "",
        "Incoming Tightness:",
        "|JAVA:General|",
        "(Trunk) Help Text for trunk_tightness_in"
    },

    {
        as_uac_trunk_option_index_trunk_tightness_out,
        "",
        "Outgoing Tightness:",
        "|JAVA:General|",
        "(Trunk) Help Text for trunk_tightness_out"
    },

    {
        as_uac_trunk_option_index_trunk_qb_over_qmax,
        "",
        "QB over QMax:",
        "|JAVA:General|",
        "(Trunk) Help Text for trunk_qb_over_qmax"
    },

    {
        as_uac_docroot_option_index_absolute,
        "subtype:directory;;empty_desc:<Root>;;",
        "Absolute Path:",
        "|JAVA_TOP:Docroot|JAVA_TOP_P2P:Docroot|JAVA_USER:Docroot|",
        "The Absolute Path describes the area of the file system that is accessible by Aspera users.\nThe default empty value gives users access to the entire file system."
    },

    {
        as_uac_docroot_option_index_show_as,
        "",
        "Shown Path:",
        "|JAVA:General|",
        "(Docroot) Help Text for show_as"
    },

    {
        as_uac_docroot_option_index_description,
        "",
        "Description:",
        "|JAVA:General|",
        "(Docroot) Help Text for description"
    },

    {
        as_uac_docroot_option_index_filter,
        "",
        "File filter:",
        "|JAVA:General|",
        "(Docroot) Help Text for filter"
    },

    {
        as_uac_docroot_option_index_read_allowed,
        "",
        "Read Allowed:",
        "|JAVA_TOP:Docroot|JAVA_TOP_P2P:Docroot|JAVA_USER:Docroot|",
        "Setting this to true allows users to transfer files from the designated area of the file system as specified by the Absolute Path value."
    },

    {
        as_uac_docroot_option_index_write_allowed,
        "",
        "Write Allowed:",
        "|JAVA_TOP:Docroot|JAVA_TOP_P2P:Docroot|JAVA_USER:Docroot|",
        "Setting this to true allows users to transfer to the designated area of the file system as specified by the Absolute Path value."
    },

    {
        as_uac_docroot_option_index_dir_allowed,
        "",
        "Browse Allowed:",
        "|JAVA_TOP:Docroot|JAVA_TOP_P2P:Docroot|JAVA_USER:Docroot|",
        "Setting this to true allows users to browse the designated area of the file system as specified by the Absolute Path value."
    },

    {
        as_uac_central_server_option_index_address,
        "",
        "Address:",
        "|JAVA_TOP:Transfer Server|JAVA_TOP_P2P:Transfer Server|",
        "This is the network interface address on which the transfer server listens.\nThe default value 127.0.0.1 enables the transfer server to accept transfer requests from the local computer.\nSetting the value to 0.0.0.0 allows the Aspera transfer server to accept transfer requests on all network interfaces for this node.\nAlternatively, a specific network interface address may be specified."
    },

    {
        as_uac_central_server_option_index_port,
        "range:1;65535;;",
        "Port:",
        "|JAVA_TOP:Transfer Server|JAVA_TOP_P2P:Transfer Server|",
        "The port at which the transfer server will accept transfer requests.\nValid port numbers range between 1 and 65535."
    },
  
    {
        as_uac_database_option_index_adapter,
        "",
        "Adapter:",
        "|JAVA:General|",
        "(Database) Help Text for adapter"
    },    

    {
        as_uac_database_option_index_server,
        "",
        "Host IP:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "The transfer server can optionally log transfer information to a database server.\nEnter the IP address of the database server (or the IP address of the Aspera Console server)."
    },

    {
        as_uac_database_option_index_port,
        "range:1;65535;;",
        "Port:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "The default value for an Aspera Console installation is 4406.\nValid port numbers range between 1 and 65535."
    },

    {
        as_uac_database_option_index_user,
        "empty_desc:<None>;;",
        "User:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "User login for the database server."
    },

    {
        as_uac_database_option_index_password,
        "empty_desc:<None>;;",
        "Password:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "Password to the database"
    },

    {
        as_uac_database_option_index_database_name,
        "empty_desc:<None>;;",
        "Database Name:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "Name of the database used to store Aspera transfer data."
    },

    {
        as_uac_database_option_index_threads,
        "",
        "Threads:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "The number of parallel connections used for database logging.\nA higher value may be useful when a large number of files are being transferred within a short timeframe."
    },

    {
        as_uac_database_option_index_exit_on_database_error,
        "",
        "Stop Transfers on Database Error:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "Quits all ongoing transfers and no new transfers are permitted when a database error prevents data from being written to the database.\nSet this to true if all transfers must be logged by your organization."
    },

    {
        as_uac_database_option_index_session_progress,
        "",
        "Show Session Progress:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "Setting this value to true will log transfer status such as number of files transferred, and bytes transferred, at a given interval."
    },

    {
        as_uac_database_option_index_session_progress_interval,
        "",
        "Session Progress Interval (seconds):",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "The frequency at which an Aspera node logs transfer session information, up to 65535 seconds."
    },

    {
        as_uac_database_option_index_file_events,
        "",
        "Show File Events:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "Setting this value to true enables the logging of complete file paths and file names.\nPerformance may be impacted when transferring datasets containing thousands of files.\nAlso see File Per Session for setting a threshold for the number of files to log per session."
    },

    {
        as_uac_database_option_index_file_progress,
        "",
        "Show File Progress:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "Setting this value to true will log file status such as bytes transferred, at a given interval."
    },

    {
        as_uac_database_option_index_file_errors,
        "",
        "File Error:",
        "|JAVA:General|",
        "(Database) Help Text for file_errors"
    },

    {
        as_uac_database_option_index_file_progress_interval,
        "",
        "File Progress Interval (seconds):",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "The frequency at which an Aspera node logs file transfer information, up to 65535 seconds.\nThe default setting of 1 logs information every second."
    },

    {
        as_uac_database_option_index_files_per_session,
        "",
        "File Per Session:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "The value set will be the cut-off point for file names logged in a given session.\nFor instance, if the value is set to 50, the first 50 file names will be recorded for any session.\nThe session will still record the number of files transferred along with the number of files completed, failed or skipped.\nThe default setting of 0 logs all file names for a given session."
    },

    {
        as_uac_database_option_index_ignore_empty_files,
        "",
        "Ignore Empty Files:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "Setting this to true will block the logging of zero-byte files."
    },

    {
        as_uac_database_option_index_ignore_skipped_files,
        "",
        "Ignore Skipped Files:",
        "|JAVA:General|",
        "(Database) Help Text for ignore_skipped_files"
    },

    {
        as_uac_database_option_index_ignore_no_transfer_files,
        "",
        "Ignore No-transfer Files:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "Setting this to true will block the logging of files that have not been transferred because they exist at the destination at the time the transfer started."
    },

    {
        as_uac_database_option_index_rate_events,
        "",
        "Show Rate Events:",
        "|JAVA_TOP:Database|JAVA_TOP_P2P:Database|",
        "Setting this to true will log changes made to the Target Rate, Minimum Rate, and Transfer Policy by any user or Aspera node administrator during a transfer."
    },

    {
        as_uac_http_server_option_index_cert_file,
        "subtype:file;*.cert;;empty_desc:<None>;;",
        "Cert File:",
        "|JAVA_TOP:HTTP Fallback Server|",
        "The absolute path to an SSL certificate file.\nIf left blank, the default certificate file that came with your Aspera Enterprise Server will be used."
    },
     
    {
        as_uac_http_server_option_index_key_file,
        "subtype:file;*.key;;empty_desc:<None>;;",
        "Key File:",
        "|JAVA_TOP:HTTP Fallback Server|",
        "The absolute path to an SSL key file.\nIf left blank, the default key file that came with your Aspera Enterprise Server will be used."
    },

    {
        as_uac_http_server_option_index_bind_address,
        "",
        "Bind Address:",
        "|JAVA_TOP:HTTP Fallback Server|",
        "This is the network interface address on which the HTTP Fallback Server listens.\nThe default value 0.0.0.0 allows the Aspera HTTP Fallback Server to accept transfer requests on all network interfaces for this node.\nAlternatively, a specific network interface address may be specified."
    },

    {
        as_uac_http_server_option_index_mgmt_address,
        "",
        "Management Address:",
        "|JAVA:General|",
        "(HTTP Server) Help Text for mgmt_address"
    },

    {
        as_uac_http_server_option_index_file_root,
        "subtype:directory;;",
        "File Root (unused):",
        "|JAVA:General|",
        "(HTTP Server) Help Text for file_root"
    },

    {
        as_uac_http_server_option_index_restartable_transfers,
        "",
        "Restartable Transfers:",
        "|JAVA_TOP:HTTP Fallback Server|",
        "Setting this to true allows interrupted transfers to resume at the point of interruption."
    },

    {
        as_uac_http_server_option_index_session_activity_timeout,
        "",
        "Session Activity Timeout:",
        "|JAVA_TOP:HTTP Fallback Server|",
        "The default value of 0 means the HTTP Fallback Server will never timeout due to lack of communication from the client.\nAny value greater than 0 sets the amount of time, in seconds, that the HTTP Fallback Server will wait before canceling the transfer."
    },

    {
        as_uac_http_server_option_index_http_port,
        "range:1;65535;;",
        "HTTP Port:",
        "|JAVA_TOP:HTTP Fallback Server|",
        "The port on which the HTTP server listens.\nValid port numbers range between 1 and 65535."
    },

    {
        as_uac_http_server_option_index_https_port,
        "range:1;65535;;",
        "HTTPS Port:",
        "|JAVA_TOP:HTTP Fallback Server|",
        "The port on which the HTTPS server listens.\nValid port numbers range between 1 and 65535."
    },

    {
        as_uac_http_server_option_index_enable_http,
        "",
        "Enable HTTP:",
        "|JAVA_TOP:HTTP Fallback Server|",
        "Enables the Aspera HTTP Fallback Server that allows failed UDP transfers to continue over HTTP."
    },

    {
        as_uac_http_server_option_index_enable_https,
        "",
        "Enable HTTPS:",
        "|JAVA_TOP:HTTP Fallback Server|",
        "Enables the secure Aspera HTTPS Fallback Server that allows failed UDP transfers to continue over HTTPS."
    },

    {
        as_uac_http_server_option_index_reset_key,
        "",
        "Reset Key:",
        "|JAVA:General|",
        "(HTTP Server) Help Text for reset_key"
    },

    {
        as_uac_user_option_index_transfer_encryption_content_protection_required,
        "",
        "Content Protection Required:",
        "|JAVA_TOP:Authorization|JAVA_TOP_P2P:Authorization|JAVA_USER:Authorization|",
        "Set to true to require that content be left encrypted at the destination.\nUse this option when all content uploaded to this server must be stored on disk as secure envelopes."
    },

    {
        as_uac_user_option_index_transfer_encryption_content_protection_strong_pass_required,
        "",
        "Strong Password Required for Content Encryption:",
        "|JAVA_TOP:Authorization|JAVA_TOP_P2P:Authorization|JAVA_USER:Authorization|",
        "Set to true to require strong passphrase for content protection\n(8 characters long, containing at least one letter, number and special symbol). "
    },    

    { unknown_as_uac_index, 0, 0, 0, 0 }
};
#endif
