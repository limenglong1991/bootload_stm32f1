/*
 *  cmd.c
 *
 *  message process
 *
 *  Created on: 2016. 5. 14.
 *      Author: Baram, PBHP
 */

#include "cmd.h"
#include "msg.h"
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "crc.h"

#define DOWNLOAD_ID 0
#define JUMP_ID 1
#define REBOOT_ID 2

#define FLASH_FW_SIZE (256 * 1024) // 768KB
#define FLASH_FW_ADDR_START 0x08040000
#define FLASH_FW_ADDR_END (FLASH_FW_ADDR_START + FLASH_FW_SIZE)

#define FLASH_CONFIG_SIZE (32 * 1024) // 32KB
#define FLASH_CONFIG_ADDR_START 0x08010000
#define FLASH_CONFIG_ADDR_END (FLASH_CONFIG_ADDR_START + FLASH_CONFIG_SIZE)

#define CMD_PACKET_LENGTH 200
#define CMD_MAX_LENGTH (20 * 1024)

typedef struct
{
  uint32_t length;
  uint32_t length_received;
  uint32_t length_total;

  uint16_t count;
  uint16_t count_total;

} cmd_flag;

cmd_flag flag;

uint8_t command_buf[CMD_MAX_LENGTH];
uint8_t reply_buf[CMD_MAX_LENGTH];

void jump_to_fw(void);

/*---------------------------------------------------------------------------
     TITLE   : cmd_init
     WORK    :
---------------------------------------------------------------------------*/
void cmd_init(void)
{
}
/*---------------------------------------------------------------------------
     TITLE   : resp_ack
     WORK    :
---------------------------------------------------------------------------*/
void resp_ack(uint8_t ch, mavlink_ack_t *p_ack)
{
  mavlink_message_t mav_msg;

  mavlink_msg_ack_pack_chan(0, 0, ch, &mav_msg, p_ack->msg_id, p_ack->err_code, p_ack->length_received, p_ack->ack_length, p_ack->data);

  msg_send(ch, &mav_msg);
}

/*---------------------------------------------------------------------------
     TITLE   : cmd_receive_command
     WORK    :
---------------------------------------------------------------------------*/
BOOL cmd_receive_command(msg_t *p_msg, void *command_data, uint8_t *need_reply)
{
  err_code_t err_code = OK;
  BOOL ret = FALSE;
  mavlink_ack_t mav_ack;
  mavlink_packet_t mav_data;
  uint32_t tTime;
  tTime = millis();

  do
  {
    if (millis() - tTime > 100)
    {
      tTime = millis();
      led_toggle(0);
    }
#if 1
    if (msg_recv(0, p_msg) == TRUE)
#else
    if (msg_get_resp(0, p_msg, 500) == TRUE)
#endif
    {

      mavlink_msg_packet_decode(p_msg->p_msg, &mav_data);

      if (mav_data.addr == 0)
      {
        flag.count = 0;
        flag.count_total = 0;

        flag.length = 0;
        flag.length_total = 0;
        flag.length_received = 0;

        memset(command_data, 0, CMD_MAX_LENGTH);
      }

      if ((flag.length_received + mav_data.length) <= CMD_MAX_LENGTH)
      {
        memcpy(&command_data[flag.length_received], &mav_data.data[0], mav_data.length);
      }
      flag.count += 1;
      flag.length_received += mav_data.length;

      flag.count_total += 1;
      flag.length_total += mav_data.length;

      flag.length = mav_data.total_length;

      mav_ack.msg_id = p_msg->p_msg->msgid;
      mav_ack.err_code = err_code;
      resp_ack(p_msg->ch, &mav_ack);

      if (mav_data.is_last_packet == 1)
      {
        ret = TRUE;
        break;
      }
    }
  } while (1);

  *need_reply = mav_data.resp;

  return ret;
}

