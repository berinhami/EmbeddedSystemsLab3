#include <ESP8266WiFi.h>

const char* ssid = "wifiName";
const char* password = "wifiPassword";

WiFiClient client;

const int echo = D5;
const int trig = D6;

int duration = 0;
int distance = 0;

String send = "-";

void setup() {

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration/2) /28.5;
  Serial.println(distance);

  if(distance > 30){
    send = "/OFF";
  }
  else if(distance > 20){
    send = "/GREEN";
  }
  else if(distance > 10){
    send = "/YELLOW";
  }
  else if(distance > 5){
    send = "/RED";
  }
  else{
    send = "/CYCLE";
  }
  
  Serial.print(send);
  delay(500);
  
  if(client.connect("192.168.0.21", 80)){
    client.print(String("GET" ) + send + " HTTP/1.1\r\n" + "Host: " + "192.168.0.21"  + "\r\n" + "Connection: keep-alive\r\n\r\n");
  }
  
}
