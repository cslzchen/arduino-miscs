#include "storage.h"
#include "data.h"

void setup() {
    Serial.begin(9600);
    while (!Serial) {}
}

void loop() {
    setDeviceId();
    long deviceId = getDeviceId();
    Serial.print("Device ID:\t");
    Serial.println(deviceId, DEC);

    TestResult firstResult = {144, 1553356437, 37.70f, 7.70f, 7.70f, true};
    TestResult secondResult = {169, 1553358153, 36.60f, 6.60f, 6.60f, false};
    storeOneTestResult(0, firstResult);
    storeOneTestResult(1, secondResult);

    int index = 0;
    TestResult result = getOneTestResult(index);
    if (!result.valid) {
        Serial.println("Invalid test result!");
        delay(1000);
        exit(1);
    }
    Serial.print("User ID:\t");
    Serial.println(result.userId);
    Serial.print("Timestamp:\t");
    Serial.println(result.timeStamp);
    Serial.print("Indicator A:\t");
    Serial.println(result.indicatorA);
    Serial.print("Indicator B:\t");
    Serial.println(result.indicatorB);
    Serial.print("Indicator C:\t");
    Serial.println(result.indicatorC);
    Serial.print("Is Valid:\t");
    Serial.println(result.valid);

    delay(1000);
    exit(0);
}
