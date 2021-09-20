#define echoPin 4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#include <dht.h>
#define dht_apin A1 // Analog Pin sensor is connected to
#include <Wire.h>


#include <ArduinoJson.h>

const int DOOR_SENSOR_PIN = 5; // Arduino pin connected to door sensor's pin
int led = 6;
int doorState;
int state;

dht DHT;
// defines variables
long duration; // variable for the duration of sound wave travel
float distance; // variable for the distance measurement

void setup() {
  Serial.begin(9600);// initialize serial
  delay(500);//Delay to let system boot
  
  
  delay(100);//Wait before accessing Sensor
  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT 
}

void loop() {
  doorState = digitalRead(DOOR_SENSOR_PIN); // read state
  if (doorState == HIGH) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  // read the input on analog pin 0 for soil moisture:
  int sensorValue = analogRead(A0);
  delay(100);// delay in between reads for stability

  //Ultra sonic distance senosr
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delay(100);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delay(100);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
 
  DHT.read11(dht_apin);  
    int volume = (21*55) - (distance*55);
    

    StaticJsonDocument<128> root;
    
    
    root["Moisture Level"] = sensorValue;
    root["Volume of Water"] = volume;
    root["Temperature"] = DHT.temperature;
    root["Humidity"] = DHT.humidity;
    root["Door Status"] = doorState;

    serializeJson(root, Serial);
    Serial.println();
    
    delay(500);//Wait 0.5 seconds before accessing sensor again.
    
  
}
