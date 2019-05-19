#include "settings.h"
#include "bluetooth.h"

void setup() {
    Serial.begin(BAUD);
    while (!Serial) {}
    BTSerial.begin(BAUD);
    while (!BTSerial) {}
}

void loop() {
    startBTModule();
    delay(EXEC_DELAY_LONG);
}
