#include <stdint.h>
#include <stdbool.h>
#include <stdio.h> // Required for sprintf
#include <string.h> // Required for strcat, strlen
#include "gpio.h"
#include "chibios_config.h"
#include <ch.h>
#include <hal.h>

#include "mx8650_constants.h"
#include "mx8650.h"

// platforms/chibios/drivers/ws2812_bitbang.c

#define NUMBER_NOPS 6
#define CYCLES_PER_SEC (CPU_CLOCK / NUMBER_NOPS)
#define NS_PER_SEC (1000000000L) // Note that this has to be SIGNED since we want to be able to check for negative values of derivatives
#define NS_PER_CYCLE (NS_PER_SEC / CYCLES_PER_SEC)
#define NS_TO_CYCLES(n) ((n) / NS_PER_CYCLE)
#define MX8650_T 20 // Width of a bit ~1.8us

#define wait_ns(x)                                  \
    do {                                            \
        for (int i = 0; i < NS_TO_CYCLES(x); i++) { \
            __asm__ volatile("nop\n\t"              \
                             "nop\n\t"              \
                             "nop\n\t"              \
                             "nop\n\t"              \
                             "nop\n\t"              \
                             "nop\n\t");            \
        }                                           \
    } while (0)

uint8_t readByte(void) {
    uint8_t data = 0x00;

    for (unsigned char bit = 0; bit < 8; bit++) {
        gpio_write_pin_low(MX8650_SCLK_PIN);
        wait_ns(MX8650_T);
        gpio_write_pin_high(MX8650_SCLK_PIN);
        data |= (gpio_read_pin(MX8650_SDIO_PIN) << (7 - bit));
        wait_ns(MX8650_T);
    }

    return data;
}

void sendByte(uint8_t byte) {
    for (unsigned char bit = 0; bit < 8; bit++) {
        bool is_one = byte & (1 << (7 - bit));
        if (is_one) {
            // 1
            gpio_write_pin_low(MX8650_SCLK_PIN);
            gpio_write_pin_high(MX8650_SDIO_PIN);
            wait_ns(MX8650_T);
            gpio_write_pin_high(MX8650_SCLK_PIN);
            wait_ns(MX8650_T);
        } else {
            // 0
            gpio_write_pin_low(MX8650_SCLK_PIN);
            gpio_write_pin_low(MX8650_SDIO_PIN);
            wait_ns(MX8650_T);
            gpio_write_pin_high(MX8650_SCLK_PIN);
            wait_ns(MX8650_T);
        }
    }
}

static bool global_deviceFound = false;

uint8_t mx8650_read(uint8_t addr)
{
    chSysLock(); // disable interrupts
    sendByte(addr);
    gpio_set_pin_input(MX8650_SDIO_PIN);
    chSysUnlock();
    wait_ns(MX8650_T);
    wait_ns(MX8650_T);
    chSysLock();
    uint8_t data = readByte();
    gpio_set_pin_output(MX8650_SDIO_PIN);
    chSysUnlock();
    return data;
}

void mx8650_write(uint8_t addr, uint8_t data)
{
    chSysLock(); // disable interrupts
    sendByte(addr);
    sendByte(data);
    chSysUnlock();
}

void mx8650_init(void)
{
    gpio_set_pin_output(MX8650_SCLK_PIN);
    gpio_write_pin_high(MX8650_SCLK_PIN);
    gpio_set_pin_output(MX8650_SDIO_PIN);

    mx8650_write(0x80 | SLEEP_MODE_ADDR, DISABLE_SLEEP);
    mx8650_write(0x80 | DPI_ADDR, DPI_1600);
    mx8650_write(0x80 | 0x09, 0x5A);
    mx8650_write(0x80 | IMG_THRES_ADDR, 0x04);
    mx8650_write(0x80 | IMG_RECG_ADDR, IMG_RATE_HIGH);
}

bool mx8650_verify(void)
{
    return mx8650_read(0x00) == 48;
}

const char* mx8650_getMotionStatus(void)
{
    if (mx8650_read(MOTION_STATUS_ADDR) >= 0x84)
        return "IN MOTION";
    else
        return "IDLE";
}

uint8_t mx8650_getMotionData(void)
{
    return mx8650_read(MOTION_STATUS_ADDR);
}

int8_t mx8650_getDeltaX(void)
{
    return mx8650_read(DELTA_X_ADDR);
}

int8_t mx8650_getDeltaY(void)
{
    return mx8650_read(DELTA_Y_ADDR);
}

// Note: C does not have a built-in String class. Using char arrays.
// The caller is responsible for providing a buffer for the result.
void mx8650_getPID(char* pid_buffer, size_t buffer_size)
{
    char temp[4];
    uint8_t part1 = mx8650_read(0x00);
    uint8_t part2 = mx8650_read(0x01);

    snprintf(temp, sizeof(temp), "%X", part1);
    strncpy(pid_buffer, temp, buffer_size - 1);
    pid_buffer[buffer_size - 1] = '\0'; // Ensure null termination

    snprintf(temp, sizeof(temp), "%X", part2);
    strncat(pid_buffer, temp, buffer_size - strlen(pid_buffer) - 1);

    // Convert to uppercase (basic implementation)
    for (int i = 0; pid_buffer[i]; i++) {
        if (pid_buffer[i] >= 'a' && pid_buffer[i] <= 'z') {
            pid_buffer[i] = pid_buffer[i] - 32;
        }
    }
}

