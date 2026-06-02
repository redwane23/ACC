#ifndef CRC_H
#define CRC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

uint32_t crc_r_calc (const uint8_t*, const uint16_t);
bool crc_chk (const uint8_t*, const uint16_t);

#endif
