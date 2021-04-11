/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}

void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (uartHandle->Instance == USART1)
  {
    /* USER CODE BEGIN USART1_MspInit 0 */

    /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    //HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    //HAL_NVIC_EnableIRQ(USART1_IRQn);
    /* USER CODE BEGIN USART1_MspInit 1 */

    /* USER CODE END USART1_MspInit 1 */
  }
  else if (uartHandle->Instance == USART2)
  {
    /* USER CODE BEGIN USART2_MspInit 0 */

    /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USER CODE BEGIN USART2_MspInit 1 */

    /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle)
{

  if (uartHandle->Instance == USART1)
  {
    /* USER CODE BEGIN USART1_MspDeInit 0 */

    /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    //HAL_NVIC_DisableIRQ(USART1_IRQn);
    /* USER CODE BEGIN USART1_MspDeInit 1 */

    /* USER CODE END USART1_MspDeInit 1 */
  }
  else if (uartHandle->Instance == USART2)
  {
    /* USER CODE BEGIN USART2_MspDeInit 0 */

    /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);

    /* USER CODE BEGIN USART2_MspDeInit 1 */

    /* USER CODE END USART2_MspDeInit 1 */
  }
}

void HAL_UART_SendNByte(uint8_t *data, uint16_t len)
{
  while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) == 0)
    ;
  HAL_UART_Transmit(&huart1, (uint8_t *)data, len, 0xff);
}

int HAL_UART_GetByte(uint8_t *data)
{
  if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET)
  {
    HAL_UART_Receive(&huart1, (uint8_t *)data, 1, 0xff);
    return 1;
  }
  else
  {
    return 0;
  }
}
/*
int HAL_UART_GetByte1(uint8_t *data)
{
  HAL_StatusTypeDef rx_state = HAL_OK;
  if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET)
  {
    rx_state = HAL_UART_Receive(&huart1, (uint8_t *)data, 1, 0xff);
  }

  if (rx_state == HAL_OK)
  {
    return 1;
  }
  else
  {
    return 0;
  }


  //if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET)
  //{
  //  HAL_UART_Receive(&huart1, (uint8_t *)data, 1, 0xff);
  //  return 1;
  //}
  //else
  //{
  //  return 0;
  //}

}
*/
/* USER CODE BEGIN 1 */

int _write(int fd, char *pBuffer, int size)
{
  // for (int i = 0; i < size; i++)
  // {
  //     while ((USART1->SR & 0X40) == 0)
  //         ;                     //等待上一次串口数据发送完�??????
  //     USART1->DR = (u8)pBuffer; //写DR,串口1将发送数�??????
  // }
  while (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TC) == 0)
    ;
  HAL_UART_Transmit(&huart2, (uint8_t *)pBuffer, size, 0xff);
  return size;
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
