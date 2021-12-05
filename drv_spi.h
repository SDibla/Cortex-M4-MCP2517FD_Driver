/*******************************************************************************
SPI Driver:  
	Header File

File Name:
    	drv_spi.h

Summary:
    	This header file contains the MCU specific SPI 	definitions and declarations.

Description:
	SDK NXP ECSPI Wrapper for MCP2517FD purposes.
 *******************************************************************************/

#ifndef _DRV_SPI_H
#define _DRV_SPI_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fsl_debug_console.h"


#define SPI_DEFAULT_BUFFER_LENGTH       96
#define SPI_MAX_BUFFER_LENGTH           30000

#define CHANNEL     kECSPI_Channel0
#define CS_GPIO         GPIO1
#define CS_PIN          0U
//#define INT_GPIO        GPIO1
//#define INT_PIN         5U
#define ECSPI_MASTER_BASEADDR ECSPI1
#define ECSPI_MASTER_CLK_FREQ (CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / (CLOCK_GetRootPreDivider(kCLOCK_RootEcspi1)) / (CLOCK_GetRootPostDivider(kCLOCK_RootEcspi1)))
#define SPI_BAUDRATE 10000000 //10MHz that is the maximum


//! SPI Initialization

void DRV_SPI_Initialize(void);

//! SPI Read/Write Transfer

int8_t DRV_SPI_TransferData(uint32_t *SpiTxData, uint32_t *SpiRxData, size_t spiTransferSize);

#endif	// _DRV_SPI_H
