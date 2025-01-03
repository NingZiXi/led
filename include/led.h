#ifndef LED_H
#define LED_H

#include "driver/gpio.h"
#include "driver/ledc.h"

#ifdef __cplusplus
extern "C" {
#endif

class Led {
public:
    // 构造函数
    Led(gpio_num_t pin, ledc_channel_t channel);
    // 初始化LED
    void init();
    // 点亮LED
    void on();
    // 熄灭LED
    void off();
    // 设置LED亮度
    void setBrightness(uint32_t duty);
    // 呼吸效果
    void breath(uint32_t fade_time_ms);
    // 停止呼吸效果
    void stopBreath();

private:
    gpio_num_t m_pin;
    ledc_channel_t m_channel;
    ledc_timer_t m_timer;
    ledc_mode_t m_mode;
    uint32_t m_duty_resolution;
    uint32_t m_frequency;
};

#ifdef __cplusplus
}
#endif

#endif // LED_H

