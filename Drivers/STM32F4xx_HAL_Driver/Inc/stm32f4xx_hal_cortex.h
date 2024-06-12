/**
  ******************************************************************************
  * @file    stm32f4xx_hal_cortex.h
  * @author  MCD Application Team-Li Changyi comment 2024.6.12
  * @brief   Header file of CORTEX HAL module.
  * @content 1.内存保护单元MPU配置 2.中断启禁、状态、中断优先组、抢占优先级、响应优先级配置 3. 配置 SysTick 时钟源、重载值、中断处理函数
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_HAL_CORTEX_H
#define __STM32F4xx_HAL_CORTEX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal_def.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @addtogroup CORTEX
  * @{
  */ 
/* Exported types ------------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Types Cortex Exported Types
  * @{
  */

#if (__MPU_PRESENT == 1U)
/** @defgroup CORTEX_MPU_Region_Initialization_Structure_definition MPU Region Initialization Structure Definition
  * @brief  MPU Region initialization structure 
  * @{
  */
typedef struct
{
  uint8_t                Enable;                /*!< Specifies the status of the region. 
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Enable                 */
  uint8_t                Number;                /*!< Specifies the number of the region to protect. 
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Number                 */
  uint32_t               BaseAddress;           /*!< Specifies the base address of the region to protect.                           */
  uint8_t                Size;                  /*!< Specifies the size of the region to protect. 
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Size                   */
  uint8_t                SubRegionDisable;      /*!< Specifies the number of the subregion protection to disable. 
                                                     This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF    */         
  uint8_t                TypeExtField;          /*!< Specifies the TEX field level.
                                                     This parameter can be a value of @ref CORTEX_MPU_TEX_Levels                    */                 
  uint8_t                AccessPermission;      /*!< Specifies the region access permission type. 
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Permission_Attributes  */
  uint8_t                DisableExec;           /*!< Specifies the instruction access status. 
                                                     This parameter can be a value of @ref CORTEX_MPU_Instruction_Access            */
  uint8_t                IsShareable;           /*!< Specifies the shareability status of the protected region. 
                                                     This parameter can be a value of @ref CORTEX_MPU_Access_Shareable              */
  uint8_t                IsCacheable;           /*!< Specifies the cacheable status of the region protected. 
                                                     This parameter can be a value of @ref CORTEX_MPU_Access_Cacheable              */
  uint8_t                IsBufferable;          /*!< Specifies the bufferable status of the protected region. 
                                                     This parameter can be a value of @ref CORTEX_MPU_Access_Bufferable             */
}MPU_Region_InitTypeDef; //配置内存保护单元（MPU，Memory Protection Unit）的一个区域的属性，MPU 用于设置不同内存区域的访问权限和属性
/**
  * @}
  */
