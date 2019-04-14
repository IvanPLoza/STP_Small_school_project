#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

#define BAUD_RATE 115200

AsyncWebServer server(80);

const char* ssid = "ATS - Hotspot"; // Your WiFi SSID
const char* password = "ats123ATS"; // Your WiFi Password


void buttonClicked(const char* id){
   Serial.println("Button Clicked - "+String(id));
   digitalWrite(LED_BUILTIN, HIGH);
   delay(100);
   digitalWrite(LED_BUILTIN, LOW);
}


void setup() {

    Serial.begin(BAUD_RATE);

    pinMode(LED_BUILTIN, OUTPUT);

    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);

    while (WiFi.waitForConnectResult() != WL_CONNECTED) {

        Serial.printf("Wifi Failed!");
        WiFi.begin(ssid, password);
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    
    ESPDash.init(server);   // Initiate ESPDash and attach your Async webserver instance

    // Add Respective Cards and attach Button Click Function
    ESPDash.addButtonCard("btn1", "Blink Button");
    ESPDash.attachButtonClick(buttonClicked);

    server.begin();
}

void loop() {

}