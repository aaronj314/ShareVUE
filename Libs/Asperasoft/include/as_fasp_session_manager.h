/*
 *  faspSessionManager.h
 *  
 *
 *  Created by Amos Joshua on 10/16/09.
 *  Copyright 2009 Aspera. All rights reserved.
 *
 */


#include <fasp_session.h>
#include <fasp_proto.h>
#include <libssh2.h>
#include "as_socket_libssh2channel_mediator.h"

#define FSR_DETAILS_BYTES_PER_SECOND_HISTORY_SIZE 7

#define FSR_STATE_UNINITIALIZED 0
#define FSR_STATE_STRUCTURE_INITIALIZED 1
#define FSR_STATE_CHANNEL_SOCKET_CREATED 2
#define FSR_STATE_CHANNEL_SOCKET_CONNECTED 4
#define FSR_STATE_SSH_SESSION_INITIALIZED 8
#define FSR_STATE_SSH_SESSION_STARTEDUP 16
#define FSR_STATE_SSH_AUTHORIZED 32
#define FSR_STATE_SSH_CHANNEL_OPENED 64
#define FSR_STATE_SSH_COMMAND_EXECUTED 128
#define FSR_STATE_SSH_ASCP_EXECUTED 256
#define FSR_STATE_SOCKET_PAIR_CREATED 512
#define FSR_STATE_MEDIATION_STARTED 1024
#define FSR_STATE_UUID_CREATED 2048
#define FSR_STATE_FASP_SESSION_INITIALIZED 4096
#define FSR_STATE_FASP_SESSION_OPENED 8192
#define FSR_STATE_FASP_SESSION_START_RETURNED 16384
#define FSR_STATE_FASP_SESSION_CLOSED 32768
#define FSR_STATE_FASP_RECEIVED_SESSION_START_EVENT 65536
#define FSR_STATE_DETAILS_INITIALIZED 131072
#define FSR_STATE_FASP_RECEIVED_SESSION_STOP_EVENT 262144
#define FSR_STATE_RUNNING 524288
#define FSR_STATE_FASP_SESSION_CANCELED 1048576
#define FSR_STATE_FASP_TRANSFER_SUCCESSFUL 2097152

#define FSM_SUCCESS 0
#define FSM_ERROR 1
#define FSM_LICENSE_ERROR 2
#define FSM_BAD_EXEC_PATH 3
#define FSM_FASP_INIT_FAILED 4
#define FSM_MAX_SESSIONS_EXIST 5
#define FSM_INVALID_SESSION_ID 6
#define FSM_COULD_NOT_CONNECT_TO_HOST 7
#define FSM_SOCKET_ERROR 8
#define FSM_SSH_FAILURE 9
#define FSM_SSH_AUTH_FAILURE 10
#define FSM_FASP_SESSION_FAILED 11
#define FSM_SOCKET_SSH_MEDIATION_FAILED 12

#define FSM_STATS_STRING_MAX_LEN 256
#define SSH_KEEPALIVE_INTERVAL 4


typedef struct as_fasp_session_record_details_t{
	float _progress;
	u_int64_t _total_bytes_at_destination;
	u_int64_t _bytes_sent;
	u_int64_t _last_bytes_sent;
	u_int64_t _instantaneous_bytes_per_second;
	u_int64_t _usec_elapsed;
	u_int64_t _last_usec_elapsed;
	u_int64_t _total_size_bytes;
	u_int64_t _instantaneous_seconds_remaining;
	u_int64_t _instantaneous_bytes_per_second_history[FSR_DETAILS_BYTES_PER_SECOND_HISTORY_SIZE];
	u_int64_t _effective_rate;
	int _instantaneous_bytes_per_second_history_count;
	int _instantaneous_bytes_per_second_history_index;
} as_fasp_session_record_details_t;

