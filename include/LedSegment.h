//
// Created by Therence on 23/05/2021.
//

#ifndef LIONS_LED_2_LEDSEGMENT_H
#define LIONS_LED_2_LEDSEGMENT_H

#include <FastLED.h>

class LedSegment {
private:
    CRGB *led;
    int lowBound;
    int highBound;

public:
    LedSegment(CRGB *led, int lowBound, int highBound) {
        LedSegment::led = led;
        LedSegment::lowBound = min(lowBound, highBound);
        LedSegment::highBound = max(lowBound, highBound);
    }

    void setColor(CRGB color) const {
        for (int i = lowBound; i < highBound; i++) {
            led[i] = color;
        }
    }

    bool isIn(const int i) {
        return (i >= lowBound && i < highBound);
    }

    int getLowBound() const {
        return lowBound;
    }

    int getHighBound() const {
        return highBound;
    }

    int getInterval() const {
        return highBound - lowBound;
    }
};

#endif //LIONS_LED_2_LEDSEGMENT_H
