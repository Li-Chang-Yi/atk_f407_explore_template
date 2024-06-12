/**
 ****************************************************************************************************
 * @file        sys.c
 * @author      lichangyi
 * @version     V1.0
 * @date        2024-6-9
 * @brief       ϵͳ��ʼ������(����ʱ������/�жϹ���/GPIO���õ�)
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 */
#include <stdio.h>
#include <stdint.h>

#include "sys.h"


/**
 * @brief       �����ж�������ƫ�Ƶ�ַ
 * @param       baseaddr: ��ַ
 * @param       offset: ƫ����
 * @retval      ��
 */
void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset)
{
    /* ����NVIC��������ƫ�ƼĴ���,VTOR��9λ����,��[8:0]���� */
    SCB->VTOR = baseaddr | (offset & (uint32_t)0xFFFFFE00);
}

/**
 * @brief       ִ��: WFIָ��(ִ�����ָ�����͹���״̬, �ȴ��жϻ���)
 * @param       ��
 * @retval      ��
 */
void sys_wfi_set(void)
{
    __ASM volatile("wfi");
}

/**
 * @brief       �ر������ж�(���ǲ�����fault��NMI�ж�)
 * @param       ��
 * @retval      ��
 */
void sys_intx_disable(void)
{
    __ASM volatile("cpsid i");
}

/**
 * @brief       ���������ж�
 * @param       ��
 * @retval      ��
 */
void sys_intx_enable(void)
{
    __ASM volatile("cpsie i");
}

/**
 * @brief       ����ջ����ַ
 * @note        ��������ֺ�X, ����MDK��, ʵ����û�����
 * @param       addr: ջ����ַ
 * @retval      ��
 */
void sys_msr_msp(uint32_t addr)
{
    __set_MSP(addr);    /* ����ջ����ַ */
}

/**
 * @brief       �������ģʽ
 * @param       ��
 * @retval      ��
 */
void sys_standby(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();    /* ʹ�ܵ�Դʱ�� */
    SET_BIT(PWR->CR, PWR_CR_PDDS); /* �������ģʽ */
}

/**
 * @brief       ϵͳ��λ
 * @param       ��
 * @retval      ��
 */
void sys_soft_reset(void)
{
    NVIC_SystemReset();
}

/**
 * @brief       ʱ�����ú���(��ô���)
 * @param       pllm: PLL��Ԥ��Ƶϵ��m(��PLL֮ǰ�ķ�Ƶ), m: 2~63.                     (HSI | HSE)/m
 * @param       plln: PLL��Ƶϵ��n, n: 64~432.                                        [(HSI | HSE)/m]*n         Fvco
 * @param       pllp: PLL�ķ�Ƶϵ��p, ��Ƶ����Ϊϵͳʱ��, p: 2, 4, 6, 8.(������4��ֵ) [(HSI | HSE)/m]*n/p       Fsys
 * @param       pllq: PLL�ķ�Ƶϵ��q, q: 2~15.                                        [(HSI | HSE)/m]*n/q       Fq     q��ϵͳʱ���޹�
 * @note
 *
 *              Fvco: VCOƵ�ʣ�PLL ����Ļ���Ƶ��
 *              Fsys: ϵͳʱ��Ƶ��, Ҳ����PLL��p��Ƶ���ʱ��Ƶ��
 *              Fq:   ��PLL��q��Ƶ���ʱ��Ƶ��
 *              Fs:   ��PLL����ʱ��Ƶ��, ������HSI, HSE��.
 *              Fvco = Fs * (plln / pllm);                             n/m
 *              Fsys = Fvco / pllp = Fs * (plln / (pllm * pllp));      n/(m*p)
 *              Fq   = Fvco / pllq = Fs * (plln / (pllm * pllq));      n/(m*q)
 *
 *              �ⲿ����Ϊ 8M��ʱ��, �Ƽ�ֵ: plln = 336, pllm = 8, pllp = 2, pllq = 7.
 *              �õ�:Fvco = 8 * (336 / 8) = 336Mhz
 *                   Fsys = pll_p_ck = 336 / 2 = 168Mhz
 *                   Fq   = pll_q_ck = 336 / 7 = 48Mhz
 *
 *              F407Ĭ����Ҫ���õ�Ƶ������:
 *              CPUƵ��(HCLK) = pll_p_ck = 168Mhz
 *              AHB1/2/3(rcc_hclk1/2/3) = 168Mhz
 *              APB1(rcc_pclk1) = pll_p_ck / 4 = 42Mhz
 *              APB1(rcc_pclk2) = pll_p_ck / 2 = 84Mhz
 *
 * @retval      �������: 0, �ɹ�; 1, ����;
 */
