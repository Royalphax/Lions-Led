//
// Created by Therence on 22/05/2021.
//

#ifndef LIONS_LED_2_DRIVEMODE_H
#define LIONS_LED_2_DRIVEMODE_H

#define CONFIRM_IGNITED 5

class DriveMode {

private:
    bool stop;
    bool back;
    bool right;
    bool left;

    int confirmIgnited;
    bool ignited;
    bool switchedEngine;

public:
    DriveMode() {
        stop = false;
        back = false;
        right = false;
        left = false;

        confirmIgnited = 0;
        ignited = false;
        switchedEngine = false;
    }

    bool isStop() const {
        return stop;
    }

    void setStop(bool stop) {
        DriveMode::stop = stop;
    }

    bool isBack() const {
        return back;
    }

    void setBack(bool back) {
        DriveMode::back = back;
    }

    bool isRight() const {
        return right;
    }

    void setRight(bool right) {
        DriveMode::right = right;
    }

    bool isLeft() const {
        return left;
    }

    void setLeft(bool left) {
        DriveMode::left = left;
    }

    bool isIgnited() const {
        return ignited;
    }

    void setIgnited(bool ignited) {
        if (ignited != DriveMode::ignited) {
            if (confirmIgnited < CONFIRM_IGNITED) {
                confirmIgnited++;
            } else {
                confirmIgnited = 0;
                DriveMode::ignited = ignited;
                switchedEngine = true;
            }
        } else {
            confirmIgnited = 0;
        }
    }

    bool hasSwitchEngine() {
        if (switchedEngine) {
            switchedEngine = false;
            return true;
        }
        return false;
    }
};

#endif //LIONS_LED_2_DRIVEMODE_H
