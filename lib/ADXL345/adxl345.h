#ifndef ADXL345_H
#define ADXL345_H

#include <Wire.h>
#include <Arduino.h>

#ifndef SENSORS_GRAVITY_STANDARD
#define SENSORS_GRAVITY_STANDARD 9.80665F
#endif

// I2C address for the ADXL345
#define ADXL345_ADDRESS        0x53

// ADXL345 register definitions
#define REG_DEVID              0x00
#define REG_DATA_FORMAT        0x31
#define REG_BW_RATE            0x2C
#define REG_POWER_CTL          0x2D
#define REG_DATAX0             0x32
#define REG_DATAY0             0x34
#define REG_DATAZ0             0x36

// Multiplier for converting raw values to g (4 mg/LSB in full-resolution mode)
#define MG2G_MULTIPLIER        0.004

class ADXL345 {
public:
    ADXL345();
    bool begin();
    void setRange(uint8_t range);
    void setDataRate(uint8_t rate);
    int16_t readRawX();
    int16_t readRawY();
    int16_t readRawZ();
    float getAccelX();
    float getAccelY();
    float getAccelZ();
    void getAcceleration(float &x, float &y, float &z);
    float getRoll();
    float getPitch();

private:
    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
    int16_t read16(uint8_t reg);
    uint8_t _range;
};

#endif