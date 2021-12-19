#ifndef _DEBOUNCEIN_H
#define _DEBOUNCEIN_H

#include "mbed.h"

class DebounceIn : public InterruptIn {

public:
  DebounceIn(PinName pin, PinMode mode, std::chrono::microseconds interval = 1ms, int simples = 20) : InterruptIn(pin, mode), fallSamples(simples), riseSamples(simples), interval(interval)
  {
        internalFallCallback = mbed::callback(this, &DebounceIn::internalFallCallbackHandler);
        internalFallTimerCallback = mbed::callback(this, &DebounceIn::internalFallTimerCallbackHandler);
        internalRiseCallback = mbed::callback(this, &DebounceIn::internalRiseCallbackHandler);
        internalRiseTimerCallback = mbed::callback(this, &DebounceIn::internalRiseTimerCallbackHandler);
  };

  void fall(Callback<void()> callback);
  void rise(Callback<void()> callback);

private:

  std::chrono::microseconds interval;

  Ticker fallTicker;
  int fallCounter;
  int fallSamples;
  void internalFallCallbackHandler();
  void internalFallTimerCallbackHandler();
  Callback<void()> internalFallCallback;
  Callback<void()> internalFallTimerCallback;
  Callback<void()> fallCallback;

  Ticker riseTicker;
  int riseCounter;
  int riseSamples;
  void internalRiseCallbackHandler();
  void internalRiseTimerCallbackHandler();
  Callback<void()> internalRiseCallback;
  Callback<void()> internalRiseTimerCallback;
  Callback<void()> riseCallback;

};

#endif