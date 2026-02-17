# AccessPoint

Simple C++ wrapper for running a Wi-Fi SoftAP on ESP32 using ESP-IDF.

This class handles:

- SSID
- Password
- Max number of connections
- Hidden mode
- Starting and stopping the AP

It wraps the `esp_wifi_*` API and applies the configuration internally.

---

## What It Does

- Stores AP configuration
- Fills `wifi_config_t`
- Sets authentication mode automatically
- Starts and stops the access point
- Logs basic status messages

If the password is empty, authentication mode is set to `WIFI_AUTH_OPEN`.  
Otherwise, `WIFI_AUTH_WPA_WPA2_PSK` is used.

---

## Important: Required Initialization

Before calling `AccessPoint::start()`, you **must** initialize:

- NVS
- TCP/IP stack
- Event loop
- Wi-Fi driver
- Wi-Fi mode (AP)

Minimal setup example:

```cpp
// Initialize NVS
esp_err_t ret = nvs_flash_init();
if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
}
ESP_ERROR_CHECK(ret);

// Initialize network stack
ESP_ERROR_CHECK(esp_netif_init());
ESP_ERROR_CHECK(esp_event_loop_create_default());
esp_netif_create_default_wifi_ap();

// Initialize Wi-Fi
wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
ESP_ERROR_CHECK(esp_wifi_init(&cfg));
ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
```

After this setup, you can use:

```cpp
AccessPoint ap;
ap.start();
```

Basic Usage
```cpp
AccessPoint ap("MyAP", "mypassword", 4, false);
ap.start();
```

To stop:

```cpp
ap.stop();
```

## Notes

SSID and password are stored as raw pointers (no deep copy).

Strings must remain valid while the AP is running.

No password validation is performed.

Wi-Fi must already be initialized before calling start().

This component is intended for simple SoftAP setups such as provisioning or local device configuration.