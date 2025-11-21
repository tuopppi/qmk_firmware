#pragma once

#define POINTING_DEVICE_DEBUG
#define POINTING_DEVICE_INVERT_Y

/* SPI & PMW3360 settings. */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP2
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN GP0
#define POINTING_DEVICE_CS_PIN GP1

// VDD 3.3V
// VDD not connected