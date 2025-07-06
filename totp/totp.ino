// TODO: use NTPCLient library
// TODO: use SPIFFS for secret configuration/loading
// TODO: load time/secret/wifi from file or load time from ntp
// TODO: OTP countdown (e.g. dots under name or behind?)

#include "defines.h"
#include "includes.h"
#include "constants.h"
#include "globals.h"
#include "methods.h"

void setup(void)
{
  Serial.begin(115200);

  while (!Serial)
  {
    delay(serialWaitDelay);
  }

  if (!appSettings.init())
  {
    Serial.println("Failed to load app settings.");
  }

  SPI.begin(EPD_SCLK, EPD_MISO, EPD_MOSI);

  renderer.init();

  String wellcomeText = "DON'T PANIC!"; 
  renderer.renderTextScreenCentered(&wellcomeText);
  renderer.show();

  setupCurrentTime(appSettings.get().Wifi);
}

void loop()
{
  time_t t = time(NULL);

  if (t < 1000000) {

    Serial.println("Not having a stable time yet.. TOTP is not going to work.");

    delay(1000);
    
    return;
  };

  const TotpParameters& totpParams = appSettings.get().Totp;

  String* otp = TOTP::currentOTP(totpParams.Secret);

  Serial.print(ctime(&t));
  Serial.print("   TOTP at this time is: ");
  Serial.println(*otp);
  Serial.println(currentOtp == nullptr ? "<null>" : *currentOtp);
  Serial.println();

  if (currentOtp == nullptr || *currentOtp != *otp)
  {
    renderer.renderTextScreenCentered(otp);
    renderer.show();

    String* tmp = currentOtp;
    currentOtp = otp;
    otp = tmp;
  }

  if (otp != nullptr)
  {
    delete otp;
  }

  int seconds = getSecondsOfMinute(t);

  int delayMs = (totpParams.Period - seconds % totpParams.Period) * 500; // to ms div 2 (exponential decrease)
  Serial.println(delayMs);

  delay(delayMs);
}
