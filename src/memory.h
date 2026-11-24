/**
 * @file memory.h
 *
 * @brief Anything to handle data with eeprom.
 *
 * The size of one module is at least 13 bytes :
 * - first byte : module id (TIME = 0...)
 * - 4 bytes for io values
 * - 8 bytes max for parameters value
 * We can use 8 modules together = one slot = 104 bytes and
 * for 8 slots : 832 bytes.
 * 
 * Eeprom size of 24LC256 is 32768 bytes (32Ko) : 
 * The number of notes for the looper is :
 * 16 (one bar of sixteenth notes) * 4 (bars) * 6 (PPQN) = 384
 * For note on (pitch and velocity), note off (pitch), we need :
 * 384 * 3 = 1152 bytes. Hence we can save :
 * (32768 - 832) / 1152 = 27 sequences.
 *
 * Eeprom size of Nano R4 is 8192 bytes (8Ko) : we use only one bar
 * We can save : (8192 - 832) / (96 * 3) = 25 sequences.
 * 
 * The size of the sequence in the looper memory is one (number of
 * the sequence) plus pitch on, velocities, pitch off array values. 
 * For convenience we read/write values in this order : the first 
 * value of each array, then the second value... and so on untill
 * 96 or 384 for any of the 25 sequences.
 */

#ifndef MEMORY_H
#define MEMORY_H
#include "Modules.h"

/** 
 * @brief byte size for one module 
 *
 * - module type
 * - 4 parameters IN/OUT
 * - 8 parameters (max used on a page)
 */
#define NUM_SLOT 8
#define CONFIG_SIZE 13

/**
 * @brief number of PPQN = 6 * 16 * N_BARS
 */
#ifdef nanor4
#define N_BARS 1
#elif bluepill
#define N_BARS 4
#endif

/**
 * @brief Read the byte in eeprom
 */
byte readEEPROM(unsigned int address);

/**
 * @brief Write the byte in eeprom
 */
void updateEEPROM(unsigned int address, byte data);

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
void load(byte slot_num);

/**
 * @brief Read data from memory for debug.
 *
 * @param mem_num num of memory in looper
 */
void print_sequence(byte mem_num);

#endif
