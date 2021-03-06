//add PulseSensor library
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

//add Adafruit library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 6
//Initialize strip 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

//Output heart rate data to visualizer 
const int OUTPUT_TYPE = PROCESSING_VISUALIZER;
const int PULSE_INPUT = A1;
const int THRESHOLD = 545;   //To calibrate heart rate sensor (recommended changing it by increments of 5)

PulseSensorPlayground pulseSensor;

//Initialize information for heart rate sensor reading
int sliderValue = 0;
int sliderPin = A2;
int heartRate = 0; 

void setup() {
  Serial.begin(115200);
  
  // Configure the PulseSensor manager.

  pulseSensor.analogInput(PULSE_INPUT);

  pulseSensor.setSerial(Serial);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  pulseSensor.setThreshold(THRESHOLD);

  // Now that everything is ready, start reading the PulseSensor signal.
  if (!pulseSensor.begin()) {
    /*
       PulseSensor initialization failed,
       likely because our particular Arduino platform interrupts
       aren't supported yet.

       If your Sketch hangs here, try PulseSensor_BPM_Alternative.ino,
       which doesn't use interrupts.
    */
    /*for(;;) {
      // Flash the led to show things didn't work.
      digitalWrite(PULSE_BLINK, LOW);
      delay(50);
      digitalWrite(PULSE_BLINK, HIGH);
      delay(50);
    }*/
  }

  strip.begin();
  strip.show();
}

void loop() {

//Calculate heart rate for 30 seconds - the for statatement is needed to avoid interference with the lights
  for(int i=0; i<=100; i++){

     delay(20);

  // write the latest sample to Serial.
     pulseSensor.outputSample();
  
     if (pulseSensor.sawStartOfBeat()) {
       pulseSensor.outputBeat();} 

     delay(300); 
  }


  heartRate = pulseSensor.getBeatsPerMinute();
  //heartRate = 150;
//after heart rate information has been stored, visualize stress index 
  visualization(heartRate); 
}

//the following function calculates and displays the users stress index based on their subjective scale measurement and heart rate
//each visualization will cycle through different iterations of colors (except for the low stress/low heart rate condition) 
void visualization(int heartRate)
{
  int wait = 0; 
  int x = 0; 
  int subjectiveStress = analogRead(sliderPin); 

  if (heartRate <= 70 && subjectiveStress < 250){
    Serial.println("Normal heart rate + low stress");
    wait = 50; 
    for(int i = 0; i< 100; i++){
      lowStress(wait); 
    }
  }

  else if (heartRate <= 70 && subjectiveStress >= 250){
    Serial.println("Normal heart rate + high stress");
    wait = 50; 
   
    for(int i = 0; i< 3; i++){
          highStress(wait);
          wait++; }
            for(int j = 0; j< 97; j++){
              lowStress(wait);
             wait++;} 
  }

  else if (heartRate > 70 && subjectiveStress < 250){
    wait = heartRate/15; 
    Serial.println("High heart rate + low stress");
   
    while (wait < 100) {
      for(int i = 0; i< 8; i++){
          highHeartRate(wait);
          wait++; }
          for(int j = 0; j< 92; j++){
            lowStress(wait);
            wait++;} 
    }
  }

  else if (heartRate > 70 && subjectiveStress >= 250){
    wait = heartRate/25; 
    Serial.println("High heart rate + high stress");
    while (wait < 100) {
      for(int i = 0; i< 8; i++){
          highestStress(wait);
          wait++; }
          for(int j = 0; j< 92; j++){
            lowStress(wait);
            wait++;} 
    }  
  }
}

//the following functions dictate what colors are shown based on the stress index
void highestStress(int wait){
    colorWipe(strip.Color(255, 0, 38), wait); 
    colorWipe(strip.Color(162, 0, 255), wait); 
}

void highHeartRate(int wait){
      colorWipe(strip.Color(217, 255, 0), wait); 
      colorWipe(strip.Color(255, 145, 0), wait);
}

void highStress(int wait){
      colorWipe(strip.Color(255, 102, 0), wait); 
      colorWipe(strip.Color(255, 0, 157), wait); 
}

void lowStress(int wait){
      colorWipe(strip.Color(255, 255, 255), wait);
      colorWipe(strip.Color(0, 174,255), wait);
}
//this function is necessary to rotate through different color schemes 
void colorWipe(uint32_t c, int wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }}
