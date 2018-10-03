#pragma once

class HRE_Reader
{
public:
  int clock;
  int data;
  int parity_errors;
  int read_errors;
  bool msg_good;
  char buff[64];  // 46 bytes and a term.
  
  HRE_Reader(int _clock, int _data);
  //void init(int _clock, int _data);
  int read_bit() const;
  char read_char();
  bool read_block();
};
