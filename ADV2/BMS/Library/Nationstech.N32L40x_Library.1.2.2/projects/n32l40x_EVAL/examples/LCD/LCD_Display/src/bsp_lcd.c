/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file bsp_lcd.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

/* Includes ------------------------------------------------------------------*/
#include "bsp_lcd.h"
#include "bsp_gpio.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup BSP_EVAL
  * @{
  */

/** @defgroup BSP_EVAL_GLASS_LCD
  * @brief This file includes the LCD Glass driver for LCD_GDC0689TP-11 Module 
  * @{
  */


/* Private constants ---------------------------------------------------------*/

/** @defgroup BSP_EVAL_GLASS_LCD_Private_Constants Private Constants
  * @{
  */
#define ASCII_CHAR_SPACE                0x20  /*   */
//#define ASCII_CHAR_FORWARD_SLASH      0x2F  /* / */
#define ASCII_CHAR_0                    0x30  /* 0 */
#define ASCII_CHAR_9                    0x39  /* 9 */
//#define ASCII_CHAR_COLON              0x3A  /* : */
//#define ASCII_CHAR_AT_SYMBOL          0x40  /* @ */
#define ASCII_CHAR_A                    0x41  /* A */
#define ASCII_CHAR_Z                    0x5A  /* Z */
#define ASCII_CHAR_a                    0x61  /* a */
#define ASCII_CHAR_z                    0x7A  /* z */
//#define ASCII_CHAR_LEFT_OPEN_BRACKET  0x5B  /* [ */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/** @defgroup BSP_EVAL_GLASS_LCD_Private_Variables Private Variables
  * @{
  */

/**
================================================================================
                              GLASS LCD MAPPING
================================================================================
               A
          ----------
          |         |
         F|         |B
          |         |
          ---- G ----
          |         |
         E|         |C
          |         |  _
          ----------- |_|DP  
              D

A LCD big character coding is based on the following matrix,DP will not be coding:
             COM0    COM1    COM2    COM3     
  SEG(n)    { F ,     G ,     E ,     D   }
  SEG(n+1)  { A ,     B ,     C ,     DP  }
The character 2 for example is:
-----------------------------------------------------------
             COM0    COM1     COM2    COM3  
  SEG(n)    { 0 ,     1 ,      1 ,     1  }
  SEG(n+1)  { 1 ,     1 ,      0 ,     0  }
   --------------------------------------------------------
           =  2       3        1       1      hex
   => '2' = 0x002311
     
A LCD little character coding is based on the following matrix:
             COM0    COM1    COM2    COM3     
  SEG(n)    { D ,     E ,     G ,     F   }
  SEG(n+1)  { DP1 ,   C,      B,      A   }
The character 2 for example is:
-----------------------------------------------------------
             COM0    COM1     COM2    COM3  
  SEG(n)    { 1 ,     1 ,      1 ,     0  }
  SEG(n+1)  { 0 ,     0 ,      1 ,     1  }
   --------------------------------------------------------
           =  1       1        3       2      hex

   => '2' = 0x001132
  */

__IO const uint32_t BigNumberMap[10] =
  {
    /*   0           1           2          3           4   */
    0x00003231, 0x00000220, 0x00002311, 0x00002321, 0x00001320,
    /*    5         6            7          8           9   */
    0x00003121, 0x00003131, 0x00002220, 0x00003331, 0x00003321
  };
__IO const uint32_t BigLetterMap[26] =
  {
    /*  A            B          C           D           E            F   */
    0x00003330, 0x00001131, 0x00003011, 0x00000331, 0x00003111, 0x00003110,
    /*   G            H          I            J           K         L    */
    0x00003031, 0x00001330, 0x00000020, 0x00000231, 0x00000000, 0x00001011,
    /*   M          N           O            P          Q         R      */
    0x00000000, 0x00000130, 0x00000131, 0x00003310, 0x00003320, 0x00000110,
    /*   S           T           U           V           W           X   */
    0x00003121, 0x00001111, 0x00001231, 0x00000000, 0x00000000, 0x00000000,
    /*  Y          Z     */
    0x00000000, 0x00000000
  }; //Letter unable display use 0x00000000 
    
//__IO const uint32_t LittleDigitMask[COM_NUM] =
//  {
//    0x0000F000, 0x00000F00, 0x000000F0, 0x0000000F
//  };

//const uint8_t LittleDigitShift[COM_NUM] =
//  {
//    12, 8, 4, 0
//  };


//uint32_t LittleDigit[COM_NUM]={0};     /* Little Digit frame buffer */

//__IO const uint32_t LittleNumberMap[10] =
//  {
//    /*   0           1           2          3           4   */
//    0x00001323, 0x00000220, 0x00001132, 0x00001232, 0x00000231,
//    /*    5         6            7          8           9   */
//    0x00001213, 0x00001313, 0x00000222, 0x00001333, 0x00001233
//  };
//__IO const uint32_t LittleLetterMap[26] =
//  {
//    /*  A            B          C           D           E            F   */
//    0x00000333, 0x00001311, 0x00001103, 0x00001330, 0x00001113, 0x00000113,
//    /*   G            H          I            J           K         L    */
//    0x00001303, 0x00000331, 0x00000200, 0x00001320, 0x00000000, 0x00001101,
//    /*   M          N           O            P          Q         R      */
//    0x00000000, 0x00000310, 0x00001310, 0x00000133, 0x00000233, 0x00000110,
//    /*   S           T           U           V           W           X   */
//    0x00001213, 0x00001111, 0x00001300, 0x00000000, 0x00000000, 0x00000000,
//    /*  Y          Z     */
//    0x00000000, 0x00000000
//  }; //Letter unable display use 0x00000000

/**
  * @brief LETTERS AND NUMBERS MAPPING DEFINITION
  */
#define COM_NUM         4
#define SEG_NUM         2 //max 4
#define BIG_DIGIT_MASK  ((0x1UL<<SEG_NUM)-1)

const uint8_t BigDigitShift[COM_NUM] =
  {
    12, 8, 4, 0
  };

/*digit buffer for sigle char*/
uint8_t BigDigit[COM_NUM][SEG_NUM]={0};     /* Big Digit frame buffer */

/*com and seg number for special mark*/
__IO const uint32_t LcdMarkMap[MAX_LCD_MARK][2]=
{
    /*   comx              seg set    */
    {(LCD_COMNUM_T1_REPAIR),(LCD_SEGNUM_T1_REPAIR)},    /*repair mark*/

    /*battery level*/
    {(LCD_COMNUM_W1_BATLEVEL_OFF), (LCD_SEGNUM_W1_BATLEVEL_OFF) },
    {(LCD_COMNUM_W2_BATLEVEL_1_4), (LCD_SEGNUM_W2_BATLEVEL_1_4) },
    {(LCD_COMNUM_W3_BATLEVEL_1_2), (LCD_SEGNUM_W3_BATLEVEL_1_2) },
    {(LCD_COMNUM_W4_BATLEVEL_3_4), (LCD_SEGNUM_W4_BATLEVEL_3_4) },
    {(LCD_COMNUM_W5_BATLEVEL_FULL),(LCD_SEGNUM_W5_BATLEVEL_FULL)},

    /*signal level*/
    {(LCD_COMNUM_L1_SIGNAL_LEVEL1),(LCD_SEGNUM_L1_SIGNAL_LEVEL1)},
    {(LCD_COMNUM_L2_SIGNAL_LEVEL2),(LCD_SEGNUM_L2_SIGNAL_LEVEL2)},
    {(LCD_COMNUM_L3_SIGNAL_LEVEL3),(LCD_SEGNUM_L3_SIGNAL_LEVEL3)},
    {(LCD_COMNUM_L4_SIGNAL_LEVEL4),(LCD_SEGNUM_L4_SIGNAL_LEVEL4)},

    /*Double point*/
    {(LCD_COMNUM_COL1_LITTLE_COL), (LCD_SEGNUM_COL1_LITTLE_COL) },
    {(LCD_COMNUM_COL2_BIG_COL_1ST),(LCD_SEGNUM_COL2_BIG_COL_1ST)},
    {(LCD_COMNUM_COL3_BIG_COL_2ND),(LCD_SEGNUM_COL3_BIG_COL_2ND)},

    /*unit mark*/
    {(LCD_COMNUM_S1_UNIT_MV), (LCD_SEGNUM_S1_UNIT_MV) },
    {(LCD_COMNUM_S2_UNIT_NM), (LCD_SEGNUM_S2_UNIT_NM) },
    {(LCD_COMNUM_S3_UNIT_KG), (LCD_SEGNUM_S3_UNIT_KG) },
    {(LCD_COMNUM_S4_UNIT_G),  (LCD_SEGNUM_S4_UNIT_G)  },
    {(LCD_COMNUM_S5_UNIT_MM), (LCD_SEGNUM_S5_UNIT_MM) },
    {(LCD_COMNUM_S6_UNIT_UE), (LCD_SEGNUM_S6_UNIT_UE) },
    {(LCD_COMNUM_S7_UNIT_KPA),(LCD_SEGNUM_S7_UNIT_KPA)},
    {(LCD_COMNUM_S8_UNIT_MPA),(LCD_SEGNUM_S8_UNIT_MPA)},
    {(LCD_COMNUM_S9_UNIT_OC), (LCD_SEGNUM_S9_UNIT_OC) }
};

/*two seg number for char*/
__IO const uint32_t LcdCharMap[MAX_LCD_CHAR][2]=
{
/*          segn                    segn+1   */
    {(LCD_SEGNUM_CHAR1_0),      (LCD_SEGNUM_CHAR1_1),   },   /*Little char 1*/
    {(LCD_SEGNUM_CHAR2_0),      (LCD_SEGNUM_CHAR2_1),   },   /*Little char 2*/
    {(LCD_SEGNUM_CHAR3_0),      (LCD_SEGNUM_CHAR3_1),   },   /*Little char 3*/
    {(LCD_SEGNUM_CHAR4_0),      (LCD_SEGNUM_CHAR4_1),   },   /*Little char 4*/
    
    {(LCD_SEGNUM_CHAR5_0),      (LCD_SEGNUM_CHAR5_1),   },   /*Big char 5*/
    {(LCD_SEGNUM_CHAR6_0),      (LCD_SEGNUM_CHAR6_1),   },   /*Big char 6*/
    {(LCD_SEGNUM_CHAR7_0),      (LCD_SEGNUM_CHAR7_1),   },   /*Big char 7*/
    {(LCD_SEGNUM_CHAR8_0),      (LCD_SEGNUM_CHAR8_1),   },   /*Big char 8*/
    
    {(LCD_SEGNUM_CHAR9_0),      (LCD_SEGNUM_CHAR9_1),   },   /*Big char 9*/
    {(LCD_SEGNUM_CHAR10_0),     (LCD_SEGNUM_CHAR10_1),  }    /*Big char 10*/
};

/**
  * @}
  */

    
/** @defgroup BSP_EVAL_GLASS_LCD_Private_Functions Private Functions
  * @{
  */
static void BigDigitConvert(uint8_t* c);    
static void BigDigitClear(void);
static void LCD_MspInit(void);

/**
  * @}
  */

/** @addtogroup BSP_EVAL_GLASS_LCD_Exported_Functions
  * @{
  */

/**
  * @brief  Configures the LCD GLASS relative GPIO port IOs and LCD peripheral.
  * @retval None
  */
void BSP_LCD_GLASS_Init(void)
{
    LCD_InitType Init = {0};
    /*LCD parameter config*/
    
    Init.Divider          = LCD_DIV_25;
#ifdef  LCD_8COM_USED
    Init.Prescaler        = LCD_PRESCALER_2;
    Init.Duty             = LCD_DUTY_1_8;
#else
    Init.Prescaler        = LCD_PRESCALER_4;
    Init.Duty             = LCD_DUTY_1_4;
#endif
    Init.Bias             = LCD_BIAS_1_3;
    Init.VoltageSource    = LCD_VOLTAGESOURCE_INTERNAL;
    Init.Contrast         = LCD_CONTRASTLEVEL_3;
    Init.DeadTime         = LCD_DEADTIME_0;
    Init.PulseOnDuration  = LCD_PULSEONDURATION_1;
    Init.HighDrive        = LCD_HIGHDRIVE_DISABLE;
    Init.HighDriveBuffer  = LCD_HIGHDRIVEBUFFER_ENABLE;
    Init.BlinkMode        = LCD_BLINKMODE_OFF;
    Init.BlinkFreq        = LCD_BLINKFREQ_DIV_8;
    Init.MuxSegment       = LCD_MUXSEGMENT_DISABLE;

    /* Initialize the LCD clk and used gpio*/
    LCD_MspInit();

    /*config and start LCD controller*/
    LCD_Init(&Init);
}

/**
  * @brief  Show all pixels on the LCD
  * @retval None
  */
void BSP_LCD_GLASS_ShowAll(void)
{
    LCD_Write(LCD_RAM1_COM0, 0x00000000, 0xFFFFFFFF);
    LCD_Write(LCD_RAM1_COM1, 0x00000000, 0xFFFFFFFF);
    LCD_Write(LCD_RAM1_COM2, 0x00000000, 0xFFFFFFFF);
    LCD_Write(LCD_RAM1_COM3, 0x00000000, 0xFFFFFFFF);
    LCD_Write(LCD_RAM2_COM0, 0x00000000, 0x00000FFF);
    LCD_Write(LCD_RAM2_COM1, 0x00000000, 0x00000FFF);
    LCD_Write(LCD_RAM2_COM2, 0x00000000, 0x00000FFF);
    LCD_Write(LCD_RAM2_COM3, 0x00000000, 0x00000FFF);
    
    LCD_Write(LCD_RAM1_COM4, 0x00000000, 0xFFFFFFFF);
    LCD_Write(LCD_RAM1_COM5, 0x00000000, 0xFFFFFFFF);
    LCD_Write(LCD_RAM1_COM6, 0x00000000, 0xFFFFFFFF);
    LCD_Write(LCD_RAM1_COM7, 0x00000000, 0xFFFFFFFF);
    LCD_Write(LCD_RAM2_COM4, 0x00000000, 0x000000FF);
    LCD_Write(LCD_RAM2_COM5, 0x00000000, 0x000000FF);
    LCD_Write(LCD_RAM2_COM6, 0x00000000, 0x000000FF);
    LCD_Write(LCD_RAM2_COM7, 0x00000000, 0x000000FF);
    
    LCD_UpdateDisplayRequest();
}

/**
  * @brief Setting the special mark on lcd, write ram and update
  * @param setMark:   the mark to be display
  * @param clearMark: the mark to be hide
  * @retval None
  */
void BSP_LCD_GLASS_ConfigMark(uint32_t setMark,uint32_t clearMark)
{
    uint32_t  i;

    /* Mask invalid bits */
    setMark   &= LCD_MARK_MASK;
    clearMark &= LCD_MARK_MASK;

    /* modify LCD ram */
    for(i=0;i<MAX_LCD_MARK;i++)
    {
        if(setMark & 0x01u)
            LCD_SetBit(LCD_START_COM+LcdMarkMap[i][0]*2+LcdMarkMap[i][1]/32, 0x1UL<<LcdMarkMap[i][1]);
        
        if(clearMark & 0x01u)
            LCD_ClearBit(LCD_START_COM+LcdMarkMap[i][0]*2+LcdMarkMap[i][1]/32,0x1UL<<LcdMarkMap[i][1]);
        
        setMark >>= 1;
        clearMark >>= 1;
    }
    
    /* Update the LCD display */
    LCD_UpdateDisplayRequest();
}

/**
  * @brief This function writes a char in the LCD frame buffer.
  * @param ch: the character to display.
  * @param Position: position in the LCD of the caracter to write [0:9]
  * @retval None
  * @note  Required preconditions: The LCD should be cleared before to start the
  *        write operation.
  */
void BSP_LCD_GLASS_WriteChar(uint8_t* ch, uint8_t Pos,uint32_t config)
{
    uint32_t j, k,t_com;

    if((Pos<MIN_LCD_CHAR)||(Pos>MAX_LCD_CHAR))
        return;
    
    /* Convert displayed character in segment in array digit */
    if(SET_MARK == config)
        BigDigitConvert(ch);
    else    //if(CLEAR_MARK == config)
        BigDigitClear();

    /* Modify the lcd ram */
    for(j=0;j<COM_NUM;j++)
    {
        for(k=0;k<SEG_NUM;k++)
        {
            if(Pos<LCD_BIGCHAR_START)
                t_com = COM_NUM-j-1;
            else
                t_com = j;
            
            if( ((COM_NUM-1)==t_com) && ((SEG_NUM-1)==k))   //skip "DP" position in the char
                break;

            if(BigDigit[t_com][k])
                LCD_SetBit( LCD_START_COM+(LcdCharMap[Pos-1][k]/32)+j*2,
                            0x1UL<<(LcdCharMap[Pos-1][k]%32));
            else
                LCD_ClearBit(LCD_START_COM+(LcdCharMap[Pos-1][k]/32)+j*2,
                             0x1UL<<(LcdCharMap[Pos-1][k]%32));
        }
    }

    /* Update display later */
}

/**
  * @brief  This function writes a char string in the LCD RAM.
  * @param  ptr:            The pointer of the string to be display on the LCD Glass.
  * @param  position: The string display start position [1:10].
  * @retval None
  */
void BSP_LCD_GLASS_DisplayString(uint8_t* ptr,uint8_t position)
{
    uint32_t ptrPlus;

    /*!< Send the string character by character on lCD */
    while(*ptr != '\0')
    {
        if( (position > MAX_LCD_CHAR) || (position < MIN_LCD_CHAR) )    /*check char positon*/
            break;

        if((*(ptr+1)) == '.')   /*set usefull point behind char*/
        {
            if(position<LCD_LITTLECHAR_NOPOINT)  /*for little char,at com0*/
            {
                LCD_SetBit( LCD_START_COM+LcdCharMap[position-1][1]/32, 
                            0x1UL << (LcdCharMap[position-1][1]%32));
            }
            else if((LCD_LITTLECHAR_NOPOINT<position)&&(position<LCD_BIGCHAR_NOPOINT))  /*for big char,at com3*/
            {
                LCD_SetBit( LCD_START_COM+LcdCharMap[position-1][1]/32+6, 
                            0x1UL << (LcdCharMap[position-1][1]%32));
            }
            
            ptrPlus = 2;    /*Dropped invalid point*/
        }
        else if((*(ptr+1)) == ':')  /*set usefull double point behind char*/
        {
            ptrPlus = 2;
            
            if(LCD_COL1_LITTLE_CHAR_POS == position)
                LCD_SetBit(LCD_START_COM+LCD_COMNUM_COL1_LITTLE_COL*2, 0x1UL<<LCD_SEGNUM_COL1_LITTLE_COL);
            if(LCD_COL2_BIG1_CHAR_POS == position)
                LCD_SetBit(LCD_START_COM+LCD_COMNUM_COL2_BIG_COL_1ST*2, 0x1UL<<LCD_SEGNUM_COL2_BIG_COL_1ST);
            else if(LCD_COL3_BIG2_CHAR_POS == position)
                LCD_SetBit(LCD_START_COM+LCD_COMNUM_COL3_BIG_COL_2ND*2, 0x1UL<<LCD_SEGNUM_COL3_BIG_COL_2ND);

            /*Dropped invalid double point*/
        }
        else    /*Single char without point or double point*/
        {
            ptrPlus = 1;
            
            /*clear double point*/
            if(LCD_COL1_LITTLE_CHAR_POS == position)
                LCD_ClearBit(LCD_START_COM+LCD_COMNUM_COL1_LITTLE_COL*2, 0x1UL<<LCD_SEGNUM_COL1_LITTLE_COL);
            if(LCD_COL2_BIG1_CHAR_POS == position)
                LCD_ClearBit(LCD_START_COM+LCD_COMNUM_COL2_BIG_COL_1ST*2, 0x1UL<<LCD_SEGNUM_COL2_BIG_COL_1ST);
            else if(LCD_COL3_BIG2_CHAR_POS == position)
                LCD_ClearBit(LCD_START_COM+LCD_COMNUM_COL3_BIG_COL_2ND*2, 0x1UL<<LCD_SEGNUM_COL3_BIG_COL_2ND);

            /*clear single point*/
            if(position<LCD_LITTLECHAR_NOPOINT)  /*for little char*/
            {
                LCD_ClearBit(LCD_START_COM+LcdCharMap[position-1][1]/32, 
                             0x1UL << (LcdCharMap[position-1][1]%32));
            }
            else if((LCD_LITTLECHAR_NOPOINT<position)&&(position<LCD_BIGCHAR_NOPOINT))  /*for big char,at com3*/
            {
                LCD_ClearBit(LCD_START_COM+LcdCharMap[position-1][1]/32+6, 
                             0x1UL << (LcdCharMap[position-1][1]%32));
            }
        }

        /*write single char,total 7 pixels*/
        BSP_LCD_GLASS_WriteChar(ptr,position,SET_MARK);

        position++; /*next char on LCD*/
        ptr += ptrPlus; /*next char to be display*/
    }

    LCD_UpdateDisplayRequest();   /*update display*/
}

/**
  * @brief  This function Clear the whole LCD RAM.
  * @retval None
  */
void BSP_LCD_GLASS_Clear(void)
{
    LCD_RamClear();
    LCD_UpdateDisplayRequest();
}

/**
  * @}
  */

/** @addtogroup BSP_EVAL_LCD_Private_Functions
  * @{
  */

/**
  * @brief  LCD MSP Init.
  * @param  hlcd: LCD handle
  * @retval None
  */
static void LCD_MspInit(void)
{
    LCD_ClockConfig(LCD_CLK_SRC_LSI);
    
    LCD_GPIO_Init();
}

/**
  * @brief  Converts an ascii char to LCD Digit (previous coding).
  * @param  c: a char to display.
  * @retval None
  */
static void BigDigitConvert(uint8_t* c)
{
    uint32_t ch = 0 , tmp = 0;
    uint32_t i, j;

    /* The character c is a letter in upper case*/
    if ((*c >= (uint8_t)ASCII_CHAR_A)&(*c <= (uint8_t)ASCII_CHAR_Z))
    {
        ch = BigLetterMap[*c-(uint8_t)ASCII_CHAR_A];
    }
    else if ((*c >= (uint8_t)ASCII_CHAR_a)&(*c <= (uint8_t)ASCII_CHAR_z))
    {
        ch = BigLetterMap[*c-(uint8_t)ASCII_CHAR_a];
    }
    /* The character c is a number*/
    else if ((*c >= (uint8_t)ASCII_CHAR_0)&(*c <= (uint8_t)ASCII_CHAR_9))
    {
        ch = BigNumberMap[*c-(uint8_t)ASCII_CHAR_0];
    }
    /* The character c is a space character */
    else if (*c == (uint8_t)ASCII_CHAR_SPACE)
    {
        ch = (uint32_t)0x00;
    }

    for (i = 0;i < COM_NUM; i++)
    {
        tmp = (ch >>BigDigitShift[i])& BIG_DIGIT_MASK;
        for(j=0;j<SEG_NUM;j++)
        {
            if(tmp & 0x01u)
                BigDigit[i][j] = 0x01;
            else
                BigDigit[i][j] = 0x00;

            tmp >>= 1;
        }
    }
}


/**
  * @brief  Clear LCD Digit buffer.
  * @param  : none
    * @retval : None
  */
static void BigDigitClear(void)
{
    uint32_t i, j;

    for (i = 0;i < COM_NUM; i++)
    {
        for(j=0;j<SEG_NUM;j++)
        {
            BigDigit[i][j] = 0x00;
        }
    }
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Nations Technologies Inc *****END OF FILE****/
