#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include "MQ7.h"

char auth[] = "pb5w3cD2cdDs4SXEPsjXp5zrUG7m8yuA";

char ssid[] = "#####";
char pass[] = "#####";

#define DHTPIN 4          // D2
#define DHTTYPE DHT11

MQ7 mq7(A0,16);
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  float co= mq7.getPPM();
 
 

  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
  Blynk.virtualWrite(V7, mq7.getPPM());
}
 

void setup()
{
  
  Serial.begin(115200);

 
  Blynk.begin(auth, ssid, pass, IPAddress(192,168,3,4), 8080);

    dht.begin();
 
  
  timer.setInterval(1000L, sendSensor);

}

void loop()
{
  Blynk.run();
  timer.run();
}
