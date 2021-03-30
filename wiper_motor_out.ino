#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Servo.h>
#include "FirebaseESP8266.h"                                  //>>>>>>>>>>>>>>> Install required Firebase and ESP8266 library

//#include <ArduinoJson.h>

#define FIREBASE_HOST "smartparkingv1-default-rtdb.firebaseio.com"               //>>>>>>>>>firebase auth
#define FIREBASE_AUTH "YGo26NAaKJMC8hy9UWnqAevjmTatxVivEIyeKSvh"   

FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;

WiFiClient client;

const char* ssid = "IOT31";
const char* password = "password";

int pinOne = 0;
int pinTwo = 2;

bool opendoor;

void setup() {

  //connect to wifi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  //connect to firebase

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // put your setup code here, to run once:
  pinMode(pinOne, OUTPUT);
  pinMode(pinTwo, OUTPUT);
  Serial.begin(115200);
  digitalWrite(pinTwo, HIGH);
  digitalWrite(pinOne, HIGH);
}

void loop() {
  
  Firebase.getBool(firebaseData, "ParkingIOT/openoutdoor", opendoor);
//  delay(1000);
  Serial.println(opendoor);
  //
  //
    if (opendoor == 0) {
      //do not open
      stopMotor();
    }
    else {
  //    //Serial.print("Servo is started");
      startMotor();
      delay(200);
      stopMotor();
  
      delay(50000); //30 sec
      reverseMotor();
      delay(150);
      stopMotor();
      Firebase.setBool(firebaseData, "ParkingIOT/openoutdoor", false);
    }
  //
}

void startMotor() {
  Serial.println("Starting gate");
  digitalWrite(pinTwo, LOW);
  digitalWrite(pinOne, HIGH);
}

void reverseMotor() {
  Serial.println("Closing gate");
  digitalWrite(pinOne, LOW);
  digitalWrite(pinTwo, HIGH);
}

void stopMotor() {
  Serial.println("Stoping gate");
  digitalWrite(pinOne, HIGH);
  digitalWrite(pinTwo, HIGH);
}
