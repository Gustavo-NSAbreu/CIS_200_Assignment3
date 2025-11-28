#include <iostream>
#include "../Header FIles/Utility.h"
#include "../Header FIles/SpamAnalyzer.h"

using namespace std;

typedef void (SpamAnalyzer::*MenuFunctionPointer)();

int main() {

    SpamAnalyzer analyzer;

    int option = 0;

    // Function array with all menu functions
    MenuFunctionPointer menuFunctions[9] = { 
        nullptr, // Entry 0 not used so that options align with menu indices
        SpamAnalyzer::loadData,
        SpamAnalyzer::processQueue,
        SpamAnalyzer::displayValidMessages,
        SpamAnalyzer::displayGarbledMessages,
        SpamAnalyzer::searchBySender,
        SpamAnalyzer::runFullSpamAnalysis,
        SpamAnalyzer::addKeyword,
        SpamAnalyzer::saveSuspiciousActivityReport
    };

    Utility::printMenuToConsole();
    cin >> option; // Get user input
    
    cout << endl;
    
    
    while (option != 9) {
        
        // If valid options are chosen
        if (option >= 1 && option < 9) {
            (analyzer.*menuFunctions[option])(); // Call the corresponding function
        }
        
        else cout << endl << "Invalid option!" << endl;
        
        // Prints menu again
        Utility::printMenuToConsole();
        cin >> option; // Get user input again
        cout << endl;
    }

    cout << "Exited!" << endl;

    return 0;
}