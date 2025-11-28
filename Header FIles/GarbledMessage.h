#include "Message.h"
#include "Config.h"

class GarbledMessage : public Message {
    public:
        GarbledMessage(const string& content)
            : Message(GARBLED_MESSAGE, "", "", content) {}

        void printMessage() const {
            cout << content << endl;
        }
};