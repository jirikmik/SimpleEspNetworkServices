# SimpleEspNetworkServices
Simple wrapper for network services I often use in my "from-scratch" apps for ESP32. It initializes WifiMulti (10 possible SSIDs), ArduinoOTA and PubSubClient for MQTT.

*ArduinoOTA and PubSubClient can be disabled.*

**How to use:**
1. Add this library
2. Create and fill appconfig.h file in src directory (you can find it in examples)
3. Add include of appconfig.h to build flags in platformio.ini: `build_flags = -include "src/appconfig.h"`
