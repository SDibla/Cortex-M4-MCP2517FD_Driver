/*******************************************************************************
SPI Driver:  
	Implementation

File Name:
    	drv_spi.c

Summary:
    	Implementation of MCU specific SPI functions.

Description:
	SDK NXP ECSPI Wrapper for MCP2517FD purposes.
 *******************************************************************************/

// Include files
#include "drv_spi.h"
#include "fsl_ecspi.h"
#include "fsl_gpio.h"

ecspi_master_config_t masterConfig;

void DRV_SPI_Initialize(void)
{
    ECSPI_Deinit(ECSPI_MASTER_BASEADDR);
    ECSPI_Enable(ECSPI_MASTER_BASEADDR, false);

    CLOCK_SetRootMux(kCLOCK_RootEcspi1, kCLOCK_EcspiRootmuxSysPll1);  /* Set ECSPI1 source to SYSTEM PLL1 800MHZ */
    CLOCK_SetRootDivider(kCLOCK_RootEcspi1, 2U, 5U);                  /* Set root clock to 800MHZ / 10 = 80MHZ */

    ECSPI_MasterGetDefaultConfig(&masterConfig);
    
    /* Master config:
     * masterConfig.channel = kECSPI_Channel0;
     * masterConfig.burstLength = 8;
     * masterConfig.samplePeriodClock = kECSPI_spiClock;  //The sample period clock source is SCLK.
     * masterConfig.baudRate_Bps = 500000;
     * masterConfig.chipSelectDelay = 0;
     * masterConfig.samplePeriod = 0;
     * masterConfig.txFifoThreshold = 1;
     * masterConfig.rxFifoThreshold = 0;
     * masterConfig.enableLoopback = false;
     *
     * Channel config:
     * config->channelMode           = kECSPI_Master;                   //ECSPI peripheral operates in master mode
     * config->clockInactiveState    = kECSPI_ClockInactiveStateLow;    //Clock line (SCLK) inactive state
     * config->dataLineInactiveState = kECSPI_DataLineInactiveStateLow; //Data line (MOSI&MISO) inactive state
     * config->chipSlectActiveState  = kECSPI_ChipSelectActiveStateLow; //Chip select(SS) line active state
     * config->polarity              = kECSPI_PolarityActiveHigh;       //Clock polarity
     * config->phase                 = kECSPI_ClockPhaseFirstEdge;      //clock phase
    */
    masterConfig.baudRate_Bps = SPI_BAUDRATE;
        
    /* Define the init structure for the output CS pin*/
    gpio_pin_config_t cs_config = {kGPIO_DigitalOutput, 1, kGPIO_NoIntmode};
    /* Init output CS GPIO. */
    GPIO_PinInit(CS_GPIO, CS_PIN, &cs_config);

    /* Init ECSPI */
    ECSPI_MasterInit(ECSPI_MASTER_BASEADDR, &masterConfig, ECSPI_MASTER_CLK_FREQ);

    ECSPI_Enable(ECSPI_MASTER_BASEADDR, true);
}


int8_t DRV_SPI_TransferData(uint32_t *SpiTxData, uint32_t *SpiRxData, size_t spiTransferSize)
{
    ecspi_transfer_t masterXfer;

    masterXfer.txData   = SpiTxData;
    masterXfer.rxData   = SpiRxData;
    masterXfer.dataSize = spiTransferSize;
    masterXfer.channel  = CHANNEL;

    GPIO_PinWrite(CS_GPIO, CS_PIN, 0U);

    status_t status = ECSPI_MasterTransferBlocking(ECSPI_MASTER_BASEADDR, &masterXfer);

    GPIO_PinWrite(CS_GPIO, CS_PIN, 1U);

    return (int8_t) status;
}