// Note: C does not have a built-in String class. Using char arrays.
// The caller is responsible for providing a buffer for the result.
void mx8650_getOperationalMode(char* opmode_buffer, size_t buffer_size)
{
    char temp[4];
    uint8_t mode = mx8650_read(SLEEP_MODE_ADDR);
    snprintf(temp, sizeof(temp), "%X", mode);
    strncpy(opmode_buffer, temp, buffer_size - 1);
    opmode_buffer[buffer_size - 1] = '\0'; // Ensure null termination

    // Convert to uppercase (basic implementation)
    for (int i = 0; opmode_buffer[i]; i++) {
        if (opmode_buffer[i] >= 'a' && opmode_buffer[i] <= 'z') {
            opmode_buffer[i] = opmode_buffer[i] - 32;
        }
    }
}


uint8_t mx8650_getImageQuality(void)
{
    return mx8650_read(IMG_QUALITY_ADDR);
}

// Note: C does not have a built-in String class. Using char arrays.
// The caller is responsible for providing a buffer for the result.
void mx8650_getOperationState(char* opstate_buffer, size_t buffer_size)
{
    char temp[4];
    uint8_t state = mx8650_read(OPERATION_STATE_ADDR);
    snprintf(temp, sizeof(temp), "%X", state);
    strncpy(opstate_buffer, temp, buffer_size - 1);
    opstate_buffer[buffer_size - 1] = '\0'; // Ensure null termination

    // Convert to uppercase (basic implementation)
    for (int i = 0; opstate_buffer[i]; i++) {
        if (opstate_buffer[i] >= 'a' && opstate_buffer[i] <= 'z') {
            opstate_buffer[i] = opstate_buffer[i] - 32;
        }
    }
}

uint8_t mx8650_getImageRecRate(void)
{
    return mx8650_read(IMG_RECG_ADDR);
}

uint8_t mx8650_getImageThreshold(void)
{
    return mx8650_read(IMG_THRES_ADDR);
}

uint16_t mx8650_getDPI(void)
{
    uint8_t dpi = mx8650_read(DPI_ADDR);

    switch (dpi)
    {
    case DPI_100:
        return 100;
    case DPI_800:
        return 800;
    case DPI_1200:
        return 1200;
    case DPI_1600:
        return 1600;
    default:
        return 0;
    }
}

// Note: C does not have a built-in String class. Using char arrays.
// The caller is responsible for providing a buffer for the result.
void mx8650_getLog(char* log_buffer, size_t buffer_size)
{
    global_deviceFound = mx8650_verify();

    if (global_deviceFound == true) {
        char pid_str[10]; // Adjust size as needed
        char opmode_str[10]; // Adjust size as needed
        char opstate_str[10]; // Adjust size as needed

        mx8650_getPID(pid_str, sizeof(pid_str));
        mx8650_getOperationalMode(opmode_str, sizeof(opmode_str));
        mx8650_getOperationState(opstate_str, sizeof(opstate_str));

        snprintf(log_buffer, buffer_size,
                 "Product ID: 0x%s\nOperational mode: 0x%s\nDPI: %u\nMotion status: %s\nMotion data: %u\nDelta X: %u\tDelta Y: %u\nImage quality: %u\nOperation state: %s\nImage threshold: %u\nImage recogonition rate: %u",
                 pid_str, opmode_str, mx8650_getDPI(), mx8650_getMotionStatus(),
                 mx8650_getMotionData(), mx8650_getDeltaX(), mx8650_getDeltaY(),
                 mx8650_getImageQuality(), opstate_str, mx8650_getImageThreshold(),
                 mx8650_getImageRecRate());
    } else {
        strncpy(log_buffer, "No MX8650 has been detected. Check the connections or make sure it is working.", buffer_size - 1);
        log_buffer[buffer_size - 1] = '\0'; // Ensure null termination
    }
}

void mx8650_Log(void)
{
    char log_buffer[256]; // Adjust buffer size as needed
    mx8650_getLog(log_buffer, sizeof(log_buffer));
    printf("%s\n", log_buffer);
}

void mx8650_setSleepMode(uint8_t mode)
{
    mx8650_write(SLEEP_MODE_ADDR, mode);
}

void mx8650_setDPI(uint16_t dpi)
{
    switch (dpi)
    {
    case 100:
        return mx8650_write(DPI_ADDR, DPI_100);
    case 800:
        return mx8650_setDPI(DPI_800);
    case 1200:
        return mx8650_setDPI(DPI_1200);
    case 1600:
    default:
        return mx8650_setDPI(DPI_1600);
    }
    
}

void mx8650_setImageQuality(uint8_t quality)
{
    mx8650_write(IMG_QUALITY_ADDR, quality);
}

void mx8650_setOperationState(uint8_t state)
{
    mx8650_write(OPERATION_STATE_ADDR, state);
}

void mx8650_setSleepSetting_1(uint8_t frequency)
{
    mx8650_write(SLEEP1_FREQ_ADDR, frequency);
}

void mx8650_setSleepSetting_2(uint8_t frequency)
{
    mx8650_write(SLEEP2_FREQ_ADDR, frequency);
}

void mx8650_setSleepEnterTime(uint8_t mode)
{
    mx8650_write(SLEEP_ENTER_TIME_ADDR, mode);
}

void mx8650_setImageThreshold(uint8_t threshold)
{
    mx8650_write(IMG_THRES_ADDR, threshold);
}

void mx8650_setImageRecRate(uint8_t rate)
{
    mx8650_write(IMG_RECG_ADDR, rate);
}