void cmd_send_reply(msg_t *p_msg, uint32_t reply_status, void *reply_data, uint32_t length)
{
  int ret = 0;
  err_code_t err_code = OK;
  uint16_t packet_cnt;
  uint32_t written_packet_length;
  uint32_t packet_length = 200;
  uint32_t i = 0;
  uint8_t is_last_packet;
  uint8_t resp = 0;
  uint8_t msgid = 1;
  mavlink_message_t tx_msg;
  mavlink_message_t rx_msg;
  mavlink_ack_t ack_msg;
  mavlink_ack_t mav_ack;

  //length = CMD_MAX_LENGTH;

  if (length > CMD_MAX_LENGTH)
  {
    return -1;
  }

  packet_cnt = length / CMD_PACKET_LENGTH;
  if (length % CMD_PACKET_LENGTH > 0)
  {
    packet_cnt += 1;
  }

  written_packet_length = 0;

  //for (i = 0; i < packet_cnt; i++)
  do
  {
    packet_length = length - written_packet_length;
    if (packet_length > CMD_PACKET_LENGTH)
    {
      packet_length = CMD_PACKET_LENGTH;
    }

    if (i == (packet_cnt - 1))
    {
      is_last_packet = 1;
    }
    else
    {
      is_last_packet = 0;
    }

    //cmd_flash_fw_write_packet(written_packet_length, &p_data[written_packet_length], packet_length, is_last_packet);

    mavlink_msg_packet_pack(0, 0, msgid, &tx_msg, resp, written_packet_length, packet_length, length, reply_status, is_last_packet, &reply_data[written_packet_length]);
    msg_send(0, &tx_msg);

    while (TRUE)
    {
      if (msg_recv(0, p_msg) == TRUE)
      {
        //printf("is_last_packet %d\r\n", is_last_packet);
        mavlink_msg_ack_decode(p_msg->p_msg, &ack_msg);

        if (tx_msg.msgid == ack_msg.msg_id)
          err_code = ack_msg.err_code;
        //else                                 err_code = ERR_MISMATCH_ID;
        break;
      }
    }

    written_packet_length += packet_length;

    i++;

  } while (i != packet_cnt);
}

err_code_t cmd_fun_printf(void *command_data, void *reply_data)
{
  err_code_t err_code = OK;

  err_code = flash_erase_fw_block(flag.length, flag.length_received);
  if(err_code == OK)
  {
    err_code = flash_write(FLASH_FW_ADDR_START + flag.length, command_data, flag.length_received);
  }
  printf("err_code = %d\r\n", err_code);
  return err_code;
}

void cmd_handle_command()
{
  static msg_t msg;
  static uint8_t need_reply;
  err_code_t err_code;
  if (cmd_receive_command(&msg, command_buf, &need_reply))
  {
    switch (msg.p_msg->msgid)
    {
    case DOWNLOAD_ID:
      err_code = cmd_fun_printf(command_buf, reply_buf);
      break;
    case JUMP_ID:
      cmd_jump_to_fw(&msg);
      break;
    case REBOOT_ID:
      NVIC_SystemReset();
      break;
    default:
      break;
    }

    printf("need_reply = %d\r\n", need_reply);

    if (need_reply == 1)
    {
      cmd_send_reply(&msg, (uint32_t)err_code, reply_buf, 300);
    }
  }
}
/*---------------------------------------------------------------------------
     TITLE   : cmd_jump_to_fw
     WORK    :
---------------------------------------------------------------------------*/
void cmd_jump_to_fw(msg_t *p_msg)
{
  jump_to_fw();
}
/*---------------------------------------------------------------------------
     TITLE   : cmd_send_error
     WORK    :
---------------------------------------------------------------------------*/
/*
void cmd_send_error(msg_t *p_msg, err_code_t err_code)
{

  mavlink_ack_t mav_ack;
  mavlink_read_version_t mav_data;

  mavlink_msg_read_version_decode(p_msg->p_msg, &mav_data);

  mav_ack.msg_id = p_msg->p_msg->msgid;
  mav_ack.err_code = err_code;
  resp_ack(p_msg->ch, &mav_ack);
}
*/
/*---------------------------------------------------------------------------
     TITLE   : check_fw
     WORK    :
---------------------------------------------------------------------------*/
BOOL check_fw(void)
{
  BOOL ret = TRUE;
  uint32_t *p_addr = (uint32_t *)FLASH_FW_ADDR_START;

  if (p_addr[0] == 0xFFFFFFFF)
    ret = FALSE;

  return ret;
}

/*---------------------------------------------------------------------------
     TITLE   : jump_to_fw
     WORK    :
---------------------------------------------------------------------------*/
void jump_to_fw(void)
{

  if (check_fw() == FALSE)
    return;

  bsp_deinit();

  SCB->VTOR = FLASH_FW_ADDR_START;

  __asm volatile("ldr r0, =0x08040000 \n"
                 "ldr sp, [r0]        \n"
                 "ldr pc, [r0, #4]    \n");
}
