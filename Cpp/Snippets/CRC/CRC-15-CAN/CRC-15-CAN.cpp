#include "CRC-15-CAN.h"

uint16_t CRC15CAN::update_crc(uint16_t crc, uint8_t data) {
    crc ^= (data << 7);
    for (int i = 0; i < 8; i++) {
        if (crc & 0x4000) {
            crc = (crc << 1) ^ POLY;
        } else {
            crc <<= 1;
        }
    }
    return crc & 0x7FFF;
}

uint16_t CRC15CAN::compute(const std::vector<uint8_t>& data) {
    uint16_t crc = INIT;
    for (uint8_t byte : data) {
        crc = update_crc(crc, byte);
    }
    return crc ^ CHECK;
}

bool CRC15CAN::verify(const std::vector<uint8_t>& data, uint16_t received_crc) {
    return compute(data) == received_crc;
}

bool CRC15CAN::correct(std::vector<uint8_t>& data, uint16_t received_crc) {
    uint16_t computed_crc = compute(data);
    if (computed_crc == received_crc) {
        return true; // No errors
    }

    // Attempt to correct single-bit errors
    for (std::size_t i = 0; i < data.size(); i++) {
        for (int bit = 0; bit < 8; bit++) {
            data[i] ^= (1 << bit); // Flip the bit
            if (compute(data) == received_crc) {
                return true; // Corrected a single-bit error
            }
            data[i] ^= (1 << bit); // Restore the bit
        }
    }
    return false; // Unrecoverable error
}
