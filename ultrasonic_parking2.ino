//this is for second sensor

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "FirebaseESP8266.h"                                  //>>>>>>>>>>>>>>> Install required Firebase and ESP8266 library

//#include <ArduinoJson.h>

#define FIREBASE_HOST "smartparkingv1-default-rtdb.firebaseio.com"               //>>>>>>>>>firebase auth
#define FIREBASE_AUTH "YGo26NAaKJMC8hy9UWnqAevjmTatxVivEIyeKSvh"

FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;

WiFiClient client;
// const int ProxSensor = A0;
const char* ssid = "IOT31";
const char* password = "password";


#define echoPin 15 //d8
#define trigPin 13 //d7

#define echoPin1 4 //d1
#define trigPin1 5  //d2
long duration;
int distance;
long duration1;
int distance1;
int a;
int b;

boolean value;
boolean statusofslot2;
boolean vacancy1;

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  Serial.begin(9600);


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

}

void loop() {

  a=func();
  int b;
  b=func1();

  if(a<20 && b<20){
  Serial.print("A:");
  Serial.println(a);
  value=true;
  statusofslot2=true;


  vacancy1=true;

 
 Firebase.setBool(firebaseData, "/ParkingIOT/SLOT2/status",statusofslot2);

  }else{
      value = false;
      statusofslot2=false;
    
      Firebase.setBool(firebaseData, "/ParkingIOT/SLOT2/status",statusofslot2);
  
    }

  }

  int func() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    return distance;
  }

  int func1() {
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    duration1 = pulseIn(echoPin1, HIGH);
    distance1 = duration1 * 0.034 / 2;
    // Displays the distance on the Serial Monitor
    Serial.print("Distance1: ");
    Serial.print(distance1);
    Serial.println(" cm");
    return distance1;
  }
