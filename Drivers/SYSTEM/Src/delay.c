/**
 ****************************************************************************************************
 * @file        delay.c
 * @author      lichangyi
 * @version     V1.0
 * @date        2024-05-29
 * @brief       ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���(֧��ucosii)
 *              �ṩdelay_init��ʼ�������� delay_us��delay_ms����ʱ����
 * @license     
 ****************************************************************************************************
 * @attention
 *
 * �޸�SYS_SUPPORT_OS���ִ���, Ĭ�Ͻ�֧��UCOSII 2.93.01�汾, ����OS��ο�ʵ��
 * �޸�delay_init����ʹ��8��Ƶ,ȫ��ͳһʹ��MCUʱ��
 * �޸�delay_usʹ��ʱ��ժȡ����ʱ, ����OS
 * �޸�delay_msֱ��ʹ��delay_us��ʱʵ��.
 *
 ****************************************************************************************************
 */

#include "sys.h"
#include "delay.h"


static uint32_t g_fac_us = 0;       /* us��ʱ������ */

/* ���SYS_SUPPORT_OS������,˵��Ҫ֧��OS��(������UCOS) */
#if SYS_SUPPORT_OS

/* ��ӹ���ͷ�ļ� ( ucos��Ҫ�õ�) */
#include "os.h"

/* ����g_fac_ms����, ��ʾms��ʱ�ı�����, ����ÿ�����ĵ�ms��, (����ʹ��os��ʱ��,��Ҫ�õ�) */
static uint16_t g_fac_ms = 0;

/*
 *  ��delay_us/delay_ms��Ҫ֧��OS��ʱ����Ҫ������OS��صĺ궨��ͺ�����֧��
 *  ������3���궨��:
 *      delay_osrunning    :���ڱ�ʾOS��ǰ�Ƿ���������,�Ծ����Ƿ����ʹ����غ���
 *      delay_ostickspersec:���ڱ�ʾOS�趨��ʱ�ӽ���,delay_init�����������������ʼ��systick
 *      delay_osintnesting :���ڱ�ʾOS�ж�Ƕ�׼���,��Ϊ�ж����治���Ե���,delay_msʹ�øò����������������
 *  Ȼ����3������:
 *      delay_osschedlock  :��������OS�������,��ֹ����
 *      delay_osschedunlock:���ڽ���OS�������,���¿�������
 *      delay_ostimedly    :����OS��ʱ,���������������.
 *
 *  �����̽���UCOSII��֧��,����OS,�����вο�����ֲ
 */

/* ֧��UCOSII */
#define delay_osrunning     OSRunning           /* OS�Ƿ����б��,0,������;1,������ */
#define delay_ostickspersec OS_TICKS_PER_SEC    /* OSʱ�ӽ���,��ÿ����ȴ��� */
#define delay_osintnesting  OSIntNesting        /* �ж�Ƕ�׼���,���ж�Ƕ�״��� */


/**
 * @brief     us����ʱʱ,�ر��������(��ֹ���us���ӳ�)
 * @param     ��
 * @retval    ��
 */
void delay_osschedlock(void)
{
    OSSchedLock();                      /* UCOSII�ķ�ʽ,��ֹ���ȣ���ֹ���us��ʱ */
}

/**
 * @brief     us����ʱʱ,�ָ��������
 * @param     ��
 * @retval    ��
 */
void delay_osschedunlock(void)
{
    OSSchedUnlock();                    /* UCOSII�ķ�ʽ,�ָ����� */
}

/**
 * @brief     us����ʱʱ,�ָ��������
 * @param     ticks: ��ʱ�Ľ�����
 * @retval    ��
 */
void delay_ostimedly(uint32_t ticks)
{
    OSTimeDly(ticks);                               /* UCOSII��ʱ */
}

/**
 * @brief     systick�жϷ�����,ʹ��OSʱ�õ�
 * @param     ticks : ��ʱ�Ľ�����  
 * @retval    ��
 */  
void SysTick_Handler(void)
{
    /* OS ��ʼ����,��ִ�������ĵ��ȴ��� */
    if (delay_osrunning == OS_TRUE)
    {
        /* ���� uC/OS-II �� SysTick �жϷ����� */
        OS_CPU_SysTickHandler();
    }
    HAL_IncTick();
}
#endif

/**
 * @brief     ��ʼ���ӳٺ���
 * @param     sysclk: ϵͳʱ��Ƶ��, ��CPUƵ��(rcc_c_ck), 168MHz (MHz��Ӧus��)  sysclk = 168
 * @retval    ��
 */  
