#include <app_settings_storage.h>

#include <FS.h>
#include <LittleFS.h>
#include <SD.h>

bool FSAppSettingsStorage::init()
{
   if (!LittleFS.begin()) 
   {
    Serial.println("LittleFS mount failed. Formatting...");
    
    LittleFS.format();
    return LittleFS.begin();
  }

  return true;
}

std::optional<AppParameters> FSAppSettingsStorage::load()
{
  if (!LittleFS.exists(_filePath)) 
  {
    Serial.println("Settings file not found in LittleFS.");
    return std::nullopt;
  }

  File file = LittleFS.open(_filePath, "r");
  
  if (!file) 
  {
    Serial.println("Failed to open settings file.");
    return std::nullopt;
  }

  std::optional<AppParameters> result = AppParametersParser::parse(file);
  
  file.close();

  return result;
}

bool FSAppSettingsStorage::save(const AppParameters& params)
{
  File file = LittleFS.open(_filePath, "w");

  if (!file) 
  {
    Serial.println("Failed to create settings file on LittleFS.");
    return false;
  }

  if (!AppParametersParser::serialize(params, file)) 
  {
    Serial.println("Failed to write to settings file.");
    file.close();

    return false;
  }

  file.close();
  Serial.println("Settings saved to LittleFS.");

  return true;
}

bool SDAppSettingsStorage::init()
{
  return SD.begin();
}

std::optional<AppParameters> SDAppSettingsStorage::load()
{
  if (!SD.exists(_filePath)) 
  {
    Serial.println("Settings file not found in SD.");
    return std::nullopt;
  }

  File file = SD.open(_filePath, "r");
  
  if (!file) 
  {
    Serial.println("Failed to open settings file.");
    return std::nullopt;
  }

  std::optional<AppParameters> result = AppParametersParser::parse(file);
  
  file.close();

  return result;
}

bool SDAppSettingsStorage::save(const AppParameters& params)
{
  File file = SD.open(_filePath, "w");
  
  if (!file) 
  {
    Serial.println("Failed to create settings file on SD.");
    return false;
  }

  if (!AppParametersParser::serialize(params, file)) 
  {
    Serial.println("Failed to write to settings file.");
    file.close();

    return false;
  }

  file.close();
  Serial.println("Settings saved to SD.");

  return true;
}