//tilt the acceleromter to drive, turn knob to control damping


// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 300

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

int knob = 0;


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
float gy = 0.0;

int x = 0;

int x0 = 81;
int x1 = 241;
float pi = 3.14159;

float theta = 0.0;
float t = 0.0;
int period = 15;
float y[] = {0.0,0.0};
float E;
float f0 = 0.0;  //velocity
float f1 = 0.0;  //accelleration
float f[] = {0.0,0.0};
float k1[] = {0.0,0.0};
float k2[] = {0.0,0.0};
float k3[] = {0.0,0.0};
float k4[] = {0.0,0.0};
  
float thetadot = 0.0;
float force;
      
float yindex = 0.1;
float ynext[] = {0.0,0.0};
 
float gamma = 0.1; 
float omega0 = 0.9;
float h = 0.02; //time step in fractions of natural period 
float A = 0.8;  

float knob2force = 1.0;

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

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)


   for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      if(i > x0 && i < x1){
        strip.setPixelColor(i,30,0,0);                     
      }
      else{
        strip.setPixelColor(i,0,0,0);            
      }
   }
   A = 0.0;
   
}

void loop() {

  
  button1 = !digitalRead(button1pin);  
  button2 = !digitalRead(button2pin);  
  

  //position a white dot on a red background
    
  knob = analogRead(A2);

  //theta = -(-pi + float(knob)*2*pi/1023.0);
   

    lis.read();      // get X Y and Z data at once

    /* Or....get a new sensor event, normalized */ 
    sensors_event_t event; 
    lis.getEvent(&event);
    
    /* Display the results (acceleration is measured in m/s^2) */
  
    gx= event.acceleration.x;
    gy= event.acceleration.y; 
    gz= event.acceleration.z;

//  Serial.println(gx);
  //force = -float(knob)/500.0; 
  force = gx/5;
  gamma = float(knob)/100.0;
  
  k1[0] = getf0(t,y,gamma,omega0,A,force);
  k1[1] = getf1(t,y,gamma,omega0,A,force);

  ynext[0] = y[0] + 0.5*h*k1[0];
  ynext[1] = y[1] + 0.5*h*k1[1];
  
  k2[0] = getf0(t+0.5*h,ynext,gamma,omega0,A,force);
  k2[1] = getf1(t+0.5*h,ynext,gamma,omega0,A,force);

  ynext[0] = y[0] + 0.5*h*k2[0];
  ynext[1] = y[1] + 0.5*h*k2[1];
  
  k3[0] = getf0(t+0.5*h,ynext,gamma,omega0,A,force);
  k3[1] = getf1(t+0.5*h,ynext,gamma,omega0,A,force);

  ynext[0] = y[0] + h*k3[0];
  ynext[1] = y[1] + h*k3[1];

  k4[0] = getf0(t+h,ynext,gamma,omega0,A,force);
  k4[1] = getf1(t+h,ynext,gamma,omega0,A,force);
  
  
  ynext[0] = y[0] + 0.1667*h*(k1[0] + 2*k2[0] + 2*k3[0] + k4[0]);
  ynext[1] = y[1] + 0.1667*h*(k1[1] + 2*k2[1] + 2*k3[1] + k4[1]);  

  if(ynext[0] >= pi){
     ynext[0] = ynext[0] - 2*pi;
  }
  if(ynext[0] <= -pi){
     ynext[0] = ynext[0] + 2*pi;
  }

  theta = y[0];
  thetadot = y[1];

  y[0] = ynext[0];
  y[1] = ynext[1];

  t = t + h;
         
  
  x = int(theta*(float(x1) - float(x0))/(2*pi) + 0.5*(float(x1) + float(x0)));
       
      
  for(int i = x0; i < x1; i++) { // For each pixel in strip...
     if(i == x){
        strip.setPixelColor(i, 200,200,200);
     }
     else{
       strip.setPixelColor(i, 10,0,0);      
     }  
  }
  Serial.println(x);
  strip.show(); // Update strip with new contents
}


float getf0(float t,float y[],float gamma, float omega0, float A,float force){
  float result;
  result = y[1];
  return result;
}

float getf1(float t,float y[],float gamma, float omega0,float A, float force){
  float result;
  result = -sin(y[0]) - gamma*y[1] + A*cos(omega0*t) + force;
  return result;
}