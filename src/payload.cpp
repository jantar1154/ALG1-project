#include "payload.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

Payload::Payload() {
    this->payload_bytes = 0x00;
}

Payload::Payload(const string& input_string) {
    this->payload_bytes = 0x00;
    for (int i = 0; i < 5; ++i) {
        const string byte_substr = input_string.substr(i*2, 2);
        const uint8_t byte = stoi(byte_substr, 0, 16);
        // Shift the byte by 2 bytes left i times and add it do `payload_bytes`
        this->payload_bytes |= ((uint64_t)byte << (32-i*8));
    }
}

uint16_t Payload::get_battery_voltage() const {
    uint16_t voltage = this->payload_bytes >> 32;
    voltage &= 0xFF;
    voltage *= 30;
    return voltage;
}

float Payload::get_temperature() const {
    const uint16_t temp_bytes = this->payload_bytes >> 16;
    const uint8_t temp_byte_hi = temp_bytes >> 8 & 0xFF;
    const uint8_t temp_byte_lo = temp_bytes & 0x00FF;
    float temp = (256*temp_byte_hi + temp_byte_lo) / 10.0;
    return temp;
}

float Payload::get_humidity() const {
    const uint8_t humi_hi = this->payload_bytes >> 8 & 0xFF;
    const uint8_t humi_lo = this->payload_bytes & 0xFF;
    float humidity = (256*humi_hi + humi_lo) / 10.0;
    return humidity;
}

uint64_t Payload::get_bytes() const {
    return this->payload_bytes;
}
