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
 * @file main.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32l40x.h"
#include "n32l40x_rcc.h"

#include "n32l40x_rng.h"
#include "n32l40x_hash.h"
#include "n32l40x_des.h"
#include "n32l40x_aes.h"

#include "log.h"

#include <string.h>
#ifdef __IAR_ARM
#pragma pack(4)
#endif
void DumpWords(const uint32_t* words, uint32_t len)
{
    for (uint32_t i = 0; i < len; ++i)
    {
        log_info("0x%08x, ", (unsigned int)words[i]);
    }
}

void DumpBytes(const uint8_t* bytes, uint32_t len)
{
    for (uint32_t i = 0; i < len; ++i)
    {
        log_info("%02x", (unsigned int)bytes[i]);
    }
}

void TestRand(void)
{
    uint32_t buf[8];
    uint32_t seed[2] = {1, 2};
    if (RNG_OK != GetPseudoRand_U32(buf, 8, seed))
    {
        log_error("GetPseudoRand_U32 failed.\n");
    }
    else
    {
        log_info("Pseudo random with seed 1,2: ");
        DumpWords(buf, 8);
        log_info("\n");
    }
    seed[0] = 3;
    seed[1] = 4;
    if (RNG_OK != GetPseudoRand_U32(buf, 8, seed))
    {
        log_error("GetPseudoRand_U32 failed.\n");
    }
    else
    {
        log_info("Pseudo random with seed 3,4: ");
        DumpWords(buf, 8);
        log_info("\n");
    }

    if (RNG_OK != GetTrueRand_U32(buf, 8))
    {
        log_error("GetTrueRand_U32 failed.\n");
    }
    else
    {
        log_info("True random: ");
        DumpWords(buf, 8);
        log_info("\n");
    }
}

#define HASH_TEST_MSG "Hello!"

void CalcHASH(const HASH_ALG* hashAlg, char* msg, uint8_t* result)
{
    HASH_CTX ctx;
    ctx.hashAlg  = hashAlg;
    ctx.sequence = HASH_SEQUENCE_FALSE;
    if (HASH_Init_OK != HASH_Init(&ctx))
    {
        log_error("HASH_Init failed.\n");
        return;
    }
    if (HASH_Start_OK != HASH_Start(&ctx))
    {
        log_error("HASH_Start failed.\n");
        return;
    }
    if (HASH_Update_OK != HASH_Update(&ctx, (uint8_t*)msg, strlen(msg)))
    {
        log_error("HASH_Update failed.\n");
        return;
    }
    if (HASH_Complete_OK != HASH_Complete(&ctx, result))
    {
        log_error("HASH_Complete failed.\n");
        return;
    }
}

void TestSHA1()
{
    uint8_t result[20];
    CalcHASH(HASH_ALG_SHA1, HASH_TEST_MSG, result);
    log_info("SHA1 of message `%s` is: ", HASH_TEST_MSG);
    DumpBytes(result, 20);
    log_info("\n");
}


void TestSHA224()
{
    uint8_t result[28];
    CalcHASH(HASH_ALG_SHA224, HASH_TEST_MSG, result);
    log_info("SHA224 of message `%s` is: ", HASH_TEST_MSG);
    DumpBytes(result, 28);
    log_info("\n");
}

void TestSHA256()
{
    uint8_t result[32];
    CalcHASH(HASH_ALG_SHA256, HASH_TEST_MSG, result);
    log_info("SHA256 of message `%s` is: ", HASH_TEST_MSG);
    DumpBytes(result, 32);
    log_info("\n");
}

