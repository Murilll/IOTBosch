#include <common.h>
#include <FirebaseESP32.h>
#include <FirebaseFS.h>
#include <Utils.h>

//#include <Firebase.h>
#define FIREBASE_HOST "https://iotbosch-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "VWZU7VfyzpfSVyGsNmupCLYsPfzPaYa2aFWuCBUl"
FirebaseData firebaseData;
FirebaseJson json;


#include "dht.h"
#define pinoDHT 4
dht DHT;


#include <LiquidCrystal.h>
LiquidCrystal lcd(19,23,18,17,16,15);


#include <WiFi.h>
#define WIFI_SSID "Murilll"
#define WIFI_PASSWORD "123456789"



// --------------------------------------------------------------------

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.begin(9600);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  while (WiFi.status() != WL_CONNECTED)
   {
     Serial.print(".");
     delay(300);
    }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  }

void loop() {
  DHT.read11(pinoDHT);
  float t = DHT.temperature;
  float h = DHT.humidity;

  lcd.setCursor(0,0);
  
  json.set("/Temperatura",t);
  json.set("/Umidade",h);
  Firebase.updateNode (firebaseData,"/Sensor",json);
  lcd.setCursor(0,0);
  lcd.print("Umidade:" + (String)DHT.humidity);
  lcd.setCursor(0,1);
  lcd.print("Temp:"+ (String)DHT.temperature);

}




  
