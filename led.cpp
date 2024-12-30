#include "Led.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "Led";

// 构造函数
Led::Led(gpio_num_t pin, ledc_channel_t channel)
    : m_pin(pin), m_channel(channel), m_timer(LEDC_TIMER_0), m_mode(LEDC_LOW_SPEED_MODE),
      m_duty_resolution(LEDC_TIMER_13_BIT), m_frequency(5000) {}

// 初始化LED
void Led::init() {
    // 设置GPIO为输出模式
    gpio_reset_pin(m_pin);
    gpio_set_direction(m_pin, GPIO_MODE_OUTPUT);

    // 配置LEDC定时器
    ledc_timer_config_t ledc_timer = {
        .speed_mode = m_mode,
        .duty_resolution = static_cast<ledc_timer_bit_t>(m_duty_resolution),
        .timer_num = m_timer,
        .freq_hz = m_frequency,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // 配置LEDC通道
    ledc_channel_config_t ledc_channel = {
        .gpio_num = m_pin,
        .speed_mode = m_mode,
        .channel = m_channel,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = m_timer,
        .duty = 0, // 初始占空比为0
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel);
}

// 点亮LED
void Led::on() {
    ledc_set_duty(m_mode, m_channel, 8191); // 设置占空比为最大值，高电平点亮
    ledc_update_duty(m_mode, m_channel);
}

// 熄灭LED
void Led::off() {
    ledc_set_duty(m_mode, m_channel, 0); // 设置占空比为0，低电平熄灭
    ledc_update_duty(m_mode, m_channel);
}

// 设置LED亮度
void Led::setBrightness(uint32_t duty) {
    ledc_set_duty(m_mode, m_channel, duty); // 直接设置占空比
    ledc_update_duty(m_mode, m_channel);
}

// 呼吸效果
void Led::breath() {
    for (int duty = 0; duty < 8192; duty += 100) {
        setBrightness(duty);
        vTaskDelay(30 / portTICK_PERIOD_MS);
    }
    for (int duty = 8192; duty > 0; duty -= 100) {
        setBrightness(duty);
        vTaskDelay(30 / portTICK_PERIOD_MS);
    }
}
