/**
  ******************************************************************************
  * @file    stm32f4xx_hal_def.h 
  * @author  MCD Application Team-Li Changyi comment 2024.6.10
  * @brief   This file contains HAL common defines, enumeration, macros and 
  *          structures definitions. 
  *          HAL库的通用枚举、宏、结构体  例如有状态、锁定、返回值的枚举类型
  ******************************************************************************

  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_HAL_DEF
#define __STM32F4xx_HAL_DEF

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "Legacy/stm32_hal_legacy.h"
#include <stddef.h>

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  HAL Status structures definition  
  */  
typedef enum 
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;      // 状态枚举类型

/** 
  * @brief  HAL Lock structures definition  
  */
typedef enum 
{
  HAL_UNLOCKED = 0x00U,
  HAL_LOCKED   = 0x01U    
} HAL_LockTypeDef;        // 锁定枚举类型

/* Exported macro ------------------------------------------------------------*/

#if !defined(UNUSED)
#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */ // 告诉编译器将X转为void是有意的，避免编译器警告未使用的参数 使用方法 UNUSED(unusedParam); 
#endif /* UNUSED */

#define HAL_MAX_DELAY      0xFFFFFFFFU    // 最大延时数

#define HAL_IS_BIT_SET(REG, BIT)         (((REG) & (BIT)) == (BIT))     // 用于检查某个或某些位（由 BIT 指定）是否被设置为1
#define HAL_IS_BIT_CLR(REG, BIT)         (((REG) & (BIT)) == 0U)        // 用于检查某个或某些位（由 BIT 指定）是否被清除为0

#define __HAL_LINKDMA(__HANDLE__, __PPP_DMA_FIELD__, __DMA_HANDLE__)               \
                        do{                                                      \
                              (__HANDLE__)->__PPP_DMA_FIELD__ = &(__DMA_HANDLE__); \
                              (__DMA_HANDLE__).Parent = (__HANDLE__);             \
                          } while(0U)  
// 将外设句柄与 DMA 句柄之间关联 1. 将一个 DMA 句柄与一个外设的 DMA 字段关联 2.将一个外设的句柄设置为 DMA 句柄的父句柄  分行符后面不能有空格
/** @brief Reset the Handle's State field.
  * @param __HANDLE__ specifies the Peripheral Handle.
  * @note  宏使用的目的: 
  *          - 当句柄作为局部变量声明时，在第一次将其作为参数传递给 HAL_PPP_Init() 之前，必须使用此宏将句柄的 State 字段设置为 0。
  *            否则，State 字段可能包含任意值，第一次调用 HAL_PPP_Init() 时，可能会跳过底层硬件初始化，即 HAL_PPP_MspInit() 不会被执行
  *          - 当需要重新配置底层硬件时，可以调用此宏然后再调用 HAL_PPP_Init()。在 HAL_PPP_Init() 函数中，
  *            当句柄的 State 字段被设置为 0 时，会执行 HAL_PPP_MspInit() 函数，从而重新配置底层硬件                        
  * @retval None
  */
#define __HAL_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = 0U)

#if (USE_RTOS == 1U)
  /* Reserved for future use */
  #error "USE_RTOS should be 0 in the current HAL release"
#else
  #define __HAL_LOCK(__HANDLE__)                                           \
                                do{                                        \
                                    if((__HANDLE__)->Lock == HAL_LOCKED)   \
                                    {                                      \
                                       return HAL_BUSY;                    \
                                    }                                      \
                                    else                                   \
                                    {                                      \
                                       (__HANDLE__)->Lock = HAL_LOCKED;    \
                                    }                                      \
                                  }while (0U)

  #define __HAL_UNLOCK(__HANDLE__)                                          \
                                  do{                                       \
                                      (__HANDLE__)->Lock = HAL_UNLOCKED;    \
                                    }while (0U)
#endif /* USE_RTOS */     // 锁机制 在多任务操作系统（如 RTOS）或中断服务程序（ISR）中访问共享资源时会用到

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
  #ifndef __weak
    #define __weak  __attribute__((weak))
  #endif
  #ifndef __packed
    #define __packed  __attribute__((packed))
  #endif
#elif defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */
  #ifndef __weak
    #define __weak   __attribute__((weak))
  #endif /* __weak */
  #ifndef __packed
    #define __packed __attribute__((__packed__))
  #endif /* __packed */
