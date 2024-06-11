/**
  ******************************************************************************
  * @file    stm32f4xx_hal_def.h 
  * @author  MCD Application Team-Li Changyi comment 2024.6.10
  * @brief   This file contains HAL common defines, enumeration, macros and 
  *          structures definitions. 
  *          HAL���ͨ��ö�١��ꡢ�ṹ��  ������״̬������������ֵ��ö������
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
} HAL_StatusTypeDef;      // ״̬ö������

/** 
  * @brief  HAL Lock structures definition  
  */
typedef enum 
{
  HAL_UNLOCKED = 0x00U,
  HAL_LOCKED   = 0x01U    
} HAL_LockTypeDef;        // ����ö������

/* Exported macro ------------------------------------------------------------*/

#if !defined(UNUSED)
#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */ // ���߱�������XתΪvoid������ģ��������������δʹ�õĲ��� ʹ�÷��� UNUSED(unusedParam); 
#endif /* UNUSED */

#define HAL_MAX_DELAY      0xFFFFFFFFU    // �����ʱ��

#define HAL_IS_BIT_SET(REG, BIT)         (((REG) & (BIT)) == (BIT))     // ���ڼ��ĳ����ĳЩλ���� BIT ָ�����Ƿ�����Ϊ1
#define HAL_IS_BIT_CLR(REG, BIT)         (((REG) & (BIT)) == 0U)        // ���ڼ��ĳ����ĳЩλ���� BIT ָ�����Ƿ����Ϊ0

#define __HAL_LINKDMA(__HANDLE__, __PPP_DMA_FIELD__, __DMA_HANDLE__)               \
                        do{                                                      \
                              (__HANDLE__)->__PPP_DMA_FIELD__ = &(__DMA_HANDLE__); \
                              (__DMA_HANDLE__).Parent = (__HANDLE__);             \
                          } while(0U)  
// ���������� DMA ���֮����� 1. ��һ�� DMA �����һ������� DMA �ֶι��� 2.��һ������ľ������Ϊ DMA ����ĸ����  ���з����治���пո�
/** @brief Reset the Handle's State field.
  * @param __HANDLE__ specifies the Peripheral Handle.
  * @note  ��ʹ�õ�Ŀ��: 
  *          - �������Ϊ�ֲ���������ʱ���ڵ�һ�ν�����Ϊ�������ݸ� HAL_PPP_Init() ֮ǰ������ʹ�ô˺꽫����� State �ֶ�����Ϊ 0��
  *            ����State �ֶο��ܰ�������ֵ����һ�ε��� HAL_PPP_Init() ʱ�����ܻ������ײ�Ӳ����ʼ������ HAL_PPP_MspInit() ���ᱻִ��
  *          - ����Ҫ�������õײ�Ӳ��ʱ�����Ե��ô˺�Ȼ���ٵ��� HAL_PPP_Init()���� HAL_PPP_Init() �����У�
  *            ������� State �ֶα�����Ϊ 0 ʱ����ִ�� HAL_PPP_MspInit() �������Ӷ��������õײ�Ӳ��                        
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
#endif /* USE_RTOS */     // ������ �ڶ��������ϵͳ���� RTOS�����жϷ������ISR���з��ʹ�����Դʱ���õ�

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
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */  // ���ֱ����� 4�ֽڶ���ĺ겻һ��
  #ifndef __ALIGN_BEGIN
    #define __ALIGN_BEGIN
  #endif
  #ifndef __ALIGN_END
    #define __ALIGN_END      __attribute__ ((aligned (4)))
  #endif
  
#elif defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */  //  1. GCC ������ 
  #ifndef __ALIGN_END
  #define __ALIGN_END    __attribute__ ((aligned (4)))                // __ALIGN_END ��__attribute__ ((aligned(4))) ��ʾ����������ĩβʹ�ö�������
  #endif /* __ALIGN_END */
  #ifndef __ALIGN_BEGIN                                               // __ALIGN_BEGIN ������Ϊ��
    #define __ALIGN_BEGIN
  #endif /* __ALIGN_BEGIN */

#else
  #ifndef __ALIGN_END                                                 // __ALIGN_END ������Ϊ��  ��������������������˵
    #define __ALIGN_END
  #endif /* __ALIGN_END */
  
  #ifndef __ALIGN_BEGIN      
    #if defined   (__CC_ARM)      /* ARM Compiler V5*/               //  2. ARM Compiler V5 ������
#define __ALIGN_BEGIN    __align(4)                                  //  __ALIGN_BEGIN: ʹ�� __align(4)����ʾ������������ʼ����ʹ�ö�������
    #elif defined (__ICCARM__)    /* IAR Compiler */                 //  3. IAR ������
      #define __ALIGN_BEGIN                                          //  __ALIGN_BEGIN: ������Ϊ��  IAR ������ ʹ�� #pragma ����
    #endif /* __CC_ARM */                                           
  #endif /* __ALIGN_BEGIN */                                                                                      
#endif /* __GNUC__ */


/** 
  * @brief  __RAM_FUNC definition
  */ 
#if defined ( __CC_ARM   ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))   // ������ARM Compiler V5
/* ARM Compiler V4/V5 and V6
   --------------------------
   RAM functions are defined using the toolchain options. 
   Functions that are executed in RAM should reside in a separate source module.
   Using the 'Options for File' dialog you can simply change the 'Code / Const' 
   area of a module to a memory space in physical RAM.
   Available memory areas are declared in the 'Target' tab of the 'Options for Target'
   dialog. 
   1.__RAM_FUNC ������������Ҫ�� RAM ��ִ�еĺ���
   2.���ݲ�ͬ�ı��������궨��������ͬ������Ӧ���������������﷨����������
   3.ʹ����Щ�꣬����ȷ���ؼ�������� RAM ��ִ�ж�����ͨ���������У������ִ���ٶȺ���Ӧʱ��
   4.��ô����Ҫ�������˽�
*/
#define __RAM_FUNC                  // ��Ϊ������ѡ���Ѿ���������Щ������ RAM ���ã����Բ���Ҫ����ĺ궨�壬��� __RAM_FUNC ������Ϊ�ա�

#elif defined ( __ICCARM__ )        // IAR ������
/* ICCARM Compiler
   ---------------
   RAM functions are defined using a specific toolchain keyword "__ramfunc". 
*/
#define __RAM_FUNC __ramfunc        // IAR ������ __RAM_FUNC �ĺ궨��

#elif defined   (  __GNUC__  )      // GCC ������
/* GNU Compiler
   ------------
  RAM functions are defined using a specific toolchain attribute 
   "__attribute__((section(".RamFunc")))".
*/
#define __RAM_FUNC __attribute__((section(".RamFunc")))   // GCC ������ __RAM_FUNC  �ĺ궨��

#endif

/** 
  * @brief  __NOINLINE definition
  */ 
#if defined ( __CC_ARM   ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) || defined   (  __GNUC__  )
/* ARM V4/V5 and V6 & GNU Compiler
   -------------------------------
*/
#define __NOINLINE __attribute__ ( (noinline) )  // ǿ�ƺ��������������Ż�,���ں�����ǰ

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


