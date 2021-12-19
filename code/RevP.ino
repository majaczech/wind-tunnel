/* This is improved demo sketch for the Modern Device Rev P Wind Sensor
* Requires a Wind Sensor Rev P from Modern Device
* http://moderndevice.com/product/wind-sensor-rev-p/
* 
* The Rev P requires at least at least an 8 volt supply. The easiest way to power it 
* if you are using an Arduino is to use a 9 volt or higher supply on the external power jack
* and power the sensor from Vin.
* 
* Hardware hookup 
* Sensor     Arduino Pin
* Ground     Ground
* +10-12V      Vin
* Out          A0
* TMP          A2
*
* Paul Badger 2014
* code in the public domain
*/

#include <SPI.h> //for the SD card module
#include <SD.h> // for the SD card
#include <RTClib.h> // for the RTC
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // LiquidCrystal_I2C library
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 is the i2c address of the LCM1602 IIC v1 module (might differ)

const int OutPin  = A0;   // wind sensor analog pin  hooked up to Wind P sensor "OUT" pin
const int TempPin = A2;   // temp sesnsor analog pin hooked up to Wind P sensor "TMP" pin




void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.setBacklight(255);
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
}

void loop() {

    // read wind
    int windADunits = analogRead(OutPin);
    // Serial.print("RW ");   // print raw A/D for debug
    // Serial.print(windADunits);
    // Serial.print("\t");
    
    
    // wind formula derived from a wind tunnel data, annemometer and some fancy Excel regressions
    // this scalin doesn't have any temperature correction in it yet
    float windMPH =  pow((((float)windADunits - 264.0) / 85.6814), 3.36814);
//    Serial.print(windMPH);
 //   Serial.print(" MPH\t");   
    Serial.print(windMPH*0.44704,2);
    Serial.print(" M/s\t");
  //  Serial.print(windMPH*1.609,2);
 //   Serial.print(" KmPH\t");
    lcd.setCursor(0,0);  
    lcd.print("v =");
    lcd.print(windMPH*0.44704,2);
    lcd.print(" m/s");
    
    // temp routine and print raw and temp C
    int tempRawAD = analogRead(TempPin);  
    // Serial.print("RT ");    // print raw A/D for debug
    // Serial.print(tempRawAD);
    // Serial.print("\t");
    
    // convert to volts then use formula from datatsheet 
    // Vout = ( TempC * .0195 ) + .400
    // tempC = (Vout - V0c) / TC   see the MCP9701 datasheet for V0c and TC
    
    float tempC = ((((float)tempRawAD * 5.0) / 1024.0) - 0.400) / .0195; 
    Serial.print(tempC,1);
    Serial.println(" C");
    lcd.setCursor(0,1);  
    lcd.print("Temp =");
    lcd.print(tempC,1);
    lcd.print("Deg C");
    delay(1000);
}
