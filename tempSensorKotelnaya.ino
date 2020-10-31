/* ESP & Blynk */
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial    

/* Blynk credentials */
char auth[] = "YIDDyQbQK6HI7QDgAK_lswE-2i7YwVFk";

/* WiFi credentials */
char ssid[] = "Keenetic-7031";
char pass[] = "XbAsnErK";

/* TIMER */
#include <SimpleTimer.h>
SimpleTimer timer;

/* DS18B20 Temperature Sensor */
#include <OneWire.h>
#include<DallasTemperature.h> 
#define ONE_WIRE_BUS 2 // DS18B20 подключаем на D4 на плате  
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
int temp_0;
int temp_1;

void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  DS18B20.begin();
  timer.setInterval(1000L, getSendData);
  Serial.println(" ");
  Serial.println("Testing Dual Sensor data");
}

void loop() 
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
}

/***************************************************
 * Send Sensor data to Blynk
 **************************************************/
void getSendData()
{
  DS18B20.requestTemperatures(); 
  temp_0 = DS18B20.getTempCByIndex(0); // Sensor 0 показания для датчика 1 в цельсиях
  temp_1 = DS18B20.getTempCByIndex(1); // Sensor 0 показания для датчика 2 в цельсиях 

  Serial.print("Temp_0: ");
  Serial.print(temp_0);
  Serial.print(" oC . Temp_1: ");
  Serial.print(temp_1);
  Serial.println(" oC");
   
  Blynk.virtualWrite(10, temp_0); //вывод данных на виртуальный пин V10
  Blynk.virtualWrite(11, temp_1); //вывод данных навиртуальный пин V11
}
