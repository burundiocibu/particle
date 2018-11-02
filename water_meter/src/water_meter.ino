// Please see water_meter/README.md

#include <map>
#include <utility>
#include <vector>
#include "HRE_Reader.h"

// define pin useage to interface to the meter
const int hre_clk = D0;
const int hre_data = D1;
HRE_Reader reader(hre_clk, hre_data);

// This is the amount counted on the previous register.
// (the mechanical Recordall unit that was intsalled with the system)
const double prior_usage = 167490.11;


// These vars are strings because the way doubles display on
// homeassistant: full precision. 
String total_usage_s; // total usage in galons
String flow_rate_s;   // instantaneous flow in galons per minute
String hour_usage_s;  // usage in the current hour
String day_usage_s;   // usage for current day
String week_usage_s;  // usage for current week
String month_usage_s; // usage for current month

typedef std::pair<unsigned long, double> Obs;
typedef std::map<unsigned long, unsigned long> History;

// These are intended to store the useage at the start
// of the indicated time
retained Obs obs_hour, obs_day, obs_week, obs_month, obs_user;


void setup()
{
   // Current meter reading, in gallons
   Particle.variable("total_usage", total_usage_s);
   // Instantanious flow rate, in gallons per minute
   Particle.variable("flow_rate",  flow_rate_s);
   // total number of HRE read errors since device start
   Particle.variable("read_errors", reader.read_errors);

   // Usage since various times
   Particle.variable("hour_usage", hour_usage_s);
   Particle.variable("day_usage",  day_usage_s);
   Particle.variable("week_usage", week_usage_s);
   Particle.variable("month_usage", month_usage_s);
}


void loop()
{
   static unsigned long reads=0;
   static Obs curr, prev;

   if (!reader.read_block())
      return;
   reads++;
   
   prev = curr;
   curr.second = 0.01 * atol(reader.buff+24);
   curr.first = millis();

   if (reads<2)
      return;

   // Handle the system time counter wrapping around
   if (curr.first < prev.first)
      return;
   
   double total_usage = curr.second + prior_usage;
   total_usage_s = String(total_usage, 2);

   double use = curr.second - prev.second; // gallons
   double dt = 1.666e-5 * (curr.first - prev.first); // dt in minutes
   double flow_rate = use/dt; // gallons/min
   flow_rate_s = String(flow_rate, 3);
//   if (flow_rate > 0)
//      Particle.publish("rate", String(total_usage, 2) + " gal, " +
//                       String(flow_rate, 2) + " gpm, " +
//                       String(60 * dt, 2) + " sec" , PRIVATE);


   static int prev_hour=-1;
   if (Time.hour() != prev_hour)
   {
      String msg = "hour:" + hour_usage_s +
         ", day:" + day_usage_s +
         ", week:" + week_usage_s +
         ", month:" + month_usage_s;
      Particle.publish("usage",  msg, PRIVATE);
   }
   
   // useage for current hour
   if (Time.hour() != prev_hour)
   {
      obs_hour.first = Time.now();
      obs_hour.second = total_usage;
      prev_hour = Time.hour();
   }
   hour_usage_s = String(total_usage - obs_hour.second, 2);

   // useage for current day
   static int prev_day = -1;
   if (Time.day() != prev_day)
   {
      obs_day.first = Time.now();
      obs_day.second = total_usage;
      prev_day = Time.day();
   }
   day_usage_s = String(total_usage - obs_day.second, 1);

   // useage for current week
   static int prev_weekday = -1;
   if (prev_weekday == -1 || (Time.weekday() != prev_weekday && prev_weekday == 7))
   {
      obs_week.first = Time.now();
      obs_week.second = total_usage;
      prev_weekday = Time.weekday();
   }
   week_usage_s = String(total_usage - obs_week.second, 1);

   // usage for current month
   static int prev_month = -1;
   if (Time.month() != prev_month)
   {
      obs_month.first = Time.now();
      obs_month.second = total_usage;
      prev_month = Time.month();
   }
   month_usage_s = String(total_usage - obs_month.second, 1);

}
