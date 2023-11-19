#ifndef BUS_H
#define BUS_H

#include "common.h"

u8_t bus_read(u16_t address);
void bus_write(u16_t address, u8_t value);

#endif // BUS_H
