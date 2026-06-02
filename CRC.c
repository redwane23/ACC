#include "headers/CRC.h"

#define crc_r_poly 0xedb88320U //polynomial flipped to account for serial communication being LSB first
  
uint32_t crc_r_calc (const uint8_t* msg, const uint16_t byte_len) {
  uint32_t result = 0xffffffffU; //to aid in detetction of leading zeroes added erroneously

  if (msg != NULL){ //standard misra ull checking

  //treat the message byte by byte to be able to work ith flexible sizes
    for (uint16_t i = 0U; i < byte_len; i++) {
      result ^= (uint32_t)msg[i];

  //using the register shift method to calculate the crc (right shift since the polynomial is flipped)
      for (uint8_t j = 0U; j < 8U; j++) {
        if ((result & 1U) != 0U) {//if a bit with value = 1 falls from the regester we xor with polynomial
          result = (result >> 1U) ^ crc_r_poly;
        } else { //if zero drops we dont xor
          result = result >> 1U;
        }
      }
    } //undo the ffff xor
    result ^= 0xffffffffU;
  } else { //if no message we send a crc of 0
    result = 0U;
  }
  return result;
}

bool crc_chk (const uint8_t* msg, const uint16_t byte_len_w_crc) {
  bool valid = false;

  if ((msg != NULL) && (byte_len_w_crc > 4U) ){ //check if message exists and if the length is valid for a 32bit crc message
    uint16_t data_len = byte_len_w_crc - 4U;

    //calculate the crc
    uint32_t calc_crc = crc_r_calc (msg, data_len); //we declared a variable data_len to not avoid arguments with side effects

    //crc extraction from msg
    uint32_t res_crc = 0U;
    res_crc |= (uint32_t)msg[byte_len_w_crc - 4U];
    res_crc |= ((uint32_t)msg[byte_len_w_crc - 3U]) << 8U; //shifting the bit to properly be recounctrected (shift values are in bits)
    res_crc |= ((uint32_t)msg[byte_len_w_crc - 2U]) << 16U;
    res_crc |= ((uint32_t)msg[byte_len_w_crc - 1U]) << 24U;

    if (res_crc == calc_crc) {
      valid = true;
    }
  } 
  return valid;
}

