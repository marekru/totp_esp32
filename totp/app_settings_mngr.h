#ifndef APP_SETTINGS_MNGR_H
#define APP_SETTINGS_MNGR_H

#include <app_settings_storage.h>
#include <memory>

class AppSettingsManager {
    AppParameters _settings;
    std::unique_ptr<IAppSettingsStorage> _internalStorage;
    std::unique_ptr<IAppSettingsStorage> _externalStorage;
  public:

    AppSettingsManager();

    const AppParameters& get() 
    {
      return _settings;
    };

    bool init();
};

#endif // APP_SETTINGS_MNGR_H
