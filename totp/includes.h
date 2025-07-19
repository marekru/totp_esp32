#ifndef INCLUDES_H
#define INCLUDES_H

#define LILYGO_T5_V213

// TODO: #include <NTPClient.h> see TOTP library example
#include <TOTP-RC6236-generator.hpp>

#include <boards.h>
#include <GxEPD.h>

#include <GxDEPG0213BN/GxDEPG0213BN.h>    // 2.13" b/w  form DKE GROUP

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include <renderer.h>
#include <app_settings_mngr.h>

#endif // INCLUDES_H

