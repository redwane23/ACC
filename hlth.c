#include "headers/hlth.h"
#include "headers/CRC.h"

#define ver_msk 0x5aa5U

health_challange_t health_challange = {0U, 0U, 0U};
health_reply_t health_reply = {0U, 0U, 0U};

bool hndl_chall (const uint16_t iter_acc) {
  bool msg_valid = false;
  const uint16_t health_msg_len = 8U; //8 bytes is the size of these messages

    if (crc_chk((const uint8_t*)&health_challange, health_msg_len)) {
      if (iter_acc == health_challange.iteration) {
        health_reply.iteration = iter_acc;
        health_reply.reply = (~(health_challange.seed)) ^ ver_msk;
        health_reply.crc = crc_r_calc ((const uint8_t*)&health_reply, 4U); //size of the msg without crc
        msg_valid = true;
       }
    }
  return msg_valid;
}
