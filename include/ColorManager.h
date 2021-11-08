//
// Created by Therence on 22/05/2021.
//

#ifndef LIONS_LED_2_COLORMANAGER_H
#define LIONS_LED_2_COLORMANAGER_H

#include <FastLED.h>
#include <math.h>

#define FADING 100

class ColorManager {
public:

    CHSV FULL_RED, RED;
    CHSV FULL_WHITE, WHITE;
    CHSV FULL_ORANGE, ORANGE;

    ColorManager() {
            FULL_RED = rgb2hsv_approximate(CRGB::Red);
            RED = FULL_RED;
            RED.v = FADING;
            FULL_WHITE = rgb2hsv_approximate(CRGB::White);
            WHITE = FULL_WHITE;
            WHITE.v = FADING;
            FULL_ORANGE = rgb2hsv_approximate(CRGB::OrangeRed);
            ORANGE = FULL_ORANGE;
            ORANGE.v = FADING;
    }

    CHSV getFading(const CRGB rgb, int position, int max) const {
        CHSV hsv = rgb2hsv_approximate(rgb);
        hsv.v = position * 255 / max;
        return hsv;
    }

    CHSV getExpFading(const CRGB rgb, double position, double max) const {
        double eMax = log(255.0);
        double eVal = position * eMax / max;

        CHSV hsv = rgb2hsv_approximate(rgb);
        hsv.v = exp(eVal);

        return hsv;
    }
};


#endif //LIONS_LED_2_COLORMANAGER_H
