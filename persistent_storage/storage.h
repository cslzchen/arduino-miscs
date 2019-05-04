#ifndef STORAGE_H
#define STORAGE_H

#include <EEPROM.h>
#include "data.h"

/**
 * Read one single byte at a given address.
 */
byte readOneByte(int addr) {
    if (addr >= 0 && addr < EEPROM.length()) {
        return EEPROM.read(addr);
    } else {
        return NULL;
    }
}

/**
 * Read a full string with starting (inclusive) and ending (exclusive) address.
 */
String readByteStr(int startAddr, int endAddr) {
    if (startAddr < 0 || endAddr >= EEPROM.length()) {
        return NULL;
    }
    String bytes = "";
    for (int addr = startAddr; addr < endAddr; addr++) {
        bytes.concat((char)EEPROM.read(addr));
    }
    return bytes;
}

/**
 * Store the Device ID, which always starts at address 0.
 */
void setDeviceId() {
    long deviceId = 1234567890;
    EEPROM.put(0, deviceId);
}

/**
 * Read the Device ID.
 */
long getDeviceId() {
    long deviceId = 0;
    EEPROM.get(0, deviceId);
    return deviceId;
}

/**
 * Get the starting address of test result entries.
 */
int getStartAddr() {
    return sizeof(long);
}

/**
 * Get the size of each test result entry.
 */
int getEntrySize() {
    return sizeof(TestResult);
}

/**
 * Store the test result at a given address.
 */
bool storeOneTestResult(int index, TestResult result) {
    int addr = getStartAddr() + index * getEntrySize();
    if (addr + getEntrySize() >= EEPROM.length()) {
        addr = getStartAddr();
    }
    EEPROM.put(addr, result);
}

/**
 * Read the test result at a given address.
 */
TestResult getOneTestResult(int index) {
    TestResult result;
    int addr = getStartAddr() + index * getEntrySize();
    if (addr + getEntrySize() >= EEPROM.length()) {
        return nullResult;
    }
    EEPROM.get(addr, result);
    return result;
}

#endif
