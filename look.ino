#include <Bluepad32.h>

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

void onConnectedController(ControllerPtr ctl) {
    bool foundEmptySlot = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            Serial.printf("CALLBACK: Controller is connected, index=%d\n", i);
            // Additionally, you can get certain gamepad properties like:
            // Model, VID, PID, BTAddr, flags, etc.
            ControllerProperties properties = ctl->getProperties();
            Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id,
                           properties.product_id);
            myControllers[i] = ctl;
            foundEmptySlot = true;
            break;
        }
    }
    if (!foundEmptySlot) {
        Serial.println("CALLBACK: Controller connected, but could not found empty slot");
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    bool foundController = false;

    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i);
            myControllers[i] = nullptr;
            foundController = true;
            break;
        }
    }

    if (!foundController) {
        Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}

void dumpGamepad(ControllerPtr ctl) {
    Serial.printf(
        "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
        "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
        ctl->index(),        // Controller Index
        ctl->dpad(),         // D-pad
        ctl->buttons(),      // bitmask of pressed buttons
        ctl->axisX(),        // (-511 - 512) left X Axis
        ctl->axisY(),        // (-511 - 512) left Y axis
        ctl->axisRX(),       // (-511 - 512) right X axis
        ctl->axisRY(),       // (-511 - 512) right Y axis
        ctl->brake(),        // (0 - 1023): brake button
        ctl->throttle(),     // (0 - 1023): throttle (AKA gas) button
        ctl->miscButtons(),  // bitmask of pressed "misc" buttons
        ctl->gyroX(),        // Gyro X
        ctl->gyroY(),        // Gyro Y
        ctl->gyroZ(),        // Gyro Z
        ctl->accelX(),       // Accelerometer X
        ctl->accelY(),       // Accelerometer Y
        ctl->accelZ()        // Accelerometer Z
    );
}




void processGamepad(ControllerPtr ctl) {
    // There are different ways to query whether a button is pressed.
    // By query each button individually:
    //  a(), b(), x(), y(), l1(), etc...
    if (ctl->a()) {
        static int colorIdx = 0;
        // Some gamepads like DS4 and DualSense support changing the color LED.
        // It is possible to change it by calling:
        switch (colorIdx % 3) {
            case 0:
                // Red
                ctl->setColorLED(255, 0, 0);
                break;
            case 1:
                // Green
                ctl->setColorLED(0, 255, 0);
                break;
            case 2:
                // Blue
                ctl->setColorLED(0, 0, 255);
                break;
        }
        colorIdx++;
    }

    if (ctl->b()) {
        // Turn on the 4 LED. Each bit represents one LED.
        static int led = 0;
        led++;
        ctl->setPlayerLEDs(led & 0x0f);
    }

    if (ctl->x()) {
        ctl->playDualRumble(0 /* delayedStartMs */, 250 /* durationMs */, 0x80 /* weakMagnitude */,
                            0x40 /* strongMagnitude */);
    }

    // Another way to query controller data is by getting the buttons() function.
    // See how the different "dump*" functions dump the Controller info.

    if (ctl->dpad() == 0x08) {  // Left D-pad
      Serial.println("D-pad Left pressed");
    }
    else if (ctl->dpad() == 0x02) {  // Down D-pad
      Serial.println("D-pad Down pressed");
    }
    else if (ctl->dpad() == 0x04) {  // Right D-pad
      Serial.println("D-pad Right pressed");
    }
    else if (ctl->dpad() == 0x01) {  // Up D-pad
      Serial.println("D-pad Up pressed");
    }

    if (ctl->dpad() == (0x08 | 0x02)) {  // Left + Down (0x08 + 0x02 = 0x0A)
      Serial.println("D-pad Left + Down pressed");
    }
    else if (ctl->dpad() == (0x08 | 0x04)) {  // Left + Right (0x08 + 0x04 = 0x0C)
      Serial.println("D-pad Left + Right pressed");
    }
    else if (ctl->dpad() == (0x02 | 0x04)) {  // Down + Right (0x02 + 0x04 = 0x06)
      Serial.println("D-pad Down + Right pressed");
    }
    else if (ctl->dpad() == (0x01 | 0x08)) {  // Up + Left (0x01 + 0x08 = 0x09)
      Serial.println("D-pad Up + Left pressed");
    }
    else if (ctl->dpad() == (0x01 | 0x02)) {  // Up + Down (0x01 + 0x02 = 0x03)
      Serial.println("D-pad Up + Down pressed");
    }
    else if (ctl->dpad() == (0x01 | 0x04)) {  // Up + Right (0x01 + 0x04 = 0x05)
      Serial.println("D-pad Up + Right pressed");
    }
    // Check for all directions pressed together (0x08 + 0x02 + 0x04 + 0x01 = 0x0F)
    else if (ctl->dpad() == (0x08 | 0x02 | 0x04 | 0x01)) {  // All directions
      Serial.println("All D-pad directions pressed");
    }
    dumpGamepad(ctl);
}

void processControllers() {
    for (auto myController : myControllers) {
        if (myController && myController->isConnected() && myController->hasData()) {
            processGamepad(myController);
        }
    }
}

// Arduino setup function. Runs in CPU 1
void setup() {
    Serial.begin(115200);
    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    // Setup the Bluepad32 callbacks
    BP32.setup(&onConnectedController, &onDisconnectedController);

    BP32.forgetBluetoothKeys();
    BP32.enableVirtualDevice(false);
}

void loop() {

    bool dataUpdated = BP32.update();
    if (dataUpdated)
        processControllers();

    delay(150);
}