#endif /* __GNUC__ */


/* Macro to get variable aligned on 4-bytes, for __ICCARM__ the directive "#pragma data_alignment=4" must be used instead */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */  // 三种编译器 4字节对齐的宏不一样
  #ifndef __ALIGN_BEGIN
    #define __ALIGN_BEGIN
  #endif
  #ifndef __ALIGN_END
    #define __ALIGN_END      __attribute__ ((aligned (4)))
  #endif
  
#elif defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */  //  1. GCC 编译器 
  #ifndef __ALIGN_END
  #define __ALIGN_END    __attribute__ ((aligned (4)))                // __ALIGN_END ：__attribute__ ((aligned(4))) 表示变量在声明末尾使用对齐属性
  #endif /* __ALIGN_END */
  #ifndef __ALIGN_BEGIN                                               // __ALIGN_BEGIN 被定义为空
    #define __ALIGN_BEGIN
  #endif /* __ALIGN_BEGIN */

#else
  #ifndef __ALIGN_END                                                 // __ALIGN_END 被定义为空  对于下面两个编译器来说
    #define __ALIGN_END
  #endif /* __ALIGN_END */
  
  #ifndef __ALIGN_BEGIN      
    #if defined   (__CC_ARM)      /* ARM Compiler V5*/               //  2. ARM Compiler V5 编译器
#define __ALIGN_BEGIN    __align(4)                                  //  __ALIGN_BEGIN: 使用 __align(4)，表示变量在声明开始部分使用对齐属性
    #elif defined (__ICCARM__)    /* IAR Compiler */                 //  3. IAR 编译器
      #define __ALIGN_BEGIN                                          //  __ALIGN_BEGIN: 被定义为空  IAR 编译器 使用 #pragma 对齐
    #endif /* __CC_ARM */                                           
  #endif /* __ALIGN_BEGIN */                                                                                      
#endif /* __GNUC__ */


/** 
  * @brief  __RAM_FUNC definition
  */ 
#if defined ( __CC_ARM   ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))   // 我们是ARM Compiler V5
/* ARM Compiler V4/V5 and V6
   --------------------------
   RAM functions are defined using the toolchain options. 
   Functions that are executed in RAM should reside in a separate source module.
   Using the 'Options for File' dialog you can simply change the 'Code / Const' 
   area of a module to a memory space in physical RAM.
   Available memory areas are declared in the 'Target' tab of the 'Options for Target'
   dialog. 
   1.__RAM_FUNC 宏用于声明需要在 RAM 中执行的函数
   2.根据不同的编译器，宏定义有所不同，以适应各编译器的特殊语法和链接需求
   3.使用这些宏，可以确保关键代码段在 RAM 中执行而不是通常的闪存中，以提高执行速度和响应时间
   4.怎么用需要更深入了解
*/
#define __RAM_FUNC                  // 因为编译器选项已经处理了这些函数的 RAM 放置，所以不需要额外的宏定义，因此 __RAM_FUNC 被定义为空。

#elif defined ( __ICCARM__ )        // IAR 编译器
/* ICCARM Compiler
   ---------------
   RAM functions are defined using a specific toolchain keyword "__ramfunc". 
*/
#define __RAM_FUNC __ramfunc        // IAR 编译器 __RAM_FUNC 的宏定义

#elif defined   (  __GNUC__  )      // GCC 编译器
/* GNU Compiler
   ------------
  RAM functions are defined using a specific toolchain attribute 
   "__attribute__((section(".RamFunc")))".
*/
#define __RAM_FUNC __attribute__((section(".RamFunc")))   // GCC 编译器 __RAM_FUNC  的宏定义

#endif

/** 
  * @brief  __NOINLINE definition
  */ 
#if defined ( __CC_ARM   ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) || defined   (  __GNUC__  )
/* ARM V4/V5 and V6 & GNU Compiler
   -------------------------------
*/
#define __NOINLINE __attribute__ ( (noinline) )  // 强制函数不进行内联优化,用在函数名前

#elif defined ( __ICCARM__ )
/* ICCARM Compiler
   ---------------
*/
#define __NOINLINE _Pragma("optimize = no_inline")

#endif

#ifdef __cplusplus
}
#endif

#endif /* ___STM32F4xx_HAL_DEF */


