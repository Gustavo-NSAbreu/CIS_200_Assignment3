#pragma once

#include <string>
#include "Message.h"
#include "Config.h"

using namespace std;

class InstantMessage : public Message {
private:
    string platform;
public:
    InstantMessage(const string& sender, const string& timestamp, const string& content,
          const string& platform)
        : Message(INSTANT_MESSAGE, sender, timestamp, content), platform(platform) {}

    void printMessage() const override {
        cout << "[" << type << "] " << "From " << platform << ", " << sender << " says " << content << endl;
    }
};