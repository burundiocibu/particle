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

String tmin_pipe_s;
String tmax_pipe_s;

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

uint32_t last_publish=0;  // seconds since the unix epoch

void setup()
{
  pinMode(ow_vcc, OUTPUT);
  pinMode(ow_gnd, OUTPUT);
  digitalWrite(ow_vcc, HIGH);
  digitalWrite(ow_gnd, LOW);

  Particle.variable("tmin_pipe", tmin_pipe_s);
  Particle.variable("tmax_pipe", tmax_pipe_s);
}

void loop()
{
   sensor.read(particleSensor, 5);
   double t_photon = sensor.fahrenheit();

   // get the min/max temps along the pipe at this time
   double t_min=999, t_max=-999;
   for (auto it = pipeSensors.begin(); it != pipeSensors.end(); ++it)
   {
      sensor.read(*it, 5);
      double t=sensor.fahrenheit();
      if (t>t_max) t_max = t;
      if (t<t_min) t_min = t;
   }
   tmin_pipe_s = String(t_min, 1);
   tmax_pipe_s = String(t_max, 1);

   // Only publish data as events every 5 minutes
   if (Time.now() - last_publish > 300)
   {
      Particle.publish("t_photon", String(t_photon, 2), PRIVATE);
      Particle.publish("tmin_pipe", tmin_pipe_s, PRIVATE);
      Particle.publish("tmax_pipe", tmax_pipe_s, PRIVATE);
      last_publish = Time.now();
   }
   
   delay(10000);
}
