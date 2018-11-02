/*
Please see Readme.md
*/

#include <vector>

#include "jcl.h"

#include "MAX17043.h"

jcl::DS18 sensor(D4, true);
int ow_vcc=D5;
int ow_gnd=D3;

jcl::AddrVec sensors;

bool publish = false;

bool scan_bus = false;

double voltage = 0;
double soc = 0;
bool alert;

void setup()
{
  pinMode(ow_vcc, OUTPUT);
  pinMode(ow_gnd, OUTPUT);
  digitalWrite(ow_vcc, HIGH);
  digitalWrite(ow_gnd, LOW);

  Particle.function("scanBus", scanBus);
  Particle.function("readList", readList);
  Particle.function("readAddr", readAddr);

  Particle.variable("v_batt", voltage);
  Particle.variable("soc", soc);
  Particle.variable("alert", alert);

  // Set up the MAX17043 LiPo fuel gauge:
  lipo.begin(); // Initialize the MAX17043 LiPo fuel gauge

  // Quick start restarts the MAX17043 in hopes of getting a more accurate
  // guess for the SOC.
  lipo.quickStart();
  
  // We can set an interrupt to alert when the battery SoC gets too low.
  // We can alert at anywhere between 1% - 32%:
  lipo.setThreshold(10); // Set alert threshold to 10%.
}


void loop()
{
   if (scan_bus)
   {
      Serial.println("Scanning bus");
      sensors.clear();
   
      while (true)
      {
         sensor.setConversionTime(800);
         if (sensor.read())
         {
            String msg = "sensor " + String(sensors.size()) + ": " + sensor.dump();
            Serial.println(msg);
            Particle.publish("scan", msg, PRIVATE);
            uint8_t addr[8];
            sensor.getAddr(addr);
            sensors.push_back(jcl::Addr(addr, addr+sizeof(addr)));
         }
         if (sensor.searchDone())
            break;
      }
   
      String msg = "Found " + String(sensors.size()) + " sensors";
      Serial.println(msg);
      Particle.publish("scan", msg, PRIVATE);
      scan_bus = false;
   }
   else
   {
      int i=0;
      for (auto it = sensors.begin(); it != sensors.end(); ++it)
      {
         sensor.read(*it, 5);
         String msg = String(i++) + ": " + sensor.dump();
         Serial.println(msg);
         if (publish)
            Particle.publish("sensor", msg, PRIVATE);
      }
   
      if (sensors.size())
         Serial.println("");

      publish = false;
   }

   // lipo.getVoltage() returns a voltage value (e.g. 3.93)
   voltage = lipo.getVoltage();
   // lipo.getSOC() returns the estimated state of charge (e.g. 79%)
   soc = lipo.getSOC();
   // lipo.getAlert() returns a 0 or 1 (0=alert not triggered)
   alert = lipo.getAlert();
   
   Serial.print("Voltage: ");
   Serial.print(voltage);  // Print the battery voltage
   Serial.println(" V");
   
   Serial.print("Alert: ");
   Serial.println(alert);
   
   Serial.print("Percentage: ");
   Serial.print(soc); // Print the battery state of charge
   Serial.println(" %");
   Serial.println();
   
   delay(500);

}


int scanBus(String command)
{
   scan_bus = true;
   return 0;
}


int readList(String command)
{
   publish = true;
   return 0;
}


int readAddr(String command)
{
   jcl::Addr addr(jcl::string_to_Addr(command));
   Particle.publish("readAddr", "read " + command, PRIVATE);
   int rc = 0;
   if (sensor.read(addr, 5))
   {
      Particle.publish("readAddr", sensor.dump(), PRIVATE);
      return 10 * sensor.fahrenheit();
   }

   Particle.publish("readAddr", "Failed to read " + command, PRIVATE);
   return 0;
}
