/*
 *  cmd.h
 *
 *  command process
 *
 *  Created on: 2016. 5. 14.
 *      Author: Baram, PBHP
 */

#ifndef CMD_H
#define CMD_H


#ifdef __cplusplus
 extern "C" {
#endif


#include "def.h"
#include "bsp.h"
#include "hal.h"

void cmd_init(void);

void cmd_jump_to_fw( msg_t *p_msg );

void jump_to_fw(void);

BOOL cmd_receive_command( msg_t *p_msg, void *command_data, uint8_t *need_reply);
void cmd_send_reply( msg_t *p_msg, uint32_t reply_status, void *reply_data, uint32_t length);
err_code_t cmd_fun_printf(void *command_data, void *reply_data);
void cmd_handle_command();

#ifdef __cplusplus
}
#endif


#endif

