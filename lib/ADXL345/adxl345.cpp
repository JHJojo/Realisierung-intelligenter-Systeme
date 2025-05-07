#include "adxl345.h"

ADXL345::ADXL345() : _range(0x00) {}

bool ADXL345::begin() {
    Wire.begin();
    if (readRegister(REG_DEVID) != 0xE5) return false;
    writeRegister(REG_POWER_CTL, 0x08);
    setRange(0x01);
    return true;
}

void ADXL345::setRange(uint8_t range) {
    uint8_t format = readRegister(REG_DATA_FORMAT);
    format &= ~0x0F;
    format |= (range & 0x03);
    format |= 0x08; 
    writeRegister(REG_DATA_FORMAT, format);
    _range = range;
}

void ADXL345::setDataRate(uint8_t rate) {
    writeRegister(REG_BW_RATE, rate & 0x0F);
}

void ADXL345::writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

uint8_t ADXL345::readRegister(uint8_t reg) {
    Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(ADXL345_ADDRESS, (uint8_t)1);
    return Wire.read();
}

int16_t ADXL345::read16(uint8_t reg) {
    Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(ADXL345_ADDRESS, (uint8_t)2);
    uint8_t lo = Wire.read();
    uint8_t hi = Wire.read();
    return (int16_t)(hi << 8 | lo);
}

int16_t ADXL345::readRawX() { return read16(REG_DATAX0); }
int16_t ADXL345::readRawY() { return read16(REG_DATAY0); }
int16_t ADXL345::readRawZ() { return read16(REG_DATAZ0); }

float ADXL345::getAccelX() {
    return readRawX() * MG2G_MULTIPLIER;
}
float ADXL345::getAccelY() {
    return readRawY() * MG2G_MULTIPLIER;
}
float ADXL345::getAccelZ() {
    return readRawZ() * MG2G_MULTIPLIER;
}

void ADXL345::getAcceleration(float &x, float &y, float &z) {
    x = getAccelX() * SENSORS_GRAVITY_STANDARD;
    y = getAccelY() * SENSORS_GRAVITY_STANDARD;
    z = getAccelZ() * SENSORS_GRAVITY_STANDARD;
}

float ADXL345::getRoll() {
    float x = getAccelX(), y = getAccelY(), z = getAccelZ();
    return atan2(y, z) * 180.0 / PI;
}

float ADXL345::getPitch() {
    float x = getAccelX(), y = getAccelY(), z = getAccelZ();
    return atan(-x / sqrt(y*y + z*z)) * 180.0 / PI;
}