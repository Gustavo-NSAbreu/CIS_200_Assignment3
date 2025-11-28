#pragma once

#include <string>
#include "Message.h"
#include "Config.h"

using namespace std;

class Email : public Message {
private:
    //string subject;
    string cc;
public:
    Email(const string& sender, const string& timestamp, const string& content, string cc = "")
        : Message(EMAIL_MESSAGE, sender, timestamp, content), cc(cc) {}

    void printMessage() const override {
        cout << "[" << type << "] " << "cc=" << cc << " | " << sender << " says " << content << endl;
    }

};