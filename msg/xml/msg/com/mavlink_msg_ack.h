#pragma once
// MESSAGE ACK PACKING

#define MAVLINK_MSG_ID_ACK 254

MAVPACKED(
typedef struct __mavlink_ack_t {
 uint32_t err_code; /*<  */
 uint32_t length_received; /*<  */
 uint8_t msg_id; /*<  */
 uint8_t ack_length; /*<  */
 uint8_t data[16]; /*<  */
}) mavlink_ack_t;

#define MAVLINK_MSG_ID_ACK_LEN 26
#define MAVLINK_MSG_ID_ACK_MIN_LEN 26
#define MAVLINK_MSG_ID_254_LEN 26
#define MAVLINK_MSG_ID_254_MIN_LEN 26

#define MAVLINK_MSG_ID_ACK_CRC 68
#define MAVLINK_MSG_ID_254_CRC 68

#define MAVLINK_MSG_ACK_FIELD_DATA_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ACK { \
    254, \
    "ACK", \
    5, \
    {  { "msg_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_ack_t, msg_id) }, \
         { "err_code", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_ack_t, err_code) }, \
         { "length_received", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_ack_t, length_received) }, \
         { "ack_length", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_ack_t, ack_length) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 16, 10, offsetof(mavlink_ack_t, data) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ACK { \
    "ACK", \
    5, \
    {  { "msg_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_ack_t, msg_id) }, \
         { "err_code", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_ack_t, err_code) }, \
         { "length_received", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_ack_t, length_received) }, \
         { "ack_length", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_ack_t, ack_length) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 16, 10, offsetof(mavlink_ack_t, data) }, \
         } \
}
#endif

