/*
Please see Readme.md
*/

#include <deque>
#include <vector>

#include "jcl.h"

jcl::DS18 sensor(D4, true);

int ow_vcc=D5;
int ow_gnd=D3;

typedef std::vector<uint8_t> Addr;
typedef std::vector<Addr> AddrVec;

double pipe_Tmin=0;
double pipe_Tmax=0;

// This is in the order of the sensors from the head of the pipe
// to the end. The head is where the pipe goes into the ground to the
// house, the end is where it comes out of the tank
jcl::AddrVec pipeSensors = {
   jcl::string_to_Addr("28ff2e553218011e"), // Closest to house
   jcl::string_to_Addr("28fffb05321802a8"),
   jcl::string_to_Addr("28ffa45132180166"),
   jcl::string_to_Addr("28ff0fee31180228"),
   jcl::string_to_Addr("28ff5e4f32180150"),
   jcl::string_to_Addr("28ff7e07321802b6") // Closest to tanks
   };

// The sensor insde the tank_mgr's enclosure
jcl::Addr particleSensor(jcl::string_to_Addr("10f2f2ed010800cb"));


void setup()
{
  pinMode(ow_vcc, OUTPUT);
  pinMode(ow_gnd, OUTPUT);
  digitalWrite(ow_vcc, HIGH);
  digitalWrite(ow_gnd, LOW);

  Particle.variable("pipe_Tmin", pipe_Tmin);
  Particle.variable("pipe_Tmax", pipe_Tmax);
}

void loop()
{
   sensor.read(particleSensor, 5);
   Particle.publish("Tphoton", String(sensor.fahrenheit(), 3), PRIVATE);
   
   double t, t_min=999, t_max=-999;
   int n=0;
   for (auto it = pipeSensors.begin(); it != pipeSensors.end(); ++it)
   {
      sensor.read(*it, 5);
      double t=sensor.fahrenheit();
      if (t>t_max) t_max = t;
      if (t<t_min) t_min = t;
   }
   String msg = "(" + String(t_min, 3) + ", " + String(t_max, 3) + ")";
   Particle.publish("Tpipe", msg , PRIVATE);
   pipe_Tmin = t_min;
   pipe_Tmax = t_max;
   delay(60000);
}
