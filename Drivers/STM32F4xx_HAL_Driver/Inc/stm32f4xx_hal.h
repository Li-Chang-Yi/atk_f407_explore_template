/**
  ******************************************************************************
  * @file    stm32f4xx_hal.h
  * @author  MCD Application Team-Li Changyi comment 2024.6.9
  * @brief   This file contains all the functions prototypes for the HAL 
  *          module driver. HAL模块驱动函数原型
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_HAL_H
#define __STM32F4xx_HAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal_conf.h" //包含HAL库配置头文件

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @addtogroup HAL
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup HAL_Exported_Constants HAL Exported Constants
  * @{
  */

/** @defgroup HAL_TICK_FREQ Tick Frequency
  * @{
  */
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,    // 10HZ表示每秒产生10个滴答中断，定时器中断之间的时间间隔为 1000ms/10 = 100 毫秒
  HAL_TICK_FREQ_100HZ        = 10U,     // 同理 定时器中断时间间隔为 1000ms/100 = 10ms
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ  // 默认定时器中断时间间隔为1ms一次
} HAL_TickFreqTypeDef;
/**
  * @}
  */

/**
  * @}
  */
   
/* Exported macro ------------------------------------------------------------*/
/* 宏通常会被放在头文件中，以便在多个源文件中使用，导出的意思就时包含该头文件，通过 #include 预处理指令被导出到需要它们的源文件中*/
/** @defgroup HAL_Exported_Macros HAL Exported Macros
  * @{
  */

/** @brief  Freeze/Unfreeze Peripherals in Debug mode 
  */
#define __HAL_DBGMCU_FREEZE_TIM2()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM2_STOP))
#define __HAL_DBGMCU_FREEZE_TIM3()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM3_STOP))
#define __HAL_DBGMCU_FREEZE_TIM4()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM4_STOP))
#define __HAL_DBGMCU_FREEZE_TIM5()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM5_STOP))
#define __HAL_DBGMCU_FREEZE_TIM6()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM6_STOP))
#define __HAL_DBGMCU_FREEZE_TIM7()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM7_STOP))
#define __HAL_DBGMCU_FREEZE_TIM12()          (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM12_STOP))
#define __HAL_DBGMCU_FREEZE_TIM13()          (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM13_STOP))
#define __HAL_DBGMCU_FREEZE_TIM14()          (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM14_STOP))
#define __HAL_DBGMCU_FREEZE_RTC()            (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_RTC_STOP))
#define __HAL_DBGMCU_FREEZE_WWDG()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_WWDG_STOP))
#define __HAL_DBGMCU_FREEZE_IWDG()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_IWDG_STOP))
#define __HAL_DBGMCU_FREEZE_I2C1_TIMEOUT()   (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT))
#define __HAL_DBGMCU_FREEZE_I2C2_TIMEOUT()   (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT))
#define __HAL_DBGMCU_FREEZE_I2C3_TIMEOUT()   (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT))
#define __HAL_DBGMCU_FREEZE_CAN1()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_CAN1_STOP))
#define __HAL_DBGMCU_FREEZE_CAN2()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_CAN2_STOP))
#define __HAL_DBGMCU_FREEZE_TIM1()           (DBGMCU->APB2FZ |= (DBGMCU_APB2_FZ_DBG_TIM1_STOP))
#define __HAL_DBGMCU_FREEZE_TIM8()           (DBGMCU->APB2FZ |= (DBGMCU_APB2_FZ_DBG_TIM8_STOP))
#define __HAL_DBGMCU_FREEZE_TIM9()           (DBGMCU->APB2FZ |= (DBGMCU_APB2_FZ_DBG_TIM9_STOP))
#define __HAL_DBGMCU_FREEZE_TIM10()          (DBGMCU->APB2FZ |= (DBGMCU_APB2_FZ_DBG_TIM10_STOP))
#define __HAL_DBGMCU_FREEZE_TIM11()          (DBGMCU->APB2FZ |= (DBGMCU_APB2_FZ_DBG_TIM11_STOP))

