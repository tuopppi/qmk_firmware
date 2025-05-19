#ifndef mx8650
#define mx8650

#include <stdint.h> // Include for uint8_t and uint16_t
#include <stdbool.h> // Include for bool

#include "mx8650_constants.h"

/**
 * @author Saurav Sajeev
 * @brief This library makes the task of communicating with the mouse controller MX8650, and reading/writing datas to its internal registers.
 * @note Refer the MX8650 datasheet before transferring data to the sensor registries.
 */

// Function prototypes for the C functions
void mx8650_init(void);

/**
 * @brief Prints the log output from the controller on the Serial monitor.
 */
void mx8650_Log(void);

/**
 * @brief Gets the Motion status.
 * @returns The Motion status as a constant string ("IN MOTION" or "IDLE").
 */
const char* mx8650_getMotionStatus(void);

/**
 * @brief Gets the Motion data from the controller.
 * @returns The value of Motion data.
 */
uint8_t mx8650_getMotionData(void);

/**
 * @brief Gets the change in motion data on X axis.
 * @returns The value of change in motion data on X axis.
 */
int8_t mx8650_getDeltaX(void);

/**
 * @brief Gets the change in motion data on Y axis.
 * @returns The value of change in motion data on Y axis.
 */
int8_t mx8650_getDeltaY(void);

/**
 * @brief Gets the Product ID of the controller.
 * @param pid_buffer Buffer to store the Product ID as a Hexadecimal String.
 * @param buffer_size Size of the pid_buffer.
 */
void mx8650_getPID(char* pid_buffer, size_t buffer_size);

/**
 * @brief Gets the Operational mode of the controller.
 * @param opmode_buffer Buffer to store the Operational mode as a Hexadecimal String.
 * @param buffer_size Size of the opmode_buffer.
 * @returns The Operational mode of the controller.
 */
void mx8650_getOperationalMode(char* opmode_buffer, size_t buffer_size);

/**
 * @brief Gets the Image quality being used by the sensor array.
 * @returns The Image quality being used.
 */
uint8_t mx8650_getImageQuality(void);

/**
 * @brief Gets the rate of Image recogonition by the controller.
 * @returns The Image recogonition rate of the controller.
 */
uint8_t mx8650_getImageRecRate(void);

/**
 * @brief Gets the Image threshold used by the Motion Estimation Engine.
 * @returns The Image threshold being used by MEE.
 */
uint8_t mx8650_getImageThreshold(void);

/**
 * @brief Gets the Operation state being used.
 * @param opstate_buffer Buffer to store the Operation state as a Hexadecimal String.
 * @param buffer_size Size of the opstate_buffer.
 * @returns The Operation state.
 */
void mx8650_getOperationState(char* opstate_buffer, size_t buffer_size);

/**
 * @brief Gets the DPI (Sensitivity) being used by the Motion Estimation Engine.
 * @returns The DPI being used by MEE.
 */
uint16_t mx8650_getDPI(void);

/**
 * @brief Sets the Sleep mode. You may use the built-in sleep constants or refer the datasheet.
 * @param mode The Sleep mode to be changed to.
 */
void mx8650_setSleepMode(uint8_t mode);

/**
 * @brief Sets the DPI.
 * @param state The DPI to set.
 */
void mx8650_setDPI(uint16_t dpi);

/**
 * @brief Sets the Image quality. You may refer the datasheet before setting the image quality.
 * @param quality The Image quality to set.
 */
void mx8650_setImageQuality(uint8_t quality);

/**
 * @brief Sets the Operation state. You may refer the datasheet before setting the Operation state.
 * @param state The Operation state to set.
 */
void mx8650_setOperationState(uint8_t state);

/**
 * @brief Sets the frequency of Sleep mode 1. You may use the built-in Sleep frequency constants or refer the datasheet before setting.
 * @param frequency The Sleep frequency to set.
 */
void mx8650_setSleepSetting_1(uint8_t frequency);

/**
 * @brief Sets the frequency of Sleep mode 2. You may use the built-in Sleep frequency constants or refer the datasheet before setting.
 * @param freqency The Sleep frequency to set.
 */
void mx8650_setSleepSetting_2(uint8_t frequency);

/**
 * @brief Sets the time to enter both sleep modes seperately. You may  refer the datasheet before setting.
 * @param mode The time to enter sleep modes.
 */
void mx8650_setSleepEnterTime(uint8_t mode);

/**
 * @brief Sets the Image threshold value. You may refer the datasheet before setting.
 * @param threshold The threshold to be used by the Motion Estimation Engine.
 */
void mx8650_setImageThreshold(uint8_t threshold);

/**
 * @brief Sets the Image recogonition rate. You may use the built-in Image recogonition rate constants or refer the datasheet before setting.
 * @param rate The rate to be used by the Motion Estimation Engine.
 */
void mx8650_setImageRecRate(uint8_t rate);

bool mx8650_verify(void);

#endif