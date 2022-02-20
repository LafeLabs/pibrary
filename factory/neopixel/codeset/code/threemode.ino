// A basic everyday NeoPixel strip test program.

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

int x = 0;


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

  //  Serial.print(gx);
 // Serial.print(",");
//  Serial.println(gz);

  

  if(!button1 && !button2){
        rainbow(10);             // Flowing rainbow cycle along the whole strip
  }
  if(button1){    
    //position a white dot on a red background
    knob = analogRead(A2);
    x = int(300.0*float(knob)/1023.0);
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
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
  if(button2){
    //color wheel, calculate R, G, B from gx and gz and make all pixels that color at mag power set by knob
    //knob sets the angle
    knob = analogRead(A2);
    float angle = 0.0;
    angle = 3.14159*float(knob - 512)/512.0;  //scale from -pi to pi
    //color wheel, take dot product of angle with three colors 120 degrees apart, red is vertical
    int red = int(255.0*(cos(angle)));
    int green = int(255.0*(0.866*sin(angle) - 0.5*cos(angle)));
    int blue = int(255.0*(-0.866*sin(angle) - 0.5*cos(angle)));
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
       strip.setPixelColor(i, red,green,blue);      
    }
    strip.show(); // Update strip with new contents
    Serial.println(angle);
  }
}




// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
 
    }
    knob = analogRead(A2);
    strip.setBrightness(knob/4); // 
 //   Serial.println(knob/4);
    strip.show(); // Update strip with new contents
    button1 = !digitalRead(button1pin);  
    button2 = !digitalRead(button2pin);  
    if(!button1&&!button2){
          delay(wait);  // Pause for a moment
    }
    else{
      break;
    }
  }  
}

