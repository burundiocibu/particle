// jcl library by Jon Little
//
// This is a refactoring of the DS18 class to provide more functionality tou help
// managing bunch of them on a single buss
//
#pragma once

#include "Particle.h"
#include "OneWire.h"

namespace jcl
{
   String addr_to_String(const uint8_t addr[]);

   enum DS18Type
   {
      WIRE_UNKNOWN,
      WIRE_DS1820,
      WIRE_DS18B20,
      WIRE_DS1822,
      WIRE_DS2438
   };

   class DS18
   {
     public:
      DS18(uint16_t pin, bool parasitic = false);

      bool read();
      bool read(uint8_t addr[8]);
      bool read(uint8_t addr[8], int maxRetry);
      int16_t raw() const;
      float celsius() const;
      float fahrenheit() const;
      void getAddr(uint8_t dest[8]) const;
      void getData(uint8_t dest[9]) const;
      DS18Type type() const;

      String dump() const;

      bool searchDone() const;
      bool crcError() const;
      bool getRetryCount() const {return _retryCount;}

      void setConversionTime(uint16_t ms);

     private:
      void init();

      OneWire _wire;
      bool _parasitic;
      uint16_t _conversionTime;
      int16_t _raw;
      float _celsius;
      uint8_t _addr[8];
      uint8_t _data[9];
      DS18Type _type;
      bool _searchDone;
      bool _crcError;

      int _retryCount;
   };

}
