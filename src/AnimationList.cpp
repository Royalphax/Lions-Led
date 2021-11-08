//
// Created by Therence on 22/05/2021.
//

#include "AnimationList.h"
#include <time.h>

void AnimationList::add(Animation * animation) {
    switch (animation->getType()) {
        case IN:
            if (nbInAnimations >= NB_MAX_ANIMATIONS)
                return;
            this->inAnimations[this->nbInAnimations] = animation;
            this->nbInAnimations++;
            break;
        case OUT:
            if (nbOutAnimations >= NB_MAX_ANIMATIONS)
                return;
            this->outAnimations[this->nbOutAnimations] = animation;
            this->nbOutAnimations++;
            break;
    }
}

Animation * AnimationList::getRandom(const AnimationType type) {
    srand(time(NULL));
    int rdm;
    switch (type) {
        case IN:
            rdm = (rand() % this->nbInAnimations);
            return this->inAnimations[rdm];
        case OUT:
            rdm = (rand() % this->nbOutAnimations);
            return this->outAnimations[rdm];
    }
    // Par defaut ???
    return this->inAnimations[0];
}
