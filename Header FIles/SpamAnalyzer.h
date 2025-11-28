#pragma once

#include <set>
#include <queue>
#include <list>
#include <vector>

#include "Message.h"

class SpamAnalyzer {

    // Flag count by type
    int flaggedBySender = 0;
    int flaggedByKeyword = 0;
    int flaggedByFrequency = 0;

    set<string> keywords;
    set<string> trustedSenders;

    set<string> curerntSenders;

    queue<Message*> allMessages;
    list<Message*> validMessages;
    vector<Message*> searchableMessages;

    list<Message*> garbledMessages;
    set<Message*> suspiciousMessages;

public:
    void loadData();
    void readKeywordFile();
    void readMessageFile();
    void readValidSenderFile();

    void processQueue();

    void displayValidMessages();
    void displayGarbledMessages();

    void searchBySender();

    void runFullSpamAnalysis();
    
    void addKeyword();
    
    void saveSuspiciousActivityReport();
    
};