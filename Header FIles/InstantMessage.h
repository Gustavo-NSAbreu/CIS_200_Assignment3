#pragma once

#include <string>
#include "Message.h"

using namespace std;

class InstantMessage : public Message {
private:
    string platform;
public:
    InstantMessage(const string& sender, const string& timestamp, const string& content,
          const string& platform)
        : Message(sender, timestamp, content), platform(platform) {}

    void printMessage() const override {
        
    }

};