/*
Please see Readme.md
*/

#include <deque>
#include <vector>

#include "jcl.h"

jcl::DS18 sensor(D4, true);
int ow_vcc=D5;
int ow_gnd=D3;

String tmin_pipe_s;
String tmax_pipe_s;
String t_photon_s;
String t_ambient_s;
int read_errors=0;
int range_errors=0;

void setup()
{
   pinMode(ow_vcc, OUTPUT);
   pinMode(ow_gnd, OUTPUT);
   digitalWrite(ow_vcc, HIGH);
   digitalWrite(ow_gnd, LOW);

   Particle.variable("tmin_pipe", tmin_pipe_s);
   Particle.variable("tmax_pipe", tmax_pipe_s);
   Particle.variable("t_photon", t_photon_s);
   Particle.variable("t_ambient", t_ambient_s);

   Particle.variable("read_errors", read_errors);
   Particle.variable("range_errors", range_errors);
}


// This is in the order of the sensors from the head of the pipe
// to the end. The head is where the pipe goes into the ground to the
// house, the end is where it comes out of the tank
jcl::AddrVec pipeSensors = {
   jcl::string_to_Addr("28ff870232180262"), // Pump head
   jcl::string_to_Addr("28ff2e553218011e"), // Closest to house
   jcl::string_to_Addr("28fffb05321802a8"),
   jcl::string_to_Addr("28ffa45132180166"),
   jcl::string_to_Addr("28ff0fee31180228"),
   jcl::string_to_Addr("28ff5e4f32180150"),
   jcl::string_to_Addr("28ff7e07321802b6") // Closest to tank valve
   };

jcl::Addr t_photon_addr(jcl::string_to_Addr("10f2f2ed010800cb"));
jcl::Addr t_ambient_addr(jcl::string_to_Addr("28ff99e33118017c"));

void loop()
{
   if (sensor.read(t_photon_addr, 5))
      t_photon_s = String(sensor.fahrenheit(), 2);

   if (sensor.read(t_ambient_addr, 5))
      t_ambient_s = String(sensor.fahrenheit(), 2);
   
   // get the min/max temps along the pipe at this time
   double t_min=999, t_max=-999;
   double t_sum=0;
   int n_read;
   for (auto it = pipeSensors.begin(); it != pipeSensors.end(); ++it)
   {
      if (sensor.read(*it, 5))
      {
         double t=sensor.fahrenheit();
         if (t>t_max) t_max = t;
         if (t<t_min) t_min = t;
      }
      else
         read_errors++;
   }
   if (t_max - t_min < 15)
   {
      tmin_pipe_s = String(t_min, 2);
      tmax_pipe_s = String(t_max, 2);
   }
   else
      range_errors++;

   // Only publish data as events every 5 minutes
   static uint32_t last_publish=0;  // seconds since the unix epoch
   if (Time.now() - last_publish > 300)
   {
      String msg =
         "t_photon:" + t_photon_s +
         ", t_ambient:" + t_ambient_s +
         ", tmin_pipe:" + tmin_pipe_s +
         ", tmax_pipe:" + tmax_pipe_s +
         ", read_errors:" + String(read_errors) +
         ", range_errors:", String(range_errors);
      Particle.publish(msg, PRIVATE);
      last_publish = Time.now();
   }
}
