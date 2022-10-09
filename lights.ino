#include <ESP8266WiFi.h>

const char* ssid = "wifiName";
const char* password = "wifiPassword";

//variables
int distance = 0;
int red = D5;
int yellow = D6;
int green = D7;
bool turniton = false;
const unsigned long eventInterval = 400;
unsigned long previousTime = 0;
int countme = 0;

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  //set up pins
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
 
  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {

    
  //cycle code
  unsigned long currentTime = millis();
  if(turniton == true){
    if(currentTime - previousTime >= eventInterval){
      if(countme % 2 == 0){
   
        digitalWrite(red, HIGH);
        digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);
      }
      if(countme % 2 == 1){

        digitalWrite(red, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);
      }
      countme++;
      previousTime = currentTime;
    }
  }

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available() && turniton == true){
    delay(1);
  
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  if (request.indexOf("/RED") != -1) {
    turniton = false;
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    Serial.println("Im red");
  } 
  if (request.indexOf("/YELLOW") != -1){
    turniton = false;
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    Serial.println("Im yellow");
  }
  if (request.indexOf("/GREEN") != -1){
    turniton = false;
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
    Serial.println("Im green");
  }
  if (request.indexOf("/OFF") != -1){
    turniton = false;
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    Serial.println("Im Off");
  }
  
  if (request.indexOf("/CYCLE") != -1){  
    turniton = true;
  }
}
