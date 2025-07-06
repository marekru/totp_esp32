#ifndef TOTP_PARAMS_H
#define TOTP_PARAMS_H

#include <Arduino.h> 

struct TotpParameters
{
  public:
    String Name;
    int Period; // in seconds
    String Secret; //base32
};


#endif // TOTP_PARAMS_H