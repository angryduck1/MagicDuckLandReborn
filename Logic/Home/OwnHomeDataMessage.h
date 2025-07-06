#ifndef OWNHOMEDATAMESSAGE_H
#define OWNHOMEDATAMESSAGE_H

#include "PiranhaMessage.h"
#include "LogicClientAvatar.h"
#include "LogicClientHome.h"
#include <memory.h>

using namespace std;

class OwnHomeDataMessage : public PiranhaMessage {
public:
    OwnHomeDataMessage() : PiranhaMessage(0) {
        avatar = std::make_unique<LogicClientAvatar>(LogicClientAvatar());
        home = std::make_unique<LogicClientHome>(LogicClientHome());
    }

    void encode() override {
        PiranhaMessage::encode();

        stream.writeInt(0);
        home->encode(stream);
        avatar->encode(stream);
    }

    int getMessageType() const override {
        return 24101;
    }
private:
    std::unique_ptr<LogicClientAvatar> avatar;
    std::unique_ptr<LogicClientHome> home;

};

#endif