as_fasp_session_record_details_t *as_fasp_session_record_details_alloc();
int as_fasp_session_record_details_init(as_fasp_session_record_details_t *sess_details);
void as_fasp_session_record_details_destroy(as_fasp_session_record_details_t *sess_details);
void as_fasp_session_record_details_dealloc(as_fasp_session_record_details_t *sess_details);
void as_fasp_session_record_details_pushInstantaneousBytesPerSecond(as_fasp_session_record_details_t *sess_details, u_int64_t bytes_per_second);

typedef struct as_fasp_session_record_t{
	// Fasp
	fasp_session_def_t *_fasp_sd;
	fasp_session_t *_fasp_session;
	volatile int _session_state;
	volatile int _session_was_cancelled;
	char _uuid_string[AS_MAX_UUID_STR_SIZE + 1];
	// SSH
	LIBSSH2_CHANNEL *_channel;
	LIBSSH2_SESSION *_ssh_session;
	// Socket<->Channel Mediation
	as_socket_libssh2channel_mediator_t	*_socket1_to_channel_mediator;
	as_socket_libssh2channel_mediator_t *_channel_to_socket1_mediator;
	as_socket_t _channel_sock;
	as_socket_t _sockets[2];
	char *_public_key_filename;
	char *_private_key_filename;
	char *_key_passphrase;
	// Details
	pthread_mutex_t _details_mutex;
	as_fasp_session_record_details_t *_details;
} as_fasp_session_record_t;


as_fasp_session_record_t *as_fasp_session_record_alloc();
int as_fasp_session_record_init(as_fasp_session_record_t *sess_record, fasp_session_def_t *fasp_sd);
void as_fasp_session_record_destroy(as_fasp_session_record_t *sess_record);
void as_fasp_session_record_dealloc(as_fasp_session_record_t *sess_record);
int as_fasp_session_record_lockDetailsMutex(as_fasp_session_record_t *sess_record);
int as_fasp_session_record_unlockDetailsMutex(as_fasp_session_record_t *sess_record);
int as_fasp_session_record_tryLockDetailsMutex(as_fasp_session_record_t *sess_record);
void as_fasp_session_record_updateDetails(as_fasp_session_record_t *sess_record, transfer_t *xfer);




typedef struct as_fasp_session_manager_t{
	as_fasp_session_record_t **_sessions; // Array of sessions
	int _max_number_of_sessions;
	int _current_number_of_sessions;
	int _fasp_initialized_successfully;
	char _error_message[FASP_ERRSTR_MAXLEN];
	int _error_code;
	void (*_fasp_callback)(int, int);
	pthread_mutex_t _keyboard_interactive_auth_mutex;
	int _id_of_session_doing_keyboard_interactive_auth;
} as_fasp_session_manager_t;

extern as_fasp_session_manager_t *g_session_manager;

// Session Manager Creation / Destruction (and session methods)
as_fasp_session_manager_t *as_fasp_session_manager_alloc();
int as_fasp_session_manager_init(as_fasp_session_manager_t *manager, int max_number_of_sessions);
void as_fasp_session_manager_destroy(as_fasp_session_manager_t *manager);
void as_fasp_session_manager_dealloc(as_fasp_session_manager_t *manager);
int as_fasp_session_manager_isValidSessionID(as_fasp_session_manager_t *manager, int session_id);
int as_fasp_session_manager_verifySessionStructureInitializedAndContainsSessionDefinitionObject(as_fasp_session_manager_t *manager, int session_id);

// Fasp Initialization
int as_fasp_session_manager_initializeFasp(as_fasp_session_manager_t *manager, char* executablePath, char* logDiretory);
int as_fasp_session_manager_faspHasBeenInitialized(as_fasp_session_manager_t *manager);

// Session Creation / Destruction
int as_fasp_session_manager_createSession(as_fasp_session_manager_t *manager); // Creates a new session and returns the sessionID, -1 on failure
int as_fasp_session_manager_destroySession(as_fasp_session_manager_t *manager, int session_id); // Completely destroys a session

