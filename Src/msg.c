/*
 *  msg.c
 *
 *  message process
 *
 *  Created on: 2016. 5. 14.
 *      Author: Baram, PBHP
 */

#include "msg.h"
#include "vcp.h"
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "usart.h"

void msg_init(void)
{
}

void msg_send(uint8_t ch, mavlink_message_t *p_msg)
{
  uint8_t buf[1024];
  uint32_t len;
  int i;

  len = mavlink_msg_to_send_buffer(buf, p_msg);

  switch (ch)
  {
  case 0:
    HAL_UART_SendNByte(buf, len);
    //vcp_write(buf, len);
    break;

  case 1:
    break;
  }
}

BOOL msg_recv(uint8_t ch, msg_t *p_msg)
{
  BOOL ret = FALSE;
  static mavlink_message_t msg[MSG_CH_MAX];
  mavlink_status_t status[MSG_CH_MAX];
  uint8_t data;
  /*
  static uint32_t tTime;
  tTime = millis();

  if (millis() - tTime > 500)
  {
    tTime = millis();
    led_toggle(0);
  }
*/

  p_msg->ch = ch;

  if (HAL_UART_GetByte(&data) == 1)
  {
    if (ch == 0)
    {
      if (mavlink_parse_char(MAVLINK_COMM_0, data, &msg[ch], &status[ch]) == MAVLINK_FRAMING_OK)
      {
        p_msg->p_msg = &msg[ch];
        ret = TRUE;
      }
    }
    else
    {
      if (mavlink_parse_char(MAVLINK_COMM_1, data, &msg[ch], &status[ch]) == MAVLINK_FRAMING_OK)
      {
        p_msg->p_msg = &msg[ch];
        ret = TRUE;
      }
    }
  }
  return ret;
}
/*
BOOL msg_recv_c(uint8_t ch, mavlink_message_t *p_msg)
{
  BOOL ret = FALSE;
  static mavlink_message_t msg[MSG_CH_MAX];
  mavlink_status_t status[MSG_CH_MAX];
  uint8_t data;

  if (HAL_UART_GetByte(&data) == 1)
  {
    if (ch == 0)
    {
      if (mavlink_parse_char(MAVLINK_COMM_0, data, &msg[ch], &status[ch]) == MAVLINK_FRAMING_OK)
      {
        p_msg = &msg[ch];
        ret = TRUE;
      }
    }
    else
    {
      if (mavlink_parse_char(MAVLINK_COMM_1, data, &msg[ch], &status[ch]) == MAVLINK_FRAMING_OK)
      {
        p_msg = &msg[ch];
        ret = TRUE;
      }
    }
  }
  return ret;
}
*/
/*
BOOL msg_recv1(uint8_t ch, uint8_t data, mavlink_message_t *p_msg)
{
  BOOL ret = FALSE;
  mavlink_status_t status[MSG_CH_MAX];

  if (ch == 0)
  {
    if (mavlink_parse_char(MAVLINK_COMM_0, data, p_msg, &status[ch]) == MAVLINK_FRAMING_OK)
    {
      //p_msg = &msg[ch];
      ret = TRUE;
    }
  }
  else
  {
    if (mavlink_parse_char(MAVLINK_COMM_1, data, p_msg, &status[ch]) == MAVLINK_FRAMING_OK)
    {
      //p_msg = &msg[ch];
      ret = TRUE;
    }
  }

  return ret;
}
*/
/*
uint8_t msg_get_resp(uint8_t chan, msg_t *p_msg, uint32_t timeout)
{
  BOOL ret = FALSE;
  int ch_ret;
  int length;
  uint8_t ch;
  static mavlink_message_t msg[MSG_CH_MAX];
  int retry = timeout;
  uint32_t tTime;
  tTime = millis();

  while (1)
  {
    if (millis() - tTime > 100)
    {
      tTime = millis();
      led_toggle(0);
    }

    ch_ret = HAL_UART_GetByte1(&ch);

    if (ch_ret == 0)
    {
      if (retry-- <= 0)
      {
        ret = FALSE;
        break;
      }
      else
      {
        continue;
      }
    }
    else
    {
      retry = timeout;
    }

    ret = msg_recv1(chan, ch, &msg[chan]);

    if (ret == TRUE)
    {
      *(p_msg->p_msg) = msg[chan];
      break;
    }
  }

  return ret;
}
*/