#define __HAL_DBGMCU_UNFREEZE_TIM2()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM2_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM3()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM3_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM4()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM4_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM5()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM5_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM6()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM6_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM7()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM7_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM12()          (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM12_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM13()          (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM13_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM14()          (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM14_STOP))
#define __HAL_DBGMCU_UNFREEZE_RTC()            (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_RTC_STOP))
#define __HAL_DBGMCU_UNFREEZE_WWDG()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_WWDG_STOP))
#define __HAL_DBGMCU_UNFREEZE_IWDG()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_IWDG_STOP))
#define __HAL_DBGMCU_UNFREEZE_I2C1_TIMEOUT()   (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT))
#define __HAL_DBGMCU_UNFREEZE_I2C2_TIMEOUT()   (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT))
#define __HAL_DBGMCU_UNFREEZE_I2C3_TIMEOUT()   (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT))
#define __HAL_DBGMCU_UNFREEZE_CAN1()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_CAN1_STOP))
#define __HAL_DBGMCU_UNFREEZE_CAN2()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_CAN2_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM1()           (DBGMCU->APB2FZ &= ~(DBGMCU_APB2_FZ_DBG_TIM1_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM8()           (DBGMCU->APB2FZ &= ~(DBGMCU_APB2_FZ_DBG_TIM8_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM9()           (DBGMCU->APB2FZ &= ~(DBGMCU_APB2_FZ_DBG_TIM9_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM10()          (DBGMCU->APB2FZ &= ~(DBGMCU_APB2_FZ_DBG_TIM10_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM11()          (DBGMCU->APB2FZ &= ~(DBGMCU_APB2_FZ_DBG_TIM11_STOP))

/** @brief  Main Flash memory mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_FLASH()             (SYSCFG->MEMRMP &= ~(SYSCFG_MEMRMP_MEM_MODE))

/** @brief  System Flash memory mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH()       do {SYSCFG->MEMRMP &= ~(SYSCFG_MEMRMP_MEM_MODE);\
                                                         SYSCFG->MEMRMP |= SYSCFG_MEMRMP_MEM_MODE_0;\
                                                        }while(0);

/** @brief  Embedded SRAM mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_SRAM()       do {SYSCFG->MEMRMP &= ~(SYSCFG_MEMRMP_MEM_MODE);\
                                                  SYSCFG->MEMRMP |= (SYSCFG_MEMRMP_MEM_MODE_0 | SYSCFG_MEMRMP_MEM_MODE_1);\
                                                 }while(0);

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx)|| defined(STM32F417xx)
/** @brief  FSMC Bank1 (NOR/PSRAM 1 and 2) mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_FSMC()       do {SYSCFG->MEMRMP &= ~(SYSCFG_MEMRMP_MEM_MODE);\
                                                  SYSCFG->MEMRMP |= (SYSCFG_MEMRMP_MEM_MODE_1);\
                                                 }while(0);
#endif /* STM32F405xx || STM32F415xx || STM32F407xx || STM32F417xx */

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
/** @brief  FMC Bank1 (NOR/PSRAM 1 and 2) mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_FMC()       do {SYSCFG->MEMRMP &= ~(SYSCFG_MEMRMP_MEM_MODE);\
                                                 SYSCFG->MEMRMP |= (SYSCFG_MEMRMP_MEM_MODE_1);\
                                                }while(0);

/** @brief  FMC/SDRAM Bank 1 and 2 mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_FMC_SDRAM()       do {SYSCFG->MEMRMP &= ~(SYSCFG_MEMRMP_MEM_MODE);\
                                                       SYSCFG->MEMRMP |= (SYSCFG_MEMRMP_MEM_MODE_2);\
                                                      }while(0);
#endif /* STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx || STM32F469xx || STM32F479xx */ 

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F413xx) || defined(STM32F423xx)
/** @defgroup Cortex_Lockup_Enable Cortex Lockup Enable
  * @{
  */
/** @brief  SYSCFG Break Lockup lock
  *         Enables and locks the connection of Cortex-M4 LOCKUP (Hardfault) output to TIM1/8 input
  * @note   The selected configuration is locked and can be unlocked by system reset
  */
#define __HAL_SYSCFG_BREAK_PVD_LOCK()      do {SYSCFG->CFGR2 &= ~(SYSCFG_CFGR2_PVD_LOCK); \
                                               SYSCFG->CFGR2 |= SYSCFG_CFGR2_PVD_LOCK;    \
                                              }while(0)
/**
 * @}
 */

/** @defgroup PVD_Lock_Enable PVD Lock
  * @{
  */
/** @brief  SYSCFG Break PVD lock
  *         Enables and locks the PVD connection with Timer1/8 Break Input, , as well as the PVDE and PLS[2:0] in the PWR_CR register
  * @note   The selected configuration is locked and can be unlocked by system reset
  */
#define __HAL_SYSCFG_BREAK_LOCKUP_LOCK()     do {SYSCFG->CFGR2 &= ~(SYSCFG_CFGR2_LOCKUP_LOCK); \
                                                 SYSCFG->CFGR2 |= SYSCFG_CFGR2_LOCKUP_LOCK;    \
                                                }while(0)
