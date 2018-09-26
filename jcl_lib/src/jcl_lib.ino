/*
  Test code to check out the library on a photon.
*/

#include "jcl.h"

jcl::DS18 sensor(D4, true);
int sensorNum=0;
int ow_vcc=D5;
int ow_gnd=D3;

String msg;

void setup()
{
  Serial.begin(9600);

  pinMode(ow_vcc, OUTPUT);
  pinMode(ow_gnd, OUTPUT);
  digitalWrite(ow_vcc, HIGH);
  digitalWrite(ow_gnd, LOW);

  Particle.variable("status", msg);
}

void loop()
{
  // Read the next available 1-Wire temperature sensor
  if (sensor.read())
  {
    String msg = jcl::DS18_dump(sensor);
    Serial.printf(msg);
    Serial.printf("\n");
    Particle.publish("sensor", msg, PRIVATE);
    sensorNum++;
  }
  else
  {
    // Once all sensors have been read you'll get searchDone() == true
    // Next time read() is called the first sensor is read again
    if (sensor.searchDone())
    {
      msg = "Found " + String(sensorNum) + " sensors";
      Serial.println(msg);
      Particle.publish("sensor", msg, PRIVATE);
      sensorNum = 0;
      delay(10000);
    }
    else
      Serial.printf(DS18_dump(sensor));
  }
}
