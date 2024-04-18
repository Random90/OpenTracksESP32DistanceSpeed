#include <stdio.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

static const char *TAG = "OTDS Main";

#define BLINK_GPIO 10

static uint8_t s_led_state = 0;

static void blinkLed(void) { gpio_set_level(BLINK_GPIO, s_led_state); }

static void configureLed(void) {
  gpio_reset_pin(BLINK_GPIO);
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

static void startBlinkLoop() {
  while (1) {
    ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
    blinkLed();
    s_led_state = !s_led_state;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void app_main(void) {
  configureLed();
  startBlinkLoop();
}
