
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
