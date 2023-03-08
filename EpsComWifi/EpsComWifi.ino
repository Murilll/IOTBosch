#include <common.h>
#include <FirebaseESP32.h>
#include <FirebaseFS.h>
#include <Utils.h>

#include <LiquidCrystal.h>
#include <FirebaseESP32.h>
#include "dht.h"
#include <WiFi.h>

#define CONNECTION_TIMEOUT 10
#define WIFI_SSID "Murilll"
#define WIFI_PASSWORD "123456789"

int dhtpino = 4;
dht DHT;

LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

void setup() {
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
int timeout = 0;
  lcd.begin(16, 2);
  Serial.begin(9600);
  delay(200);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
    timeout++;
    if(timeout >= CONNECTION_TIMEOUT*5)
    {
      ESP.restart();
    }
    
  }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

}

 void loop() {
  DHT.read11(dhtpino);
  lcd.setCursor(0, 0);
  lcd.print("Umidade: " + (String)DHT.humidity);
  lcd.setCursor(0, 1);
  lcd.print("Temperatura:" + (String)DHT.temperature);
  delay(1000);
}
