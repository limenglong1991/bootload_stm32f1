#include "bsp.h"


USBD_HandleTypeDef USBD_Device;



void bsp_init()
{
  // STM32Cube HAL Init
  HAL_Init();

  // Clock Setup
  // SYSCLK(Hz)    = 216000000
  // HCLK(Hz)      = 216000000
  // HSE(Hz)       = 25000000
  SystemClock_Config();

  //USBD_RESET();

  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  led_init();
  button_init();

  HAL_Delay(200);

#if 0
  /* Init Device Library */
  USBD_Init(&USBD_Device, &VCP_Desc, 0);

  /* Add Supported Class */
  USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);

  /* Add CDC Interface Class */
  USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);

  /* Start Device Process */
  USBD_Start(&USBD_Device);
#endif
}


void bsp_deinit()
{
  //USBD_DeInit(&USBD_Device);

  HAL_RCC_DeInit();
  HAL_DeInit();
}
