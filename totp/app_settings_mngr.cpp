#include "app_settings_mngr.h"
#include "app_settings_storage.h"

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
    return false;
  }

  if (!_externalStorage->init())
  {
    return false;
  }

  std::optional<AppParameters> internalAppParams = _internalStorage->load();
  
  // TODO: force rewrite internal params!!!
  if (internalAppParams.has_value())
  {
    _settings = internalAppParams.value();
    return true;
  }
  else 
  {
    std::optional<AppParameters> externalAppParams = _externalStorage->load();
    
    if (externalAppParams.has_value())
    {
      if (!_internalStorage->save(externalAppParams.value()))
      {
        // TODO: log error
        return false;
      }

      _settings = externalAppParams.value();
      return true;
    }
  }

  return false;
}