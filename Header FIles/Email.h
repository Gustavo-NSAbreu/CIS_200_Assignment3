#pragma once

#include <string>
#include "Message.h"

using namespace std;

class Email : public Message {
private:
    string subject;
    string cc;
public:
    Email(const string& sender, const string& timestamp, const string& content,
          const string& subject, const string& cc = "")
        : Message(sender, timestamp, content), subject(subject), cc(cc) {}

    void printMessage() const override {
        
    }

};