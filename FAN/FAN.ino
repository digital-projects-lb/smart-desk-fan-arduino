#include <DHT11.h>
#include <Servo.h>

int REDpin = 10;
int GREENpin = 9;
int BLUEpin = 8;
int TEMP = 4;
int servo1 = 2;  // Fan
int servo2 = 3;  // Ultrasonic rotator

Servo myservo1;
Servo myservo2;

int distanceThreshold = 0;
int cm = 0;

DHT11 dht(TEMP);

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);         // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);      // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup() {
  Serial.begin(9600);
  pinMode(TEMP, INPUT);

  myservo1.attach(servo1);
  myservo2.attach(servo2);

  pinMode(GREENpin, OUTPUT);
  pinMode(BLUEpin, OUTPUT);
  pinMode(REDpin, OUTPUT);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // set threshold distance to activate LEDs
  distanceThreshold = 350;
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7, 6);

  // Sweep the servo2 from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle += 1) {
    myservo2.write(angle);
    delay(15);
  }

  // Sweep the servo2 from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle -= 1) {
    myservo2.write(angle);
    delay(15);
  }

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  //cm = 15;           //testing
  //temperature = 33;  //testing

  if (temperature > 30) {
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);

    if (cm < 20) {
      // Sweep the servo1 from 0 to 180 degrees
      for (int angle = 0; angle <= 180; angle += 1) {
        myservo1.write(angle);
        delay(15);
      }

      // Sweep the servo1 from 180 to 0 degrees
      for (int angle = 180; angle >= 0; angle -= 1) {
        myservo1.write(angle);
        delay(15);
      }
      delay(1000);
    }
  }
  else if (temperature < 10) {
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, HIGH);
  }
  else {
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
  }

  // Serial print proximity
  Serial.print(cm);
  Serial.println(" cm, ");

  // Serial Print temperature
  Serial.print(temperature);
  Serial.println(" Celsius");
}
