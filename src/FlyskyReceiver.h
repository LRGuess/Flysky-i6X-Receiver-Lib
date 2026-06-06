#ifndef FLYSKYRECEIVER_H
#define FLYSKYRECEIVER_H

#include <Arduino.h>
#include <IBusBM.h>

class FlyskyReceiver {
    public: 
        FlyskyReceiver();

        void begin(HardwareSerial& serial);

        int readAxis(byte channelInput, int minLimit, int maxLimit, int defaultValue);

        bool readSwitch(byte switchInput, bool defaultValue);

    private:
        IBusBM iBusRc;
}

#endif