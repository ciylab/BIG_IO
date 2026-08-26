/**
 * @file eeprom.h
 *
 * @brief Anything to handle data with eeprom.
 */

#ifndef EEPROM_H
#define EEPROM_H

/**
 * @brief load data from slot 0
 */
void init_from_eeprom();

/**
 * @brief to save the 8 modules
 * @param slot_num rank of slot in memory
 */
void save(int slot_num);

/**
 * @brief to save only one module
 *
 * @param offset firt byte num
 * @param module_num from 0 to 7
 */
void save_module(int offset, byte module_num);

/**
 * @brief Write default values (factory preset) in the first slot.
 */
void write_factory();

/**
 * @brief Write simple the second slot.
 */
void write_simple();

/**
 * @brief Write null values (factory preset) in the other slot.
 *
 * @param slot_num slot num (> 2)
 */
void write_null(int slot_num);

/**
 * @brief load 8 modules in memory from eeprom.
 *
 * @param slot_num slot num from 0 to 7
 */
void load(int slot_num);

/**
 * @brief load a module in memory from eeprom.
 * 
 * @param offset the first byte
 * @param slot_num slot num from 0 to 7
 */
void load_module_from_eeprom(int offset, byte module_num);

/**
 * @brief Read data from memory for test.
 *
 * @param module_num in the current modules
 */
void read_memory(byte module_num);

/**
 * @brief Read data from eeprom for test
 *
 * @param begin the first byte
 * @param length number of bytes
 */
void read_eeprom(int begin, int length); 
#endif
