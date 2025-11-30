#pragma once


/* PMW3360 */
#define POINTING_DEVICE_INVERT_Y
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP2
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN GP0
#define POINTING_DEVICE_CS_PIN GP1

#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS

//#define SMTD_DEBUG_ENABLED
#define MAX_DEFERRED_EXECUTORS 10 // sm_td
#define TAPPING_TERM 220

// This is the time in ms to consider two keys released within that period as a hold action for the first key and a tap action for second.
// If two keys has bigger time between their releases, they will be considered as a tap action for both keys.
// NOTE: there can be  OVERRIDDES in keymap.c get_smtd_timeout
#define SMTD_GLOBAL_RELEASE_TERM 30 // avoid E>N to become command N
