/**
  ******************************************************************************
  * @file    Templates/Src/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    26-June-2015
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "functions.h"

/** @addtogroup STM32F0xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern SPI_HandleTypeDef SpiHandle;
extern I2C_HandleTypeDef I2cHandle;
extern TIM_HandleTypeDef microTimHandle;

volatile uint64_t microTick = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    int i = 0;
    /* User may add here some code to deal with this error */
    setRGBLed(0, 0, 0);
    while (i < 20)
    {
        toggleRedLed();
        for (uint64_t j = 0; j < 400000; j++)
            ;
        i++;
    }
    if (DEBUG_ENABLED())
        debug_printf("Something went wrong, rebooting...\n");
    Reboot();
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    HAL_IncTick();

    if (HAL_GetTick() % 10 == 0)
    {
        tickCommunicationWatchdog(10);
    }
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/
/**
  * @brief  This function handles DMA interrupt request.
  * @param  None
  * @retval None
  */
void SPIx_DMA_RX_IRQHandler(void)
{
    HAL_DMA_IRQHandler(SpiHandle.hdmarx);
    HAL_DMA_IRQHandler(SpiHandle.hdmatx);
}

/**
  * @brief  This function handles DMA interrupt request.
  * @param  None
  * @retval None
  * @Note   This function is redefined in "main.h" and related to DMA
  *         used for I2C data reception
  */
void I2Cx_DMA_RX_IRQHandler(void)
{
    HAL_DMA_IRQHandler(I2cHandle.hdmarx);
    HAL_DMA_IRQHandler(I2cHandle.hdmatx);
}

/**
  * @brief  This function handles EXT interrupt request.
  * @param  None
  * @retval None
  */

void EXTI0_1_IRQHandler(uint16_t GPIO_Pin)
{
    HAL_GPIO_EXTI_IRQHandler(PHOTODIODE_2_PIN);
}

void EXTI2_3_IRQHandler(uint16_t GPIO_Pin)
{
    /* EXTI line interrupt detected */
    HAL_GPIO_EXTI_IRQHandler(TOUCH_CHANGE_PIN);
}

void EXTI4_15_IRQHandler(uint16_t GPIO_Pin)
{
    /* EXTI line interrupt detected */
    HAL_GPIO_EXTI_IRQHandler(PHOTODIODE_1_PIN);
    HAL_GPIO_EXTI_IRQHandler(IMU_INT_PIN);
    HAL_GPIO_EXTI_IRQHandler(CHARGING_STATUS_PIN);
    HAL_GPIO_EXTI_IRQHandler(RADIO_IRQ_PIN);
}

/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
void MICRO_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&microTimHandle);
    microTick += MICRO_PERIOD;
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/