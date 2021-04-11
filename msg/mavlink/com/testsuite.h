/** @file
 *    @brief MAVLink comm protocol testsuite generated from com.xml
 *    @see http://qgroundcontrol.org/mavlink/
 */
#pragma once
#ifndef COM_TESTSUITE_H
#define COM_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_com(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

    mavlink_test_com(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_packet(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PACKET >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_packet_t packet_in = {
        963497464,963497672,963497880,41,108,175,{ 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185 }
    };
    mavlink_packet_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.addr = packet_in.addr;
        packet1.total_length = packet_in.total_length;
        packet1.reply_status = packet_in.reply_status;
        packet1.resp = packet_in.resp;
        packet1.length = packet_in.length;
        packet1.is_last_packet = packet_in.is_last_packet;
        
        mav_array_memcpy(packet1.data, packet_in.data, sizeof(uint8_t)*200);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PACKET_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PACKET_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_packet_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_packet_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_packet_pack(system_id, component_id, &msg , packet1.resp , packet1.addr , packet1.length , packet1.total_length , packet1.reply_status , packet1.is_last_packet , packet1.data );
    mavlink_msg_packet_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_packet_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.resp , packet1.addr , packet1.length , packet1.total_length , packet1.reply_status , packet1.is_last_packet , packet1.data );
    mavlink_msg_packet_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_packet_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_packet_send(MAVLINK_COMM_1 , packet1.resp , packet1.addr , packet1.length , packet1.total_length , packet1.reply_status , packet1.is_last_packet , packet1.data );
    mavlink_msg_packet_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_ack(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ACK >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_ack_t packet_in = {
        963497464,963497672,29,96,{ 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178 }
    };
    mavlink_ack_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.err_code = packet_in.err_code;
        packet1.length_received = packet_in.length_received;
        packet1.msg_id = packet_in.msg_id;
        packet1.ack_length = packet_in.ack_length;
        
        mav_array_memcpy(packet1.data, packet_in.data, sizeof(uint8_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ACK_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ACK_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_ack_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_ack_pack(system_id, component_id, &msg , packet1.msg_id , packet1.err_code , packet1.length_received , packet1.ack_length , packet1.data );
    mavlink_msg_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_ack_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.msg_id , packet1.err_code , packet1.length_received , packet1.ack_length , packet1.data );
    mavlink_msg_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_ack_send(MAVLINK_COMM_1 , packet1.msg_id , packet1.err_code , packet1.length_received , packet1.ack_length , packet1.data );
    mavlink_msg_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_com(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_packet(system_id, component_id, last_msg);
    mavlink_test_ack(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // COM_TESTSUITE_H
