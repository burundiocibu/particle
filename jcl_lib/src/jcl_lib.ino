/*
Please see Readme.md
*/

#include <vector>

#include "jcl.h"

jcl::DS18 sensor(D4, true);
int ow_vcc=D5;
int ow_gnd=D3;

jcl::AddrVec sensors;

void setup()
{
  pinMode(ow_vcc, OUTPUT);
  pinMode(ow_gnd, OUTPUT);
  digitalWrite(ow_vcc, HIGH);
  digitalWrite(ow_gnd, LOW);

  Particle.function("scanBus", scanBus);
  Particle.function("readList", readList);
}


void loop()
{
   int i=0;
   for (auto it = sensors.begin(); it != sensors.end(); ++it)
   {
      sensor.read(*it, 5);
      String msg = "sensor " + String(i++) + ": " + sensor.dump();
      Serial.println(msg);
   }
   
   if (sensors.size())
      Serial.println("");
}


int scanBus(String command)
{
   Serial.println("Scanning bus");
   
   uint8_t addr[8];
   sensors.clear();
   
   while (true)
   {
      sensor.setConversionTime(750);
      if (sensor.read())
      {
         String msg = "sensor " + String(sensors.size()) + ": " + sensor.dump();
         Serial.println(msg);
         Particle.publish("sensor", msg, PRIVATE);
         sensor.getAddr(addr);
         sensors.push_back(jcl::Addr(addr, addr+sizeof(addr)));
      }
      if (sensor.searchDone())
         break;
   }
   
   String msg = "Found " + String(sensors.size()) + " sensors";
   Serial.println(msg);
   Particle.publish("scan", msg, PRIVATE);
   
   return sensors.size();
}


int readList(String command)
{
   jcl::AddrVec sensors = {
      jcl::string_to_Addr("10f0efed01080035"),
      jcl::string_to_Addr("10b6bbed01080078"),
      jcl::string_to_Addr("28ff37ef3118021d")
   };

   Serial.println("Reading listed sensors");

   for (auto it = sensors.begin(); it != sensors.end(); ++it)
   {
      sensor.read(*it, 5);
      Serial.println(sensor.dump());
   }
   return 0;
}

