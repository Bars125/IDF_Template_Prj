// Multipurpose variables
#define Record_Button 27                              // record audio while holding a button
#define THRESHOLD 40                                  // Greater the value, more the sensitivity on the wake-up Pin
#define wifi_state_led 26                             // Wifi status LED
#define record_state_led 14                           // Recording audio
#define customDelay(ms) vTaskDelay(pdMS_TO_TICKS(ms)) // Macros TICKS to ms

// INMP 441 Connection ports
#define I2S_SD GPIO_NUM_32
#define I2S_WS GPIO_NUM_25
#define I2S_SCK GPIO_NUM_33

// Recording variables
#define I2S_PORT I2S_NUM_0
#define I2S_SAMPLE_RATE 16000
#define I2S_SAMPLE_BITS 16
#define I2S_READ_LEN (I2S_SAMPLE_BITS * 1024)
#define RECORD_TIME 5 // Record N seconds
#define I2S_CHANNEL_NUM 1
#define FLASH_RECORD_SIZE (I2S_CHANNEL_NUM * I2S_SAMPLE_RATE * I2S_SAMPLE_BITS / 8 * RECORD_TIME)

// Libraries
#include <stdio.h>
#include <string.h>
#include "driver/gpio.h"
#include "freertos/freeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "network_param.h"
#include "esp_log.h"

// global variables
// File file;
const char filename[] = "/recording.wav";
const int headerSize = 44;
bool isWIFIConnected = false;
bool isRecorded = false;

// func prototypes
void connectToWiFi();

void app_main(void)
{
    gpio_set_direction(GPIO_NUM_26,GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_26, 0);
    connectToWiFi();
    customDelay(1000);
    gpio_set_level(GPIO_NUM_26, 0);
}

void connectToWiFi()
{
    if (strlen(WIFI_SSID) == 0 || strlen(WIFI_PASSWORD) == 0)
    {
        ESP_LOGE("WiFi", "Invalid WiFi credentials!");
        return;
    }

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_storage(WIFI_STORAGE_RAM);

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASSWORD,
        },
    };

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    esp_wifi_start(); // выполняется асинхронно

    /*int attempts = 0;
    wifi_mode_t mode;
    while ((esp_wifi_get_mode(&mode) == ESP_OK) && (mode == WIFI_MODE_STA) &&
           (esp_wifi_connect() != ESP_OK) && (attempts < 10))
    {
        ESP_LOGI("WiFi", "Connecting to WiFi...");
        customDelay(1000);
        attempts++;
    }

    if (attempts < 10)
    {
        ESP_LOGI("WiFi", "Connected to WiFi... %s", WIFI_SSID);
        gpio_set_level(GPIO_NUM_26, 1);
    }
    else
    {
        esp_wifi_stop();
        ESP_LOGE("WiFi", "Failed to connect to WiFi!");
    }*/
}
