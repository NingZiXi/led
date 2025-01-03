# LED 控制库

这个库提供了一种简单且高效的方式来使用 ESP32 微控制器控制 LED。它支持基本的 LED 操作，如点亮和熄灭 LED、设置亮度以及创建呼吸效果。该库专为 ESP-IDF 框架设计。

## 功能

- **初始化**: 使用特定的 GPIO 引脚和 LEDC 通道初始化 LED。
- **开关控制**: 轻松地打开和关闭 LED。
- **亮度设置**: 设置 LED 的亮度。
- **呼吸效果**: 创建 LED 的呼吸效果。

## 安装

1. 将 `Led.h` 文件添加到你的 ESP-IDF 项目中。
2. 确保你的项目中包含了 ESP-IDF 框架，并且正确配置了 GPIO 和 LEDC 驱动。

## 使用方法

### 初始化 LED

首先，你需要创建一个 `Led` 类的实例，并调用 `init()` 方法来初始化 LED。

```cpp
#include "Led.h"

// 使用 GPIO 2 和 LEDC 通道 0 初始化 LED
Led myLed(GPIO_NUM_2, LEDC_CHANNEL_0);

void app_main() {
    myLed.init();
}
```

### 控制 LED

你可以使用 `on()` 和 `off()` 方法来打开和关闭 LED。

```cpp
void app_main() {
    myLed.init();

    while (1) {
        myLed.on();  // 打开 LED
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 延迟 1 秒
        myLed.off();  // 关闭 LED
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 延迟 1 秒
    }
}
```

### 设置亮度

使用 `setBrightness()` 方法来设置 LED 的亮度。亮度值的范围取决于 LEDC 的分辨率。

```cpp
void app_main() {
    myLed.init();

    while (1) {
        myLed.setBrightness(512);  // 设置亮度为 50%
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 延迟 1 秒
        myLed.setBrightness(1023);  // 设置亮度为 100%
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 延迟 1 秒
    }
}
```

### 呼吸效果

使用 `breath()` 方法来创建 LED 的呼吸效果。

```cpp
void app_main() {
    myLed.init();

    while (1) {
        myLed.breath(2000);  // 开始呼吸效果
    }
}
```

## 依赖

- ESP-IDF 框架
- `driver/gpio.h`
- `driver/ledc.h`

## 许可证

这个项目使用 MIT 许可证。有关更多信息，请参阅 `LICENSE` 文件。

