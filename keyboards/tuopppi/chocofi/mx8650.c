#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include "chibios_config.h"
#include <ch.h>
#include <hal.h>
#include "wait.h"

#include "mx8650.h"
#include "mx8650_constants.h"
#include "report.h"

uint8_t readByte(void)
{
    uint8_t data = 0x00;

    for (unsigned char bit = 0; bit < 8; bit++) {
        gpio_write_pin_low(MX8650_SCLK_PIN);
        wait_us(1);
        gpio_write_pin_high(MX8650_SCLK_PIN);
        data |= (gpio_read_pin(MX8650_SDIO_PIN) << (7 - bit));
        wait_us(3);
    }

    return data;
}

void sendByte(uint8_t byte)
{
    for (unsigned char bit = 0; bit < 8; bit++) {
        bool is_one = byte & (1 << (7 - bit));
        if (is_one) {
            gpio_write_pin_low(MX8650_SCLK_PIN);
            gpio_write_pin_high(MX8650_SDIO_PIN);
            wait_us(1);
            gpio_write_pin_high(MX8650_SCLK_PIN);
            wait_us(3);
        } else {
            gpio_write_pin_low(MX8650_SCLK_PIN);
            gpio_write_pin_low(MX8650_SDIO_PIN);
            wait_us(1);
            gpio_write_pin_high(MX8650_SCLK_PIN);
            wait_us(3);
        }
    }
}

uint8_t mx8650_read(uint8_t addr)
{
    chSysLock(); // disable interrupts
    sendByte(addr);
    gpio_set_pin_input(MX8650_SDIO_PIN);
    chSysUnlock();
    wait_us(100);
    chSysLock();
    uint8_t data = readByte();
    gpio_set_pin_output(MX8650_SDIO_PIN);
    chSysUnlock();
    return data;
}

void mx8650_write(uint8_t addr, uint8_t data)
{
    chSysLock(); // disable interrupts
    sendByte(0x80 | addr); // set write bit
    sendByte(data);
    chSysUnlock();
}

void mx8650_init(void)
{
    gpio_set_pin_output(MX8650_SCLK_PIN);
    gpio_write_pin_high(MX8650_SCLK_PIN);
    gpio_set_pin_output(MX8650_SDIO_PIN);
}

bool mx8650_verify(void)
{
    return mx8650_read(0x00) == 48;
}

/**
 * @brief Gets the Motion data from the controller.
 * @returns The value of Motion data.
 */
uint8_t mx8650_getMotionData(void)
{
    return mx8650_read(MOTION_STATUS_ADDR);
}

/**
 * @brief Gets the change in motion data on X axis.
 * @returns The value of change in motion data on X axis.
 */
int8_t mx8650_getDeltaX(void)
{
    return mx8650_read(DELTA_X_ADDR);
}

/**
 * @brief Gets the change in motion data on Y axis.
 * @returns The value of change in motion data on Y axis.
 */
int8_t mx8650_getDeltaY(void)
{
    return mx8650_read(DELTA_Y_ADDR);
}

/**
 * @brief Gets the Operational mode of the controller.
 * @returns The Operational mode of the controller.
 */
uint8_t mx8650_getOperationalMode(void)
{
    return mx8650_read(SLEEP_MODE_ADDR);
}

/**
 * @brief Gets the Image quality being used by the sensor array.
 * @returns The Image quality being used.
 */
uint8_t mx8650_getImageQuality(void)
{
    return mx8650_read(IMG_QUALITY_ADDR);
}

/**
 * @brief Gets the Operation state being used.
 * @param opstate_buffer Buffer to store the Operation state as a Hexadecimal String.
 * @param buffer_size Size of the opstate_buffer.
 * @returns The Operation state.
 */
uint8_t mx8650_getOperationState(void)
{
    return mx8650_read(OPERATION_STATE_ADDR);
}

/**
 * @brief Gets the rate of Image recogonition by the controller.
 * @returns The Image recogonition rate of the controller.
 */
uint8_t mx8650_getImageRecRate(void)
{
    return mx8650_read(IMG_RECG_ADDR);
}

/**
 * @brief Gets the Image threshold used by the Motion Estimation Engine.
 * @returns The Image threshold being used by MEE.
 */
uint8_t mx8650_getImageThreshold(void)
{
    return mx8650_read(IMG_THRES_ADDR);
}

/**
 * @brief Gets the DPI (Sensitivity) being used by the Motion Estimation Engine.
 * @returns The DPI being used by MEE.
 */
uint8_t mx8650_getDPI(void)
{
    return mx8650_read(DPI_ADDR);
}

/**
 * @brief Sets the Sleep mode. You may use the built-in sleep constants or refer the datasheet.
 * @param mode The Sleep mode to be changed to.
 */
