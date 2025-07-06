#include "app_parameters.h"
#include <Stream.h>


bool AppParametersParser::serialize(const AppParameters& params, Stream& stream)
{
  StaticJsonDocument<512> doc;
  
  JsonObject wifi = doc.createNestedObject("Wifi");
  wifi["Ssid"] = params.Wifi.Ssid;
  wifi["Pass"] = params.Wifi.Pass;

  JsonObject totp = doc.createNestedObject("Totp");

  totp["Name"] = params.Totp.Name;
  totp["Period"] = params.Totp.Period;
  totp["Secret"] = params.Totp.Secret;

  return serializeJson(doc, stream) != 0;
}