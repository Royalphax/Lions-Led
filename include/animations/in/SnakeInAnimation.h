//
// Created by Therence on 22/05/2021.
//

#ifndef LIONS_LED_2_SNAKEINANIMATION_H
#define LIONS_LED_2_SNAKEINANIMATION_H

#include <Animation.h>
#include <LedManager.h>

class SnakeInAnimation : public Animation {
private:
    LedManager * ledManager;
public:
    SnakeInAnimation(LedManager *ledManager) : Animation(IN) {
        SnakeInAnimation::ledManager = ledManager;
    }

    void animate() const {
        CRGB *led = ledManager->getLed();
        ColorManager color = ledManager->getColor();
        int NUM_LED = ledManager->getSize();
        int HALF_LED = NUM_LED / 2;
        int MAX_LED = NUM_LED - 1;

        for (int i = 0; i < NUM_LED; i++) {

            int y = HALF_LED - abs(i - HALF_LED);
            int z = 3 + (y * 10 / HALF_LED);

            for (int x = 0; x < z; x++) if (inRange(i + x, 0, NUM_LED)) led[i + x] = color.FULL_RED;
            for (int x = 0; x < z; x++) if (inRange(MAX_LED - i - x, 0, NUM_LED)) led[MAX_LED - i - x] = color.FULL_RED;

            FastLED.show();

            if (i < HALF_LED) {
                for (int x = 0; x < z; x++) if (inRange(i + x, 0, NUM_LED)) led[i + x] = CRGB::Black;
                for (int x = 0; x < z; x++) if (inRange(MAX_LED - i - x, 0, NUM_LED)) led[MAX_LED - i - x] = CRGB::Black;

                delay(15 + (z - 3) * 3);
            } else {
                for (int x = 0; x < z; x++) {
                    if (inRange(i + x, 0, NUM_LED)) {
                        if (ledManager->isInSegment(i + x)) {
                            led[i + x] = color.RED;
                        } else {
                            led[i + x] = CRGB::Black;
                        }
                    }
                }
                for (int x = 0; x < z; x++) {
                    if (inRange(MAX_LED - i - x, 0, NUM_LED)) {
                        if (ledManager->isInSegment(MAX_LED - i - x)) {
                            led[MAX_LED - i - x] = color.RED;
                        } else {
                            led[MAX_LED - i - x] = CRGB::Black;
                        }
                    }
                }

                delay(15 + (z - 3));
            }
        }
        FastLED.show();
    };
};


#endif //LIONS_LED_2_SNAKEINANIMATION_H
