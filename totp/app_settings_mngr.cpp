#include "app_settings_mngr.h"
#include "app_settings_storage.h"
#include "methods.h"

const char* SettingsPath = "/config.json";

AppSettingsManager::AppSettingsManager()
{
  _internalStorage = std::make_unique<FSAppSettingsStorage>(SettingsPath);
  _externalStorage = std::make_unique<SDAppSettingsStorage>(SettingsPath);
}

bool AppSettingsManager::init()
{
  if (!_internalStorage->init())
  {
    Serial.println("Failed to init internal storage.");
    
    return false;
  }

  std::optional<AppParameters> internalAppParams = _internalStorage->load();

  if (_externalStorage->init())
  {
    Serial.println("External storage initialized.");

    std::optional<AppParameters> externalAppParams = _externalStorage->load();

    // new params are available and (old are not available or we can rewrite it)
    if (externalAppParams.has_value() && (!internalAppParams.has_value() || externalAppParams.value().ForceConfigRewrite))
    {
      if (_internalStorage->save(externalAppParams.value()))
      {
        Serial.println("Saved new app settings to internal storage.");
        _settings = externalAppParams.value();
        return true;
      }
      else
      {
        Serial.println("Failed to save new app settings.");
      }
    }
  }
  else 
  {
    Serial.println("Failed to init external storage.");
  }

  if (internalAppParams.has_value())
  {
    Serial.println("Loaded app settings.");

    _settings = internalAppParams.value();
    return true;
  }

  return false;
}