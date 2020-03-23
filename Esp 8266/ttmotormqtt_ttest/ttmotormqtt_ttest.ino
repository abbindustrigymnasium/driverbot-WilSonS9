#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>
Servo servo;
//Install libraries PubSubClient and EspMQTTClient

#define motorPinRightDir  0//D2
#define motorPinRightSpeed 5//D1
#define motorPinLeftDir 2
#define motorPinLeftSpeed 4

String vel = "";
String dir = "0";
int velint = 0;
String deg = "90";
String pay = "";

const char* ssid = "Spisringsgatan9";
const char* password =  "Darten10Zebran10";

const char* mqttServer = "maqiatto.com";
const int mqttPort = 1883;
const char* mqttUser = "g3.vibestol@gmail.com";
const char* mqttPassword = "G3Vibestol2020";

String Sub = "g3.vibestol@gmail.com/motor";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPinRightDir, OUTPUT);
  pinMode(motorPinRightSpeed, OUTPUT);
  pinMode(motorPinLeftDir, OUTPUT);
  pinMode(motorPinLeftSpeed, OUTPUT);
  servo.attach(15);
  servo.write(0);
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
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
 
  client.publish("g3.vibestol@gmail.com/motor", "Hello from ESP8266");
  client.subscribe("g3.vibestol@gmail.com/motor");
 
}

void loop() {
  velint = vel.toInt();
  client.loop();
  digitalWrite(motorPinRightDir, dir.toInt());
  analogWrite(motorPinRightSpeed, velint);
  servo.write(deg.toInt());
  Serial.println(dir + vel + deg);
}

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 pay = "";
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    pay += (char)payload[i];
  }
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

void DriveDirSpeed(int Direction, String Speed) {
  if (Direction == 1) {
    Serial.println("Framåt!");
    Serial.println("Hastighet: " + Speed);
    } else {
    Serial.println("Bakåt!");
    Serial.println("Hastighet: " + Speed);
      }
}
