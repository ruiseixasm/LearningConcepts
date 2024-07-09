#ifndef CRC15CAN_H
#define CRC15CAN_H

#include <vector>
#include <cstdint>
#include <cinttypes>

class CRC15CAN {
public:
    static uint16_t compute(const std::vector<uint8_t>& data);
    static bool verify(const std::vector<uint8_t>& data, uint16_t received_crc);
    static bool correct(std::vector<uint8_t>& data, uint16_t received_crc);

private:
    static constexpr uint16_t POLY = 0x4599;
    static constexpr uint16_t INIT = 0x0000;
    static constexpr uint16_t CHECK = 0x0000;

    static uint16_t update_crc(uint16_t crc, uint8_t data);
};

#endif // CRC15CAN_H
