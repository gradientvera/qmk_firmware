RGB_MATRIX_EFFECT(trans_flag)

//#define RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#define HUE(hue) (hue / 360.0 * 255.0)

bool trans_flag(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t blue_hue = HUE(197.0);
    uint8_t pink_hue = HUE(348.0);

    HSV     hsv   = rgb_matrix_config.hsv;
    uint8_t scale = scale8(64, rgb_matrix_config.speed);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        int16_t y = g_led_config.point[i].y;

        // Function key row
        if(y == 0) {
            // The x range will be 0..224, map this to 0..7
            // Relies on hue being 8-bit and wrapping
            hsv.h = rgb_matrix_config.hsv.h + (scale * g_led_config.point[i].x >> 5);
        } else {
            hsv.s = 255;
        }

        // Number row
        if(y == 15) {
            hsv.h = blue_hue;
        }

        // QWERTY row
        if(y == 27) {
            hsv.h = pink_hue;
        }

        // ASDFGH row
        if(y == 40) {
            hsv.s = 0;
        }

        // ZXCVBN row
        if(y == 52) {
            hsv.h = pink_hue;
        }

        // Spacebar row
        if(y == 64) {
            hsv.h = blue_hue;
        }

        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS

