/**
 * @file eeprom.h
 *
 * @brief Anything to handle data with eeprom.
 *
 * Eeprom size of 24LC256 is 32768 bytes. 
 *
 * The size of one module is at least 13 bytes :
 * - first byte : module id (TIME = 0...)
 * - 4 bytes for io values
 * - 8 bytes max for parameters value
 * We can use 8 modules simultaneously = one slot. 
 * The maximum number of note is for the looper module:
 * - 16 (one bar of sixteenth notes) * 4 (bars) * 6 (PPQN) = 384
 * For note on (pitch and velocity), note off (pitch), we need by slot :
 * -24LC256 is 32768 bytes. 
 *
 * The size of one module is at least 13 bytes :
 * - first byte : module id (TIME = 0...)
 * - 4 bytes for io values
 * - 8 bytes max for parameters value
 * We can use 8 modules simultaneously = one slot. 
 * The maximum number of note is for the looper module:
 * - 16 (one bar of sixteenth notes) * 4 (bars) * 6 (PPQN) = 384
 * For note on (pitch and velocity), note off (pitch), we need by slot :
 * - (13 + 384 * 3) * 8 = (13 + 384 * 3) * 8 = 9320 bytes
 * and we are limited to 3 slots !!!!!
 * To use 8 slots, we decided to limit the number of
 * notes in looper and we have 32768 / 8 / 8 = 512 bytes by module 
 * hence 512 - 13 = 499 bytes for one sequence. For each note we
 * need 6 bytes : 
 * - the pitch
 * - the velocity
 * - the rank from 0 to 383 for note on (2 bytes)
 * - the rank from 0 to 383 for note off (2 bytes)
 * With a chunck size of 32 bytes, we can write 5 notes by chunk
 * We can use sequence of 5 * (499 / 32) = 75 notes.
 */

#ifndef EEPROM_H
#define EEPROM_H

/**
 * @brief The maximum number of notes in looper
 */
#define NUM_NOTES 75 

/** 
 * @brief byte size for one module 
 *
 * - module type
 * - 4 parameters IN/OUT
 * - 8 parameters (max used on a page)
 */
#define CONFIG_SIZE 13

/**
 * @brief load data from slot 0
 */
void init_from_eeprom();

/**
 * @brief to save the 8 modules
 * @param slot_num rank of slot in memory
 */
void save(byte slot_num);

/**
 * @brief load 8 modules in memory from eeprom.
 *
 * @param slot_num slot num from 0 to 7
 */
void load(int slot_num);

/**
 * @brief Read data from memory for test.
 *
 * @param module_num in the current modules
 * @see Play.h
 * @see Conf.h
 */
void read_memory(byte module_num);

#endif
