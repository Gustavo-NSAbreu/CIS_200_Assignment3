#pragma once

#include <string>
#include "Message.h"

using namespace std;

class TextMessage : public Message {
private:
    string phoneNumber;
public:
    TextMessage(const string& sender, const string& timestamp, const string& content,
          const string& phoneNumber)
        : Message(sender, timestamp, content), phoneNumber(phoneNumber) {}

    void printMessage() const override {
        
    }

};