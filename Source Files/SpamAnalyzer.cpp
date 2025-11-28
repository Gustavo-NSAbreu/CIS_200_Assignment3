#include <iostream>
#include <fstream>
#include <string>
#include <List>
#include <ctime>
#include "../Header FIles/Utility.h"
#include "../Header FIles/Config.h"
#include "../Header FIles/SpamAnalyzer.h"

using namespace std;

// Runs read functions
void SpamAnalyzer::loadData() {
    readMessageFile();
    readKeywordFile();
    readValidSenderFile();
}

// Separates valid and garbled messages into diferent container
void SpamAnalyzer::processQueue() {
    int totalMessages;
    int garbledMessageCount = 0;
    int validMessageCount = 0;

    while(!allMessages.empty()) {
        // Get message in front of queue
        Message* message = allMessages.front();

        // If garbled, send it to garbled list, then pop it from queue
        if(message->type == GARBLED_MESSAGE) {
            garbledMessages.push_front(message);
            allMessages.pop();
            garbledMessageCount++;
            continue;
        }

        // If valid, sent it to valid list and vector, then pop it from queue
        validMessages.push_front(message);
        searchableMessages.push_back(message);
        allMessages.pop();
        validMessageCount++;
    }

    totalMessages = validMessageCount + garbledMessageCount;

    cout << "Queue processed: " << totalMessages  << " total messages" << endl;
    cout << validMessageCount << " valid messages moved to valid list" << endl;
    cout << garbledMessageCount << " garbled messages moved to garbled list" << endl;
}

// Displays valid messages
void SpamAnalyzer::displayValidMessages() {
    for(Message* message : validMessages) {
        cout << *message;
    }
}

// Displays garbled messages
void SpamAnalyzer::displayGarbledMessages() {
    for(Message* message : garbledMessages) {
        cout << *message;
    }
}

// Searches messages sent by sender chosen by user
void SpamAnalyzer::searchBySender() {

    string sender;
    cout << "Enter sender: ";
    cin >> sender;
    
    cout << sender << endl;
    
    for(Message* message : searchableMessages) {
        if(message->sender != sender) continue;

        message->printMessage();
    }
}


// Runs the Keyword, Sender and Frequency rules 
void SpamAnalyzer::runFullSpamAnalysis() {

    // Clear list to if function is being rerun
    suspiciousMessages.clear();

    set<string> currentSenders;
    int timeWindow;
    long timeWindowInSeconds;
    int timeDifference;

    cout << "Suspicious Messages:" << endl;
    //
    //
    //Keyword and Trusted Sender Rules first because they are simpler
    //
    //
    for(Message* message : validMessages) {
        currentSenders.insert(message->sender);
        
        // Keyword Rule
        for(auto& keyword : keywords) {
            size_t rc =  message->content.find(keyword);
            
            // If current keyword is not found, do nothing 
            if(rc == string::npos) continue;
            
            // Flags message as suspicious
            suspiciousMessages.insert(message);
            flaggedByKeyword++;
            cout << "[" << message->type << "] " << message->dateAndTime << " | " << message->sender << " | Keyword: " << keyword << endl;
        }
        
        // Trusted Sender Rule
        bool isFromTrustedSender = false;
        
        for(auto& trustedSender : trustedSenders) {
            
            size_t rc = trustedSender.find(UMICH_EMAIL_DOMAIN);
            
            // If message sender doesn't match current sender from the trusted list
            // and  message sender doesn't end with @umich.edu, do nothing
            if(message->sender != trustedSender && rc == string::npos) continue;
            
            // If message sender is in the trusted list or ends with @umich.edu
            isFromTrustedSender = true;
        }
        
        
        if(!isFromTrustedSender) {
            cout << "[" << message->type << "] " << message->dateAndTime << " | " << message->sender << " | Untrusted Sender" << endl;
            cout << message->sender << endl;
            // Flags message as suspicious
            suspiciousMessages.insert(message);
            flaggedBySender++;
        }
    }

    //
    //
    // Frequency Rule
    //
    //
    cout << "Enter time window (minutes): ";
    cin >> timeWindow;
    cout << timeWindow << endl << endl;

    // Transform minuts in seconds
    timeWindowInSeconds = timeWindow * 60;
    
    // Frequency Rule
    for(string currentSender : currentSenders) {
        vector<Message*> currentSenderMessages;

        for(Message* message : validMessages) {
            // Gather all messages from same sender
            if(message->sender == currentSender) currentSenderMessages.push_back(message);
        }

        // Sender must have sent more then 5 messages, so if less, do nothing
        if(currentSenderMessages.size() < MIN_MESSAGES_AMOUNT) continue;


        // Make a sliding window: j is the start of window, i is the end of window
        int i = 0;
        for (int j = 0; j < currentSenderMessages.size(); ++j) {
            timeDifference = currentSenderMessages[i]->timestamp - currentSenderMessages[j]->timestamp;

            // Move i forward while window is too wide
            while (timeDifference > timeWindowInSeconds) {
                i++;
            }

            // Now messages from i to j is the largest  window ending at j.
            int windowSize = j - i + 1;

            if (windowSize < MIN_MESSAGES_AMOUNT) continue;
            
            // Flag all messages in this window
            cout << "High frequency sender: " << currentSender << endl;
            for (int k = i; k <= j; k++) {
                suspiciousMessages.insert(currentSenderMessages[k]);
                cout << "[" << currentSenderMessages[k]->type << "] " << currentSenderMessages[k]->dateAndTime << " | " << currentSenderMessages[k]->sender << endl;
            }
            flaggedByFrequency++;
        }
    }
}

// Inserts new keyword to the list
void SpamAnalyzer::addKeyword() {
    string keyword;

    cout << "Enter new keyword: ";
    cin >> keyword;
    cout << endl;
    
    keywords.insert(keyword);
}

// Outputs values to a file
void SpamAnalyzer::saveSuspiciousActivityReport() {

    
    ofstream outputStream;
    outputStream.open(OUTPUT_FILE);
    if (outputStream.fail()) {
        cerr << "*** ERROR: Cannot open " << OUTPUT_FILE << endl;
        return;
    }

    time_t t = time(0);   // Get the time now
    tm* now = localtime(&t);


    // Output to file

    // Header
    outputStream << OUTPUT_FILE_HEADER << now->tm_year + 1900 << "-" << now->tm_mon + 1 << "-" << now->tm_mday << endl;
    outputStream << "-------------------------------------------------" << endl;

    // Values
    outputStream << "Keyword Violations: " << flaggedByKeyword << endl;
    outputStream << "Untrusted Senders: " << flaggedBySender << endl;
    outputStream << "High-Frequency Senders: " << flaggedByFrequency << endl;

    outputStream.close();
}