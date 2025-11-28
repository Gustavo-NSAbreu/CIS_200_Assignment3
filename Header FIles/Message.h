#pragma once

#include "Utility.h"
#include "Config.h"

#include <string>

using namespace std;

class Message {

friend class SpamAnalyzer;

protected:
    string type;
    string sender;
    string dateAndTime;
    time_t timestamp;
    string content;
public:
    Message(const string& msgType, const string& sndr, const string& time, const string& cont)
        : type(msgType), sender(sndr), dateAndTime(time), content(cont) {
            if(type == GARBLED_MESSAGE) return;
            
            timestamp = Utility::stringToTimestamp(dateAndTime);
        }
        
    virtual void printMessage() const = 0;

    friend ostream& operator<<(ostream& os, const Message& message);
    virtual ~Message() = default;
};