// Session Attribute Setters
int as_fasp_session_manager_setSessionSourceList(as_fasp_session_manager_t *manager, int session_id, char **sourcelist); 
int as_fasp_session_manager_setSessionTargetRate(as_fasp_session_manager_t *manager, int session_id, u_int64_t target_rate);
int as_fasp_session_manager_setSessionRemoteUser(as_fasp_session_manager_t *manager, int session_id, char *remote_user);
int as_fasp_session_manager_setSessionRemotePassword(as_fasp_session_manager_t *manager, int session_id, char *remote_password);
int as_fasp_session_manager_setSessionKeyAuthenticationParameters(as_fasp_session_manager_t *manager, int session_id, const char *public_fname, const char *private_fname, const char* key_passphrase);
int as_fasp_session_manager_setSessionRemoteHost(as_fasp_session_manager_t *manager, int session_id, char *remote_host);
int as_fasp_session_manager_setSessionDestination(as_fasp_session_manager_t *manager, int session_id, char *remote_destination);
int as_fasp_session_manager_setSessionTcpPort(as_fasp_session_manager_t *manager, int session_id, unsigned int outgoing_tcp_port);
int as_fasp_session_manager_setSessionUdpPort(as_fasp_session_manager_t *manager, int session_id, unsigned int outgoing_udp_port);
int as_fasp_session_manager_setSessionTransferOp(as_fasp_session_manager_t *manager, int session_id, int transfer_op);
int as_fasp_session_manager_setSessionResumePolicy(as_fasp_session_manager_t *manager, int session_id, int resume_policy);

// Session Attribute Getters 
fasp_session_def_t *as_fasp_session_manager_getSessionDefinitionStructure(as_fasp_session_manager_t *manager, int session_id);
int as_fasp_session_manager_getSessionState(as_fasp_session_manager_t *manager, int session_id);
char **as_fasp_session_manager_getSessionSourceList(as_fasp_session_manager_t *manager, int session_id); 
u_int64_t as_fasp_session_manager_getSessionTargetRate(as_fasp_session_manager_t *manager, int session_id);
char * as_fasp_session_manager_getSessionRemoteUser(as_fasp_session_manager_t *manager, int session_id);
char * as_fasp_session_manager_getSessionRemotePassword(as_fasp_session_manager_t *manager, int session_id);
char * as_fasp_session_manager_getSessionRemoteHost(as_fasp_session_manager_t *manager, int session_id);
char * as_fasp_session_manager_getSessionDestination(as_fasp_session_manager_t *manager, int session_id);
unsigned int as_fasp_session_manager_getSessionTcpPort(as_fasp_session_manager_t *manager, int session_id);
unsigned int as_fasp_session_manager_getSessionUdpPort(as_fasp_session_manager_t *manager, int session_id);
int as_fasp_session_manager_getSessionTransferOp(as_fasp_session_manager_t *manager, int session_id);
int as_fasp_session_manager_getSessionResumePolicy(as_fasp_session_manager_t *manager, int session_id);

// Session Stats
u_int64_t as_fasp_session_manager_stats_getTotalSizeInBytes(as_fasp_session_manager_t *manager, int session_id);
u_int64_t as_fasp_session_manager_stats_getTotalSentInBytes(as_fasp_session_manager_t *manager, int session_id);
u_int64_t as_fasp_session_manager_stats_getTotalAtDestinationInBytes(as_fasp_session_manager_t *manager, int session_id);
u_int64_t as_fasp_session_manager_stats_getTotalRemainingInBytes(as_fasp_session_manager_t *manager, int session_id);
u_int64_t as_fasp_session_manager_stats_getInstantaneousRateInBitsPerSecond(as_fasp_session_manager_t *manager, int session_id);
u_int64_t as_fasp_session_manager_stats_getInstantaneousTimeRemainingInSeconds(as_fasp_session_manager_t *manager, int session_id);
double as_fasp_session_manager_stats_getMeanRateInBitsPerSecond(as_fasp_session_manager_t *manager, int session_id);
u_int64_t as_fasp_session_manager_stats_getEffectiveRateInBitsPerSecond(as_fasp_session_manager_t *manager, int session_id);
int64_t as_fasp_session_manager_stats_getMeanTimeRemainingInSeconds(as_fasp_session_manager_t *manager, int session_id);
u_int64_t as_fasp_session_manager_stats_getTotalTimeElapsedInSeconds(as_fasp_session_manager_t *manager, int session_id);
float as_fasp_session_manager_stats_getTotalProgress(as_fasp_session_manager_t *manager, int session_id);

