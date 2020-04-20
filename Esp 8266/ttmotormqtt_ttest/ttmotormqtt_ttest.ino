#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>
Servo servo;
//First, we install some libraries to help control the driverbot
// The libraries are: a wifi client for the esp8266, a mqtt library to connect to the broker, and a servo library to control the servo

// Here, we define some pins for the engine
#define motorPinRightDir  0//D2
#define motorPinRightSpeed 5//D1
#define motorPinLeftDir 2
#define motorPinLeftSpeed 4

// Here, we define some variables that will be sent to the engine and servo later on
String vel = "";
String dir = "0";
int velint = 0;
String deg = "90";
String pay = "";

// Here, we have the ssid and password for the local wifi, which is necessary for the microcontroller to connect to the broker
const char* ssid = "Spisringsgatan9";
const char* password =  "Darten10Zebran10";

// Here, we define some things for the mqtt library like our username and password
const char* mqttServer = "maqiatto.com";
const int mqttPort = 1883;
const char* mqttUser = "g3.vibestol@gmail.com";
const char* mqttPassword = "G3Vibestol2020";

// This is the topic being subscribed to
String Sub = "g3.vibestol@gmail.com/motor";

// This thing sets up the wifi and allows it to be connected a bit later
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Here, we define that the 4 following pins will be outputs
  // We also define where the servo is connected, and tell it write 90 degrees, straight forward, at the start of the program
  pinMode(motorPinRightDir, OUTPUT);
  pinMode(motorPinRightSpeed, OUTPUT);
  pinMode(motorPinLeftDir, OUTPUT);
  pinMode(motorPinLeftSpeed, OUTPUT);
  servo.attach(15);
  servo.write(90);
 
  Serial.begin(115200);
 
//  This is where the microcontroller connects to the wifi
  WiFi.begin(ssid, password);
 
//  While connecting, it writes that it is connecting to the wifi, and when connected, it says so
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
//  Defines some mqtt things, the broker and port we use and the function used to callback when a message is received
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
//  Here, we connect the microcontroller to the mqtt broker
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("pubsubttmotorganggang", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
//  Publishes a message in the topic, and also subscribes to the same topic where it will fetch data later
  client.publish("g3.vibestol@gmail.com/motor", "Hello from ESP8266");
  client.subscribe("g3.vibestol@gmail.com/motor");
 
}

void loop() {
  // Here, we write to the engine and servo with the data received from the mqtt broker
  // We also log the direction, velocity and the angle for the servo to be used for basic debugging in the serial monitor
  velint = vel.toInt();
  client.loop();
  digitalWrite(motorPinRightDir, dir.toInt());
  analogWrite(motorPinRightSpeed, velint);
  servo.write(deg.toInt());
  Serial.println(dir + vel + deg);
}

// This is the callback function that will be called upon when a message is received in the topic
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  // Because the payload of the message is received as an unsigned char, we use a for-loop to get the payload as a string
  // The payload as a string is saved in the "pay" variable
 pay = "";
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    pay += (char)payload[i];
  }
  // Here, we log the payload in the serial monitor
  // We also define that the first character if the payload is the direction, the next 3 the angle and the last 4 the speed
  // The front end is designed so that even if the angle or speed is less than 3 or 4 characters, it will still be sent 3 or 4 characters
    Serial.println(pay);
    dir = pay.substring(0, 1);
    vel = pay.substring(1, 5);
    deg = pay.substring(5, 8);
    Serial.println(dir);
    Serial.println(vel);
    Serial.println(deg);
  Serial.println();
  Serial.println("-----------------------");
 
}

// This is a function used to print some basic information in the serial monitor
// More extensive logging is done in the front end, on the website
void DriveDirSpeed(int Direction, String Speed) {
  if (Direction == 1) {
    Serial.println("Framåt!");
    Serial.println("Hastighet: " + Speed);
    } else {
    Serial.println("Bakåt!");
    Serial.println("Hastighet: " + Speed);
      }
}
