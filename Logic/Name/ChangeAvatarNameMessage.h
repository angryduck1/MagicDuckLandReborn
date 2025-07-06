#ifndef CHANGEAVATARNAMEMESSAGE_H
#define CHANGEAVATARNAMEMESSAGE_H

#include "PiranhaMessage.h"
#include <string>

class ChangeAvatarNameMessage : public PiranhaMessage {
public:
    ChangeAvatarNameMessage() : PiranhaMessage(0) {

    }

    void decode() override {
        name = stream.readString();
        isNameSetByUser = stream.readBoolean();
    }

    int getMessageType() {
        return 10212;
    }

    bool getNameSetByUser() {
        return isNameSetByUser;
    }

    std::string getName() {
        return name;
    }

private:
    std::string name;
    bool isNameSetByUser;
};

#endif // CHANGEAVATARNAMEMESSAGE_H