// Formatted Stats
void as_fasp_session_manager_getUnitsFromBytes(u_int64_t bytes, u_int64_t *bytes_in_bytes, u_int64_t *kbytes_in_bytes, u_int64_t *mbytes_in_bytes, u_int64_t *gbytes_in_bytes);
void as_fasp_session_manager_getLargestUnitsAsStringFromBytes(u_int64_t bytes, char *buffer, const char *suffix);
void as_fasp_session_manager_getUnitsFromMicroseconds(u_int64_t microseconds, u_int64_t *seconds_in_microseconds, u_int64_t *minutes_in_microseconds, u_int64_t *hours_in_microseconds, u_int64_t *days_in_microseconds);
void as_fasp_session_manager_getTimeAsStringFromMicroseconds(u_int64_t microseconds, char *buffer);
void as_fasp_session_manager_formatted_stats_getTotalSize(as_fasp_session_manager_t *manager, int session_id, char *buffer);
void as_fasp_session_manager_formatted_stats_getTotalSent(as_fasp_session_manager_t *manager, int session_id, char *buffer);
void as_fasp_session_manager_formatted_stats_getTotalAtDestination(as_fasp_session_manager_t *manager, int session_id, char *buffer);
void as_fasp_session_manager_formatted_stats_getTotalRemaining(as_fasp_session_manager_t *manager, int session_id, char *buffer);
void as_fasp_session_manager_formatted_stats_getInstantaneousRate(as_fasp_session_manager_t *manager, int session_id, char *buffer);
void as_fasp_session_manager_formatted_stats_getInstantaneousTimeRemaining(as_fasp_session_manager_t *manager, int session_id, char *buffer);
void as_fasp_session_manager_formatted_stats_getMeanRate(as_fasp_session_manager_t *manager, int session_id, char *buffer);
void as_fasp_session_manager_formatted_stats_getEffectiveRate(as_fasp_session_manager_t *manager, int session_id, char *buffer);
void as_fasp_session_manager_formatted_stats_getMeanTimeRemaining(as_fasp_session_manager_t *manager, int session_id, char *buffer);
void as_fasp_session_manager_formatted_stats_getTotalTimeElapsed(as_fasp_session_manager_t *manager, int session_id, char *buffer);

// SSH Methods
int as_fasp_session_manager_establishSshConnection(as_fasp_session_manager_t *manager, int session_id);
int as_fasp_session_manager_executeSshCommandOnRemoteHost(as_fasp_session_manager_t *manager, int session_id, const char* command);
int as_fasp_session_manager_shutdownSshConnection(as_fasp_session_manager_t *manager, int session_id);

// Keyboard-interactive methods
int as_fasp_session_manager_lockKeyboardInteractiveAuthMutex(as_fasp_session_manager_t *manager);
int as_fasp_session_manager_tryLockKeyboardInteractiveAuthMutex(as_fasp_session_manager_t *manager);
int as_fasp_session_manager_unlockKeyboardInteractiveAuthMutex(as_fasp_session_manager_t *manager);

// Fasp Methods
int as_fasp_session_manager_startFaspSession(as_fasp_session_manager_t *manager, int session_id);

// Session Methods
int as_fasp_session_manager_startSession(as_fasp_session_manager_t *manager, int session_id);
int as_fasp_session_manager_cancelSession(as_fasp_session_manager_t *manager, int session_id, char *reason);
int as_fasp_session_manager_shutdownSession(as_fasp_session_manager_t *manager, int session_id);