uint8_t sys_stm32_clock_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq) /* HAL����ʱ����صı�����������f4xx_hal_rcc.c���� */
{
    HAL_StatusTypeDef ret = HAL_OK; /* f4xx_hal_def.h */
    RCC_OscInitTypeDef rcc_osc_init = {0}; /* RCC = Reset and Clock Control */
    RCC_ClkInitTypeDef rcc_clk_init = {0}; /* OSC = Oscillator ���� ���� */

    __HAL_RCC_PWR_CLK_ENABLE();                                         /* ʹ��PWRʱ�� */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);      /* ���õ�ѹ�������ѹ�����Ա�������δ�����Ƶ�ʹ��� */

    /* ʹ��HSE����ѡ��HSE��ΪPLLʱ��Դ������PLL1������USBʱ�� */
    rcc_osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;        /* ʱ��ԴΪHSE */
    rcc_osc_init.HSEState = RCC_HSE_ON;                          /* ��HSE */
    rcc_osc_init.PLL.PLLState = RCC_PLL_ON;                      /* ��PLL */
    rcc_osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;              /* PLLʱ��Դѡ��HSE */
    rcc_osc_init.PLL.PLLN = plln;                                /* PLL�ǽṹ���еĽṹ�� */
    rcc_osc_init.PLL.PLLM = pllm;
    rcc_osc_init.PLL.PLLP = pllp;
    rcc_osc_init.PLL.PLLQ = pllq;  
    ret = HAL_RCC_OscConfig(&rcc_osc_init);                      /* ��ʼ��RCC(��Ҫ) */
    if(ret != HAL_OK)
    {
        return 1;                                                /* ʱ�ӳ�ʼ��ʧ�ܣ���������������Լ��Ĵ��� */
    }
    /* HSE | HSI -> PLLSource -> HSE -> PLLN\PLLM\PLLP\PLLQ -> PLLCLK | HSE | HSI -> SYSCLKSource & CSS  -> SYSCLK */
    /* ѡ��PLLCLK��Ϊϵͳʱ��ԴSYSCLK��������AHB -> HCLK��APB1 -> PCLK1��APB2 -> PCLK2 */
    rcc_clk_init.ClockType = ( RCC_CLOCKTYPE_SYSCLK \
                                    | RCC_CLOCKTYPE_HCLK \
                                    | RCC_CLOCKTYPE_PCLK1 \
                                    | RCC_CLOCKTYPE_PCLK2);

    rcc_clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;         /* ����PLLCLK Ϊϵͳʱ��SYSCLK��Դ */
    rcc_clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;                /* AHB��Ƶϵ��Ϊ1 */
    rcc_clk_init.APB1CLKDivider = RCC_HCLK_DIV4;                 /* APB1��Ƶϵ��Ϊ4 */
    rcc_clk_init.APB2CLKDivider = RCC_HCLK_DIV2;                 /* APB2��Ƶϵ��Ϊ2 */
    ret = HAL_RCC_ClockConfig(&rcc_clk_init, FLASH_LATENCY_5);   /* ͬʱ����FLASH��ʱ����Ϊ5WS��Ҳ����6��CPU����(��Ҫ) */
    if(ret != HAL_OK)
    {
        return 1;                                                /* ʱ�ӳ�ʼ��ʧ�� */
    }
    
    /* STM32F405x/407x/415x/417x Z�汾������֧��Ԥȡ���� */
    if (HAL_GetREVID() == 0x1001)
    {
        __HAL_FLASH_PREFETCH_BUFFER_ENABLE();                    /* ʹ��flashԤȡ */
    }
    return 0;
}


#ifdef  USE_FULL_ASSERT                                          /* ���ԣ��ж��β� */

/**
 * @brief       ��������ʾ�����ʱ��˺����������������ļ���������
 * @param       file��ָ��Դ�ļ�
 *              line��ָ�����ļ��е�����
 * @retval      ��
 */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    while (1)
    {  
        printf("assert error��file is %s, line is %u",file, line); 
        for (volatile int i = 0; i < 1000000; i++);  // ����ʱ�Է�ֹ�������
        //printf("assert error��file is %s, line is %u",__FILE__,__LINE__);    
    }
}
#endif




