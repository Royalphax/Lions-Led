//
// Created by Therence on 22/05/2021.
//

#ifndef LIONS_LED_2_LEDMANAGER_H
#define LIONS_LED_2_LEDMANAGER_H

#include <FastLED.h>
#include <ColorManager.h>
#include <AnimationList.h>
#include "DriveMode.h"
#include "LedSegment.h"

#define MAX_LED_SEGMENTS 3
#define SCROLLING_DELAY_NORMAL 20
#define SCROLLING_DELAY_FAST   10
#define SCROLLING_DELAY_STAY   200

class LedManager {
private:
    CRGB * led;
    int size;
    ColorManager color;
    AnimationList animationList;
    DriveMode * driveMode;
    LedSegment * ledSegment[MAX_LED_SEGMENTS];

public:

    LedManager(CRGB * led, const int size, DriveMode *driveMode);
    void begin();
    void startEngine();
    void loop();
    void stopEngine();
    bool isInSegment(const int i);

    void stopLight();
    void rightLight();
    void leftLight();
    void warnLight();
    void backLight();

    CRGB *getLed() const;
    void setLed(CRGB * led);
    int getSize() const;
    void setSize(int size);
    const ColorManager &getColor() const;
    void setColor(const ColorManager &color);
};


#endif //LIONS_LED_2_LEDMANAGER_H
