#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
  uint16_t iteration;
  uint16_t seed;
  uint32_t crc;
} health_challange_t;
typedef struct {
  uint16_t iteration;
  uint16_t reply;
  uint32_t crc;
} health_reply_t;
#pragma pack(pop)

extern health_challange_t health_challange;
extern health_reply_t health_reply;
