#pragma once
// MESSAGE PACKET PACKING

#define MAVLINK_MSG_ID_PACKET 255

MAVPACKED(
typedef struct __mavlink_packet_t {
 uint32_t addr; /*<  */
 uint32_t total_length; /*<  */
 uint32_t reply_status; /*<  */
 uint8_t resp; /*<  0:No Resp, 1:Resp*/
 uint8_t length; /*<  */
 uint8_t is_last_packet; /*<  */
 uint8_t data[200]; /*<  */
}) mavlink_packet_t;

#define MAVLINK_MSG_ID_PACKET_LEN 215
#define MAVLINK_MSG_ID_PACKET_MIN_LEN 215
#define MAVLINK_MSG_ID_255_LEN 215
#define MAVLINK_MSG_ID_255_MIN_LEN 215

#define MAVLINK_MSG_ID_PACKET_CRC 155
#define MAVLINK_MSG_ID_255_CRC 155

#define MAVLINK_MSG_PACKET_FIELD_DATA_LEN 200

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PACKET { \
    255, \
    "PACKET", \
    7, \
    {  { "resp", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_packet_t, resp) }, \
         { "addr", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_packet_t, addr) }, \
         { "length", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_packet_t, length) }, \
         { "total_length", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_packet_t, total_length) }, \
         { "reply_status", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_packet_t, reply_status) }, \
         { "is_last_packet", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_packet_t, is_last_packet) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 200, 15, offsetof(mavlink_packet_t, data) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PACKET { \
    "PACKET", \
    7, \
    {  { "resp", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_packet_t, resp) }, \
         { "addr", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_packet_t, addr) }, \
         { "length", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_packet_t, length) }, \
         { "total_length", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_packet_t, total_length) }, \
         { "reply_status", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_packet_t, reply_status) }, \
         { "is_last_packet", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_packet_t, is_last_packet) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 200, 15, offsetof(mavlink_packet_t, data) }, \
         } \
}
#endif

