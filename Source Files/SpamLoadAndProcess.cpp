#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


#include "../Header FIles/Email.h"
#include "../Header FIles/Config.h"
#include "../Header FIles/SpamAnalyzer.h"
#include "../Header FIles/TextMessage.h"
#include "../Header FIles/GarbledMessage.h"
#include "../Header FIles/InstantMessage.h"

using namespace std;

void SpamAnalyzer::readMessageFile() {

    string messageType; // Type
    string sender, timestamp, content; // Base message class
    string platform; // Instant
    // string subject = ""; // Emails
    string cc = ""; // Emails
    string phoneNumber; // Text

    string buffer;

    // Open file
    ifstream isMessage(MESSAGES_FILE);
    if (!isMessage) {
        cerr << "Error: Unable to open file " << MESSAGES_FILE << endl;
        return;
    }

    // Lambda function so this block can be reused

    auto readLine = [&]() {
        string line;

        getline(isMessage, messageType, ',');
  
        size_t rc = messageType.find("GARBLED");

        // Returns out of function if the word GARBLED is found in messageType
        if(rc != string::npos && rc == 0) {
            allMessages.push(new GarbledMessage(messageType));
            return;
        }

        // Get base message info
        getline(isMessage >> ws, sender, ',');
        getline(isMessage >> ws, timestamp, ',');

        timestamp += ":00"; // adding seconds to timestamp

        // Treat the rest of line as a string stream
        getline(isMessage, line);
        
        stringstream ss(line);

        // Add text message to queue
        if(messageType == TEXT_MESSAGE) {
            getline(ss >> ws, content);
            allMessages.push(new TextMessage(sender, timestamp, content));
            return;
        }

        getline(ss >> ws, content, ',');

        // Add instant message to queue
        if(messageType == INSTANT_MESSAGE) {
            getline(ss, buffer, '=');
            getline(ss, platform);
            allMessages.push(new InstantMessage(sender, timestamp, content, platform));
        }

        // Add email message to queue
        else if(messageType == EMAIL_MESSAGE) {
            string tail;
            getline(ss, tail);

            // Try to find the optional cc
            size_t pos = tail.find("cc=");
            if (pos != string::npos) {
                cc = tail.substr(pos + 3); // skip "cc="
            } else {
                cc = ""; // In case there is no cc
            }

            allMessages.push(new Email(sender, timestamp, content, cc));
        }

        curerntSenders.insert(sender);
    };

    readLine();
    while(!isMessage.eof() && !isMessage.fail()) {
        readLine();
    }

    isMessage.close();
}

void SpamAnalyzer::readKeywordFile() {

    string keyword;

    // Open file
    ifstream isKeyword(KEYWORDS_FILE);
    if (!isKeyword) {
        cerr << "Error: Unable to open file " << KEYWORDS_FILE << endl;
        return;
    }

    isKeyword >> keyword; // reads first keyword from the file

    while(!isKeyword.eof() && !isKeyword.fail()) {
        keywords.insert(keyword); // insert the keyword into the set
        
        isKeyword >> keyword; // reads next keyword from the file
    }

    isKeyword.close();

}

void SpamAnalyzer::readValidSenderFile() {

    string sender;
    
    // Open file
    ifstream isValidSender(VALID_SENDERS_FILE);
    if (!isValidSender) {
        cerr << "Error: Unable to open file " << VALID_SENDERS_FILE << endl;
        return;
    }

    isValidSender >> sender; // reads first sender from the file

    while(!isValidSender.eof() && !isValidSender.fail()) {
        trustedSenders.insert(sender); // insert the sender into the set
        
        isValidSender >> sender; // reads next sender from the file
    }

    isValidSender.close();

}