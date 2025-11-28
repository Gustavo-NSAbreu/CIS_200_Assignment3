#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "../Header FIles/Config.h"
#include "../Header FIles/Utility.h"

using namespace std;

/**
 *  Prints to the console the main menu options of the program.
 */
void Utility::printMenuToConsole() {
    cout << endl << endl;
    cout
        << "===== SPAM & PHISHING ANALYZER =====" << endl << endl
        << "1. Load Data (Messages, Valid Senders, Watch Keywords)" << endl
        << "2. Process Queue (Move Valid and Garbled Messages)" << endl
        << "3. Display Valid Messages (Chronological Order)" << endl
        << "4. Display Garbled Messages" << endl
        << "5. Search Messages by Sender" << endl
        << "6. Run Full Spam Analysis" << endl
        << "7. Add New Suspicious Keyword" << endl
        << "8. Save Suspicious Activity Report" << endl
        << "9. Exit" << endl
        << "Enter your choice: ";
}

// Populates the dateTime structure parsing the string manually
void getTime(tm &dateTime, string dateAndTime) {
    int year, month, day, hour, minute, second;
    char dash1, dash2, colon1, colon2;

    istringstream ss(dateAndTime);

    // Parse the string into the tm structure
    ss >> year >> dash1 >> month >> dash2 >> day
       >> hour >> colon1 >> minute >> colon2 >> second;

    if (ss.fail()) {
        cerr << "Failed to parse date/time string." << endl;
        return;
    }

    
    dateTime.tm_year = year - 1900;
    dateTime.tm_mon  = month - 1;
    dateTime.tm_mday = day;
    dateTime.tm_hour = hour;
    dateTime.tm_min  = minute;
    dateTime.tm_sec  = second;

}

time_t Utility::stringToTimestamp(string dateAndTime) {
    tm dateTime = {};

    getTime(dateTime, dateAndTime);

    // converts structure into timestamp
    time_t timestamp = mktime(&dateTime);

    if (timestamp == -1) { // mktime returns -1 on error
        std::cerr << "Failed to convert to timestamp." << std::endl;
        return 1;
    }

    return timestamp;
}