#endif /* __MPU_PRESENT */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup CORTEX_Exported_Constants CORTEX Exported Constants
  * @{
  */

/** @defgroup CORTEX_Preemption_Priority_Group CORTEX Preemption Priority Group
  * @{
  */
#define NVIC_PRIORITYGROUP_0         0x00000007U /*!< 0 bits for pre-emption priority
                                                      4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         0x00000006U /*!< 1 bits for pre-emption priority
                                                      3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         0x00000005U /*!< 2 bits for pre-emption priority
                                                      2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         0x00000004U /*!< 3 bits for pre-emption priority
                                                      1 bits for subpriority */
#define NVIC_PRIORITYGROUP_4         0x00000003U /*!< 4 bits for pre-emption priority
                                                      0 bits for subpriority */
/**
  * @}
  */

/** @defgroup CORTEX_SysTick_clock_source CORTEX _SysTick clock source 
  * @{
  */
#define SYSTICK_CLKSOURCE_HCLK_DIV8    0x00000000U
#define SYSTICK_CLKSOURCE_HCLK         0x00000004U

/**
  * @}
  */

#if (__MPU_PRESENT == 1)
/** @defgroup CORTEX_MPU_HFNMI_PRIVDEF_Control MPU HFNMI and PRIVILEGED Access control
  * @{
  */
#define  MPU_HFNMI_PRIVDEF_NONE           0x00000000U
#define  MPU_HARDFAULT_NMI                MPU_CTRL_HFNMIENA_Msk
#define  MPU_PRIVILEGED_DEFAULT           MPU_CTRL_PRIVDEFENA_Msk
#define  MPU_HFNMI_PRIVDEF               (MPU_CTRL_HFNMIENA_Msk | MPU_CTRL_PRIVDEFENA_Msk)

/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Enable CORTEX MPU Region Enable
  * @{
  */
#define  MPU_REGION_ENABLE     ((uint8_t)0x01)
#define  MPU_REGION_DISABLE    ((uint8_t)0x00)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Instruction_Access CORTEX MPU Instruction Access
  * @{
  */
#define  MPU_INSTRUCTION_ACCESS_ENABLE      ((uint8_t)0x00)
#define  MPU_INSTRUCTION_ACCESS_DISABLE     ((uint8_t)0x01)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Access_Shareable CORTEX MPU Instruction Access Shareable
  * @{
  */
#define  MPU_ACCESS_SHAREABLE        ((uint8_t)0x01)
#define  MPU_ACCESS_NOT_SHAREABLE    ((uint8_t)0x00)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Access_Cacheable CORTEX MPU Instruction Access Cacheable
  * @{
  */
#define  MPU_ACCESS_CACHEABLE         ((uint8_t)0x01)
#define  MPU_ACCESS_NOT_CACHEABLE     ((uint8_t)0x00)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Access_Bufferable CORTEX MPU Instruction Access Bufferable
  * @{
  */
#define  MPU_ACCESS_BUFFERABLE         ((uint8_t)0x01)
#define  MPU_ACCESS_NOT_BUFFERABLE     ((uint8_t)0x00)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_TEX_Levels MPU TEX Levels
  * @{
  */
#define  MPU_TEX_LEVEL0    ((uint8_t)0x00)
#define  MPU_TEX_LEVEL1    ((uint8_t)0x01)
#define  MPU_TEX_LEVEL2    ((uint8_t)0x02)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Size CORTEX MPU Region Size
  * @{
  */
#define   MPU_REGION_SIZE_32B      ((uint8_t)0x04)
#define   MPU_REGION_SIZE_64B      ((uint8_t)0x05)
#define   MPU_REGION_SIZE_128B     ((uint8_t)0x06)
#define   MPU_REGION_SIZE_256B     ((uint8_t)0x07)
#define   MPU_REGION_SIZE_512B     ((uint8_t)0x08)
#define   MPU_REGION_SIZE_1KB      ((uint8_t)0x09)
#define   MPU_REGION_SIZE_2KB      ((uint8_t)0x0A)
#define   MPU_REGION_SIZE_4KB      ((uint8_t)0x0B)
#define   MPU_REGION_SIZE_8KB      ((uint8_t)0x0C)
#define   MPU_REGION_SIZE_16KB     ((uint8_t)0x0D)
#define   MPU_REGION_SIZE_32KB     ((uint8_t)0x0E)
#define   MPU_REGION_SIZE_64KB     ((uint8_t)0x0F)
#define   MPU_REGION_SIZE_128KB    ((uint8_t)0x10)
#define   MPU_REGION_SIZE_256KB    ((uint8_t)0x11)
#define   MPU_REGION_SIZE_512KB    ((uint8_t)0x12)
#define   MPU_REGION_SIZE_1MB      ((uint8_t)0x13)
#define   MPU_REGION_SIZE_2MB      ((uint8_t)0x14)
#define   MPU_REGION_SIZE_4MB      ((uint8_t)0x15)
#define   MPU_REGION_SIZE_8MB      ((uint8_t)0x16)
#define   MPU_REGION_SIZE_16MB     ((uint8_t)0x17)
#define   MPU_REGION_SIZE_32MB     ((uint8_t)0x18)
#define   MPU_REGION_SIZE_64MB     ((uint8_t)0x19)
#define   MPU_REGION_SIZE_128MB    ((uint8_t)0x1A)
#define   MPU_REGION_SIZE_256MB    ((uint8_t)0x1B)
#define   MPU_REGION_SIZE_512MB    ((uint8_t)0x1C)
#define   MPU_REGION_SIZE_1GB      ((uint8_t)0x1D)
#define   MPU_REGION_SIZE_2GB      ((uint8_t)0x1E)
#define   MPU_REGION_SIZE_4GB      ((uint8_t)0x1F)
/**
  * @}
  */
   
/** @defgroup CORTEX_MPU_Region_Permission_Attributes CORTEX MPU Region Permission Attributes 
  * @{
  */
#define  MPU_REGION_NO_ACCESS      ((uint8_t)0x00)
#define  MPU_REGION_PRIV_RW        ((uint8_t)0x01)
#define  MPU_REGION_PRIV_RW_URO    ((uint8_t)0x02)
#define  MPU_REGION_FULL_ACCESS    ((uint8_t)0x03)
#define  MPU_REGION_PRIV_RO        ((uint8_t)0x05)
#define  MPU_REGION_PRIV_RO_URO    ((uint8_t)0x06)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Number CORTEX MPU Region Number
  * @{
  */
#define  MPU_REGION_NUMBER0    ((uint8_t)0x00)
#define  MPU_REGION_NUMBER1    ((uint8_t)0x01)
#define  MPU_REGION_NUMBER2    ((uint8_t)0x02)
#define  MPU_REGION_NUMBER3    ((uint8_t)0x03)
#define  MPU_REGION_NUMBER4    ((uint8_t)0x04)
#define  MPU_REGION_NUMBER5    ((uint8_t)0x05)
#define  MPU_REGION_NUMBER6    ((uint8_t)0x06)
#define  MPU_REGION_NUMBER7    ((uint8_t)0x07)
/**
  * @}
  */
#endif /* __MPU_PRESENT */

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CORTEX_Exported_Functions
  * @{
  */
  
/** @addtogroup CORTEX_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions *****************************/
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);                                   // 设置 NVIC 的优先级分组
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);   // 设置中断的优先级(抢占优先级，子优先级）子优先级 = 响应优先级
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);                                                     // 启用中断
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);                                                    // 禁用中断
void HAL_NVIC_SystemReset(void);                                                             // 触发系统复位
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);                                             // 配置 SysTick 计时器 `TicksNumb`是 SysTick 计数器的重装载值
// 优先级分组确定了中断优先级字段中抢占优先级占几位，响应优先级占几位
// NVIC_PRIORITYGROUP_0: 0 位抢占优先级，4 位响应优先级
// NVIC_PRIORITYGROUP_1: 1 位抢占优先级，3 位响应优先级
// NVIC_PRIORITYGROUP_2: 2 位抢占优先级，2 位响应优先级 抢占优先级占用 2 位，可以有 4 个等级（0 到 3） 响应优先级占用 2 位，可以有 4 个等级（0 到 3）
// NVIC_PRIORITYGROUP_3: 3 位抢占优先级，1 位响应优先级
// NVIC_PRIORITYGROUP_4: 4 位抢占优先级，0 位响应优先级

/** @addtogroup CORTEX_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions ***********************************************/
uint32_t HAL_NVIC_GetPriorityGrouping(void);                                                  // 获取当前的优先级分组
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority);
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);                                              // 获取中断的挂起状态
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);                                                  // 设置中断为挂起状态
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);                                                // 清除中断的挂起状态
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn);                                                  // 获取中断的激活状态
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);                                         // 配置 SysTick的时钟源
void HAL_SYSTICK_IRQHandler(void);                                                            // SysTick 中断处理函数
void HAL_SYSTICK_Callback(void);                                                              // SysTick 中断回调函数 没用到

