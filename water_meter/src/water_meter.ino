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

double total_usage; // total usage in galons
double flow_rate;   // instantaneous flow in galons per minute
double hour_usage;  // usage in the current hour
double day_usage;   // usage for current day
double week_usage;  // usage for current week
double month_usage; // usage for current month

typedef std::pair<unsigned long, double> Obs;
typedef std::map<unsigned long, unsigned long> History;

// These are intended to store the useage at the start
// of the indicated time
retained Obs obs_hour, obs_day, obs_week, obs_month, obs_user;


void setup()
{
   // Current meter reading, in gallons
   Particle.variable("total_usage", total_usage);
   // Instantanious flow rate, in gallons per minute
   Particle.variable("flow_rate",  flow_rate);
   // total number of HRE read errors since device start
   Particle.variable("read_errors", reader.read_errors);

   // Usage since various times
   Particle.variable("hour_usage", hour_usage);
   Particle.variable("day_usage",  day_usage);
   Particle.variable("week_usage", week_usage);
   Particle.variable("month_usage", month_usage);
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
   
   total_usage = curr.second + prior_usage;

   double use = curr.second - prev.second; // gallons
   double dt = 1.666e-5 * (curr.first - prev.first); // dt in minutes
   flow_rate = use/dt;  // gallons per minute
   if (flow_rate > 0)
      Particle.publish("rate", String(total_usage, 2) + " gal, " +
                       String(flow_rate, 2) + " gpm, " +
                       String(60 * dt, 2) + " sec" , PRIVATE);


   // useage for current hour
   static int prev_hour=-1;
   if (Time.hour() != prev_hour)
   {
      String msg = "hour:" + String(hour_usage, 2) +
         ", day:" + String(day_usage, 0) +
         ", week:" + String(week_usage, 0) +
         ", month:" + String(month_usage, 0);
      Particle.publish("usage",  msg, PRIVATE);
   }
   
   if (Time.hour() != prev_hour)
   {
      obs_hour.first = Time.now();
      obs_hour.second = total_usage;
      prev_hour = Time.hour();
   }
   hour_usage = total_usage - obs_hour.second;

   // useage for current day
   static int prev_day = -1;
   if (Time.day() != prev_day)
   {
      obs_day.first = Time.now();
      obs_day.second = total_usage;
      prev_day = Time.day();
   }
   day_usage = total_usage - obs_day.second;

   // useage for current week
   static int prev_weekday = -1;
   if (prev_weekday == -1 || (Time.weekday() != prev_weekday && prev_weekday == 7))
   {
      obs_week.first = Time.now();
      obs_week.second = total_usage;
      prev_weekday = Time.weekday();
   }
   week_usage = total_usage - obs_week.second;

   // usage for current month
   static int prev_month = -1;
   if (Time.month() != prev_month)
   {
      obs_month.first = Time.now();
      obs_month.second = total_usage;
      prev_month = Time.month();
   }
   month_usage = total_usage - obs_month.second;

}
