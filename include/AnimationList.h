//
// Created by Therence on 22/05/2021.
//

#ifndef LIONS_LED_2_LISTEANIMATION_H
#define LIONS_LED_2_LISTEANIMATION_H

#include "Animation.h"

#define NB_MAX_ANIMATIONS 50

class AnimationList {

private:
    Animation * inAnimations[NB_MAX_ANIMATIONS];
    int nbInAnimations;

    Animation * outAnimations[NB_MAX_ANIMATIONS];
    int nbOutAnimations;

public:
    void add(Animation * animation);
    Animation * getRandom(const AnimationType type);
};


#endif //LIONS_LED_2_LISTEANIMATION_H
