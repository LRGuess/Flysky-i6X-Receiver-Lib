#include "FlyskyReceiver.h"

FlyskyReceiver::FlyskyReceiver() {
}

void FlyskyReceiver::begin(HardwareSerial& serial) {
    iBusRc.begin(serial);
}

int FlyskyReceiver::readAxis(byte channelInput, int minLimit, int maxLimit, int defaultValue){
    uint16_t ch = iBusRc.readChannel(channelInput);

    if (ch < 100) return defaultValue;

    return map(ch, 1000, 2000, minLimit, maxLimit);
}

bool FlyskyReceiver::readSwitch(byte switchInput, bool defaultValue) {
    int intDefaultValue = defaultValue ? 100 : 0;

    int ch = readAxis(switchInput, 0, 100, intDefaultValue);

    bool switchValue = ch > 50;

    return !switchValue;
}