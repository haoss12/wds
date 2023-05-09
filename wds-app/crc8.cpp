#include "crc8.h"

uint8_t crc8(const std::string &data) {
    uint8_t len = data.length();
    uint8_t *p = (uint8_t *) data.c_str();
    uint16_t i;
    uint16_t crc = 0x0;

    while (len--) {
        i = (crc ^ *p++) & 0xff;
        crc = (crc_table[i] ^ (crc << 8)) & 0xff;
    }

    return crc & 0xff;
}
