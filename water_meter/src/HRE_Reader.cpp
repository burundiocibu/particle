#include "Particle.h"
#include "HRE_Reader.h"

// The meter returns ascii text something like
//KG44?Q45484=0444444V;RB000000022;IB018435683
// where the RB...; is the miligalons used


HRE_Reader::HRE_Reader(int _clock, int _data):
   parity_errors(0), msg_good(false), read_errors(0),
   clock(_clock), data(_data)
{
   pinMode(clock, OUTPUT);
   pinMode(data, INPUT);

   // Note that the level shifter inverts this line and we want to leave it
   // high when not being read.
   digitalWrite(clock, LOW);
}


int HRE_Reader::read_bit() const
{
   digitalWrite(clock, HIGH);
   delay(2);
   int bit=digitalRead(data);
   digitalWrite(clock, LOW);
   delay(2);
   return bit;
}

char HRE_Reader::read_char()
{
   // toss the start bit
   read_bit();

   char ch=0;
   int parity=0;
   for (int i=0; i<7; i++)
   {
      int b = read_bit();
      ch |= b << i;
      parity += b;
   }

   if (parity==read_bit())
      parity_errors++;

   // and toss the stop bit
   read_bit();

   return ch;
}

bool HRE_Reader::read_block()
{
   parity_errors = 0;

   // First find the header
   int run=0;
   while (run < 62)
    if (read_bit()) run++;
    else run=0;

   memset(buff, 0, sizeof(buff));
   for (int i=0; i<46; i++)
      buff[i] = read_char();
   msg_good = parity_errors == 0;

   if (!msg_good)
      read_errors++;
   
   return msg_good;
}
