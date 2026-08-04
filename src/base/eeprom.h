/**
 * @file eeprom.h
 */

#ifndef EEPROM_H
#define EEPROM_H

void init_eeprom();
void save(int slot_num);
void write_factory();
void write_null(int i);
void load(int slot_num);
void test_eeprom();
#endif
