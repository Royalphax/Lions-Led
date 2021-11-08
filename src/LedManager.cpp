//
// Created by Therence on 22/05/2021.
//

#include <animations/in/SnakeInAnimation.h>
#include <animations/out/SnakeOutAnimation.h>
#include "LedManager.h"

LedManager::LedManager(CRGB * led, const int size, DriveMode * driveMode) {
    LedManager::led = led;
    LedManager::size = size;
    LedManager::color = ColorManager();
    LedManager::animationList = AnimationList();
    LedManager::driveMode = driveMode;
    LedManager::ledSegment[0] = new LedSegment(led, 0, 25);
    LedManager::ledSegment[1] = new LedSegment(led, 28, 72);
    LedManager::ledSegment[2] = new LedSegment(led, 75, 100);
}

void LedManager::begin() {
    animationList.add(new SnakeInAnimation(this));
    animationList.add(new SnakeOutAnimation(this));
}

void LedManager::startEngine() {
    animationList.getRandom(IN)->animate();
}

void LedManager::loop() {
    stopLight();
    if (driveMode->isRight() && driveMode->isLeft()) {
        while (driveMode->isRight() && driveMode->isLeft()) {
            warnLight();
        }
    } else if (driveMode->isRight()) {
        rightLight();
    } else if (driveMode->isLeft()) {
        leftLight();
    } else if (driveMode->isBack()) {
        backLight();
    } else {
        ledSegment[0]->setColor(color.RED);
        ledSegment[2]->setColor(color.RED);
    }
    FastLED.show();
}

void LedManager::stopEngine() {
    animationList.getRandom(OUT)->animate();
}

bool LedManager::isInSegment(const int i) {
    for (int x = 0; x < MAX_LED_SEGMENTS; x++)
        if (ledSegment[x]->isIn(i))
            return true;
    return false;
}

/* LIGHT ANIMATIONS */

void LedManager::stopLight() {
    if (driveMode->isStop()) {
        ledSegment[1]->setColor(color.FULL_RED);
    } else {
        ledSegment[1]->setColor(color.RED);
    }
}

void LedManager::rightLight() {
    for (int i = 0; i < ledSegment[2]->getInterval(); i++) {
        int y = ledSegment[2]->getLowBound() + i;
        led[y] = color.getFading(color.FULL_ORANGE, y - ledSegment[2]->getLowBound(), ledSegment[2]->getInterval());
        stopLight();
        backLight();
        FastLED.show();
        delay(SCROLLING_DELAY_NORMAL);
    }
    delay(SCROLLING_DELAY_STAY);
    ledSegment[2]->setColor(CRGB::Black);
    FastLED.show();
}

void LedManager::leftLight() {
    for (int i = 0; i < ledSegment[0]->getInterval(); i++) {
        int x = ledSegment[0]->getHighBound() - 1 - i;
        led[x] = color.getFading(color.FULL_ORANGE, ledSegment[0]->getHighBound() - x, ledSegment[0]->getInterval());
        stopLight();
        backLight();
        FastLED.show();
        delay(SCROLLING_DELAY_NORMAL);
    }
    delay(SCROLLING_DELAY_STAY);
    ledSegment[0]->setColor(CRGB::Black);
    FastLED.show();
}

void LedManager::warnLight() {
    // Pas meme intervalle, on fait un flash progressif des deux cotes
    if (ledSegment[0]->getInterval() != ledSegment[2]->getInterval()) {
        for (int i = 0; i < 100; i++) {
            ledSegment[0]->setColor(color.getFading(color.FULL_ORANGE, i, 100));
            ledSegment[2]->setColor(color.getFading(color.FULL_ORANGE, i, 100));
            stopLight();
            FastLED.show();
            delay(SCROLLING_DELAY_FAST);
        }
        delay(SCROLLING_DELAY_STAY);
        ledSegment[0]->setColor(CRGB::Black);
        ledSegment[2]->setColor(CRGB::Black);
        FastLED.show();
        return;
    }
    // Meme intervalle, on va synchroniser les scrolling
    int max = min(ledSegment[0]->getInterval(), ledSegment[2]->getInterval());
    for (int i = 0; i < max; i++) {
        int x = ledSegment[0]->getHighBound() - 1 - i;
        int y = ledSegment[2]->getLowBound() + i;
        led[x] = color.getFading(color.FULL_ORANGE, ledSegment[0]->getHighBound() - x, ledSegment[0]->getInterval());
        led[y] = color.getFading(color.FULL_ORANGE, y - ledSegment[2]->getLowBound(), ledSegment[2]->getInterval());
        stopLight();
        FastLED.show();
        delay(SCROLLING_DELAY_FAST);
    }
    delay(SCROLLING_DELAY_STAY);
    ledSegment[0]->setColor(CRGB::Black);
    ledSegment[2]->setColor(CRGB::Black);
    FastLED.show();
}

void LedManager::backLight() {
    if (!driveMode->isBack())
        return;
    if (!driveMode->isLeft())
        ledSegment[0]->setColor(color.FULL_WHITE);
    if (!driveMode->isRight())
        ledSegment[2]->setColor(color.FULL_WHITE);
}

/* GETTERS AND SETTERS */

CRGB * LedManager::getLed() const {
    return led;
}

void LedManager::setLed(CRGB * led) {
    LedManager::led = led;
}

int LedManager::getSize() const {
    return size;
}

void LedManager::setSize(int size) {
    LedManager::size = size;
}

const ColorManager &LedManager::getColor() const {
    return color;
}

void LedManager::setColor(const ColorManager &color) {
    LedManager::color = color;
}
