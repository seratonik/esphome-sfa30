#include <SensirionI2CSfa3x.h>
#include <Wire.h>

SensirionI2CSfa3x sfa3x;

class SFA30 : public PollingComponent, public Sensor {
 public:
  // constructor
  SFA30() : PollingComponent(10000) {}
  Sensor *temperature_sensor = new Sensor();
  Sensor *hcho_sensor = new Sensor();
  Sensor *humidity_sensor = new Sensor();

  float get_setup_priority() const override { return esphome::setup_priority::BUS; }

  void setup() override {
    // This will be called by App.setup()
    
    Wire.begin();

    uint16_t error;
    char errorMessage[256];

    sfa3x.begin(Wire);

    // Start Measurement
    error = sfa3x.startContinuousMeasurement();
    if (error) {
        errorToString(error, errorMessage, 256);
        ESP_LOGD("error", errorMessage);
    }
  }
  void update() override {
    // This will be called every "update_interval" milliseconds.
    uint16_t error;
    char errorMessage[256];

    int16_t hcho;
    int16_t humidity;
    int16_t temperature;
    error = sfa3x.readMeasuredValues(hcho, humidity, temperature);
    if (error) {
       errorToString(error, errorMessage, 256);
       ESP_LOGD("error", errorMessage);
    } else {
        hcho_sensor->publish_state(hcho / 5.0);
        humidity_sensor->publish_state(humidity / 100.0);
        temperature_sensor->publish_state(temperature / 200.0);
    }
  }
};