void TestDES(void)
{
  DES_PARM DES_Parm;
#if  (defined __IAR_ARM) || (defined __GCC_ARM)

    uint8_t key[8]   = {1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t plain[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    uint8_t cipher[8];
    uint8_t plainOut[8];
#else
    __align(4) uint8_t key[8]   = {1, 2, 3, 4, 5, 6, 7, 8};
    __align(4) uint8_t plain[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    __align(4) uint8_t cipher[8];
    __align(4) uint8_t plainOut[8];
#endif
    DES_Parm.in        = (uint32_t*)plain;
    DES_Parm.out       = (uint32_t*)cipher;
    DES_Parm.key       = (uint32_t*)key;
    DES_Parm.iv        = NULL; // IV is not needed in ECB mode
    DES_Parm.inWordLen = sizeof(plain) / sizeof(uint32_t);
    DES_Parm.Mode      = DES_ECB;
    DES_Parm.En_De     = DES_ENC;
    DES_Parm.keyMode   = DES_KEY;

    // encrypt data
    if (DES_Init_OK != DES_Init(&DES_Parm))
    {
        log_error("DES_Init failed.\n");
        return;
    }
    if (DES_Crypto_OK != DES_Crypto(&DES_Parm))
    {
        log_error("DES_Crypto failed\n");
        return;
    }

    log_info("DES ECB encrypt:\n");
    log_info("key = ");
    DumpBytes(key, sizeof(key));
    log_info("\n");
    log_info("plain = ");
    DumpBytes(plain, sizeof(plain));
    log_info("\n");
    log_info("cipher = ");
    DumpBytes(cipher, sizeof(cipher));
    log_info("\n");

    DES_Parm.in    = (uint32_t*)cipher;
    DES_Parm.out   = (uint32_t*)plainOut;
    DES_Parm.En_De = DES_DEC;

    // decrypt data
    if (DES_Init_OK != DES_Init(&DES_Parm))
    {
        log_error("DES_Init failed.\n");
        return;
    }
    if (DES_Crypto_OK != DES_Crypto(&DES_Parm))
    {
        log_error("DES_Crypto failed\n");
        return;
    }

    log_info("decrypt out = ");
    DumpBytes(plainOut, 8);
    log_info("\n");
    if (memcmp(plain, plainOut, sizeof(plain)) != 0)
    {
        log_error("DES decrypt result do not equal plain data.\n");
        return;
    }
}

void TestAES(void)
{
    AES_PARM AES_Parm;
   
 #ifdef __IAR_ARM

    uint8_t key[16]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    uint8_t plain[16] = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00};
    uint8_t cipher[16];
    uint8_t plainOut[16];
#else
    __align(4) uint8_t key[16]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    __align(4) uint8_t plain[16] = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00};
    __align(4) uint8_t cipher[16];
    __align(4) uint8_t plainOut[16];
#endif
    
    AES_Parm.in         = (uint32_t*)plain;
    AES_Parm.out        = (uint32_t*)cipher;
    AES_Parm.key        = (uint32_t*)key;
    AES_Parm.iv         = NULL; // IV is not needed in ECB mode
    AES_Parm.inWordLen  = sizeof(plain) / sizeof(uint32_t);
    AES_Parm.keyWordLen = sizeof(key) / sizeof(uint32_t);
    AES_Parm.Mode       = AES_ECB;
    AES_Parm.En_De      = AES_ENC;

    // encrypt data
    if (AES_Init_OK != AES_Init(&AES_Parm))
    {
        log_error("AES_Init failed.\n");
        return;
    }
    if (AES_Crypto_OK != AES_Crypto(&AES_Parm))
    {
        log_error("AES_Crypto failed\n");
        return;
    }

    log_info("AES ECB encrypt:\n");
    log_info("key = ");
    DumpBytes(key, sizeof(key));
    log_info("\n");
    log_info("plain = ");
    DumpBytes(plain, sizeof(plain));
    log_info("\n");
    log_info("cipher = ");
    DumpBytes(cipher, sizeof(cipher));
    log_info("\n");

    AES_Parm.in    = (uint32_t*)cipher;
    AES_Parm.out   = (uint32_t*)plainOut;
    AES_Parm.En_De = AES_DEC;

    // decrypt data
    if (AES_Init_OK != AES_Init(&AES_Parm))
    {
        log_error("AES_Init failed.\n");
        return;
    }
    if (AES_Crypto_OK != AES_Crypto(&AES_Parm))
    {
        log_error("AES_Crypto failed\n");
        return;
    }

    log_info("decrypt out = ");
    DumpBytes(plainOut, sizeof(plainOut));
    log_info("\n");
    if (memcmp(plain, plainOut, sizeof(plain)) != 0)
    {
        log_error("AES decrypt result do not equal plain data.\n");
        return;
    }
}


int main(void)
{
    log_init();
    log_info("-----------------------\nAlgorithm demo start.\n");

    // RNG test
    TestRand();

    // HASH test
    TestSHA1();
    TestSHA224();
    TestSHA256();

    // Cryptogram algorithm
    TestDES();
    TestAES();

    while (1)
        ;
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param file pointer to the source file name
 * @param line assert_param error line source number
 */
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}

#endif