/**
 * @}
 */
#endif /* STM32F410Tx || STM32F410Cx || STM32F410Rx || STM32F413xx || STM32F423xx */
/**
  * @}
  */

/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */
#define IS_TICKFREQ(FREQ) (((FREQ) == HAL_TICK_FREQ_10HZ)  || \
                           ((FREQ) == HAL_TICK_FREQ_100HZ) || \
                           ((FREQ) == HAL_TICK_FREQ_1KHZ))
/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup HAL_Exported_Variables
  * @{
  */
extern __IO uint32_t uwTick;   // 为什么这里要用 extern 关键字呢？
extern uint32_t uwTickPrio;    // 因为除了定义该变量的f4xx_hal.c文件要用，还有其他.c要用，比如rcc.c
extern HAL_TickFreqTypeDef uwTickFreq;
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup HAL_Exported_Functions_Group1   第一组 初始化和配置函数
  * @{
  */
/* Initialization and Configuration functions  ******************************/
HAL_StatusTypeDef HAL_Init(void);   // 设置系统时钟，配置中断优先级分组，并调用HAL_MspInit进行底层硬件初始化
HAL_StatusTypeDef HAL_DeInit(void); // 恢复系统到复位状态，并调用HAL_MspDeInit进行底层硬件去初始化
void HAL_MspInit(void);             // 用于初始化MCU特定的硬件资源，如时钟、GPIO和中断等
void HAL_MspDeInit(void);           // 用于反初始化MCU特定的硬件资源
HAL_StatusTypeDef HAL_InitTick (uint32_t TickPriority);  // 初始化系统滴答定时器（SysTick），用于生成系统时钟节拍

/** @addtogroup HAL_Exported_Functions_Group2  第二组 外设控制函数
  * @{
  */
/* Peripheral Control functions  ************************************************/
void HAL_IncTick(void);                                     // 增加系统滴答计数器，通常在SysTick_Handler中调用
void HAL_Delay(uint32_t Delay);                             // 产生一个指定毫秒的延时
uint32_t HAL_GetTick(void);                                 // 获取系统滴答计数值，单位为毫秒
uint32_t HAL_GetTickPrio(void);                             // 获取滴答定时器的中断优先级
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);// 设置系统滴答频率
HAL_TickFreqTypeDef HAL_GetTickFreq(void);                  // 获取当前系统滴答频率
void HAL_SuspendTick(void);                                 // 暂停系统滴答计数
void HAL_ResumeTick(void);                                  // 恢复系统滴答计数
                                                            
uint32_t HAL_GetHalVersion(void);                           // 获取当前HAL库的版本
uint32_t HAL_GetREVID(void);                                // 获取MCU的修订ID
uint32_t HAL_GetDEVID(void);                                // 获取MCU的设备ID

void HAL_DBGMCU_EnableDBGSleepMode(void);                   // 启用调试时进入睡眠模式
void HAL_DBGMCU_DisableDBGSleepMode(void);                  // 禁用调试时进入睡眠模式
void HAL_DBGMCU_EnableDBGStopMode(void);                    // 启用调试时进入停止模式
void HAL_DBGMCU_DisableDBGStopMode(void);                   // 禁用调试时进入停止模式
void HAL_DBGMCU_EnableDBGStandbyMode(void);                 // 启用调试时进入待机模式
void HAL_DBGMCU_DisableDBGStandbyMode(void);                // 禁用调试时进入待机模式

void HAL_EnableCompensationCell(void);                      // 启用电压补偿单元
void HAL_DisableCompensationCell(void);                     // 禁用电压补偿单元

uint32_t HAL_GetUIDw0(void);                                // 获取UID的第0个字 UID(MCU的唯一标识符)
uint32_t HAL_GetUIDw1(void);                                // 获取UID的第1个字 
uint32_t HAL_GetUIDw2(void);                                // 获取UID的第2个字 

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
void HAL_EnableMemorySwappingBank(void);
void HAL_DisableMemorySwappingBank(void);
#endif /* STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx || STM32F469xx || STM32F479xx */ 
/**
  * @}
  */

/**
  * @}
  */
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup HAL_Private_Variables HAL Private Variables
  * @{
  */
/**
  * @}
  */
/* Private constants ---------------------------------------------------------*/
/** @defgroup HAL_Private_Constants HAL Private Constants
  * @{
  */
/**
  * @}
  */
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @}
  */

/**
  * @}
  */ 
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_H */