void delay_init(uint16_t sysclk)
{
#if SYS_SUPPORT_OS                                      /* �����Ҫ֧��OS */
    uint32_t reload;
#endif
    g_fac_us = sysclk;                                  /* ������HAL_Init���Ѷ�systick�������ã��������������������� 168MHZ*/
#if SYS_SUPPORT_OS                                      /* �����Ҫ֧��OS. */
    reload = sysclk;                                    /* ÿ���ӵļ������� ��λΪM */
    reload *= 1000000 / delay_ostickspersec;            /* ����delay_ostickspersec�趨���ʱ��,reloadΪ24λ
                                                         * �Ĵ���,���ֵ:16777216,��168M��,Լ��0.09986s����
                                                         */
    g_fac_ms = 1000 / delay_ostickspersec;              /* ����OS������ʱ�����ٵ�λ */
    SysTick->CTRL |= 1 << 1;                            /* ����SYSTICK�ж� */
    SysTick->LOAD = reload;                             /* ÿ1/delay_ostickspersec���ж�һ�� */
    SysTick->CTRL |= 1 << 0;                            /* ����SYSTICK */
#endif 
}

/**
 * @brief     ��ʱnus
 * @note      �����Ƿ�ʹ��OS, ������ʱ��ժȡ������us��ʱ
 * @param     nus: Ҫ��ʱ��us��
 * @note      nusȡֵ��Χ: 0 ~ (2^32 / fac_us) (fac_usһ�����ϵͳ��Ƶ, �����������)
 * @retval    ��
 */
void delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;        /* LOAD��ֵ-������0ʱ�����ص�ֵ */
    ticks = nus * g_fac_us;                 /* ��Ҫ�Ľ����������� g_fac_us = 168 */
                                            /* 1s��168M�Σ�1us��168�� Ҳ����SysTick->VAL��Ҫ�仯168*/
#if SYS_SUPPORT_OS                          /* �����Ҫ֧��OS */
    delay_osschedlock();                    /* ���� OS ����������� */
#endif

    told = SysTick->VAL;                    /* �ս���ʱ�ļ�����ֵ */
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)                /* û�г������ص���� */
            {
                tcnt += told - tnow;        /* SYSTICK��һ���ݼ��ļ����� */
            }
            else                            /* ������һ�����أ�����������˼����أ� */
            {
                tcnt += told + (reload - tnow);  /* told = told����0������ʱ��; (reload - tnow) = ��reload����tnow������ʱ�� */
            }
            
            told = tnow;                    /* �ȸ���ֵ���ж��Ƿ�����ѭ�� */
            if (tcnt >= ticks) 
            {
                break;                      /* ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳� */
            }
        }
    }

#if SYS_SUPPORT_OS                          /* �����Ҫ֧��OS */
    delay_osschedunlock();                  /* �ָ� OS ����������� */
#endif 

}

/**
 * @brief     ��ʱnms
 * @param     nms: Ҫ��ʱ��ms�� (0< nms <= (2^32 / fac_us / 1000))(fac_usһ�����ϵͳ��Ƶ, �����������)
 * @retval    ��
 */
void delay_ms(uint16_t nms)
{
    
#if SYS_SUPPORT_OS  /* �����Ҫ֧��OS, ������������os��ʱ���ͷ�CPU */
    if (delay_osrunning && delay_osintnesting == 0)     /* ���OS�Ѿ�������,���Ҳ������ж�����(�ж����治���������) */
    {
        if (nms >= g_fac_ms)                            /* ��ʱ��ʱ�����OS������ʱ������ */
        {
            delay_ostimedly(nms / g_fac_ms);            /* OS��ʱ */
        }

        nms %= g_fac_ms;                                /* OS�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ */
    }
#endif

    delay_us((uint32_t)(nms * 1000));                   /* ��ͨ��ʽ��ʱ */
}

/**
 * @brief       HAL���ڲ������õ�����ʱ
 * @note        HAL�����ʱĬ����Systick���������û�п�Systick���жϻᵼ�µ��������ʱ���޷��˳�
 * @param       Delay : Ҫ��ʱ�ĺ�����
 * @retval      None
 */
void HAL_Delay(uint32_t Delay)                          /* weak���� �û������¶��� HAL_Delayֻ��ʵ�ֺ��뼶����ʱ��ȥ��������*/
{
     delay_ms(Delay);
}
/**
 *  �˺���ΪHAL���ж�����ӳٺ�����ʹ��ǰ�迪��SysTick��
 *  ͨ������ HAL_GetTick() ������ȡʱ�䣬��δ�ﵽʱ�䣬����һ��ѭ���ڡ�
 *  Ϊ��ʹ uwTick ������ÿ����һ��SysTick�ж�ʱ����������SysTick_Handler() �е��� HAL_IncTick()��
 *  HAL_IncTick() ��һ��WEAK����ĺ�����Ĭ����ʹÿ������һ�α���uwTick ����1.
 *  ���ù�ϵ: tick�ж� -> SysTick_Handler -> HAL_IncTick(uwTick����)   HAL_Delay -> HAL_GetTick(�õ�uwTick) -> �Ƚ�ǰ��GetTick��ֵ���趨��Delayֵ
 *  �ж���һ�㲻��ʹ��ԭʼ��HAL_Delay����ΪSystick���ж����ȼ�����͵ģ��ж�������HAL_Delay�ᵼ����ʱ�����������
*/








