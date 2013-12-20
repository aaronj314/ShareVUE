/*
 * fasp_proto.h
 *
 * FASP protocol specifications
 *
 * Packet types, formats and sizes for FASP messages (TCP and UDP)
 *
 * Aspera, Inc.
 */

#ifndef __FASP_PROTO_H__
#define __FASP_PROTO_H__


#define TCP_MAX_PDU_SIZE                    0xFFFF
#define UDP_MAX_PDU_SIZE                    MAX_DGRAM_SIZE


/* Data PDU flags */
#define DATA_TICK_NONE                      0x00
#define DATA_TICK_NET                       0x01 // network measure (not app)
#define DATA_TICK_REX                       0x02 // rex rtt measure
#define DATA_TICK_VLQ                       0x04 // vlink queue tick 

/* TCP PDU types */

#define PROTOCOL_NOP                        0x01
#define PROTOCOL_OPEN_SESSION               0x02
#define PROTOCOL_CLOSE_SESSION              0x03
#define PROTOCOL_PROBE_STOP                 0x04

/* UDP PDU types */

#define PROTOCOL_STATISTICS                 0x11
#define PROTOCOL_REQUEST_RETRANSMISSIONS    0x12
#define PROTOCOL_CONTROL                    0x13
/* Local UDP message */
#define PROTOCOL_VLINK_STAT                 0x14

#define PROTOCOL_DATA                       0x18
#define PROTOCOL_DATA_FLAG_1                0x19 //PROTOCOL_DATA | DATA_TICK_NET
#define PROTOCOL_DATA_FLAG_2                0x1a //PROTOCOL_DATA | DATA_TICK_REX
#define PROTOCOL_DATA_FLAG_AND_12           0x1b //PROTOCOL_DATA | MULT FLAGS
#define PROTOCOL_DATA_FLAG_3                0x1c //PROTOCOL_DATA | DATA_TICK_VLQ 
#define PROTOCOL_DATA_FLAG_AND_13           0x1d //PROTOCOL_DATA | MULT FLAGS
#define PROTOCOL_DATA_FLAG_AND_23           0x1e //PROTOCOL_DATA | MULT FLAGS
#define PROTOCOL_DATA_FLAG_AND_123          0x1f //PROTOCOL_DATA | MULT FLAGS

#define PROTOCOL_UDP_PORTOPEN               0x20
#define PROTOCOL_MTURTT_PROBE               0x21              
#define PROTOCOL_BWMEAS_PROBE               0x22

/* Size of generic headers (bytes) */

#define STREAM_PDU_HEADER_SIZE              4

#define UDP_PDU_HEADER_SIZE                 2

/* Size of fixed field headers (bytes) */

#define STREAM_STOP_PDU_HEADER_SIZE         12
#define STREAM_ERROR_PDU_HEADER_SIZE        8
#define STREAM_NOP_PDU_HEADER_SIZE          4

#define UDP_DATA_PDU_HEADER_SIZE            12
#define UDP_DATASEC_PDU_HEADER_SIZE         16

#define UDP_START_PDU_HEADER_SIZE           8   

#define UDP_REX_PDU_HEADER_SIZE             12
#define UDP_STATS_PDU_HEADER_SIZE           84
#define OLD_UDP_STATS_PDU_HEADER_SIZE       36  /* TBD: Remove */

#define VLINK_STAT_PDU_SIZE                 12

#endif

