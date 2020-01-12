RGB_MATRIX_EFFECT(ONLY_CAPS)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool ONLY_CAPS(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV hsv  = rgb_matrix_config.hsv;
    RGB rgb1 = hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color(i, rgb1.r, rgb1.g, rgb1.b);
        } else {
            rgb_matrix_set_color_all(0, 0, 0);
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
