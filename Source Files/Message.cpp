#include <iostream>
#include "../Header FIles/Message.h"

ostream& operator<<(ostream& os, const Message& message) {
    message.printMessage();
    return os;  // return the stream
}