/**
 * @brief Pack a packet message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param resp  0:No Resp, 1:Resp
 * @param addr  
 * @param length  
 * @param total_length  
 * @param reply_status  
 * @param is_last_packet  
 * @param data  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_packet_pack(uint8_t system_id, uint8_t component_id, uint8_t msg_id, mavlink_message_t* msg,
                               uint8_t resp, uint32_t addr, uint8_t length, uint32_t total_length, uint32_t reply_status, uint8_t is_last_packet, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PACKET_LEN];
    _mav_put_uint32_t(buf, 0, addr);
    _mav_put_uint32_t(buf, 4, total_length);
    _mav_put_uint32_t(buf, 8, reply_status);
    _mav_put_uint8_t(buf, 12, resp);
    _mav_put_uint8_t(buf, 13, length);
    _mav_put_uint8_t(buf, 14, is_last_packet);
    _mav_put_uint8_t_array(buf, 15, data, 200);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PACKET_LEN);
#else
    mavlink_packet_t packet;
    packet.addr = addr;
    packet.total_length = total_length;
    packet.reply_status = reply_status;
    packet.resp = resp;
    packet.length = length;
    packet.is_last_packet = is_last_packet;
    printf("packet.length %d\r\n", packet.length);
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*200);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PACKET_LEN);
#endif

    msg->msgid = msg_id;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PACKET_MIN_LEN, MAVLINK_MSG_ID_PACKET_LEN, MAVLINK_MSG_ID_PACKET_CRC);
}

/**
 * @brief Pack a packet message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param resp  0:No Resp, 1:Resp
 * @param addr  
 * @param length  
 * @param total_length  
 * @param reply_status  
 * @param is_last_packet  
 * @param data  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_packet_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               uint8_t msg_id, mavlink_message_t* msg,
                                   uint8_t resp,uint32_t addr,uint8_t length,uint32_t total_length,uint32_t reply_status,uint8_t is_last_packet,const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PACKET_LEN];
    _mav_put_uint32_t(buf, 0, addr);
    _mav_put_uint32_t(buf, 4, total_length);
    _mav_put_uint32_t(buf, 8, reply_status);
    _mav_put_uint8_t(buf, 12, resp);
    _mav_put_uint8_t(buf, 13, length);
    _mav_put_uint8_t(buf, 14, is_last_packet);
    _mav_put_uint8_t_array(buf, 15, data, 200);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PACKET_LEN);
#else
    mavlink_packet_t packet;
    packet.addr = addr;
    packet.total_length = total_length;
    packet.reply_status = reply_status;
    packet.resp = resp;
    packet.length = length;
    packet.is_last_packet = is_last_packet;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*200);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PACKET_LEN);
#endif

    msg->msgid = msg_id;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PACKET_MIN_LEN, MAVLINK_MSG_ID_PACKET_LEN, MAVLINK_MSG_ID_PACKET_CRC);
}

/**
 * @brief Encode a packet struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param packet C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_packet_encode(uint8_t system_id, uint8_t component_id, uint8_t msg_id, mavlink_message_t* msg, const mavlink_packet_t* packet)
{
    return mavlink_msg_packet_pack(system_id, component_id, msg_id, msg, packet->resp, packet->addr, packet->length, packet->total_length, packet->reply_status, packet->is_last_packet, packet->data);
}

/**
 * @brief Encode a packet struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param packet C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_packet_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, uint8_t msg_id, mavlink_message_t* msg, const mavlink_packet_t* packet)
{
    return mavlink_msg_packet_pack_chan(system_id, component_id, chan, msg_id, msg, packet->resp, packet->addr, packet->length, packet->total_length, packet->reply_status, packet->is_last_packet, packet->data);
}

/**
 * @brief Send a packet message
 * @param chan MAVLink channel to send the message
 *
 * @param resp  0:No Resp, 1:Resp
 * @param addr  
 * @param length  
 * @param total_length  
 * @param reply_status  
 * @param is_last_packet  
 * @param data  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_packet_send(mavlink_channel_t chan, uint8_t msg_id, uint8_t resp, uint32_t addr, uint8_t length, uint32_t total_length, uint32_t reply_status, uint8_t is_last_packet, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PACKET_LEN];
    _mav_put_uint32_t(buf, 0, addr);
    _mav_put_uint32_t(buf, 4, total_length);
    _mav_put_uint32_t(buf, 8, reply_status);
    _mav_put_uint8_t(buf, 12, resp);
    _mav_put_uint8_t(buf, 13, length);
    _mav_put_uint8_t(buf, 14, is_last_packet);
    _mav_put_uint8_t_array(buf, 15, data, 200);
    _mav_finalize_message_chan_send(chan, msg_id, buf, MAVLINK_MSG_ID_PACKET_MIN_LEN, MAVLINK_MSG_ID_PACKET_LEN, MAVLINK_MSG_ID_PACKET_CRC);
#else
    mavlink_packet_t packet;
    packet.addr = addr;
    packet.total_length = total_length;
    packet.reply_status = reply_status;
    packet.resp = resp;
    packet.length = length;
    packet.is_last_packet = is_last_packet;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*200);
    _mav_finalize_message_chan_send(chan, msg_id, (const char *)&packet, MAVLINK_MSG_ID_PACKET_MIN_LEN, MAVLINK_MSG_ID_PACKET_LEN, MAVLINK_MSG_ID_PACKET_CRC);
#endif
}

/**
 * @brief Send a packet message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_packet_send_struct(mavlink_channel_t chan, uint8_t msg_id, const mavlink_packet_t* packet)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_packet_send(chan, msg_id, packet->resp, packet->addr, packet->length, packet->total_length, packet->reply_status, packet->is_last_packet, packet->data);
#else
    _mav_finalize_message_chan_send(chan, msg_id, (const char *)packet, MAVLINK_MSG_ID_PACKET_MIN_LEN, MAVLINK_MSG_ID_PACKET_LEN, MAVLINK_MSG_ID_PACKET_CRC);
#endif
}

#if MAVLINK_MSG_ID_PACKET_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_packet_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan, uint8_t msg_id, uint8_t resp, uint32_t addr, uint8_t length, uint32_t total_length, uint32_t reply_status, uint8_t is_last_packet, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, addr);
    _mav_put_uint32_t(buf, 4, total_length);
    _mav_put_uint32_t(buf, 8, reply_status);
    _mav_put_uint8_t(buf, 12, resp);
    _mav_put_uint8_t(buf, 13, length);
    _mav_put_uint8_t(buf, 14, is_last_packet);
    _mav_put_uint8_t_array(buf, 15, data, 200);
    _mav_finalize_message_chan_send(chan, msg_id, buf, MAVLINK_MSG_ID_PACKET_MIN_LEN, MAVLINK_MSG_ID_PACKET_LEN, MAVLINK_MSG_ID_PACKET_CRC);
#else
    mavlink_packet_t *packet = (mavlink_packet_t *)msgbuf;
    packet->addr = addr;
    packet->total_length = total_length;
    packet->reply_status = reply_status;
    packet->resp = resp;
    packet->length = length;
    packet->is_last_packet = is_last_packet;
    mav_array_memcpy(packet->data, data, sizeof(uint8_t)*200);
    _mav_finalize_message_chan_send(chan, msg_id, (const char *)packet, MAVLINK_MSG_ID_PACKET_MIN_LEN, MAVLINK_MSG_ID_PACKET_LEN, MAVLINK_MSG_ID_PACKET_CRC);
#endif
}
#endif

#endif

// MESSAGE PACKET UNPACKING


/**
 * @brief Get field resp from packet message
 *
 * @return  0:No Resp, 1:Resp
 */
static inline uint8_t mavlink_msg_packet_get_resp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field addr from packet message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_packet_get_addr(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field length from packet message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_packet_get_length(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field total_length from packet message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_packet_get_total_length(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field reply_status from packet message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_packet_get_reply_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field is_last_packet from packet message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_packet_get_is_last_packet(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  14);
}

/**
 * @brief Get field data from packet message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_packet_get_data(const mavlink_message_t* msg, uint8_t *data)
{
    return _MAV_RETURN_uint8_t_array(msg, data, 200,  15);
}

/**
 * @brief Decode a packet message into a struct
 *
 * @param msg The message to decode
 * @param packet C-struct to decode the message contents into
 */
static inline void mavlink_msg_packet_decode(const mavlink_message_t* msg, mavlink_packet_t* packet)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    packet->addr = mavlink_msg_packet_get_addr(msg);
    packet->total_length = mavlink_msg_packet_get_total_length(msg);
    packet->reply_status = mavlink_msg_packet_get_reply_status(msg);
    packet->resp = mavlink_msg_packet_get_resp(msg);
    packet->length = mavlink_msg_packet_get_length(msg);
    packet->is_last_packet = mavlink_msg_packet_get_is_last_packet(msg);
    mavlink_msg_packet_get_data(msg, packet->data);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PACKET_LEN? msg->len : MAVLINK_MSG_ID_PACKET_LEN;
        memset(packet, 0, MAVLINK_MSG_ID_PACKET_LEN);
    memcpy(packet, _MAV_PAYLOAD(msg), len);
#endif
}
