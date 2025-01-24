#include <stdio.h>
#include <stdint.h>
#include "n32l40x.h"
#include "User_Sysclock_Config.h"

/**
 * @brief  Configures system clock after wake-up from low power mode: enable HSE, PLL
 *         and select PLL as system clock source.
 * @param  freq: PLL clock eg 64000000
 * @param  src 
 *   This parameter can be one of the following values:
 *     @arg SYSCLK_PLLSRC_HSI,
 *     @arg SYSCLK_PLLSRC_HSIDIV2,
 *     @arg SYSCLK_PLLSRC_HSI_PLLDIV2,
 *     @arg SYSCLK_PLLSRC_HSIDIV2_PLLDIV2,
 *     @arg SYSCLK_PLLSRC_HSE,
 *     @arg SYSCLK_PLLSRC_HSEDIV2,
 *     @arg SYSCLK_PLLSRC_HSE_PLLDIV2,
 *     @arg SYSCLK_PLLSRC_HSEDIV2_PLLDIV2,       
 */
void SetSysClockToPLL(uint32_t freq, SYSCLK_PLL_TYPE src)
{
    uint32_t pllsrcclk=0;
    uint32_t pllsrc=0;
    uint32_t pllmul=0;
    uint32_t plldiv = RCC_PLLDIVCLK_DISABLE;
    uint32_t latency=0;
    uint32_t pclk1div=0, pclk2div=0;
    uint32_t msi_ready_flag = RESET;
    ErrorStatus HSEStartUpStatus=ERROR;
    ErrorStatus HSIStartUpStatus=ERROR;
    if (HSE_VALUE != 8000000)
    {
       /* HSE_VALUE == 8000000 is needed in this project! */
       while (1);
    }
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    if ((src == SYSCLK_PLLSRC_HSI)         || (src == SYSCLK_PLLSRC_HSIDIV2) 
     || (src == SYSCLK_PLLSRC_HSI_PLLDIV2) || (src == SYSCLK_PLLSRC_HSIDIV2_PLLDIV2))
    {
       /* Enable HSI */
       RCC_ConfigHsi(RCC_HSI_ENABLE);
       /* Wait till HSI is ready */
       HSIStartUpStatus = RCC_WaitHsiStable();
       if (HSIStartUpStatus != SUCCESS)
       {
          /* If HSI fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this
             error Go to infinite loop */
          while (1);
       }
       if ((src == SYSCLK_PLLSRC_HSIDIV2) || (src == SYSCLK_PLLSRC_HSIDIV2_PLLDIV2))
       {
          pllsrc = RCC_PLL_HSI_PRE_DIV2;
          pllsrcclk = HSI_VALUE/2;
          if(src == SYSCLK_PLLSRC_HSIDIV2_PLLDIV2)
          {
             plldiv = RCC_PLLDIVCLK_ENABLE;
             pllsrcclk = HSI_VALUE/4;
          }
       }
       else if ((src == SYSCLK_PLLSRC_HSI) || (src == SYSCLK_PLLSRC_HSI_PLLDIV2))
       {
          pllsrc = RCC_PLL_HSI_PRE_DIV1;
          pllsrcclk = HSI_VALUE;
          if(src == SYSCLK_PLLSRC_HSI_PLLDIV2)
          {
             plldiv = RCC_PLLDIVCLK_ENABLE;
             pllsrcclk = HSI_VALUE/2;
          }
       }
    } 
    else if ((src == SYSCLK_PLLSRC_HSE)         || (src == SYSCLK_PLLSRC_HSEDIV2) 
            || (src == SYSCLK_PLLSRC_HSE_PLLDIV2) || (src == SYSCLK_PLLSRC_HSEDIV2_PLLDIV2))
    {
       /* Enable HSE */
       RCC_ConfigHse(RCC_HSE_ENABLE);
       /* Wait till HSE is ready */
       HSEStartUpStatus = RCC_WaitHseStable();
       if (HSEStartUpStatus != SUCCESS)
       {
          /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this
             error Go to infinite loop */
          while (1);
       }
       if ((src == SYSCLK_PLLSRC_HSEDIV2) || (src == SYSCLK_PLLSRC_HSEDIV2_PLLDIV2))
       {
          pllsrc = RCC_PLL_SRC_HSE_DIV2;
          pllsrcclk = HSE_VALUE/2;
          if(src == SYSCLK_PLLSRC_HSEDIV2_PLLDIV2)
          {
             plldiv = RCC_PLLDIVCLK_ENABLE;
             pllsrcclk = HSE_VALUE/4;
          }
       }
       else if ((src == SYSCLK_PLLSRC_HSE) || (src == SYSCLK_PLLSRC_HSE_PLLDIV2))
       {
          pllsrc = RCC_PLL_SRC_HSE_DIV1;
          pllsrcclk = HSE_VALUE;
          if(src == SYSCLK_PLLSRC_HSE_PLLDIV2)
          {
             plldiv = RCC_PLLDIVCLK_ENABLE;
             pllsrcclk = HSE_VALUE/2;
          }
       }
    }
    latency = (freq/32000000);
    if(freq > 54000000)
    {
       pclk1div = RCC_HCLK_DIV4;
       pclk2div = RCC_HCLK_DIV2;
    }
    else
    {
       if(freq > 27000000)
       {
          pclk1div = RCC_HCLK_DIV2;
          pclk2div = RCC_HCLK_DIV1;
       }
       else
       {
          pclk1div = RCC_HCLK_DIV1;
          pclk2div = RCC_HCLK_DIV1;
       }
    }
    if(((freq % pllsrcclk) == 0) && ((freq / pllsrcclk) >= 2) && ((freq / pllsrcclk) <= 32))
    {
       pllmul = (freq / pllsrcclk);
       if(pllmul <= 16)
       {
          pllmul = ((pllmul - 2) << 18);
       }
       else
       {
          pllmul = (((pllmul - 17) << 18) | (1 << 27));
       }
    }
    else
    {
       while(1);
    }
    /* Cheak if MSI is Ready */
    if(RESET == RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_MSIRD))
    {
       /* Enable MSI and Config Clock */
       RCC_ConfigMsi(RCC_MSI_ENABLE, RCC_MSI_RANGE_4M);
       /* Waits for MSI start-up */
       while(SUCCESS != RCC_WaitMsiStable());
       msi_ready_flag = SET;
    }
    /* Select MSI as system clock source */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_MSI);
    FLASH_SetLatency(latency);
    /* HCLK = SYSCLK */
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);
    /* PCLK2 = HCLK */
    RCC_ConfigPclk2(pclk2div);
    /* PCLK1 = HCLK */
    RCC_ConfigPclk1(pclk1div);
    /* Disable PLL */
    RCC_EnablePll(DISABLE);
    RCC_ConfigPll(pllsrc, pllmul, plldiv);
    /* Enable PLL */
    RCC_EnablePll(ENABLE);
    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_CTRL_FLAG_PLLRDF) == RESET);
    /* Select PLL as system clock source */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLLCLK);
    /* Wait till PLL is used as system clock source */
    while (RCC_GetSysclkSrc() != 0x0C);
    if(msi_ready_flag == SET)
    {
       /* MSI oscillator OFF */
       RCC_ConfigMsi(RCC_MSI_DISABLE, RCC_MSI_RANGE_4M);
    }
}
