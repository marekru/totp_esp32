## Configuration

- configuration via web server:
  - wifi in AP (Access Point) Mode with baked in password:
    https://randomnerdtutorials.com/esp32-access-point-ap-web-server/
  - webserver with html gui allowing to upload QR code or otp 'link'
  - or just webserver recieving json, and json will be create in local app?
  - best would be some mobile app, but that would be overkill

- configuration via spiffs: (https://coolplaydev.com/esp32-spiffs-file-uploads-without-arduino-ide)
  - create spiffs from files using mkspiffs (https://github.com/igrr/mkspiffs)
  - upload spiffs using esptool  (python thingie meh (pip install esptool))
    - `esptool --chip esp32 --port COM4 --baud 460800 write_flash 0x290000 spiffs.bin`

- configuration via sd card:
  - use SD library to read file from sd-card
  - json format same as for web server
  - https://forum.arduino.cc/t/read-sd-card-file-and-put-values-into-variables/644367/10
  - store into preferences

(https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/)
- configuraiton via USB:
  - pyserial
  - e.g. from chatgpt but json format would be probably easier
  ```python
    import serial
    ser = serial.Serial('COM3', 115200)
    ser.write(b'SET_TIME:2025-06-11T12:00:00\n')
    ser.write(b'SET_WIFI:MySSID,MyPassword\n')
    ser.write(b'SET_SECRET:apikey123456\n')
    ser.close()
  ```

  ```c
  void setup() {
    Serial.begin(115200);
  }

  void loop() {
    if (Serial.available()) {
      String input = Serial.readStringUntil('\n');
      if (input.startsWith("SET_TIME:")) {
        String timeStr = input.substring(9);
        // parse and apply time
      } else if (input.startsWith("SET_WIFI:")) {
        // store WiFi credentials
      } else if (input.startsWith("SET_SECRET:")) {
        // store secret
      }
    }
  }
  ```

- bluetooth?
  - Implement GATT server on ESP32???


#### Using preferencies:

```c
#include <Preferences.h>

Preferences prefs;

void setup() {
  Serial.begin(115200);

  // Start preferences with a namespace
  prefs.begin("config", false);

  // Store data
  prefs.putString("wifi_ssid", "MySSID");
  prefs.putString("wifi_pass", "MyPassword");
  prefs.putInt("timezone", 2);

  // Read data
  String ssid = prefs.getString("wifi_ssid", "defaultSSID");
  int tz = prefs.getInt("timezone", 0);

  Serial.println("SSID: " + ssid);
  Serial.println("Timezone: " + String(tz));

  prefs.end();  // Close session to free memory
}

void loop() {}
```

#### JSON Condig

```json
{
  "wifi":{
    "ssid": "",
    "pass": "",
  },
  "codes":[
    {
      "name": "",
      "secret": "", // base32 format
      "refresh_interval": 30,
    }
  ],
  "time": "",
  "timezone": "",
}
```


### OTP transfer
- decode otpauth-migration link: (https://github.com/dim13/otpauth) or (https://github.com/digitalduke/otpauth-migration-decoder) or (https://github.com/yehudah/google-authenticator-exporter)
- qr code reader



# Case
- https://www.printables.com/model/412141-lilygo-ttgo-t5-213-case
- https://www.thingiverse.com/thing:5991134
- https://www.thingiverse.com/thing:4209788


# Time sync

- RTC
  - https://www.theelectronics.co.in/2022/04/how-to-use-internal-rtc-of-esp32.html
  - https://forum.arduino.cc/t/esp32-internal-rtc-date/695185/3


# First Iteration:
  
## Setup

  - [x] credential storage (interface)
  - [x] loading credentials from SD card
  - wifi time sync

## Visualization
  - support for one OTP (or multiple on one display)
  - display progress OTP bar (dots?)
  - OTP name
  - mode icon

# Second Iteration

## Setup
  - AP mode on button
  - button to navigate
  - select wifi

## Visualization
  - multiple OTP support
  - fonts rendering