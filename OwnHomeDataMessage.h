#ifndef OWNHOMEDATAMESSAGE_H
#define OWNHOMEDATAMESSAGE_H

#include "PiranhaMessage.h"
#include "LogicClientAvatar.h"
#include "LogicClientHome.h"
#include <memory.h>

class OwnHomeDataMessage : public PiranhaMessage {
public:
    OwnHomeDataMessage() : PiranhaMessage(0) {

    }

    void encode() override {
        stream.writeInt(0);
        home->encode();
        avatar->encode();
    }

    int getMessageType() const override {
        return 24101;
    }
private:
    std::unique_ptr<LogicClientAvatar> avatar;
    std::unique_ptr<LogicClientHome> home;

};

#endif
