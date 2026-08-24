/**
 * @file eeprom.h
 */

#ifndef EEPROM_H
#define EEPROM_H

void init_from_eeprom();
void save(int slot_num);
void save_module(int offset, byte module_num);
void write_factory();
void write_simple();
void write_null(int i);
void load(int slot_num);
void load_module(int offset, byte module_num);
void serial_data(byte module_num);
#endif
