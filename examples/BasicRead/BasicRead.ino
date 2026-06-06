#include <FlyskyReceiver.h>

FlyskyReceiver receiver;

void setup(){
    Serial.begin(9600);

    Serial2.begin(115200);

    receiver.begin(Serial2);
}

void loop(){
    int throttle = receiver.readAxis(2, -100, 100, 0);

    bool armSwitch = receiver.readSwitch(5, false);

    Serial.print("Throttle: ");
    Serial.print(throttle);

    Serial.print(" | Arm: ");
    Serial.println(armSwitch);

    delay(100)
}