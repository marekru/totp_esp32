#ifndef STORAGE_H
#define STORAGE_H

#include <app_parameters.h>

class IAppSettingsStorage 
{
  public:
    virtual bool init() = 0;
    virtual std::optional<AppParameters> load() = 0;
    virtual bool save(const AppParameters& params) = 0;
};

//////
class FSAppSettingsStorage : public IAppSettingsStorage
{
  const char* _filePath = NULL;
  public:
    FSAppSettingsStorage(const char* filePath) : _filePath(filePath) {}
    bool init() override;
    std::optional<AppParameters> load() override;
    bool save(const AppParameters& params) override;
};

//////
class SDAppSettingsStorage : public IAppSettingsStorage
{
  const char* _filePath = NULL;
  public:
    SDAppSettingsStorage(const char* filePath) : _filePath(filePath) {}
    bool init() override;
    std::optional<AppParameters> load() override;
    bool save(const AppParameters& params) override;
};

#endif // STORAGE_H
