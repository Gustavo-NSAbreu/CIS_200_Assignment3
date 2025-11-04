#pragma once

#include <string>

using namespace std;

class Message {

friend class SpamAnalyzer;

private:
    string sender;
    string timestamp;
    string content;
public:
    Message(const string& sndr, const string& time, const string& cont)
        : sender(sndr), timestamp(time), content(cont) {}
        
    virtual void printMessage() const = 0;
    virtual ~Message() = default;
};