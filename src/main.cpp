#include <Arduino.h>
#include <Wire.h>
#include <adxl345.h>  

ADXL345 accel;      

void setup() {
  Serial.begin(9600);
  while (!Serial);    

  if (!accel.begin()) {
    Serial.println("ADXL345 nicht gefunden!");
    while (1);  
  }

  accel.setRange(0x01);    
  accel.setDataRate(0x0A);  
}

void loop() {
  float roll  = accel.getRoll();
  float pitch = accel.getPitch();

  Serial.print("Roll:  ");
  Serial.print(roll, 2);   
  Serial.print(" °\t");

  Serial.print("Pitch: ");
  Serial.print(pitch, 2);
  Serial.println(" °");

  delay(200);
}
