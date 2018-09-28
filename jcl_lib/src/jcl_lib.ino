/*
  Test code to check out the library on a photon.
*/

#include "jcl.h"

jcl::DS18 sensor(D4, false);
int ow_vcc=D5;
int ow_gnd=D3;

const int MAX_SENSORS = 10;
retained uint8_t addr[MAX_SENSORS][8];
retained int num_sensors = 0;



void setup()
{
   Serial.begin(9600);

   pinMode(ow_vcc, OUTPUT);
   pinMode(ow_gnd, OUTPUT);
   digitalWrite(ow_vcc, HIGH);
   digitalWrite(ow_gnd, LOW);
}

void loop()
{
   if (Serial.available())
   {
      // clear out the input buffer...
      while(Serial.available())
         Serial.read();

      Serial.println("Scanning bus");
      num_sensors = 0;
   
      while (true)
      {
         sensor.setConversionTime(750);
         if (sensor.read())
         {
            Serial.printf("sensor %d: ", num_sensors);
            Serial.println(sensor.dump());
            sensor.getAddr(addr[num_sensors]);
            num_sensors++;
         }
         if (sensor.searchDone())
            break;
         Particle.process();
      }
      Serial.printlnf("Found %d sensors\n", num_sensors);
   }
   else if (num_sensors)
   {
      for (int i=0; i<num_sensors; i++)
      {
         Serial.printf("sensor %d: 0x", i);
         Serial.printf(jcl::addr_to_String(addr[i]));
         if (sensor.read(addr[i], 5))
            Serial.printlnf(", %6.3f (%d)", sensor.celsius(), sensor.getRetryCount());
         else
            Serial.printlnf("read error (%d)", sensor.getRetryCount());
      }
      Serial.println("");
   }
}
