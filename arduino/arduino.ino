#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#define LED1 5
#define LED2 4
#define TEMP_LED 12 


//----------------------------------------

#include "DHT.h"  //--> Include the DHT Sensor Library 
#define DHTTYPE DHT11

#include "PageIndex.h" 

#define LEDonBoard 2 


#define MQ2_PIN A0 


int mq2Value = 0;
bool bufferSnooze = false; 
const char* ssid = "Galaxy A24 F4D1";
const char* password = "12345678987654321";
//----------------------------------------

ESP8266WebServer server(80);  

const int DHTPin = 13; 
DHT dht(DHTPin, DHTTYPE);

void readMQ2Sensor() {
  mq2Value = analogRead(MQ2_PIN); // Lecture de la valeur analogique du capteur MQ2
  if (mq2Value > 500) {
    // Activer le buffer (sonner l'alarme)
    bufferSnooze = false;
  } else {
    // Désactiver le buffer (arrêter l'alarme)
    bufferSnooze = true;
  }
}
//

// Fonction pour gérer l'affichage des données du capteur MQ2 sur la page web
void handleMQ2Data() {
  readMQ2Sensor(); // Appel de la fonction pour lire les données du capteur
  String mq2Data = "MQ2 Gas Value: " + String(mq2Value);
  server.send(200, "text/plain", mq2Data); // Envoi de la valeur du gaz à la requête client AJAX
}

// Fonction pour gérer l'état du tampon sur la page web
void handleBufferState() {
  String bufferState = bufferSnooze ? "Snooze" : "Active";
  server.send(200, "text/plain", bufferState); // Envoi de l'état du tampon à la requête client AJAX
}

void handleLED1Control() {
  String ledState = server.arg("state");
  digitalWrite(LED1, ledState == "on" ? LOW : HIGH); // Assuming active low LEDs
  server.send(200, "text/plain", "LED1 " + ledState);
}
void handleMotionDetected() {
  server.send(200, "text/plain", "Motion Detected");
  // You can also turn on an LED here if you want a physical indication of motion
}

void handleLED2Control() {
  String ledState = server.arg("state");
  digitalWrite(LED2, ledState == "on" ? LOW : HIGH); // Assuming active low LEDs
  server.send(200, "text/plain", "LED2 " + ledState);
}

//----------------------------------------This routine is executed when you open NodeMCU ESP8266 IP Address in browser
void handleRoot() {
 String s = MAIN_page; //--> Read HTML contents
 server.send(200, "text/html", s); //--> Send web page
}


void handleDHT11Temperature() {
  float t = dht.readTemperature(); // Read temperature as Celsius
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("DHT11 || Temperature : ");
    Serial.print(t);
    Serial.print(" || ");
    // Turn on TEMP_LED if temperature is greater than 15 degrees Celsius
    if (t > 20) {
      digitalWrite(TEMP_LED, HIGH); // Turn on the LED
    } else {
      digitalWrite(TEMP_LED, LOW); // Turn off the LED
    }
  }
  server.send(200, "text/plain", String(t)); // Send temperature value to client
}


void handleDHT11Humidity() {
  float h = dht.readHumidity();
  String Humidity_Value = String(h);
 
  server.send(200, "text/plane", Humidity_Value); //--> Send Humidity value only to client ajax request
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor !");
  }
  else {
    Serial.print("Humidity : ");
    Serial.println(h);
  }
}


//----------------------------------------
//----------------------------------------Setup
void setup(void){
  Serial.begin(115200);
  delay(500);
  dht.begin();  //--> Start reading DHT11 sensors
  delay(500);
  
  
  WiFi.begin(ssid, password); 
  Serial.println("");
     pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(TEMP_LED, OUTPUT);
  digitalWrite(LED1, HIGH); 
  digitalWrite(LED2, HIGH); 
  digitalWrite(TEMP_LED, HIGH);
 
  server.on("/led1", handleLED1Control); 
  server.on("/led2", handleLED2Control);

  pinMode(LEDonBoard,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(LEDonBoard, HIGH); //--> Turn off Led On Board
  
  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(LEDonBoard, LOW);
    delay(250);
    digitalWrite(LEDonBoard, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(LEDonBoard, HIGH); 
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //----------------------------------------
  server.on("/", handleRoot); 
  server.on("/readTemperature", handleDHT11Temperature);  
  server.on("/readHumidity", handleDHT11Humidity);  

  server.begin(); //--> Start server
  Serial.println("HTTP server started");


//
pinMode(MQ2_PIN, INPUT); 
server.on("/readMQ2", handleMQ2Data);
server.on("/bufferState", handleBufferState);


}
//----------------------------------------
//----------------------------------------Loop
void loop(){
  server.handleClient();  //Handle client requests

}
//----------------------------------------