# Based on https://github.com/IOsetting/hk32f030m-template/blob/master/Makefile
##### Project #####

PROJECT 		?= app
# The path for generated files
BUILD_DIR 		= Build


##### Options #####

# Enable printf float %f support, y:yes, n:no
ENABLE_PRINTF_FLOAT	?= n
# Build with FreeRTOS, y:yes, n:no
USE_FREERTOS	?= n
# Programmer, jlink or pyocd
FLASH_PROGRM	?= jlink


##### Toolchains #######

# path to gcc arm
ARM_TOOCHAIN 	?= /opt/gcc-arm/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi/bin
# path to JLinkExe
JLINKEXE		?= /opt/SEGGER/JLink/JLinkExe
# JLink device type: HK32F030MD4P6, HK32F030MF4U6, HK32F030MF4P6 or HK32F030MJ4M6
JLINK_DEVICE	?= HK32F030MF4P6
# path to PyOCD
PYOCD_EXE		?= pyocd
# PyOCD device type: hk32f030md4p6, hk32f030mf4p6, hk32f030mf4u6, hk32f030mj4m6
PYOCD_DEVICE	?= hk32f030mf4p6


##### Paths ############

# Link descript file
LDSCRIPT		= Library/LDScripts/hk32f030mf4p6.ld
# Library build flags
LIB_FLAGS       = HK32F030MF4P6

# C source folders
CDIRS	:= Code/App \
		Code/Drive \
		Code/User \
		Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/CMSIS/HK32F030M/Source/GCC \
		Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/CMSIS/HK32F030M/Source \
		Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/HK32F030M_Lib/src/ \
		Library/Debug

# C source files (if there are any single ones)
CFILES :=   
# Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/HK32F030M_Lib/src/hk32f030m_rcc.c \
# Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/HK32F030M_Lib/src/hk32f030m_exti.c \
# Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/HK32F030M_Lib/src/hk32f030m_gpio.c \
# Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/HK32F030M_Lib/src/hk32f030m_misc.c \
# Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/HK32F030M_Lib/src/hk32f030m_adc.c \
# Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/HK32F030M_Lib/src/hk32f030m_tim.c \
# Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/HK32F030M_Lib/src/hk32f030m_usart.c

# ASM source folders
ADIRS	:= Code/User
# ASM single files
AFILES	:= Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/CMSIS/HK32F030M/Source/GCC/startup_hk32f030mf4p6.s

# Include paths
INCLUDES	:= Code/App \
			Code/Drive \
			Code/User \
			Libraries/CMSIS/HK32F030M/Source/ \
			Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/CMSIS/HK32F030M/Include \
			Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/CMSIS/CM0/Core/ \
			Library/HK32F030Mxx_Library_V1.1.6/HK32F030M/HK32F030M_Lib/inc \
			Library/Debug

ifeq ($(USE_FREERTOS),y)
CDIRS		+= Libraries/FreeRTOS \
			Libraries/FreeRTOS/portable/GCC/ARM_CM0

CFILES		+= Libraries/FreeRTOS/portable/MemMang/heap_4.c

INCLUDES	+= Libraries/FreeRTOS/include \
			Libraries/FreeRTOS/portable/GCC/ARM_CM0
endif

include ./rules.mk
