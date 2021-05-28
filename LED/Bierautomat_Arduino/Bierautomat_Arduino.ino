#include <Adafruit_NeoPixel.h>

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

#define LED_PIN1    4
#define LED_PIN2    5
#define LED_PIN3    6
#define LED_PIN4    7

#define LED_COUNT 148

#define strip1Length 150
#define strip2Length 149
#define strip3Length 150
#define strip4Length 150

Adafruit_NeoPixel strip1(LED_COUNT, LED_PIN1, NEO_GRB);
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN2, NEO_GRB);
Adafruit_NeoPixel strip3(LED_COUNT, LED_PIN3, NEO_GRB);
Adafruit_NeoPixel strip4(LED_COUNT, LED_PIN4, NEO_GRB);


#define DELAYVAL 0

String mode = "rainbow";

int newRed = 255;
int newGreen = 255;
int newBlue = 255;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  
  pinMode(LED_PIN1,OUTPUT);
  pinMode(LED_PIN2,OUTPUT);
  pinMode(LED_PIN3,OUTPUT);
  pinMode(LED_PIN4,OUTPUT);

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif

  strip1.begin();              // INITIALIZE NeoPixel strip object (REQUIRED)
  strip1.show();               // Turn OFF all pixels ASAP
  strip1.setBrightness(255);   // Set BRIGHTNESS to about 1/5 (max = 255)

  strip2.begin();           
  strip2.show();            
  strip2.setBrightness(255); 

  strip3.begin();           
  strip3.show();            
  strip3.setBrightness(255); 
  
  strip4.begin();           
  strip4.show();            
  strip4.setBrightness(255); 
}

void loop() {

  clearAll();
  
  readInput();

  if(mode == "default"){
    showDefault();
  }

  if(mode == "red"){
    showRed();
  }

  if(mode == "rainbow"){
    rainbow(2); 
  } 
  
  showAll();
  
}

void showDefault(){
  for(int i = 0; i <= 4*LED_COUNT; i++){
    setPixel(i, 0, 0, 0);
  }
}

void setPixel(int pos, int red, int green, int blue){
  if(pos >= 0 && pos < LED_COUNT){
    strip1.setPixelColor(pos, strip1.Color(red, green, blue));
  }
  
  if(pos >= LED_COUNT && pos < 2*LED_COUNT){
    strip2.setPixelColor(pos-LED_COUNT, strip2.Color(red, green, blue));
  }

  if(pos >= 2*LED_COUNT && pos < 3*LED_COUNT){
    strip3.setPixelColor(pos-2*LED_COUNT, strip3.Color(red, green, blue));
  }

  if(pos >= 3*LED_COUNT && pos < 4*LED_COUNT){
    strip4.setPixelColor(pos-3*LED_COUNT, strip4.Color(red, green, blue));
  }
}

/*
void setPixelHue(int pos, int pixelHue){
  if(pos >= 0 && pos < LED_COUNT){
    strip1.setPixelColor(pos, strip1.gamma32(strip1.ColorHSV(pixelHue)));
  }
  
  if(pos >= LED_COUNT && pos < 2*LED_COUNT){
    strip2.setPixelColor(pos-LED_COUNT, strip2.gamma32(strip2.ColorHSV(pixelHue)));
  }

  if(pos >= 2*LED_COUNT && pos < 3*LED_COUNT){
    strip3.setPixelColor(pos-2*LED_COUNT, strip3.gamma32(strip3.ColorHSV(pixelHue)));
  }

  if(pos >= 3*LED_COUNT && pos < 4*LED_COUNT){
    strip4.setPixelColor(pos-3*LED_COUNT, strip4.gamma32(strip4.ColorHSV(pixelHue)));
  }
}
*/


void setPixelHue(int pos, int pixelHue){
  if(pos >= 0 && pos <= strip1Length){
    strip1.setPixelColor(pos, strip1.gamma32(strip1.ColorHSV(pixelHue)));
  }
  
  else if(pos > strip1Length && pos <= strip1Length + strip2Length ){
    strip2.setPixelColor(pos - strip1Length, strip2.gamma32(strip2.ColorHSV(pixelHue)));
  }

  else if(pos > strip1Length + strip2Length && pos <= strip1Length + strip2Length + strip3Length){
    strip3.setPixelColor(pos - strip1Length - strip2Length, strip3.gamma32(strip3.ColorHSV(pixelHue)));
  }

  else if(pos > strip1Length + strip2Length + strip3Length){
    strip4.setPixelColor(pos - strip1Length - strip2Length - strip3Length, strip4.gamma32(strip4.ColorHSV(pixelHue)));
  }
}


void showRed(){
  for(int i = 0; i <= 4*LED_COUNT; i++){
    setPixel(i, 255, 0, 0);
  }
}

void showAll(){
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
}

void clearAll(){
  strip1.clear();
  strip2.clear();
  strip3.clear();
  strip4.clear();
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i < strip1Length + strip2Length + strip3Length + strip4Length; i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / 4 * LED_COUNT);
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      setPixelHue(i, pixelHue);
      strip1.setPixelColor(i, strip1.gamma32(strip1.ColorHSV(pixelHue)));
    }
    showAll();
    delay(wait);  // Pause for a moment
  }
}

void readInput(){
  if (stringComplete) {
    inputString.trim();
    
    if(inputString == "red"){
      mode = "red";
    }

    if(inputString == "rainbow"){
      mode = "rainbow";
    }
    
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
