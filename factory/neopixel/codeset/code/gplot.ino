


// The pyramids combined code with a switch 
// which selects between xy gyrator, z gyrator and simple speed control

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();



int button1pin = 3;
int button2pin = 2;

boolean button1 = false;
boolean button2 = false;

float gx = 0.0;
float gz = 0.0;


void setup(void) {


  Serial.begin(9600);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");
  pinMode(button1pin,INPUT_PULLUP); 
  pinMode(button2pin,INPUT_PULLUP); 

}

void loop() {
  
  button1 = !digitalRead(button1pin);  
  button2 = !digitalRead(button2pin);  

  lis.read();      // get X Y and Z data at once

  /* Or....get a new sensor event, normalized */ 
  sensors_event_t event; 
  lis.getEvent(&event);
  
  /* Display the results (acceleration is measured in m/s^2) */

  gx= event.acceleration.x;
  gz= -event.acceleration.z;

  
  
  Serial.print(gx);
  Serial.print(",");
  Serial.println(gz);

  if(!button1 && !button2){
  }
  if(button1){    
  }
  if(button2){
  }

 
}