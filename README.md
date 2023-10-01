# SFA30 Sensor Component for ESPHome

At the time of writing this, there is no native support in ESPHome for the
SFA30 series sensor, used for detecting Formaldehyde (HCHO). This sensor
is much less cross-sensitive than other cheaper sensors on the market,
giving more accurate results.

The included `sfa30.h` header file along with a sample yaml will get you
up and running, assuming you've wired your SFA30 sensor in I2C mode to your
ESP32.

The sensor includes an onboard humidity and temperature sensor as well to
aid in its internal algorithm, and those values are exposed through this
component in addition to the ppb formaldehyde levels.

Read about the SFA30 and find its datasheet here:
https://sensirion.com/products/catalog/SFA30

Custom Sensor Component follows the guide here:
https://esphome.io/components/sensor/custom

# Usage

Copy `sfa30.h` into the root of your ESPHome project, and add the following
to the `esphome:` section of your YAML file:

```yaml
esphone:
  # ...
  includes:
    - sfa30.h
  libraries:
    - "Wire"
    - "sensirion/Sensirion Core"
    - "sensirion/Sensirion I2C SFA3x"
```

Additionally under the `sensor:` section of that same YAML file, add:

```yaml
sensor:
  #...

  # Custom sensor definition to pull multiple values from the SFA30
  - platform: custom
    lambda: |-
      auto sfa30_sensor = new SFA30();
      App.register_component(sfa30_sensor);
      return {sfa30_sensor->temperature_sensor, sfa30_sensor->humidity_sensor, sfa30_sensor->hcho_sensor};

    sensors:
      - name: "Temperature Sensor"
        id: temp_1
        accuracy_decimals: 1
        unit_of_measurement: °C
      - name: "Humidity Sensor"
        accuracy_decimals: 1
        unit_of_measurement: "%"
        id: humid_1
      - name: "HCHO Sensor"
        accuracy_decimals: 1
        unit_of_measurement: ppb
        id: hcho_1
```

Feel free to customize the name and id of each of the sensors, but the lambda
must remain the same to match the properties in the .h file.

**Happy Sensing!**
