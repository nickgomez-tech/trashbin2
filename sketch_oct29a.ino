#include "Adafruit_TCS34725.h"
#include <Servo.h>
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);
Servo mecanism;

// HC-SR04
int trig = 6;
int echo = 5;
int servo = 13;

int time;
int distance;


void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  mecanism.attach(9);
  Serial.begin(9600);
  if(tcs.begin()){

    Serial.println("Beginning...");
    delay(2000);
  }
  else {

    Serial.println("Error");
    Serial.println("Check conections and try again!");
    while(1)delay(500);
  }
}

void loop() {
  mecanism.write(0);

  // Servo & HC-SR04
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  int time = pulseIn(echo, HIGH);
  int distance = time / 58.2;

  uint16_t R,G,B,C;
  tcs.getRawData(&R,&G,&B,&C);
  if(G> R && G > B && distance<4){
    mecanism.write(220);
    delay(5000);
  }

  else if(B> G && B > R && distance<4){
    mecanism.write(310);
    delay(5000);
  }

}
