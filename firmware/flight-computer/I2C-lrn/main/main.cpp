#include <cstdint>
#include <stdio.h>
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "ROCKET_IMU";

class MPU6050 {
private:
  i2c_master_bus_handle_t _bus_handle;
  i2c_master_dev_handle_t _dev_handle;
  uint8_t _address;

public:
  MPU6050(uint8_t addr) : _address(addr) {};
  esp_err_t init();
  uint8_t who_am_i();
};

extern "C" void app_main() {
  MPU6050 imu(0x68);
  esp_err_t ret = imu.init();
  if (ret == ESP_OK) {
    ESP_LOGI(TAG, "I2C Bus and MPU6050 Initialised.");
    uint8_t id = imu.who_am_i();

    if (id == 0x68) {
      ESP_LOGI(TAG, "Success! MPU6050 ID matches: 0x%02X", id);
    } else {
      ESP_LOGE(TAG, "Device found, but ID 0x%02X is wrong. Check AD0 pin.", id);
    }
  } else {
    ESP_LOGE(TAG, "Failed to initialise I2C. Error: %s", esp_err_to_name(ret));
  }

  while(1) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}


esp_err_t MPU6050::init() {
  // 1. Bus Config
  i2c_master_bus_config_t bus_cfg = {
    .i2c_port = I2C_NUM_0,
    .sda_io_num = GPIO_NUM_21,
    .scl_io_num = GPIO_NUM_22,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .flags = {.enable_internal_pullup = true}
  };
  ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &_bus_handle));

  // 2. Device Config
  i2c_device_config_t dev_cfg = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address = _address,
    .scl_speed_hz = 100000,
  };
  return i2c_master_bus_add_device(_bus_handle, &dev_cfg, &_dev_handle);
}

uint8_t MPU6050::who_am_i() {
  uint8_t reg = 0x75;
  uint8_t data = 0;
  // Transmit register addr, receive 1 byte of data
  i2c_master_transmit_receive(_dev_handle, &reg, 1, &data, 1, -1);
  
  return data;
}
