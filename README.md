# Flysky i6X Receiver Library

A simple Arduino library for reading channel and switch data from a Flysky i6X receiver using the iBUS protocol. This library is a wrapper around the [IBusBM library](https://github.com/bmellink/IBusBM) to simplify reading axis and switch values.

## Features

- Easy initialization.
- Read joystick/axis values with mapping to a custom range.
- Read two-position switches.
- Supports iBUS protocol.

## Installation

1.  Download the latest release of this library.
2.  In the Arduino IDE, go to `Sketch` > `Include Library` > `Add .ZIP Library...` and select the downloaded file.
3.  This library depends on the `IBusBM` library. You can install it from the Arduino Library Manager. Go to `Tools` > `Manage Libraries...` and search for `IBusBM` and install it.

## Usage

Here is a basic example of how to use the library.

```cpp
#include <FlyskyReceiver.h>

// Initialize the receiver object
FlyskyReceiver receiver;

void setup(){
    // Start serial communication for debugging
    Serial.begin(9600);

    // Begin receiver communication on a hardware serial port (e.g., Serial1)
    // The iBUS protocol uses a baud rate of 115200.
    Serial1.begin(115200);
    receiver.begin(Serial1);
}

void loop(){
    // Read the throttle channel (channel 3 on most Flysky transmitters)
    // and map it from -100 to 100.
    // The value is inverted because typically up is max, but for throttle, we might consider it differently.
    int throttle = -receiver.readAxis(2, -100, 100, 0);

    // Read the state of a switch (e.g., channel 6)
    bool armSwitch = receiver.readSwitch(6, false);

    // Print the values
    Serial.print("Throttle: ");
    Serial.print(throttle);
    Serial.print(" | Arm: ");
    Serial.println(armSwitch);

    delay(100);
}
```

## API

### `FlyskyReceiver()`

Class constructor.

### `void begin(HardwareSerial& serial)`

Starts listening for iBUS data on the specified hardware serial port.

-   `serial`: The hardware serial port connected to the receiver's iBUS output (e.g., `Serial1`, `Serial2`).

### `int readAxis(byte channelInput, int minLimit, int maxLimit, int defaultValue)`

Reads an analog channel (joystick) and maps its value to a specified range.

-   `channelInput`: The channel number to read (0-indexed, so channel 1 is `0`).
-   `minLimit`: The minimum value of the output range.
-   `maxLimit`: The maximum value of the output range.
-   `defaultValue`: The value to return if the signal is lost.
-   **Returns**: The mapped channel value.

### `bool readSwitch(byte switchInput, bool defaultValue)`

Reads a two-position switch from a channel.

-   `switchInput`: The channel number for the switch (0-indexed).
-   `defaultValue`: The value to return if the signal is lost.
-   **Returns**: `true` or `false` representing the switch position.

### `bool readSwitch(String switchCode, bool defaultValue)`

Reads a two-position switch using a letter code ('a', 'b', 'c', 'd').

-   `switchCode`: The switch letter.
-   `defaultValue`: The value to return if the signal is lost.
-   **Returns**: `true` or `false` representing the switch position.

### `int readChannelRaw(byte channelInput)`

Reads the raw 16-bit value from a channel (typically 1000-2000).

-   `channelInput`: The channel number to read (0-indexed).
-   **Returns**: The raw channel value.

### `bool readSwitchRaw(byte switchInput, bool defaultValue)`

Reads the raw value of a switch.

-   `switchInput`: The channel number for the switch (0-indexed).
-   `defaultValue`: The value to return if the signal is lost.
-   **Returns**: `true` if the raw value is > 1500, `false` otherwise.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

