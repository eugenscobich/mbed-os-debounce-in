#include "mbed.h"
#include "DebounceIn.h"

void DebounceIn::fall(Callback<void()> callback) {
    fallCallback = callback;
    InterruptIn::fall(internalFallCallback);
}

void DebounceIn::internalFallCallbackHandler() {
    InterruptIn::fall(NULL);  // detach interrupt 
    fallCounter = 0;
    fallTicker.attach(internalFallTimerCallback, interval);   
}

void DebounceIn::internalFallTimerCallbackHandler() {
    if (!read()) {
        fallCounter++;
    } else {
        //fallCounter--;
    }
    if (fallCounter == fallSamples) {
        fallTicker.detach();
        fallCallback.call();
        InterruptIn::fall(internalFallCallback);
    }
}

void DebounceIn::rise(Callback<void()> callback) {
    riseCallback = callback;
    InterruptIn::rise(internalRiseCallback);
}

void DebounceIn::internalRiseCallbackHandler() {
    InterruptIn::rise(NULL);  // detach interrupt 
    riseCounter = 0;
    riseTicker.attach(internalRiseTimerCallback, interval);   
}

void DebounceIn::internalRiseTimerCallbackHandler() {
    if (read()) {
        riseCounter++;
    } else {
        //riseCounter--;
    }
    if (riseCounter == riseSamples) {
        riseTicker.detach();
        riseCallback.call();
        InterruptIn::rise(internalRiseCallback);
    }
}