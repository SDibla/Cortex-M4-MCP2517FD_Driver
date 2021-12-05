# Cortex-M4-MCP2517FD_Driver
CAN FD Driver for MCP2517FD with SPI interface.

The files:
- drv_canfdspi_api.c
- drv_canfdspi_api.h
- drv_canfdspi_defines.h
- drv_canfdspi_register.h
They are independent of the architecture of the used microcontroller and can be used only by modifying the following two files:
- drv_spi.c
- drv_spi.h
Where the INIT function and the SPI data transfer operation must be implemented.

In this case, these two files use functions coming from the SDK released by NXP referring to the Cortex M4 core of the i.MXM8mini microprocessor.
