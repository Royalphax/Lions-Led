//
// Created by Therence on 22/05/2021.
//

#ifndef LIONS_LED_2_ANIMATION_H
#define LIONS_LED_2_ANIMATION_H

#include <FastLED.h>

enum AnimationType {
    IN, OUT
};

class Animation {

private:
    AnimationType type;

public:
    Animation(const AnimationType type);
    bool is(const AnimationType type) const;
    AnimationType getType() const;
    static bool inRange(const int x, const int low, const int high);

    virtual void animate() const = 0;
};


#endif //LIONS_LED_2_ANIMATION_H
