#ifndef DATA_H
#define DATA_H

/**
 * A structure to store one test result entry.
 */
struct TestResult {
    byte userId;
    long timeStamp;
    float indicatorA;
    float indicatorB;
    float indicatorC;
    bool valid;
};

TestResult nullResult = {255, 0, 0.00f, 0.00f, 0.00f, false};

#endif