#if (__MPU_PRESENT == 1U)
void HAL_MPU_Enable(uint32_t MPU_Control);                                                    // 启用内存保护单元 MPU
void HAL_MPU_Disable(void);                                                                   // 禁用 MPU
void HAL_MPU_ConfigRegion(MPU_Region_InitTypeDef *MPU_Init);                                  // 配置 MPU 区域
#endif /* __MPU_PRESENT */                                                                    // 清除事件（如 WFE 等待事件）
void HAL_CORTEX_ClearEvent(void);
/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup CORTEX_Private_Macros CORTEX Private Macros
  * @{
  */
#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PRIORITYGROUP_0) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_1) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_2) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_3) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_4))

#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10U)

#define IS_NVIC_SUB_PRIORITY(PRIORITY)         ((PRIORITY) < 0x10U)

#define IS_NVIC_DEVICE_IRQ(IRQ)                ((IRQ) >= (IRQn_Type)0x00U)

#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SYSTICK_CLKSOURCE_HCLK) || \
                                       ((SOURCE) == SYSTICK_CLKSOURCE_HCLK_DIV8))

#if (__MPU_PRESENT == 1U)
#define IS_MPU_REGION_ENABLE(STATE) (((STATE) == MPU_REGION_ENABLE) || \
                                     ((STATE) == MPU_REGION_DISABLE))

