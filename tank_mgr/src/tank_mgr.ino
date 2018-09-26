/*
Please see Readme.md
*/

#include <deque>

#include "jcl.h"

jcl::DS18 sensor(D4, true);

int ow_vcc=D5;
int ow_gnd=D3;

int led = D7;


std::deque<float> history;

double Tmin=0;
double Tmax=0;
double Tavg=0;
double temps[15];
size_t sensorNum = 0;
String msg;

long long int particle_sensor = 0xf2f2ed010800L;

long long int pipe_sensors[] = {
    0xff2e55321801L,
    0xfffb05321802L,
    0xffa451321801L,
    0xff0fee311802L,
    0xff5e4f321801L,
    0xff7e07321802L};


void setup()
{
  Serial.begin(9600);

  pinMode(ow_vcc, OUTPUT);
  pinMode(ow_gnd, OUTPUT);
  digitalWrite(ow_vcc, HIGH);
  digitalWrite(ow_gnd, LOW);

  sensorNum=0;
  pinMode(led, OUTPUT);
  Particle.function("led", ledToggle);
  digitalWrite(led, LOW);

  Particle.variable("Tmin", Tmin);
  Particle.variable("Tmax", Tmax);
  Particle.variable("status", msg);
}

void loop()
{
  // Read the next available 1-Wire temperature sensor
  if (sensor.read())
  {
    String msg = jcl::DS18_dump(sensor);

    uint8_t addr;
    sensor.addr(addr);
    long long int addr_lli;
    
    if (addr == 
    Particle.publish(msg);

    
    if (sensorNum < sizeof(temps))
      temps[sensorNum++] = sensor.fahrenheit();
    else
      Particle.publish("sensor", "More than " + String(sizeof(temps) + " devices found"), PRIVATE);

    Tavg = sensor.fahrenheit();

  // If sensor.read() didn't return true you can try again later
  // This next block helps debug what's wrong.
  // It's not needed for the sensor to work properly
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
      if (history.size() >= 20)
         history.pop_front();
      history.push_back(sensor.celsius());
      delay(10000);
    }
    else
      Serial.printf(DS18_dump(sensor));
  }
}

int ledToggle(String command)
{
    if (command=="on")
    {
        digitalWrite(led, HIGH);
        return 1;
    }
    else if (command=="off") {
        digitalWrite(led, LOW);
        return 0;
    }
    else if (command=="status")
    {
        return digitalRead(led);
    }
    else
    {
      return -1;
    }
}