void mx8650_setSleepMode(uint8_t mode)
{
    mx8650_write(SLEEP_MODE_ADDR, mode);
}

/**
 * @brief Sets the DPI.
 * @param state The DPI to set.
 */
void mx8650_setDPI(uint8_t dpi)
{
    mx8650_write(DPI_ADDR, dpi);
}

/**
 * @brief Sets the Image quality. You may refer the datasheet before setting the image quality.
 * @param quality The Image quality to set.
 */
void mx8650_setImageQuality(uint8_t quality)
{
    mx8650_write(IMG_QUALITY_ADDR, quality);
}

/**
 * @brief Sets the Operation state. You may refer the datasheet before setting the Operation state.
 * @param state The Operation state to set.
 */
void mx8650_setOperationState(uint8_t state)
{
    mx8650_write(OPERATION_STATE_ADDR, state);
}

/**
 * @brief Sets the frequency of Sleep mode 1. You may use the built-in Sleep frequency constants or refer the datasheet before setting.
 * @param frequency The Sleep frequency to set.
 */
void mx8650_setSleepSetting_1(uint8_t frequency)
{
    mx8650_write(SLEEP1_FREQ_ADDR, frequency);
}

/**
 * @brief Sets the frequency of Sleep mode 2. You may use the built-in Sleep frequency constants or refer the datasheet before setting.
 * @param freqency The Sleep frequency to set.
 */
void mx8650_setSleepSetting_2(uint8_t frequency)
{
    mx8650_write(SLEEP2_FREQ_ADDR, frequency);
}

/**
 * @brief Sets the time to enter both sleep modes seperately. You may  refer the datasheet before setting.
 * @param mode The time to enter sleep modes.
 */
void mx8650_setSleepEnterTime(uint8_t mode)
{
    mx8650_write(SLEEP_ENTER_TIME_ADDR, mode);
}

/**
 * @brief Sets the Image threshold value. You may refer the datasheet before setting.
 * @param threshold The threshold to be used by the Motion Estimation Engine.
 */
void mx8650_setImageThreshold(uint8_t threshold)
{
    mx8650_write(IMG_THRES_ADDR, threshold);
}

/**
 * @brief Sets the Image recogonition rate. You may use the built-in Image recogonition rate constants or refer the datasheet before setting.
 * @param rate The rate to be used by the Motion Estimation Engine.
 */
void mx8650_setImageRecRate(uint8_t rate)
{
    mx8650_write(IMG_RECG_ADDR, rate);
}

// QMK

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report)
{
  uint8_t data = mx8650_getMotionData();

  if (data >= 0x84) {
    mouse_report.x = mx8650_getDeltaX();
    mouse_report.y = mx8650_getDeltaY();
    // printf("%d %d\n", mouse_report.x, mouse_report.y);
  }

  return mouse_report;
}

void pointing_device_driver_init(void)
{
  mx8650_init();
}

uint16_t pointing_device_driver_get_cpi(void)
{
    uint8_t dpi = mx8650_getDPI();

    switch (dpi)
    {
    case DPI_800:
        return 800;
    case DPI_1000:
        return 1000;
    case DPI_1200:
        return 1200;
    case DPI_1600:
        return 1600;
    default:
        return 0;
    }
}

void pointing_device_driver_set_cpi(uint16_t cpi)
{
    switch (cpi)
    {
    case 1600:
        return mx8650_setDPI(DPI_1600);
    case 1200:
        return mx8650_setDPI(DPI_1200);
    case 1000:
        return mx8650_setDPI(DPI_1000);
    default:
    case 800:
        return mx8650_setDPI(DPI_800);
    }
}

void keyboard_post_init_kb(void) {
    wait_ms(45); // Power up time
    mx8650_write(WRITE_PROTECT_ADDR, WRITE_PROTECT_DISABLE);
    mx8650_setDPI(DPI_1200);
    mx8650_setSleepMode(DISABLE_SLEEP);
    mx8650_setImageRecRate(IMG_RATE_HIGH);
}

/**
 * @brief Prints the log output from the controller on the Serial monitor.
 */
void mx8650_Log(void)
{
    if (mx8650_verify()) {
        printf(
            "Operational mode: 0x%X\nDPI: %u\nMotion status: %s\nImage quality: %u\nOperation state: 0x%X\nImage threshold: %u\nImage recogonition rate: 0x%X\n\n",
            mx8650_getOperationalMode(),
            pointing_device_driver_get_cpi(),
            mx8650_getMotionData() >= 0x84 ? "IN MOTION" : "IDLE",
            mx8650_getImageQuality(),
            mx8650_getOperationState(),
            mx8650_getImageThreshold(),
            mx8650_getImageRecRate()
        );
    } else {
        printf("No MX8650 has been detected. Check the connections or make sure it is working.");
    }
}