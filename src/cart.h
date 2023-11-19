#ifndef CART_H
#define CART_H

#include "common.h"

typedef struct rom_header
{
  u8_t entry[0x4];  // 4 [dec]
  u8_t logo[0x30];  // 48 [dec]
  char title[0x10]; // 16 [dec]
  u16_t new_lic_code;
  u8_t sgb_flag;
  u8_t type;
  u8_t rom_size;
  u8_t ram_size;
  u8_t dest_code;
  u8_t lic_code;
  u8_t version;
  u8_t checksum;
  u16_t global_checksum;
} rom_header_t;

/// @brief Load cartridge data.
/// @param cart_name Cartridge name.
/// @return Boolean value for success or failure.
bool cart_load(char* cart_name);

u8_t cart_read(u16_t address);

void cart_write(u16_t address, u8_t value);

#endif // CART_H
