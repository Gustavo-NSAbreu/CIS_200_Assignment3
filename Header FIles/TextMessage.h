#pragma once

#include <string>
#include "Message.h"
#include "Config.h"

using namespace std;

class TextMessage : public Message {
private:
    string phoneNumber;
public:
    TextMessage(const string& sender, const string& timestamp, const string& content)
        : Message(TEXT_MESSAGE, sender, timestamp, content), phoneNumber(sender) {}

    void printMessage() const override {
        cout << "[" << type << "] " << sender << " says " << content << endl;
    }

};