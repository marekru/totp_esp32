#ifndef METHODS_H
#define METHODS_H


#include "wifi_parameters.h"

void setupCurrentTime(const WifiParameters& wifiParams);

int getSecondsOfMinute(time_t t_time);

void listDir(const char *dirname, uint8_t levels);

#endif // METHODS_H