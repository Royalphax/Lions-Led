/* ARDUINO INCLUDES */
#include <Arduino.h>
#include <FastLED.h>

/* MY INCLUDES */
#include <LedManager.h>

/* LEDS CONSTANT */
#define NUM_LEDS 100
#define DATA_PIN 3
CRGB led[NUM_LEDS];

/* Constantes pour acquisition donnees vehicule */
#define IGNITION_PIN           A0
#define STOP_PIN               A1
#define BACKTRACKING_PIN       A2
#define RIGHT_BLINKER_PIN      A3
#define LEFT_BLINKER_PIN       A4
#define ACTIVATION_THRESHOLD   750

/* MY CLASS */
LedManager * ledManager;
DriveMode * driveMode;

/* OTHER */
#define DEMO_MODE 0
byte demoStep = 0;

void setup() {
    /* SETUP INTERRUPTS */
    noInterrupts(); // Désactive les interruptions

    #ifdef ARDUINO_AVR_NANO
        bitClear(TCCR2A, WGM20); // Bit 0 du registre TCCR2A à 0
        bitClear(TCCR2A, WGM21); // Bit 1 du registre TCCR2A à 0
        TCCR2B = 0b00000110; // Clock (16 mega) / 256 -> 62 500 soit 16 micro-s et WGM22 = 0
        TIMSK2 = 0b00000001; // Interruption locale autorisee par TOIE2
    #endif
    #ifdef ARDUINO_AVR_UNO
        // https://community.platformio.org/t/is-there-a-way-to-detect-target-for-use-in-ifdef-at-compile-time/2246
    #endif

    /* INIT PINS */
    pinMode(STOP_PIN, INPUT);
    pinMode(BACKTRACKING_PIN, INPUT);
    pinMode(RIGHT_BLINKER_PIN, INPUT);
    pinMode(LEFT_BLINKER_PIN, INPUT);
    pinMode(IGNITION_PIN, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    /* INIT LEDS */
    FastLED.addLeds<WS2811, DATA_PIN, GRB>(led, NUM_LEDS);
    FastLED.setBrightness(255);
    //FastLED.showColor(CRGB::Red); // Empeche la carte de demarrer ?!

    /* INIT MY CLASS */
    driveMode = new DriveMode();

    ledManager = new LedManager(led, NUM_LEDS, driveMode);
    ledManager->begin();

    /* START INTERRUPTS */
    interrupts(); // Reactive les interruptions
}

void loop() {

    // TEST CODE
    /*digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    return;*/

    if (driveMode->hasSwitchEngine()) {
        if (driveMode->isIgnited()) {
            ledManager->startEngine();
        } else {
            ledManager->stopEngine();
        }
    }

    if (driveMode->isIgnited())
        ledManager->loop();

}

// Routine d'interruption
byte varCompteur = 0; // La variable compteur

ISR(TIMER2_OVF_vect) {
    TCNT2 = 256 - 250; // 250 x 16 µS = 4 ms
    if (varCompteur++ > 50) { // 50 * 4 ms = 200 ms
        varCompteur = 0;

        if (!DEMO_MODE) {
            driveMode->setStop(analogRead(STOP_PIN) > ACTIVATION_THRESHOLD);
            driveMode->setBack(analogRead(BACKTRACKING_PIN) > ACTIVATION_THRESHOLD);
            driveMode->setLeft(analogRead(RIGHT_BLINKER_PIN) > ACTIVATION_THRESHOLD);
            driveMode->setRight(analogRead(LEFT_BLINKER_PIN) > ACTIVATION_THRESHOLD);
            driveMode->setIgnited(analogRead(IGNITION_PIN) > ACTIVATION_THRESHOLD);
        } else {
            if (demoStep == 1) {
                for (int i = 0; i < CONFIRM_IGNITED + 1; i++) driveMode->setIgnited(true);
            } else if (demoStep == 30) {
                driveMode->setStop(true);
            } else if (demoStep == 45) {
                driveMode->setRight(true);
            } else if (demoStep == 55) {
                driveMode->setStop(false);
                driveMode->setLeft(true);
            } else if (demoStep == 65) {
                driveMode->setRight(false);
            } else if (demoStep == 75) {
                driveMode->setLeft(false);
            } else if (demoStep == 80) {
                driveMode->setStop(true);
            } else if (demoStep == 90) {
                driveMode->setStop(true);
                driveMode->setBack(true);
            } else if (demoStep == 100) {
                driveMode->setRight(true);
            } else if (demoStep == 105) {
                driveMode->setStop(true);
            } else if (demoStep == 110) {
                driveMode->setRight(false);
            } else if (demoStep == 115) {
                driveMode->setBack(false);
            } else if (demoStep == 130) {
                driveMode->setStop(true);
            } else if (demoStep == 135) {
                for (int i = 0; i < CONFIRM_IGNITED + 1; i++) driveMode->setIgnited(false);
            } else if (demoStep == 200) {
                demoStep = 0;
            }
            demoStep++;
        }
    }
}
