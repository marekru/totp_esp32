#include "methods.h"

#ifndef NTP_SERVER
#define NTP_SERVER "nl.pool.ntp.org"
#warning "You MUST set an appropriate ntp pool - see http://ntp.org"
#endif

// TODO: default timezone
#ifndef NTP_DEFAULT_TZ
#define NTP_DEFAULT_TZ "CET-1CEST,M3.5.0,M10.5.0/3"
#endif

#include <WiFi.h>
#include <SD.h>
#include "constants.h"
//#include "globals.h"

void setupCurrentTime(const WifiParameters& wifiParams)
{
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(wifiParams.Ssid, wifiParams.Pass, 6);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(wifiWaitDelay);
  }
  
  // we need a reasonable accurate time for TOTP to work.
  configTzTime(NTP_DEFAULT_TZ, NTP_SERVER);
}

int getSecondsOfMinute(time_t t_time) 
{
    struct tm* timeinfo = localtime(&t_time);
    return timeinfo->tm_sec;
}

void listDir(const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = SD.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }

  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(file.name(), levels - 1);
      }
    } else {
      Serial.print("FILE: ");
      Serial.print(file.name());
      Serial.print("\tSIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}