#define IS_MPU_INSTRUCTION_ACCESS(STATE) (((STATE) == MPU_INSTRUCTION_ACCESS_ENABLE) || \
                                          ((STATE) == MPU_INSTRUCTION_ACCESS_DISABLE))

#define IS_MPU_ACCESS_SHAREABLE(STATE)   (((STATE) == MPU_ACCESS_SHAREABLE) || \
                                          ((STATE) == MPU_ACCESS_NOT_SHAREABLE))

#define IS_MPU_ACCESS_CACHEABLE(STATE)   (((STATE) == MPU_ACCESS_CACHEABLE) || \
                                          ((STATE) == MPU_ACCESS_NOT_CACHEABLE))

#define IS_MPU_ACCESS_BUFFERABLE(STATE)   (((STATE) == MPU_ACCESS_BUFFERABLE) || \
                                          ((STATE) == MPU_ACCESS_NOT_BUFFERABLE))

#define IS_MPU_TEX_LEVEL(TYPE) (((TYPE) == MPU_TEX_LEVEL0)  || \
                                ((TYPE) == MPU_TEX_LEVEL1)  || \
                                ((TYPE) == MPU_TEX_LEVEL2))

#define IS_MPU_REGION_PERMISSION_ATTRIBUTE(TYPE) (((TYPE) == MPU_REGION_NO_ACCESS)   || \
                                                  ((TYPE) == MPU_REGION_PRIV_RW)     || \
                                                  ((TYPE) == MPU_REGION_PRIV_RW_URO) || \
                                                  ((TYPE) == MPU_REGION_FULL_ACCESS) || \
                                                  ((TYPE) == MPU_REGION_PRIV_RO)     || \
                                                  ((TYPE) == MPU_REGION_PRIV_RO_URO))

#define IS_MPU_REGION_NUMBER(NUMBER)    (((NUMBER) == MPU_REGION_NUMBER0) || \
                                         ((NUMBER) == MPU_REGION_NUMBER1) || \
                                         ((NUMBER) == MPU_REGION_NUMBER2) || \
                                         ((NUMBER) == MPU_REGION_NUMBER3) || \
                                         ((NUMBER) == MPU_REGION_NUMBER4) || \
                                         ((NUMBER) == MPU_REGION_NUMBER5) || \
                                         ((NUMBER) == MPU_REGION_NUMBER6) || \
                                         ((NUMBER) == MPU_REGION_NUMBER7))

#define IS_MPU_REGION_SIZE(SIZE)    (((SIZE) == MPU_REGION_SIZE_32B)   || \
                                     ((SIZE) == MPU_REGION_SIZE_64B)   || \
                                     ((SIZE) == MPU_REGION_SIZE_128B)  || \
                                     ((SIZE) == MPU_REGION_SIZE_256B)  || \
                                     ((SIZE) == MPU_REGION_SIZE_512B)  || \
                                     ((SIZE) == MPU_REGION_SIZE_1KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_2KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_4KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_8KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_16KB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_32KB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_64KB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_128KB) || \
                                     ((SIZE) == MPU_REGION_SIZE_256KB) || \
                                     ((SIZE) == MPU_REGION_SIZE_512KB) || \
                                     ((SIZE) == MPU_REGION_SIZE_1MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_2MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_4MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_8MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_16MB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_32MB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_64MB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_128MB) || \
                                     ((SIZE) == MPU_REGION_SIZE_256MB) || \
                                     ((SIZE) == MPU_REGION_SIZE_512MB) || \
                                     ((SIZE) == MPU_REGION_SIZE_1GB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_2GB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_4GB))

#define IS_MPU_SUB_REGION_DISABLE(SUBREGION)  ((SUBREGION) < (uint16_t)0x00FF)
#endif /* __MPU_PRESENT */

/**                                                                          
  * @}                                                                  
  */

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

#endif /* __STM32F4xx_HAL_CORTEX_H */
 