/**
 * @brief Pack a ack message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param msg_id  
 * @param err_code  
 * @param length_received  
 * @param ack_length  
 * @param data  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ack_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t msg_id, uint32_t err_code, uint32_t length_received, uint8_t ack_length, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ACK_LEN];
    _mav_put_uint32_t(buf, 0, err_code);
    _mav_put_uint32_t(buf, 4, length_received);
    _mav_put_uint8_t(buf, 8, msg_id);
    _mav_put_uint8_t(buf, 9, ack_length);
    _mav_put_uint8_t_array(buf, 10, data, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACK_LEN);
#else
    mavlink_ack_t packet;
    packet.err_code = err_code;
    packet.length_received = length_received;
    packet.msg_id = msg_id;
    packet.ack_length = ack_length;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACK_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ACK;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACK_MIN_LEN, MAVLINK_MSG_ID_ACK_LEN, MAVLINK_MSG_ID_ACK_CRC);
}

/**
 * @brief Pack a ack message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param msg_id  
 * @param err_code  
 * @param length_received  
 * @param ack_length  
 * @param data  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ack_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t msg_id,uint32_t err_code,uint32_t length_received,uint8_t ack_length,const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ACK_LEN];
    _mav_put_uint32_t(buf, 0, err_code);
    _mav_put_uint32_t(buf, 4, length_received);
    _mav_put_uint8_t(buf, 8, msg_id);
    _mav_put_uint8_t(buf, 9, ack_length);
    _mav_put_uint8_t_array(buf, 10, data, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACK_LEN);
#else
    mavlink_ack_t packet;
    packet.err_code = err_code;
    packet.length_received = length_received;
    packet.msg_id = msg_id;
    packet.ack_length = ack_length;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACK_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ACK;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACK_MIN_LEN, MAVLINK_MSG_ID_ACK_LEN, MAVLINK_MSG_ID_ACK_CRC);
}

/**
 * @brief Encode a ack struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param ack C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ack_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_ack_t* ack)
{
    return mavlink_msg_ack_pack(system_id, component_id, msg, ack->msg_id, ack->err_code, ack->length_received, ack->ack_length, ack->data);
}

/**
 * @brief Encode a ack struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param ack C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ack_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_ack_t* ack)
{
    return mavlink_msg_ack_pack_chan(system_id, component_id, chan, msg, ack->msg_id, ack->err_code, ack->length_received, ack->ack_length, ack->data);
}

/**
 * @brief Send a ack message
 * @param chan MAVLink channel to send the message
 *
 * @param msg_id  
 * @param err_code  
 * @param length_received  
 * @param ack_length  
 * @param data  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_ack_send(mavlink_channel_t chan, uint8_t msg_id, uint32_t err_code, uint32_t length_received, uint8_t ack_length, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ACK_LEN];
    _mav_put_uint32_t(buf, 0, err_code);
    _mav_put_uint32_t(buf, 4, length_received);
    _mav_put_uint8_t(buf, 8, msg_id);
    _mav_put_uint8_t(buf, 9, ack_length);
    _mav_put_uint8_t_array(buf, 10, data, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACK, buf, MAVLINK_MSG_ID_ACK_MIN_LEN, MAVLINK_MSG_ID_ACK_LEN, MAVLINK_MSG_ID_ACK_CRC);
#else
    mavlink_ack_t packet;
    packet.err_code = err_code;
    packet.length_received = length_received;
    packet.msg_id = msg_id;
    packet.ack_length = ack_length;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACK, (const char *)&packet, MAVLINK_MSG_ID_ACK_MIN_LEN, MAVLINK_MSG_ID_ACK_LEN, MAVLINK_MSG_ID_ACK_CRC);
#endif
}

/**
 * @brief Send a ack message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_ack_send_struct(mavlink_channel_t chan, const mavlink_ack_t* ack)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_ack_send(chan, ack->msg_id, ack->err_code, ack->length_received, ack->ack_length, ack->data);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACK, (const char *)ack, MAVLINK_MSG_ID_ACK_MIN_LEN, MAVLINK_MSG_ID_ACK_LEN, MAVLINK_MSG_ID_ACK_CRC);
#endif
}

#if MAVLINK_MSG_ID_ACK_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_ack_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t msg_id, uint32_t err_code, uint32_t length_received, uint8_t ack_length, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, err_code);
    _mav_put_uint32_t(buf, 4, length_received);
    _mav_put_uint8_t(buf, 8, msg_id);
    _mav_put_uint8_t(buf, 9, ack_length);
    _mav_put_uint8_t_array(buf, 10, data, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACK, buf, MAVLINK_MSG_ID_ACK_MIN_LEN, MAVLINK_MSG_ID_ACK_LEN, MAVLINK_MSG_ID_ACK_CRC);
#else
    mavlink_ack_t *packet = (mavlink_ack_t *)msgbuf;
    packet->err_code = err_code;
    packet->length_received = length_received;
    packet->msg_id = msg_id;
    packet->ack_length = ack_length;
    mav_array_memcpy(packet->data, data, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACK, (const char *)packet, MAVLINK_MSG_ID_ACK_MIN_LEN, MAVLINK_MSG_ID_ACK_LEN, MAVLINK_MSG_ID_ACK_CRC);
#endif
}
#endif

#endif

// MESSAGE ACK UNPACKING


/**
 * @brief Get field msg_id from ack message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_ack_get_msg_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field err_code from ack message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_ack_get_err_code(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field length_received from ack message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_ack_get_length_received(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field ack_length from ack message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_ack_get_ack_length(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  9);
}

/**
 * @brief Get field data from ack message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_ack_get_data(const mavlink_message_t* msg, uint8_t *data)
{
    return _MAV_RETURN_uint8_t_array(msg, data, 16,  10);
}

/**
 * @brief Decode a ack message into a struct
 *
 * @param msg The message to decode
 * @param ack C-struct to decode the message contents into
 */
static inline void mavlink_msg_ack_decode(const mavlink_message_t* msg, mavlink_ack_t* ack)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    ack->err_code = mavlink_msg_ack_get_err_code(msg);
    ack->length_received = mavlink_msg_ack_get_length_received(msg);
    ack->msg_id = mavlink_msg_ack_get_msg_id(msg);
    ack->ack_length = mavlink_msg_ack_get_ack_length(msg);
    mavlink_msg_ack_get_data(msg, ack->data);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ACK_LEN? msg->len : MAVLINK_MSG_ID_ACK_LEN;
        memset(ack, 0, MAVLINK_MSG_ID_ACK_LEN);
    memcpy(ack, _MAV_PAYLOAD(msg), len);
#endif
}
