/*
 *  msg.h
 *
 *  message process
 *
 *  Created on: 2016. 5. 14.
 *      Author: Baram, PBHP
 */

#ifndef MSG_H
#define MSG_H


#ifdef __cplusplus
 extern "C" {
#endif


#include "def.h"
#include "bsp.h"


#define MSG_CH_MAX	1


typedef struct
{
  uint8_t ch;
  mavlink_message_t *p_msg;
} msg_t;



void msg_init(void);
void msg_send(uint8_t ch, mavlink_message_t *p_msg);

BOOL msg_recv( uint8_t ch , msg_t *p_msg );
//BOOL msg_recv_c(uint8_t ch, mavlink_message_t *p_msg);
//BOOL msg_recv1( uint8_t ch , uint8_t data, mavlink_message_t *p_msg );


//uint8_t msg_get_resp(uint8_t chan, msg_t *p_msg, uint32_t timeout);

#ifdef __cplusplus
}
#endif


#endif

