/**
 * @file encoder.h
 * @brief General handle functions
 * 
 * @see BIG_IO.ino
 */

#ifndef ENCODER_H
#define ENCODER_H

/**
 * @brief To move on page.
 *
 */
void l_handleRotate(int8_t rotation);
/**
 * @brief To go up page.
 */
void l_handlePress();
/**
 * @brief Reboot.
 */
void l_handleLongPress();
/**
 * @brief To change value.
 */
void r_handleRotate(int8_t rotation);
/**
 * @brief To select. Rare use.
 */
void r_handlePress();
#endif
