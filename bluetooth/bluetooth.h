#include <SoftwareSerial.h>
#include "settings.h"

SoftwareSerial BTSerial(BT_SERIAL_RX, BT_SERIAL_TX);

/**
 * Send the data string in bytes and return the number of bytes sent.
 */
int BTSerialSend(String data) {

    int numOfBytes = data.length() + 2;
    byte bytes[numOfBytes];
    String payload = String(DELIMITOR) + data + String(END_OF_STREAM);
    payload.getBytes(bytes, numOfBytes);

    Serial.print("Sending payload: \t");
    Serial.println(payload);
    int numOfBytesSent = BTSerial.write(bytes, numOfBytes);
    Serial.print(numOfBytesSent);
    Serial.println(" bytes sent.");
    return numOfBytesSent;
}

/**
 * Start listening and handle communication between uno and app.
 */
void BTSerialListen() {
    // TODO: Implement this!
    return;
}

/**
 * Initialize bluetooth module. For development only.
 */
void initBTModule() {

    String cmdList[] = {"AT", "AT+NAMETestHC06", "AT+PIN4321", "AT+BAUD4", "AT+VERSION"};
    byte numOfCmd = 5;

    for (int i = 0; i < numOfCmd; i++) {

        // Must convert String to char array for Software Serial Write to work.
        int len = cmdList[i].length();
        char cmd[len+1];
        cmdList[i].toCharArray(cmd, len+1) ;

        Serial.print("CMD:\t");
        Serial.println(cmd);
        BTSerial.write(cmd);
        while(!BTSerial.available()) {
            delay(EXEC_DELAY_LONG);
        }
        Serial.print("RESP:\t");
        while(BTSerial.available()) {
            Serial.write(BTSerial.read());
            delay(EXEC_DELAY_MIN);
        }
        Serial.println();
        delay(EXEC_DELAY_SHORT);
    }
}

/**
 * Start bluetooth module normally or for initialization only.
 */
void startBTModule() {

    String cmd = "";
    Serial.println("Init BT Module (Y/N)?");
    while (!Serial.available()) {
        delay(EXEC_DELAY_LONG);
    }
    while(Serial.available()) {
        cmd += (char) Serial.read();
        delay(EXEC_DELAY_MIN);
    }
    Serial.println(cmd);

    if (cmd == "Y") {
        initBTModule();
    } else if (cmd == "N") {
        BTSerialListen();
    } else {
        Serial.println("Invalid Input!");
    }
    delay(EXEC_DELAY_SHORT);
    return;
}
