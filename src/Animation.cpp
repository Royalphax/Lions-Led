//
// Created by Therence on 22/05/2021.
//

#include "Animation.h"

Animation::Animation(const AnimationType type) {
    this->type = type;
}

bool Animation::is(const AnimationType type) const {
    return (this->type == type);
}

AnimationType Animation::getType() const {
    return this->type;
}

bool Animation::inRange(const int x, const int low, const int high) {
    return (x >= low && x < high);
}
