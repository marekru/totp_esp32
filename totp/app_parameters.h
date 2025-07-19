#ifndef APP_PARAMS_H
#define APP_PARAMS_H

#include <wifi_parameters.h>
#include <totp_parameters.h>
#include <optional>
#include <ArduinoJson.h>

struct AppParameters
{
  public:
    WifiParameters Wifi;
    TotpParameters Totp;
    bool ForceConfigRewrite = false;
};

class AppParametersParser 
{
  public:
    template<typename T> static std::optional<AppParameters> parse(T json);
    static bool serialize(const AppParameters& params, Stream& stream);
};


template<typename T> std::optional<AppParameters> AppParametersParser::parse(T json)
{
  // Create a JSON document; adjust size depending on JSON complexity
  StaticJsonDocument<512> doc;

  DeserializationError error = deserializeJson(doc, json);
  
  if (error) 
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    
    return std::nullopt;
  }

  AppParameters params;

  // Parse Wifi parameters
  JsonObject wifi = doc["Wifi"];
  if (!wifi.isNull()) 
  {
    params.Wifi.Ssid = wifi["Ssid"] | "";
    params.Wifi.Pass = wifi["Pass"] | "";
  }

  // Parse Totp parameters
  JsonObject totp = doc["Totp"];
  if (!totp.isNull()) 
  {
    params.Totp.Name   = totp["Name"]   | "";
    params.Totp.Period = totp["Period"] | 30; // Default to 30 seconds
    params.Totp.Secret = totp["Secret"] | "";
  }

  params.ForceConfigRewrite = doc["ForceConfigRewrite"] | false;

  return params;
}



#endif // APP_PARAMS_H